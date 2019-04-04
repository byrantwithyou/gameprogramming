/*****************************************************************************
*  
*****************************************************************************/

#ifndef _playerController_h_
#define _playerController_h_

#include <iostream>
#include "cocos2d.h"
#include "json/document.h"

USING_NS_CC;

class Game;
/**
    * @brief Player类 继承自cocos2d:cocos2d
    * 这是Player的控制类,无论是远程玩家还是本地玩家,我们都会基于一个相同的操控机制,利用指针进行操控,大大减少了无谓的代码量
    */
class Player :public cocos2d::Node
{
    
protected:
    
    std::string         _role;                                                           /// 玩家的角色类型
    Vec2                _bornPosition[4];                                                /// 玩家的出生位置
public:
        /** 
    * @brief Player的create函数
    * @param role  人物角色类型
    * @param scene Game场景 
    * @return  Player*
    */
    static Player* create(std::string role ,Game &scene)                                                    
    {
        Player *player = new Player();
        if (player)
        {
            player->setRole(role);
            player->initLocalPlayer(role, scene);
            player->initRemotePlayer(role, scene);
            
            return player;
        }
        CC_SAFE_DELETE(player);
        return nullptr;
    }
    /** 
    * @brief 初始化本地人物
    * @param roleName  人物角色类型
    * @param scene Game场景 
    * @return  void
    */
    void   initLocalPlayer(std::string roleName, Game &scene);
    /** 
    * @brief 初始化远程人物
    * @param oleName  人物角色类型
    * @param scene Game场景 
    * @return  void
    */                                 
    void    initRemotePlayer(std::string roleName, Game& scene);   
    /** 
    * @brief 设置人物永久走动
    * @param code  按键信息
    * @param scene Game场景 
    * @return  void
    */                             
    void    playerForeverMove(EventKeyboard::KeyCode code, Game &scene); 
    /** 
    * @brief 设置人物永久走动
    * @param code  按键信息
    * @param scene Game场景 
    * @return  void
    */                    
    void    executePlayerForeverMove(Game &scene, EventKeyboard::KeyCode code);
    /** 
    * @brief 每一帧来更新Player信息
    * @param delta Update默认参数
    * @param scene Game场景 
    * @patam code 按键信息
    * @return  void
    */                 
    void     updatePlayerPerFrame(int delta, Game &scene, EventKeyboard::KeyCode code);   
    /** 
    * @brief 设置人物角色
    * @param role  人物角色类型
    * @return void
    */     
    void     setRole(std::string role) { _role = role; } 
    /** 
    * @brief 设置玩家死亡
    * @param roleName  人物角色
    * @param scene     Game场景 
    * @return  void
    */                                        
    void     setPlayerDied(std::string roleName, Game &scene);       
    /** 
    * @brief 得到角色信息
    * @return  string
    */                                  
    std::string       getRole() { return _role;}                                                       
    
};

#endif /* _playerController_h_ */
