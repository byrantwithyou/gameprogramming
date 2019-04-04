/*****************************************************************************
*  Copyright (C) 2017 李坤 1061152718@qq.com
*
* 
*
*****************************************************************************/

#ifndef _MenuScene_h_
#define _MenuScene_h_

#include "cocos2d.h"
#include "GameScene.h"
#include "AudioControlScene.h"
#include "NetMenu.h"

/**
* 	@brief  游戏主菜单界面\n
* 			创建游戏主菜单, 包括开始游戏按钮, 游戏设置按钮, 退出游戏按钮, 音乐开关按钮
*/

class GameMenu : public cocos2d::Layer
{
public:

	Scene * loadScene;		///指向加载界面的指针
	bool 	is_paused;		///游戏音乐是否被暂停

	/**
	* @brief  	创建加载场景 
	*/
	void createLoadScene();

	/**
	* @brief  	创建主菜单场景
	*/
	static cocos2d::Scene* createScene();

	/**
	* @brief  	当点击音乐按钮时调用该函数
	*        	-<em>音乐正在播放</em> 静音
    *        	-<em>音乐不在播放</em> 开启声音
    * 
    * @param 	psender    指针, 指向调用回调函数的CCObject
	*/
	void menuMusicCallBack(cocos2d::Ref* pSender);

	/**
	* @brief  	自定义的initial函数, 向场景中添加各个按钮并定义相关的回调函数
	*/
	virtual bool init();

	/**
	* @brief  	在create()后调用init(), 并让相应对象加入cocos自动内存管理系统
	*/
	CREATE_FUNC(GameMenu);
};


#endif /* _MenuScene_h_ */
