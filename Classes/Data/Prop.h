/*****************************************************************************
 *  
 *****************************************************************************/

#ifndef Prop_h
#define Prop_h


#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
using namespace ui;
/**
 * @brief 道具类 继承自cocos2d:Sprite
 * 这是Pop的控制类,这里存储着道具的种类
 */
class Prop: public cocos2d::Sprite
{
private:
    int _propType; /// 道具种类
public:
    
    /** 
    * @brief Prop的create函数
    * @param filename文件的名字
    * @return  Prop*
    */
    static Prop* create(const std::string& filename)
    {
        Prop *sprite = new Prop();
        if (sprite && sprite->initWithFile(filename))
        {
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);
        return nullptr;
    }
    
    /** 
    * @brief Prop的create函数
    * @param filename文件的名字
    * @return  Prop*
    */
    static Prop* createWithSpriteFrameName(const std::string& filename)
    {
        Prop *sprite = new Prop();
        if (sprite && sprite->initWithSpriteFrameName(filename))
        {
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);
        return nullptr;
    }
    
    /** 
    * @brief 设置道具的类型
    * @param type 类型
    * @return  void
    */
    void setPropType(int type)
    {
        _propType = type;
    }
    
    /** 
    * @brief 获得道具的类型
    * @return  int
    */
    int getPropType()
    {
        return _propType;
    }

};




#endif /* Prop_h */
