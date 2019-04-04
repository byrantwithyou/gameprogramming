/*****************************************************************************
 *  
 *
 *****************************************************************************/

#include <stdio.h>
#include "GameManager.h"
#include "../Scene/GameScene.h"

static Manager* thisManager = nullptr;
template <class Type>
Type stringToNum(const std::string& str){
    std::istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}
/****************************** update scene per frame and dispatch event *************************/
void Manager::updatePerFrame(int delta, Game & scene)
{
    std::string tempCommand;
    while(( tempCommand = scene._client->executeOrder()) != "no")
    {
        scene._command.push(tempCommand);
        std::cout<<"收到的信息:"<<tempCommand<<std::endl;
    }
    
    scene._player = scene._localPlayer;
    
    if(!scene._player->isDead());
        executePlayer(delta, scene);
 

    while(scene._command.size() != 0)
    {
        _command = scene._command.front();
        scene._command.pop();
        if(_command[0] == DEAD_MESSAGE[0])
        {
            std::string name = std::string(&_command[1]);
            if(name == scene._localPlayerName)
            {
//                std::cout << "LocalPlayerDead message" << std::endl;
                scene._player = scene._localPlayer;
                scene._player->stopAllActions();
                scene._localPlayer->setPlayerDead();
                
                executePlayer(delta, scene);
            }
            else{
//                std::cout << "RemotePlayerDead message" << std::endl;
                scene._player = scene._remotePlayer[name];
                scene._player->stopAllActions();
                scene._player -> setPlayerDead();
                executePlayer(delta, scene);
            }
                
        }
        if(_command[0] != KEY_ORDER[0])
        {
            continue;
        }
        readCommand();
        // bool isPress;
        
        if(_playerName == scene._localPlayerName)
            continue;
        scene._player = scene._remotePlayer[_playerName];
        if(_code[0] == 'p')
        {
            scene._player->setKeys(scene._keyPressesedOrder[_code], true);
        }
        else
        {
            scene._player->setKeys(scene._keyReleasedOrder[_code], false);
        }
        
        executePlayer(delta, scene);
        scene._player->setPosition(_playerCurrentPosition);
    }
    for(int i = 0; i < scene._playerList.size(); i++)
    {
        _playerName = scene._playerList.at(i).player_name;
        
        if(_playerName == scene._localPlayerName)
            continue;
        
        else{
            //std::cout << "PlayerName:" << _playerName << std::endl;
            scene._player = scene._remotePlayer[_playerName];
            executePlayer(delta, scene);
        }
    }
}

void Manager::readCommand()
{
    auto leftBracket = _command.find('(');
    auto comma = _command.find(',');
    auto rightBracket = _command.find(')');
    std::string code(_command.begin() + 1, _command.begin() + 3);
    std::string playerName(_command.begin() + 3,_command.begin() + leftBracket);
    std::string spositionX(_command.begin()+ 1 + leftBracket,_command.begin() + comma);
    std::string spositionY(_command.begin()+ 1 + comma,_command.begin() + rightBracket);
    
    //std::cout << playerName << std::endl;
    
    float positionX = stringToNum<float>(spositionX);
    float positionY = stringToNum<float>(spositionY);
    //std::cout << positionX << std::endl;
   // std::cout << positionY << std::endl;
    _code = code;
    _playerName = playerName;
    _playerCurrentPosition = Vec2(positionX, positionY);
    
}

/*********************************** initial player controller object *****************************/
void Manager::playerInit(std::string player, Game & scene)
{
    
    _playerManager = Player::create(player, scene);
    scene.addChild(_playerManager);
    scene._playerManager = _playerManager;
}

/*********************************** initial pop controller object *****************************/
void Manager::popInit(Game & scene)
{
    _popManager = Pop::create(scene);
    _popManager->setScene(&scene);
    scene.addChild(_popManager);
    scene._popManager = _popManager;
}
void Manager::executePlayer(int delta,Game &scene)
{
    if(scene._player->isDead()){
        if(!scene._player->getAlreadyDead())
        {
            scene._player->setAlreadyDead();
            
            _playerManager->setPlayerDied(scene._player->getRoleName(), scene);
        }else{
            
            return;
        }
    }
    
    auto
    leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW,
    rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
    upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW,
    downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW,
    space = EventKeyboard::KeyCode::KEY_SPACE;
    
    //any of the direction is pressed and any_arrow is true;
    int any_arrow = scene.isKeyPressed(leftArrow)  +
    scene.isKeyPressed(rightArrow) +
    scene.isKeyPressed(upArrow)    +
    scene.isKeyPressed(downArrow);
    
    //one of the direction and the space is pressed,put a pop
    if ((scene.isKeyPressed(space) && any_arrow)) {
        _popManager->updatePopPerFrame(delta, scene, space);
        _playerManager->updatePlayerPerFrame(delta, scene, space);
        scene._player->setKeys(space, false);
    }
    
    //move when one of the direction is pressed and put a pop when space is pressed
    if (scene.isKeyPressed(leftArrow)) {
        isExecuteForeverMove(leftArrow, scene);
        _playerManager->updatePlayerPerFrame(delta, scene, leftArrow);
    }
    else if (scene.isKeyPressed(rightArrow) ) {
        isExecuteForeverMove(rightArrow, scene);
        _playerManager->updatePlayerPerFrame(delta, scene, rightArrow);
    }
    else if (scene.isKeyPressed(upArrow) ) {
        isExecuteForeverMove(upArrow, scene);
        _playerManager->updatePlayerPerFrame(delta, scene, upArrow);
    }
    else if (scene.isKeyPressed(downArrow) ) {
        isExecuteForeverMove(downArrow, scene);
        _playerManager->updatePlayerPerFrame(delta, scene, downArrow);
    }
    else if (scene.isKeyPressed(space)) {
      
        _popManager->updatePopPerFrame(delta, scene, space);
        _playerManager->updatePlayerPerFrame(delta, scene, space);
    }else{
          isExecuteForeverMove(leftArrow, scene);
          isExecuteForeverMove(rightArrow, scene);
          isExecuteForeverMove(upArrow, scene);
          isExecuteForeverMove(downArrow, scene);
    }

}
bool Manager::isExecuteForeverMove(EventKeyboard::KeyCode code,Game& scene)
{
    if(scene._player->getKeys(code) && scene._player->getRealKeys(code) == false)
    {
        scene._player->setRealKeys(code, true);
        scene._player->stopAllActions();
        scene._playerManager->executePlayerForeverMove(scene, code);
        return true;
    }
    if(scene._player->getRealKeys(code) && scene._player->getKeys(code) == false)
    {
        scene._player->setRealKeys(code, false);
        scene._player->stopAllActions();
        scene._playerManager->executePlayerForeverMove(scene, code);
        return false;
    }
}

