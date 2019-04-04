/*****************************************************************************
* 
*****************************************************************************/
#include "LoadLayer.h"

USING_NS_CC;

Scene* LoadLayer::createScene(){
    auto scene = Scene::create();
    auto layer = LoadLayer::create();
    scene->addChild(layer);
    
    return scene;
}

bool LoadLayer::init(){
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto bg = Sprite::create("SkyBg.png");
    this->addChild(bg);
    bg->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation.plist");
    auto barSprite = Sprite::create("ProgressBar.png");
    auto barBgSprite = Sprite::create("LoadingBar.png");
    barBgSprite->setPosition(Vec2(visibleSize.width/2,visibleSize.height/3));
    _progress = ProgressTimer::create(barSprite);
    _progress->setPercentage(0.0f);
    _progress->setScale(1.0f);
    _progress->setMidpoint(Point(0.0f, 0.5f));
    _progress->setBarChangeRate(Point(1.0f, 0.0f));
    _progress->setType(ProgressTimer::Type::BAR);
    _progress->setPosition(visibleSize.width/2,visibleSize.height/3);
    
    Label *label = Label::createWithTTF("Loading...", "fonts/Marker Felt.ttf", 40);
    Size size = Director::getInstance()->getVisibleSize();
    label->setPosition(Vec2(size.width / 2, size.height / 2));
    
    
    this->addChild(label);
    this->addChild(barBgSprite);
    this->addChild(_progress);
    
    return true;
}

void LoadLayer::onEnterTransitionDidFinish(){
    Layer::onEnterTransitionDidFinish();
    ValueMap map = FileUtils::getInstance()->getValueMapFromFile("loadLayer.plist");
    ValueVector spriteSheets = map.at("SpriteSheets").asValueVector();
    ValueVector musics = map.at("BGM").asValueVector();
    _sourceCount = spriteSheets.size() + musics.size();
    _progressInterval = 100 / _sourceCount;
    loadSpriteSheets(spriteSheets);
    loadMusic(musics);
    
}

void LoadLayer::loadMusic(ValueVector musicFiles){
    for (Value &v : musicFiles) {
        progressUpdate();
    }
}

void LoadLayer::loadSpriteSheets(ValueVector spriteSheets){
    for (Value &v : spriteSheets) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(v.asString().c_str());
        progressUpdate();
    }
}

void LoadLayer::progressUpdate(){
    if(--_sourceCount){
        _progress->setPercentage(100.0f-(_progressInterval * _sourceCount));
    }
    else{
        auto pft = ProgressFromTo::create(2.0f, 0, 100);
        auto callFunc = CallFunc::create([=]{
            auto delay = DelayTime::create(0.2f);
            auto callFunc = CallFunc::create([]{
                auto transition = TransitionSlideInB::create(2, GameMenu::createScene());
                Director::getInstance()->replaceScene(transition);
            });
            auto action = Sequence::create(delay,callFunc, NULL);
            this->runAction(action);
        });
        auto action = Sequence::create(pft,callFunc, NULL);
        _progress->runAction(action);
    }
}


