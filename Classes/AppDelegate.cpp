#include "AppDelegate.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs() {
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages() {
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
        glview = GLViewImpl::create("Sky Defence");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    auto screenSize = glview->getFrameSize();
    auto designSize = Size(2048, 1536);

    glview->setDesignResolutionSize(designSize.width, designSize.height,
                                    ResolutionPolicy::EXACT_FIT);
    CCLOG("SCREEN: w:%f h:%f", screenSize.width, screenSize.height);
    std::vector<std::string> searchPaths;
    if (screenSize.height > 768) {
        searchPaths.push_back("ipadhd");
        director->setContentScaleFactor(1536 / designSize.height);
    } else if (screenSize.height > 320) {
        searchPaths.push_back("ipad");
        director->setContentScaleFactor(768 / designSize.height);
    } else {
        searchPaths.push_back("iphone");
        director->setContentScaleFactor(380 / designSize.height);
    }

    auto fileUtils = FileUtils::getInstance();
    fileUtils->setSearchPaths(searchPaths);

    auto audioEngine = SimpleAudioEngine::getInstance();
    audioEngine->preloadBackgroundMusic(
            fileUtils->fullPathForFilename("res/audio/background.mp3").c_str());
    audioEngine->preloadEffect(fileUtils->fullPathForFilename("res/audio/bombFail.wav").c_str());
    audioEngine->preloadEffect(fileUtils->fullPathForFilename("res/audio/bombRelease.wav").c_str());
    audioEngine->preloadEffect(fileUtils->fullPathForFilename("res/audio/boom.wav").c_str());
    audioEngine->preloadEffect(fileUtils->fullPathForFilename("res/audio/health.wav").c_str());
    audioEngine->preloadEffect(fileUtils->fullPathForFilename("res/audio/pew.wav").c_str());
    audioEngine->preloadEffect(fileUtils->fullPathForFilename("res/audio/fire_truck.wav").c_str());

    audioEngine->setBackgroundMusicVolume(0.5f);
    audioEngine->setEffectsVolume(0.5f);

    // create a scene. it's an autorelease object
    auto scene = GameScene::createScene();

    // run
    director->runWithScene(scene);
    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
