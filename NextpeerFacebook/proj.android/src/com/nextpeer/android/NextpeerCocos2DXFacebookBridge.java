package com.nextpeer.android;

import java.util.HashSet;
import java.util.Set;

import android.content.Context;
import android.content.Intent;
import android.util.Log;

import com.nextpeer.android.Nextpeer;
import com.nextpeer.android.NextpeerFacebookBridge;
import com.nextpeer.android.NextpeerFacebookSession;
import com.nextpeer.android.open.NPLog;
import com.facebook.Session;

public class NextpeerCocos2DXFacebookBridge implements NextpeerFacebookBridge {
	private static NextpeerCocos2DXFacebookBridge mInstance = null;

	private OnFacebookRequestFinished mLastCallback = null;

	public static void init() {
		if (mInstance == null) {
			mInstance = new NextpeerCocos2DXFacebookBridge();
			NextpeerCocos2DX.setFacebookBridge(mInstance);
		}
	}

	public static void login() {
		Nextpeer.loginWithFacebook();
	}

	public static void logout() {
		Nextpeer.logoutFromFacebook();
	}

	private NextpeerCocos2DXFacebookBridge() {
	}

	@Override
	public NextpeerFacebookSession getCurrentSession() {
		Session fbSession = Session.getActiveSession();
		if (fbSession != null && fbSession.isOpened()) {
			final String accessToken = fbSession.getAccessToken();
			final Set<String> permissions = new HashSet<String>();
			permissions.addAll(fbSession.getPermissions());
			return new NextpeerFacebookSession(accessToken, permissions);
		}
		return null;
	}

	@Override
	public void destroyCurrentFacebookSession() {
		Session fbSession = Session.getActiveSession();
		if (fbSession != null) {
			fbSession.closeAndClearTokenInformation();
		}
	}

	@Override
	public void requestFacebookSessionWithPermissions(String[] permissions, OnFacebookRequestFinished onFinish) {
		Context context = NextpeerCocos2DX.getContext();
		if (context == null) {
			NPLog.e("FaacebookBridge: Context is not available");
			if (onFinish != null) {
				onFinish.onFailure();
			}
			return;
		}

		mLastCallback = onFinish;

		Intent t = new Intent(context, NextpeerCocos2DXFacebookBridgeActivity.class);
		t.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		t.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);

		t.putExtra(NextpeerCocos2DXFacebookBridgeActivity.ACTION, NextpeerCocos2DXFacebookBridgeActivity.ACTION_LOGIN);
		t.putExtra(NextpeerCocos2DXFacebookBridgeActivity.PERMISSIONS, join(permissions));

		context.startActivity(t);
	}

	@Override
	public void requestFacebookPermissions(String[] permissions, OnFacebookRequestFinished onFinish) {
		Context context = NextpeerCocos2DX.getContext();
		if (context == null) {
			NPLog.e("FaacebookBridge: Context is not available");
			if (onFinish != null) {
				onFinish.onFailure();
			}
			return;
		}

		mLastCallback = onFinish;

		Intent t = new Intent(context, NextpeerCocos2DXFacebookBridgeActivity.class);
		t.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		t.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);

		t.putExtra(NextpeerCocos2DXFacebookBridgeActivity.ACTION, NextpeerCocos2DXFacebookBridgeActivity.ACTION_PERMISSIONS);
		t.putExtra(NextpeerCocos2DXFacebookBridgeActivity.PERMISSIONS, join(permissions));

		context.startActivity(t);
	}

	private String join(String[] permissions) {
		StringBuilder sb = new StringBuilder();
		if (permissions.length > 0) {
			sb.append(permissions[0]);
		}
		for (int i = 1; i < permissions.length; i++) {
			sb.append(",").append(permissions[i]);
		}
		return sb.toString();
	}

	static void invokeCallback(NextpeerFacebookSession session) {
		if (mInstance != null) {
			final OnFacebookRequestFinished callback = mInstance.mLastCallback;
			mInstance.mLastCallback = null;

			if (callback != null) {
				if (session != null) {
					callback.onSucess(session);
				}
				else {
					callback.onFailure();
				}
			}
		}
	}
}
