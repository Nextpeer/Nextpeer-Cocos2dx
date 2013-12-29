package com.nextpeer.android.example;

import com.badlogic.androidgames.framework.gl.Animation;
import com.badlogic.androidgames.framework.gl.Font;
import com.badlogic.androidgames.framework.gl.Texture;
import com.badlogic.androidgames.framework.gl.TextureRegion;
import com.badlogic.androidgames.framework.impl.GLGame;

public class Assets {
    public static Texture background;
    public static TextureRegion backgroundRegion;
    
    public static Texture items;        
    public static TextureRegion mainMenu;
    public static TextureRegion ready;
    public static TextureRegion gameOver;
    public static TextureRegion highScoresRegion;
    public static TextureRegion logo;
    public static TextureRegion arrow;
    public static TextureRegion spring;
    public static TextureRegion castle;
    public static Animation coinAnim;
    public static Animation bobJump;
    public static Animation bobFall;
    public static TextureRegion arrowUp;
    public static TextureRegion arrowDown;
    public static TextureRegion bobHit;
    public static Animation opponentJump;
    public static Animation opponentFall;
    public static TextureRegion opponentHit;
    public static Animation squirrelFly;
    public static TextureRegion platform;
    public static Animation brakingPlatform;    
    public static Font font;
    
    public static void load(GLGame game) {
        background = new Texture(game, "background.png");
        backgroundRegion = new TextureRegion(background, 0, 0, 320, 480);
        
        items = new Texture(game, "items.png");        
        mainMenu = new TextureRegion(items, 0, 224, 300, 110);
        ready = new TextureRegion(items, 320, 224, 192, 32);
        gameOver = new TextureRegion(items, 352, 256, 160, 96);
        logo = new TextureRegion(items, 0, 343, 270, 165);
        arrow = new TextureRegion(items, 0, 64, 64, 64);
        
        spring = new TextureRegion(items, 128, 0, 32, 32);
        castle = new TextureRegion(items, 128, 64, 64, 64);
        coinAnim = new Animation(0.2f,                                 
                                 new TextureRegion(items, 128, 32, 32, 32),
                                 new TextureRegion(items, 160, 32, 32, 32),
                                 new TextureRegion(items, 192, 32, 32, 32),
                                 new TextureRegion(items, 160, 32, 32, 32));
        

        float opponentPosY = 380.0f;
        float opponentStartPosX = 316.0f;
        opponentJump = new Animation(0.2f,
                new TextureRegion(items, opponentStartPosX, opponentPosY, 32, 32),
                new TextureRegion(items, opponentStartPosX + 32, opponentPosY, 32, 32));
        opponentFall = new Animation(0.2f,
		                new TextureRegion(items, opponentStartPosX + 64, opponentPosY, 32, 32),
		                new TextureRegion(items, opponentStartPosX + 96, opponentPosY, 32, 32));
        opponentHit = new TextureRegion(items, opponentStartPosX + 128, opponentPosY, 32, 32);
       
        bobJump = new Animation(0.2f,
                                new TextureRegion(items, 0, 128, 32, 32),
                                new TextureRegion(items, 32, 128, 32, 32));
        bobFall = new Animation(0.2f,
                                new TextureRegion(items, 64, 128, 32, 32),
                                new TextureRegion(items, 96, 128, 32, 32));
        bobHit = new TextureRegion(items, 128, 128, 32, 32);
        
        squirrelFly = new Animation(0.2f, 
                                    new TextureRegion(items, 0, 160, 32, 32),
                                    new TextureRegion(items, 32, 160, 32, 32));
        platform = new TextureRegion(items, 64, 160, 64, 16);
        brakingPlatform = new Animation(0.2f,
                                     new TextureRegion(items, 64, 160, 64, 16),
                                     new TextureRegion(items, 64, 176, 64, 16),
                                     new TextureRegion(items, 64, 192, 64, 16),
                                     new TextureRegion(items, 64, 208, 64, 16));
        float arrowSize = 64;
        float arrowsPosX = 324;
        float arrowsPosY = 442;
        arrowUp = new TextureRegion(items, arrowsPosX, arrowsPosY, arrowSize, arrowSize);
        arrowDown = new TextureRegion(items, arrowsPosX+arrowSize, arrowsPosY, arrowSize, arrowSize);
        
        font = new Font(items, 224, 0, 16, 16, 20);     
    }       
    
    public static void reload() {
        background.reload();
        items.reload();
    }
}
