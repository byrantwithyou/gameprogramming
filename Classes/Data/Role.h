/*****************************************************************************
 *  
 *
 *****************************************************************************/

#ifndef Role_h
#define Role_h

#include <iostream>
#include <string>
#include "cocos2d.h"
USING_NS_CC;
using namespace ui;
/**
 * @brief 人物类,贼tm重要的一个类,继承自cocos2d:Sprite
 * 这里将承担set人物各种属性,人物死亡的重任！
 */
class Role: public cocos2d::Sprite
{
private:
    std::string     _roleName;                         ///人物的角色
    std::string     _playerName;                       ///玩家的姓名
    float           _speed;                            ///玩家速度
    int             _popCount;                         ///玩家泡泡数量                   
    int             _bubbleCount;                      ///玩家水柱长度
    bool            _isDead = false;                   ///玩家是否死亡
    bool            _alreadyDead = false;              ///玩家是否真正的死亡
    Vec2            _tileSize;                         ///瓦片地图的大小
    bool            _isHost;                           ///玩家是否是主机
    int             _realPopCount;                     ///真正的水泡的数量
    std::map<EventKeyboard::KeyCode, bool> _keys;      ///玩家的按键
    std::map<EventKeyboard::KeyCode, bool> _realKeys;  ///玩家的真正按键
public:
    /** 
    * @brief Role的create函数
    * @param filename文件的名字
    * @return  Role*
    */
    static Role* create(const std::string& filename)
    {
        Role *sprite = new Role();
        if (sprite && sprite->initWithFile(filename))
        {
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);
        return nullptr;
    }
    /** 
    * @brief Role的create函数
    * @param filename文件的名字
    * @return  Role*
    */
    static Role* createWithSpriteFrameName(const std::string& filename)
    {
        Role *sprite = new Role();
        if (sprite && sprite->initWithSpriteFrameName(filename))
        {
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);
        return nullptr;
    }
    /** 
    * @brief 设置人物已经死亡
    * @return  void
    */
    void setAlreadyDead()
    {
        _alreadyDead = true;
    }
    /** 
    * @brief 得到玩家是否已经死亡的信息
    * @return bool
    */
    bool getAlreadyDead()
    {
        return _alreadyDead;
    }
    /** 
    * @brief 设置人物独立的按键,这样方便对每个人进行操控
    * @param code 按键的位置
    * @param isPress 是按下了还是没有按下
    * @return  void
    */
    void setKeys(EventKeyboard::KeyCode code,bool isPress)
    {
        _keys[code] = isPress;
        _realKeys[code] = !isPress;
    }
    /** 
    * @brief 设置人物独立的按键,这样方便对每个人进行操控（真正按键）
    * @param code 按键的位置
    * @param isPress 是按下了还是没有按下
    * @return  void
    */
    void setRealKeys(EventKeyboard::KeyCode code,bool isPress)
    {
        _realKeys[code] = isPress;
    }
    /** 
    * @brief 得到人物的按键信息
    * @param code 按键的位置
    * @return bool
    */
    bool getKeys(EventKeyboard::KeyCode code)
    {
        return _keys[code];
    }
    /** 
    * @brief 得到人物真正的的按键信息
    * @param code 按键的位置
    * @return bool
    */
    bool getRealKeys(EventKeyboard::KeyCode code)
    {
        return _realKeys[code];
    }
    /** 
    * @brief 设置人物的速度
    * @param speed 速度
    * @return void
    */
    void setSpeed(float speed )
    {
        if(speed > 5)
            _speed = 5;
        else
            _speed = speed;
    }
    /** 
    * @brief 得到人物的速度
    * @return float
    */
    float getSpeed()
    {
        return _speed;
    }
    /** 
    * @brief 设置人物的泡泡数量
    * @param popCount 泡泡数量
    * @return void
    */
    void setPopCount(int popCount )
    {
        _popCount = popCount;
    }
    /** 
    * @brief 得到人物的泡泡数量
    * @return int
    */
    int getPopCount()
    {
        return _popCount;
    }
    /** 
    * @brief 设置人物水柱长度
    * @param bubble 水柱的长度
    * @return void
    */
    void setBubble(int bubble )
    {
        _bubbleCount = bubble;
    }
    /** 
    * @brief 得到水柱的长度
    * @return int
    */
    int getBubble()
    {
        return _bubbleCount;
    }
    /** 
    * @brief 设置人物死亡
    * @return void
    */
    void setPlayerDead()
    {
        _isDead = true;
    }
    /** 
    * @brief 返回人物是否人物死亡
    * @return void
    */
    bool isDead()
    {
        return _isDead;
    }
    /** 
    * @brief 设置人物的角色名字
    * @param name 名字
    * @return void
    */
    void setRoleName(std::string name)
    {
        _roleName = name;
    }
    /** 
    * @brief 得到人物的角色名字
    * @return std::string
    */
    std::string getRoleName()
    {
        return _roleName;
    }
    /** 
    * @brief 设置玩家姓名
    * @param playerName 玩家姓名
    * @return void
    */
    void setPlayerName(std::string playerName)
    {
        _playerName = playerName;
    }
    /** 
    * @brief 得到玩家姓名
    * @return std::string
    */
    std::string getPlayerName()
    {
        return _playerName;
    }
    /** 
    * @brief 得到玩家坐标位置（string方式得到）
    * @return std::string
    */
    std::string getPlayerPosition()
    {
        std::stringstream ss;
        std::stringstream ss2;
        std::string s1 = "(";
        ss << this->getPositionX();
        std::string positionX = ss.str();
        std::string s2 = ",";
        ss2 << this->getPositionY();
        std::string positionY = ss2.str();
        std::string s3 = ")";
        
        return s1 + positionX + s2 + positionY + s3;
        
    }
    
    
};



#endif /* Role_h */
