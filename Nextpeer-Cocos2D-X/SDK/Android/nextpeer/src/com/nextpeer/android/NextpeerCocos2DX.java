//
//  NextpeerCocos2DX.java
//
//  Created by Nextpeer platforms development team.
//  Copyright (c) 2015 Nextpeer, Ltd. All rights reserved.
//

package com.nextpeer.android;

import android.app.Activity;
import android.content.Context;

/**
 * Helper class for Cocos2dX integration process.
 *
 */
public final class NextpeerCocos2DX extends NextpeerListener
{
	private static Context mContext = null;
	private static NextpeerCocos2DX mInstance = null;
	private static NextpeerFacebookBridge mFacebookBridge = null;

	// Activity callbacks
	public static void onCreate(Activity mainActivity)
	{
		mContext = mainActivity;
	}

	public static void onStart()
	{
		if (Nextpeer.isNextpeerInitialized()) {
			Nextpeer.onStart();
		}
	}

	public static void onStop()
	{
		if (Nextpeer.isCurrentlyInTournament()) {
			Nextpeer.reportForfeitForCurrentTournament();
		}
	}

	protected static NextpeerCocos2DX getInstance()
	{
		if (mInstance == null) mInstance = new NextpeerCocos2DX();

		return mInstance;
	}

	public static Context getContext() {
		return mContext;
	}

	public static void setFacebookBridge(NextpeerFacebookBridge facebookBridge) {
		mFacebookBridge = facebookBridge;
	}

	// API method wrappers

	public static void initialize(String gameKey)
	{
		if (mContext == null) {
			throw new IllegalStateException("Context is null! Call to NextpeerCocos2DX.onCreate() is probably missing");
		}

		Nextpeer.initialize(new NextpeerConfiguration(mContext, gameKey, getInstance()).setFacebookBridge(mFacebookBridge));

		onStart();
	}

	public static void launch()
	{
		Nextpeer.launch();
	}

	public static void reportScoreForCurrentTournament(int score)
	{
		Nextpeer.reportScoreForCurrentTournament(score);
	}

	public static void reportControlledTournamentOverWithScore(int score)
	{
		Nextpeer.reportControlledTournamentOverWithScore(score);
	}

	public static void reportForfeitForCurrentTournament()
	{
		Nextpeer.reportForfeitForCurrentTournament();
	}

	public static void pushDataToOtherPlayers(byte[] data)
	{
		Nextpeer.pushDataToOtherPlayers(data);
	}

	public static void unreliablePushDataToOtherPlayers(byte[] data)
	{
		Nextpeer.unreliablePushDataToOtherPlayers(data);
	}

	public static boolean isCurrentlyInTournament()
	{
		return Nextpeer.isCurrentlyInTournament();
	}

	@SuppressWarnings("deprecation")
	public static int timeLeftForTournament()
	{
		return Nextpeer.timeLeftForTournament();
	}

	public static String getCurrentPlayerId()
	{
		NextpeerTournamentPlayer currentPlayer = Nextpeer.getCurrentPlayerDetails();

		if (currentPlayer == null) return null;

		return currentPlayer.playerId;
	}

	public static String getCurrentPlayerName()
	{
		NextpeerTournamentPlayer currentPlayer = Nextpeer.getCurrentPlayerDetails();

		if (currentPlayer == null) return null;

		return currentPlayer.playerName;
	}

	public static void enableRankingDisplay(boolean enableRankingDisplay)
	{
		Nextpeer.enableRankingDisplay(enableRankingDisplay);
	}

	public static void requestRecordingControlScoreModifier(String userId, int scoreModifier)
	{
		Nextpeer.requestRecordingControlScoreModifier(userId, scoreModifier);
	}

	public static void requestRecordingControlPauseRecording(String userId)
	{
		Nextpeer.requestRecordingControlPauseRecording(userId);
	}

	public static void requestRecordingControlResumeRecording(String userId)
	{
		Nextpeer.requestRecordingControlResumeRecording(userId);
	}

	public static void requestRecordingControlStopRecording(String userId)
	{
		Nextpeer.requestRecordingControlStopRecording(userId);
	}

	public static void requestRecordingControlRewindRecording(String userId, int timeDelta)
	{
		Nextpeer.requestRecordingControlRewindRecording(userId, timeDelta);
	}

	public static void requestRecordingControlFastForwardRecording(String userId, int timeDelta)
	{
		Nextpeer.requestRecordingControlFastForwardRecording(userId, timeDelta);
	}

	public static void registerToSynchronizedEvent(String eventName, int timeoutInMilliseconds)
	{
		Nextpeer.registerToSynchronizedEvent(eventName, timeoutInMilliseconds);
	}

	// NextpeerListener methods

	@Override
	public void onTournamentStart(NextpeerTournamentStartData startData)
	{
		final NextpeerTournamentPlayer[] opponents = startData.opponents.toArray(new NextpeerTournamentPlayer[0]);
		onTournamentStartNative(startData, opponents);
	}

	@Override
	public void onTournamentEnd(NextpeerTournamentEndData endData)
	{
		onTournamentEndNative(endData);
	}

	@Override
	public void onReceiveTournamentCustomMessage(NextpeerTournamentCustomMessage message)
	{
		onReceiveTournamentCustomMessageNative(message);
	}

	@Override
	public void onReceiveUnreliableTournamentCustomMessage(NextpeerTournamentCustomMessage message)
	{
		onReceiveUnreliableTournamentCustomMessageNative(message);
	}

	@Override
	public void onNextpeerAppear()
	{
		onNextpeerAppearNative();
	}

	@Override
	public void onNextpeerDisappear()
	{
		onNextpeerDisappearNative();
	}

	@Override
	public void onNextpeerReturnToGame()
	{
		onNextpeerReturnToGameNative();
	}

	@Override
	public boolean onSupportsTournament(String tournamentUuid)
	{
		return onSupportsTournamentNative(tournamentUuid);
	}

	@Override
	public void onReceiveSynchronizedEvent(String name, NextpeerSynchronizedEventFire fireReason) {
		onReceiveSynchronizedEventNative(name,fireReason);
	}

	// JNI methods

	protected native void onTournamentStartNative(NextpeerTournamentStartData startData, NextpeerTournamentPlayer[] opponents);
	protected native void onTournamentEndNative(NextpeerTournamentEndData endData);
	protected native void onReceiveTournamentCustomMessageNative(NextpeerTournamentCustomMessage message);
	protected native void onReceiveUnreliableTournamentCustomMessageNative(NextpeerTournamentCustomMessage message);

	protected native void onNextpeerAppearNative();
	protected native void onNextpeerDisappearNative();
	protected native void onNextpeerReturnToGameNative();
	protected native boolean onSupportsTournamentNative(String tournamentUuid);
	protected native void onReceiveSynchronizedEventNative(String name, NextpeerSynchronizedEventFire fireReason);
}
