/*****************************************************************************
*
*  
*  
*
*  
*****************************************************************************/

#include "MenuScene.h"
#include "ui/CocosGUI.h"
#include "AudioControlScene.h"
#include "SimpleAudioEngine.h"
#include "LoadLayer.h"

USING_NS_CC;

using namespace ui;


void GameMenu::createLoadScene()
{
	loadScene = Scene::create();
	LoadLayer * layer = LoadLayer::create();
	loadScene->addChild(layer);
}


Scene* GameMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = GameMenu::create();
	scene->addChild(layer);

	return scene;
}



bool GameMenu::init() {

	if (!Layer::init()) 
	{
		return false;
	}	

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::create("bg.png");
    this->addChild(bg);
    bg->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    
	//==============================StartButton===========================
	auto start_button = Button::create("button.png");
	start_button->setScale(1.0);
	start_button->setTitleText("Start");
	start_button->setTitleFontSize(20);
	start_button->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4 * 3));

	start_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
		
			auto transition = TransitionSlideInL::create(0.5, NetMenu::createScene());
			Director::getInstance()->replaceScene(transition);

		}
	});
	this->addChild(start_button);

	//==============================SettingButton========================
	auto set_button = Button::create("button.png");
	set_button->setScale(1.0);
	set_button->setTitleText("Setting");
	set_button->setTitleFontSize(20);
	set_button->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4 * 2));

	set_button->addTouchEventListener([](Ref* psender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {

			auto transition = TransitionSlideInL::create(0.5, AudioControl::createScene());
			Director::getInstance()->replaceScene(transition);

		}
	});
	this->addChild(set_button);


	//==============================QuitButton===========================
	auto close_button = Button::create("button.png");
	close_button->setScale(1.0);
	close_button->setTitleText("Quit");
	close_button->setTitleFontSize(20);
	close_button->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4 * 1));

	close_button->addTouchEventListener([](Ref *pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
			MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
			return;
#endif
			Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif

		}
	});
	this->addChild(close_button);



	//==============================MusicButton===========================
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("The Crave.mp3", true);
	is_paused = false;

	auto music_button = MenuItemImage::create("music.png", "nomusic.png");
	auto pause_button = MenuItemImage::create("nomusic.png","music.png");

	MenuItemToggle *toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameMenu::menuMusicCallBack, this), music_button, pause_button, NULL);
	toggleItem->setScale(1.0f);
	toggleItem->setPosition(Point(origin.x + visibleSize.width * 0.9, origin.y + visibleSize.height * 0.1));
	auto menu = Menu::create(toggleItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	return true;
}

void GameMenu::menuMusicCallBack(cocos2d::Ref* pSender)
{
	
	if (is_paused == false)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		is_paused = true;
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		is_paused = false;
	}
}
