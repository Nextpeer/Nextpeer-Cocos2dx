package com.nextpeer.android.example;

import android.app.Application;

import com.badlogic.androidgames.framework.Game;
import com.badlogic.androidgames.framework.Screen;
import com.bugsense.trace.BugSenseHandler;
import com.nextpeer.android.Nextpeer;
import com.nextpeer.android.NextpeerListener;
import com.nextpeer.android.NextpeerTournamentCustomMessage;
import com.nextpeer.android.NextpeerTournamentEndData;
import com.nextpeer.android.NextpeerTournamentStartData;

public class App extends Application  {
	
	public Game game;

	// If you wish to test the game on a device which doesn't support accelerometer (emulator) you can switch to alternate type of game control (tap on the screen)
	private boolean mDoesDeviceSupportAccelerometer = true;
    
    private NextpeerTournamentStartData mStartData;
    
	@Override
	public void onCreate() {
		super.onCreate();

        /*
         * Nextpeer integration Step
         */
		// Initialize Nextpeer with your game key
		Nextpeer.initialize(this, "06b1dfb0834145e9c3d257f5fe0d5b09", _nextpeerListener);
		
		// This sample use BugSense to track crashes.
		BugSenseHandler.initAndStartSession(this, "b039275b");
		BugSenseHandler.addCrashExtraData("sdkVersion", Nextpeer.getNextpeerVersion());
		BugSenseHandler.leaveBreadcrumb("InitApp");
	}

	// As the Activity can be removed from memory, we should save the start data and start the right screen as required
	public Screen getCurrentStartScreen() {
		if (Nextpeer.isCurrentlyInTournament() && mStartData != null) {
			return getGameScreen();
		}
		
		return getMainMenuScreen();
	}
	
	private GameScreen getGameScreen() {
		return (new GameScreen(game, mStartData, mDoesDeviceSupportAccelerometer));
	}
	
	private MainMenuScreen getMainMenuScreen() {
		return (new MainMenuScreen(game));
	}
	
    /*
     * Nextpeer integration Step
     */
	private NextpeerListener _nextpeerListener = new NextpeerListener() {
		
		@Override
		// The tournament's game scene should be loaded
		public void onTournamentStart(NextpeerTournamentStartData startData) {
			// Setup search by username on Android
			BugSenseHandler.setUserIdentifier(startData.currentPlayer.playerId);

			BugSenseHandler.leaveBreadcrumb("onTournamentStart");
			
			// Persist the start data in case that the Activity will be restarted by the OS during the transition (seen on some devices)
			mStartData = startData;
			
			// Start the game screen
			game.setScreen(getGameScreen());
			
			BugSenseHandler.leaveBreadcrumb("onGameStart");
		}
		
		@Override
		// The tournament's main menu should be loaded
		public void onTournamentEnd(NextpeerTournamentEndData endData) {
			BugSenseHandler.leaveBreadcrumb("onTournamentEnd");
			mStartData = null;
	        game.setScreen(getMainMenuScreen());
		}
		
		@Override
		// The game received a custom message on the reliable protocol
		public void onReceiveTournamentCustomMessage(NextpeerTournamentCustomMessage message) {
			sendMessageIfPossible(message);
		}

		@Override
		// The game received a custom message on the unreliable protocol
		public void onReceiveUnreliableTournamentCustomMessage(NextpeerTournamentCustomMessage message) {
			sendMessageIfPossible(message);
		}
	};

	// Send the tournament custom message to the world receiver if the current screen is the GameScreen
	private void sendMessageIfPossible(NextpeerTournamentCustomMessage message) {
		Screen screen = game.getCurrentScreen();
		
		// Act only if the current scene is the game screen
		if (screen instanceof GameScreen) {
			GameScreen gameScreen = (GameScreen)screen;
			
			// Pass the received data to the world instance which responsible on the game updates
			gameScreen.world.onReceiveTournamentCustomMessage(message);				
		}
	}
}
