package com.nextpeer.android.example;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.os.Bundle;

import com.badlogic.androidgames.framework.Screen;
import com.badlogic.androidgames.framework.impl.GLGame;
import com.bugsense.trace.BugSenseHandler;
import com.nextpeer.android.Nextpeer;

public class SuperJumper extends GLGame {
    boolean firstTimeCreate = true;

    @Override 
    public void onCreate(Bundle savedInstanceState) {
    	super.onCreate(savedInstanceState);
    	((App)getApplication()).game = this;    	
    }
    
    @Override
    public Screen getStartScreen() {
    	// This will save us in case that device terminated our previous activity, now we might need another scene (not the default main menu)
    	return ((App)getApplication()).getCurrentStartScreen();
    }
    
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {         
        super.onSurfaceCreated(gl, config);
        if(firstTimeCreate) {
            Assets.load(this);
            firstTimeCreate = false;            
        } else {
            Assets.reload();
        }
    }     
    
    // In case that the on back pressed and we still in game, we wish to forfeit the current game and show the main menu
    // However, if we presenting the main menu we wish to proceed as normal
    @Override
    public void onBackPressed() {
    	
    	Screen currentScreen = getCurrentScreen();
    	
    	boolean shouldBringBackMainMenu = false;
    	
    	// Check if the current screen is game screen, if it does - mark the game to be forfeit
    	if (currentScreen instanceof GameScreen) {
			BugSenseHandler.leaveBreadcrumb("Forfeit-Back");
    		Nextpeer.reportForfeitForCurrentTournament();
    		
    		// We wish to go back to the main menu (keep normal flow) back from the game scene 
    		shouldBringBackMainMenu = true;
    	}
    	// If the user pressed back on the HelpScreen go back to the main menu
    	else if (currentScreen instanceof BaseHelpScreen) {
    		shouldBringBackMainMenu = true;
    	}
    	
    	// If we should go back to the main menu, don't execute the back call
    	if (shouldBringBackMainMenu) {
    		setScreen(new MainMenuScreen(this));
    	}
    	// Act as usual, and allow the back button execution
    	else {
    		super.onBackPressed();
    	}
    }

    @Override
    public void onStart() {
		super.onStart();

        /*
         * Nextpeer integration Step
         */
		// Place a call to onStart in each activity.
		Nextpeer.onStart();
    }
    
    @Override
    public void onStop() {
		super.onStop();
		
    	if (getCurrentScreen() instanceof GameScreen) {

			BugSenseHandler.leaveBreadcrumb("Forfeit-Stop");
    		Nextpeer.reportForfeitForCurrentTournament();
    		setScreen(new MainMenuScreen(this));
    	}
    }
}