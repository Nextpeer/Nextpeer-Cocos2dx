package com.nextpeer.android.example;

import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.SortedMap;
import java.util.TreeMap;

import javax.microedition.khronos.opengles.GL10;

import com.badlogic.androidgames.framework.Game;
import com.badlogic.androidgames.framework.Input.TouchEvent;
import com.badlogic.androidgames.framework.gl.Camera2D;
import com.badlogic.androidgames.framework.gl.FPSCounter;
import com.badlogic.androidgames.framework.gl.SpriteBatcher;
import com.badlogic.androidgames.framework.impl.GLScreen;
import com.badlogic.androidgames.framework.math.Rectangle;
import com.badlogic.androidgames.framework.math.Vector2;
import com.nextpeer.android.Nextpeer;
import com.nextpeer.android.NextpeerTournamentStartData;
import com.nextpeer.android.example.World.WorldListener;

public class GameScreen extends GLScreen {
    static final int GAME_READY = 0;    
    static final int GAME_RUNNING = 1;
    static final int GAME_LEVEL_END = 3;
    static final int GAME_OVER = 4;
  
    int state;
    Camera2D guiCam;
    Vector2 touchPoint;
    SpriteBatcher batcher;    
    World world;
    WorldListener worldListener;
    WorldRenderer renderer;    
    Rectangle resumeBounds;
    Rectangle quitBounds;
    int lastScore;
    boolean isGameControlled = false;
    boolean reportedLastScore = false;
    boolean reportedForfeit = false;
    boolean doesDeviceSupportAccelerometer = false;
    String currentPlayerId = null;
    
    boolean shouldLogFPS = false;
    FPSCounter fpsCounter;
    
    public GameScreen(Game game, NextpeerTournamentStartData startData, boolean doesDeviceSupportAccelerometer) {
        super(game);
        this.doesDeviceSupportAccelerometer = doesDeviceSupportAccelerometer;
        this.isGameControlled = startData.tournamentIsGameControlled;
        this.currentPlayerId = startData.currentPlayer.playerId;
        
        state = GAME_READY;
        guiCam = new Camera2D(glGraphics, 320, 480);
        touchPoint = new Vector2();
        batcher = new SpriteBatcher(glGraphics, 1000);
        worldListener = new WorldListener() {
            @Override
            public void jump() {            
            }

            @Override
            public void highJump() {
            }

            @Override
            public void hit() {
            }

            @Override
            public void coin() {
            }            

            @Override
            public boolean shouldEndGame() {
            	// Let the user fail in case its a game controlled type of tournament, otherwise (time based) let the user continue playing
            	return isGameControlled;
            }
        };
        world = new World(worldListener, startData.tournamentRandomSeed);
        renderer = new WorldRenderer(glGraphics, batcher, world);
        resumeBounds = new Rectangle(160 - 96, 240, 192, 36);
        quitBounds = new Rectangle(160 - 96, 240 - 36, 192, 36);
        lastScore = 0;
        
        fpsCounter = new FPSCounter();
    }

	@Override
	public void update(float deltaTime) {
	    if(deltaTime > 0.1f)
	        deltaTime = 0.1f;
	    
	    switch(state) {
	    case GAME_READY:
	        updateReady();
	        break;
	    case GAME_RUNNING:
	        updateRunning(deltaTime);
	        break;
	    case GAME_LEVEL_END:
	        updateLevelEnd();
	        break;
	    case GAME_OVER:
	        updateGameOver();
	        break;
	    }
	}
	
	
	private void updateReady() {
        state = GAME_RUNNING;
	}
	
	private void updateRunning(float deltaTime) {
	    List<TouchEvent> touchEvents = game.getInput().getTouchEvents();
	    int len = touchEvents.size();
	    for(int i = 0; i < len; i++) {
	        TouchEvent event = touchEvents.get(i);
	        if(event.type != TouchEvent.TOUCH_UP)
	            continue;
	        
	        touchPoint.set(event.x, event.y);
	        guiCam.touchToWorld(touchPoint);
	    }
	    
	    float accelX = 0;
	    
	    if (this.doesDeviceSupportAccelerometer) {
	    	accelX = game.getInput().getAccelX();
	    }
	    // This device doesn't support accelermeter, extract the accel from the relative point to the center
	    else if (touchPoint != null && touchPoint.x > 0) {
	    	int sign = (touchPoint.x > 160.0f? -1 : 1);
	    	int dstFromCenter = Math.abs(160-(int)touchPoint.x);
	    	
	    	accelX = sign * dstFromCenter / 32; // 32 = 160/5 where 5 is the power
	    }
	    
	    world.update(deltaTime, accelX);
	    if(world.score != lastScore) {
	        lastScore = world.score;
	        
	        /*
	         * Nextpeer integration Step
	         */
	        
	        // The game's score has change, report the last known score to Nextpeer
	        Nextpeer.reportScoreForCurrentTournament(lastScore);
	    }
	    if(world.state == World.WORLD_STATE_NEXT_LEVEL) {
	        state = GAME_LEVEL_END;        
	    }
	    if(world.state == World.WORLD_STATE_GAME_OVER) {
	        state = GAME_OVER;
	    }
	}
	
	private void updateLevelEnd() {
		if (this.reportedLastScore) return;
		this.reportedLastScore = true;
		   
        /*
         * Nextpeer integration Step
         */		
		// We have reached level end, report the last known score
		if (this.isGameControlled) {
			Nextpeer.reportControlledTournamentOverWithScore(this.lastScore);	
		}
	}
	
	private void updateGameOver() {
		if (this.reportedLastScore) return;
		this.reportedLastScore = true;
		
        /*
         * Nextpeer integration Step
         */
		// We have reached level end, report the last known score
		if (this.isGameControlled) {
			Nextpeer.reportControlledTournamentOverWithScore(this.lastScore);	
		}
	}

	@Override
	public void present(float deltaTime) {
	    GL10 gl = glGraphics.getGL();
	    gl.glClear(GL10.GL_COLOR_BUFFER_BIT);
	    gl.glEnable(GL10.GL_TEXTURE_2D);
	    
	    renderer.render();
	    
	    guiCam.setViewportAndMatrices();
	    gl.glEnable(GL10.GL_BLEND);
	    gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);
	    batcher.beginBatch(Assets.items);
	    switch(state) {
	    case GAME_READY:
	        presentReady();
	        break;
	    case GAME_RUNNING:
	        presentRunning();
	        renderOpponentsHeightSoFar();
	        break;
	    case GAME_LEVEL_END:
	        presentLevelEnd();
	        break;
	    case GAME_OVER:
	        presentGameOver();
	        break;
	    }
	    batcher.endBatch();
	    gl.glDisable(GL10.GL_BLEND);
	    
	    if (this.shouldLogFPS) {
	    	fpsCounter.logFrame();
	    }
	}

	/*
	 * Printing the heights of the current player and the surrounding opponents, including their ranks
	 */
    private void renderOpponentsHeightSoFar() {
    	if (world.playerIdToHeightSoFar == null || world.playerIdToHeightSoFar.size() == 0) {
    		// We will render the opponents height when there is at least one height factor
    		return;
    	}
    	
    	// Defines how many players to print
    	final int countOfPositionsToShow = 3;
    	    	    	    	    	
    	SortedMap<Float, String> sortedHeights = new TreeMap<Float, String>();

		sortedHeights.put(world.heightSoFar, currentPlayerId);
    	for(OpponentHeightSoFar opponetHeight : world.playerIdToHeightSoFar.values()) {
    		sortedHeights.put(opponetHeight.heightSoFar, opponetHeight.opponentId);
    	}
    	
    	// Fetch the array list ids by sorted heights (last is the highest)
    	ArrayList<String> playerIdSortedByHeight = new ArrayList<String>(sortedHeights.values());
    	
    	// We need to trim the list to match the limit defined (countOfPositionsToShow)
    	int sizeOfPlayers = playerIdSortedByHeight.size();

    	// Will hold the player id, sorted by rank, including the current player, to be printed.
    	ArrayList<String> playersToPrint = null;
    	
    	// In case we have more players than we need to show, remove the unrequired players
    	if (sizeOfPlayers > countOfPositionsToShow) {
    		
    		// We going to remove items from the print array
    		playersToPrint = new ArrayList<String>(playerIdSortedByHeight);
    		
    		int indexOfCurrentPlayer = playersToPrint.indexOf(currentPlayerId);
    		// The current player is the last player, keep the next countOfPositionsToShow players 
    		if (indexOfCurrentPlayer == 0) {

    			for(int indexToRemove = sizeOfPlayers - 1; indexToRemove >= countOfPositionsToShow ; indexToRemove--) {
    				playersToPrint.remove(indexToRemove);
    			}
    		}
    		// The current player is the first player, keep the next countOfPositionsToShow - 1 players after it 
    		else if (indexOfCurrentPlayer == sizeOfPlayers - 1) {

    			for(int indexToRemove = sizeOfPlayers - countOfPositionsToShow - 1; indexToRemove >= 0 ; indexToRemove--) {
    				playersToPrint.remove(indexToRemove);
    			}
    		}
    		// The current player is in the middle, take few players around it (remove players from the top first, leave one below & above)
    		else {
    			int itemsLeftToRemove = sizeOfPlayers - countOfPositionsToShow;
    			boolean shouldNextBeRemovedFromTop = true;
    			while(itemsLeftToRemove > 0) {
    				boolean removedItem = false;
    				
    				if (shouldNextBeRemovedFromTop) {
    					if (indexOfCurrentPlayer < sizeOfPlayers - 2) {
    						playersToPrint.remove(sizeOfPlayers-1);
    						removedItem = true;
    					}
    				}
    				else {
    					if (indexOfCurrentPlayer > 1) {
    						playersToPrint.remove(0);
    						removedItem = true;
    					}
    				}
    				
    				// If we removed an item at this loop run update the indexes
    				if (removedItem) {
        				// Update the index of the current player (either we kept the index or we removed one before the current index)
        	    		indexOfCurrentPlayer = (shouldNextBeRemovedFromTop ? indexOfCurrentPlayer : (indexOfCurrentPlayer - 1));
        				itemsLeftToRemove--;
        				sizeOfPlayers--;
    				}
    	    		
    				// Switch the exit loop
    				shouldNextBeRemovedFromTop = !shouldNextBeRemovedFromTop;
    			}
    		}
    	}
    	else {
    		playersToPrint = playerIdSortedByHeight;
    	}
    	
	    int differentBetweenTexts = 20;

	    /* We print the players from the last to the first */
	    
	    // Get the actual rank of the first player (including the current player) in the sorted array (smallest value)
		int rankOfLastPlayer = playerIdSortedByHeight.size() - playerIdSortedByHeight.indexOf(playersToPrint.get(0));

	    // Print the heights (from the last rank to the first)
		int sizeOfPlayersToPrint = playersToPrint.size();
		for (int playerIndex = 0; playerIndex < sizeOfPlayersToPrint; playerIndex++) {
	    	String playerId = playersToPrint.get(playerIndex);
	    	
	    	String nameToPrint = null;
	    	float heightToPrint = 0;
	    	
	    	// Special handling for the current player
	    	if (playerId.equals(currentPlayerId)) {
	    		nameToPrint = "YOU";
	    		heightToPrint = world.heightSoFar;
	    	}
	    	else {
	    		// Take only the name from the playerIdToHeightSoFar as the height can be already modified
	    		OpponentHeightSoFar playerHeight = world.playerIdToHeightSoFar.get(playerId);	    
	    		nameToPrint = playerHeight.playerName;
	    		heightToPrint = playerHeight.heightSoFar;
	    	}

	    	String rankLine = String.format(Locale.US, "#%d %s [%dm]", rankOfLastPlayer, nameToPrint, (int)heightToPrint);
	    	
    	    Assets.font.drawText(batcher, rankLine, 10, differentBetweenTexts*(playerIndex + 1));
    	    rankOfLastPlayer--;
	    }
    }
    
	private void presentReady() {
	    batcher.drawSprite(160, 240, 192, 32, Assets.ready);
	}
	
	private void presentRunning() {
	    Assets.font.drawText(batcher,  "Score: " + lastScore, 10, 480-20);
		
        /*
         * Nextpeer integration Step
         */
	    // If we running a Nextpeer 'time-based' tournament, show the time left for the tournament
	    if (!isGameControlled) {
		    Assets.font.drawText(batcher, "Time: " + Nextpeer.timeLeftForTournament(), 10, 480-40);
	    }
	}

	private void presentLevelEnd() {
	    String topText = "Congratulations";
	    String bottomText = "You have rescued the princess!";
	    float topWidth = Assets.font.glyphWidth * topText.length();
	    float bottomWidth = Assets.font.glyphWidth * bottomText.length();
	    Assets.font.drawText(batcher, topText, 160 - topWidth / 2, 480 - 40);
	    Assets.font.drawText(batcher, bottomText, 160 - bottomWidth / 2, 40);
	}
	
	private void presentGameOver() {
	    batcher.drawSprite(160, 240, 160, 96, Assets.gameOver);        
	    String scoreString = "score: " + lastScore;
	    float scoreWidth = Assets.font.glyphWidth * scoreString.length();
	    Assets.font.drawText(batcher, scoreString, 160 - scoreWidth / 2, 480-20);
	}

    @Override
    public void pause() {
    }

    @Override
    public void resume() {        
    }

    @Override
    public void dispose() {       
    }
}
