package com.nextpeer.android.example;

public class OpponentHeightSoFar {

	public final String opponentId;
	public final String playerName;
    
    public float heightSoFar;

    public OpponentHeightSoFar(String opponentId, String playerName, float heightSoFar) {
        this.heightSoFar = heightSoFar; 
        this.opponentId = opponentId;
        this.playerName = playerName;
    }

}
