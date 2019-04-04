/*****************************************************************************
 * 
 *****************************************************************************/

#include "AppDelegate.h"
#include "Scene/GameScene.h"
#include "Scene/MenuScene.h"
#include <vector>
#include <iostream>

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(680, 680);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };
    
    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
    return 0;
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    
    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("MX1", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("MX1");
#endif
        director->setOpenGLView(glview);
	}

	director->setDisplayStats(true);

    
	director->setAnimationInterval(1.0f / 60);

	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);

	auto frameSize = glview->getFrameSize();
	
	if (frameSize.height > mediumResolutionSize.height)
	{
		director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));
	}
    
	else if (frameSize.height > smallResolutionSize.height)
	{
		director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
	}
    
	else
	{
		director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width));
	}

	register_all_packages();

	glview->setDesignResolutionSize(680, 680, ResolutionPolicy::FIXED_WIDTH);
	std::vector<std::string> searchPath;
    
    
	director->setContentScaleFactor(680 / 680);
    
	GameMenu * manager = new GameMenu();
	manager->createLoadScene();

	
	director->runWithScene(manager->loadScene);

	return true;
}


void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
}


void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
}
