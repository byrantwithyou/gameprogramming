/*****************************************************************************
*                             
*                                                                            
*  
*****************************************************************************/

#include "AudioControlScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace ui;

Scene* AudioControl::createScene() {
	auto scene = Scene::create();
	auto layer = AudioControl::create();
	scene->addChild(layer);
	return scene;
}


bool AudioControl::init() {
	if (!Layer::create())
	{
		return false;
	}

	Size visible_size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = Sprite::create("bg.png");
    this->addChild(bg);
    bg->setPosition(Vec2(visible_size.width/2, visible_size.height/2));

	auto music_text = Label::createWithTTF("MusicSound", "fonts/Marker Felt.ttf", 32);
	music_text->setPosition(Vec2(visible_size.width*0.25 + origin.x, origin.y + visible_size.height*0.7));
	this->addChild(music_text);

	auto music_slider = Slider::create();
	music_slider->loadBarTexture("sliderTrack.png");
	music_slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	music_slider->loadProgressBarTexture("sliderProgress.png");
	float musicPercent = UserDefault::getInstance()->getFloatForKey("musicPercent");

	if (musicPercent == 0.0f) {
		musicPercent = 100.0f;
	}

	music_slider->setPercent(musicPercent);
	music_slider->setPosition(Vec2(origin.x + visible_size.width*0.6, origin.y + visible_size.height*0.7));

	music_slider->addEventListener([=](Ref* pSender, Slider::EventType type) {

		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
			int percent = music_slider->getPercent();
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(static_cast<float>(percent) / 100);
			UserDefault::getInstance()->setFloatForKey("musicPercent", percent);
		}
	});
	this->addChild(music_slider);
	auto sound_text = Label::createWithTTF("EffectSound", "fonts/Marker Felt.ttf", 32);
	sound_text->setPosition(Vec2(origin.x + visible_size.width*0.25, origin.y + visible_size.height*0.5));
	this->addChild(sound_text);


	auto effects_slider = Slider::create();
	effects_slider->loadBarTexture("sliderTrack.png");
	effects_slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	effects_slider->loadProgressBarTexture("sliderProgress.png");
	float effectPercent = UserDefault::getInstance()->getFloatForKey("effectPercent");

	if (effectPercent == 0.0f) {
		effectPercent = 100.0f;
	}
	effects_slider->setPercent(effectPercent);
	effects_slider->setPosition(Vec2(origin.x + visible_size.width*0.6, origin.y + visible_size.height*0.5));
	effects_slider->addEventListener([=](Ref* pSender, Slider::EventType type) {
		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			int percent = effects_slider->getPercent();
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(static_cast<float> (percent) / 100);
			UserDefault::getInstance()->setFloatForKey("effectPercent", percent);
		}
	});
	
	this->addChild(effects_slider);
	auto return_button = Button::create("back_button.png");

	return_button->cocos2d::Node::setScale((visible_size.width * 0.1 / return_button->getContentSize().width));
	return_button->setPosition(Vec2(origin.x + visible_size.width - return_button->getContentSize().width / 2, origin.y + return_button->getContentSize().height / 2));
	return_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionSlideInL::create(0.5, GameMenu::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});

	this->addChild(return_button);

	return true;
}

























