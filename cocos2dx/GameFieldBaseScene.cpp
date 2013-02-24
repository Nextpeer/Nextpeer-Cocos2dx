
#include "GameFieldBaseScene.h"

// NP Integration steps: Import the following headers only for iOS
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "PZNextpeer.h"
#include "support/CCNotificationCenter.h"
#endif


bool GameFieldBaseScene::init()
{
	if ( !CCLayer::init() )	{
		return false;
	}
    
	// NP Integration steps: Listen when the game is ended
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(GameFieldBaseScene::nextpeerEndGame),
                                                                  NP_EVNET_END_GAME,
                                                                  NULL);
#endif
        
	return true;
}

// NP Integration steps: Add the following method (Ending game)
void GameFieldBaseScene::nextpeerEndGame(CCObject* pSender) {
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    gamePause = true;
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->popScene();
    
    // Restore the music
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}


void GameFieldBaseScene::gameOverCallBack(bool _isGameOver){
    
    if (_isGameOver) {
		// NP Integration steps: The game over changed, see how we handled
        bool didEndGameWithNextpeer = false;
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        PZ::PZNextpeer *np = PZ::PZNextpeer::shared();
        if (np->isCurrentlyInTournament()) {
            didEndGameWithNextpeer = true;
            np->reportControlledTournamentOverWithScore(gf_distance);
        }
        
#endif
        
		// NP Integration steps:  Add the gameover scene  if we didn't end the game in Nextpeer mode
        if (!didEndGameWithNextpeer) {
            
            CCScene* gameOver = GameOverScene::scene();
            this->addChild( gameOver );
        }
    }
}

void GameFieldBaseScene::update(float dd){
    
    // Updating the game score on each cycle
    gf_distance += gf_speed * dd;

    	// NP Integration steps: Report on the score of the tournament
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PZ::PZNextpeer *np = PZ::PZNextpeer::shared();
    if (np->isCurrentlyInTournament()) {
        np->reportScoreForCurrentTournament((int)gf_distance);
    }
#endif
}