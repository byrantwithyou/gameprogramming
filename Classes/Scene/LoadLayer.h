/*****************************************************************************
*  
*****************************************************************************/

#ifndef __LoadLayer_h_
#define __LoadLayer_h_

#include "iostream"
#include "cocos2d.h"
#include "MenuScene.h"
USING_NS_CC;

/**
    * @brief 预加载类
    * 完成预加载背景音乐、精灵表单等准备工作
    */
class LoadLayer : public cocos2d::Layer
{
protected:
    int 				_sourceCount;									///用来保存游戏需要加载的资源总数
    ProgressTimer* 		_progress;										///进度条
    float 				_progressInterval;								///进度条更新的次数
public:
		/**
     * @brief 静态函数，创建Scene场景
     * @return 类实例的指针
     */
    static 				cocos2d::Scene* createScene();
    	/**
     * @brief init函数，完成初始化操作
     * @retrun bool值
     */					
    virtual 			bool init();

    virtual 			void onEnterTransitionDidFinish();
		/**
     * @brief 加载背景音乐函数
     * @param musicFiles 参数1 音乐文件
     */	
    void 				loadMusic(ValueVector musicFiles);
		/**
     * @brief 
     * @param spriteSheets 参数1 精灵表单
     */	
    void 				loadSpriteSheets(ValueVector spriteSheets);		
    	/**
     * @brief 进度条更新函数
     */	
    void 				progressUpdate();								
    	/**
     * @brief 使用CREATE_FUNC宏创建当前类的对象，返回的对象将会由自动释放池管理内存的释放
     */
    CREATE_FUNC(LoadLayer);												
};

#endif /* _LoadLayer_h_ */
