/*****************************************************************************
 *  
 *
 *****************************************************************************/

#ifndef _PopController_h_
#define _PopController_h_

#include <iostream>
#include "cocos2d.h"
#include "json/document.h"

USING_NS_CC;

class Game;
/**
 * @brief Pop类 继承自cocos2d:Node
 * 这是Pop的控制类,这里控制着泡泡的释放与爆炸！
 */
class Pop :public cocos2d::Node
{
    
protected:
    
    int                _powerAbility;         ///每个人的水泡的长度
    int                _waterLength[4];       ///四个方向水柱的长度
    Sprite*            _pop;                  ///具体操控的泡泡
    Sprite*            _popEx;                ///即将要爆炸的泡泡
    Game*              _scene;                ///Game 场景
    Vector<Sprite*>*   _popVector;            ///整体泡泡的Vector
    
public:
    
    /** 
    * @brief Pop的create函数
    * @param scene Game场景 
    * @return  Pop*
    */
    static Pop* create(Game &scene)
    {
        Pop *pop = new Pop();
        if (pop)
        {
            return pop;
        }
        CC_SAFE_DELETE(pop);
        return nullptr;
    }
    /** 
    * @brief 初始化场景信息
    * @param scene Game场景 
    * @return  void
    */
    void setScene(Game* scene);
    /** 
    * @brief 每一帧升级泡泡
    * @param scene Game场景 
    * @param delta Update函数默认参数
    * @param code 按键的信息(空格)
    * @return  void
    */
    void updatePopPerFrame(int delta, Game &scene, EventKeyboard::KeyCode code);
    /** 
    * @brief 回调函数,设置泡泡爆炸的时间是2.5秒
    * @return  void
    */
    void callFunc2();
    /** 
    * @brief 判断是否放置泡泡
    * @param scene Game场景 
    * @return  void
    */
    bool whetherPutPop(Game& scene);
    /** 
    * @brief 放置泡泡
    * @param scene Game场景 
    * @return  void
    */
    void putPop(Game &scene);
    /** 
    * @brief 改变水花的长度
    * @param scene Game场景 
    * @powerAbibity 每个人的水花的长度
    * @return  void
    */
    void changeWaterLengh(Game* scene, int powerAbility);
    /** 
    * @brief 泡泡的爆炸
    * @param scene Game场景 
    * @return  void
    */
    void popExplosion(Game & scene);
        /** 
    * @brief 进行图块的消去
    * @param scene Game场景 
    * @return  void
    */
    void eraseBlocks(Game& scene);
    /** 
    * @brief 放置道具
    * @param scene Game场景 
    * @ i    放置道具的种类
    * @return  void
    */
    void setPorp(Game& scene,int i);
    
    
};


#endif /* _PopController_h_ */
