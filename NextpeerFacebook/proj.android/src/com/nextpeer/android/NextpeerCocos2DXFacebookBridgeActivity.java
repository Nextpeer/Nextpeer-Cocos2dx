package com.nextpeer.android;

import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

import com.facebook.Session;
import com.facebook.Session.NewPermissionsRequest;
import com.facebook.Session.StatusCallback;
import com.facebook.SessionState;
import com.facebook.UiLifecycleHelper;
import com.nextpeer.android.NextpeerFacebookSession;
import com.nextpeer.android.open.NPLog;

public class NextpeerCocos2DXFacebookBridgeActivity extends Activity {
	public static final String ACTION = "com.nextpeer.unity.ACTION";
	public static final String PERMISSIONS = "com.nextpeer.unity.PERMISSION";
	public static final String ACTION_LOGIN = "LOGIN";
	public static final String ACTION_PERMISSIONS = "PERMISSIONS";

	private final StatusCallback mCallback = new FacebookSessionCallback();
	private UiLifecycleHelper mHelper = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		mHelper = new UiLifecycleHelper(this, mCallback);
		mHelper.onCreate(savedInstanceState);

		String action = getIntent().getExtras().getString(ACTION);
		List<String> permissions = Arrays.asList(getIntent().getExtras().getString(PERMISSIONS).split(","));
		NPLog.i("Facebook bridge activity: Starting with action " + action + " and permissions " + permissions);

		if (ACTION_LOGIN.equals(action)) {
			Session.openActiveSession(this, true, permissions, null);
		}
		else if (ACTION_PERMISSIONS.equals(action)) {
			Session session = Session.getActiveSession();
			if (session != null && session.isOpened()) {
				NewPermissionsRequest request = new Session.NewPermissionsRequest(this, permissions);
				session.requestNewReadPermissions(request);
			}
			else {
				NPLog.e("Facebook bridge activity: No active session when requested more permissions");
				NextpeerCocos2DXFacebookBridge.invokeCallback(null);
				finish();
			}
		}
		else {
			NPLog.w("Facebook bridge activity: Unknown action");
			finish();
		}
	}

	@Override
	protected void onResume() {
		super.onResume();
		mHelper.onResume();
	}

	@Override
	protected void onPause() {
		mHelper.onPause();
		super.onPause();
	}

	@Override
	protected void onStop() {
		mHelper.onStop();
		super.onStop();
	}

	@Override
	protected void onDestroy() {
		mHelper.onDestroy();
		super.onDestroy();
	}

	@Override
	protected void onSaveInstanceState(Bundle state) {
		super.onSaveInstanceState(state);
		mHelper.onSaveInstanceState(state);
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		mHelper.onActivityResult(requestCode, resultCode, data);
	}


    private class FacebookSessionCallback implements StatusCallback {
		@Override
		public void call(Session session, SessionState state, Exception error) {
			if (error != null) {
				NPLog.e("Facebook bridge activity: error: " + error.getMessage());
				NextpeerCocos2DXFacebookBridge.invokeCallback(null);
				finish();
				return;
			}

			if (session == null) {
				NPLog.e("Facebook bridge activity: session is null");
				NextpeerCocos2DXFacebookBridge.invokeCallback(null);
				finish();
				return;
			}

			if (state.isClosed()) {
				NPLog.e("Facebook bridge activity: session is closed");
				NextpeerCocos2DXFacebookBridge.invokeCallback(null);
				finish();
				return;
			}

			if (state.isOpened()) {
				NPLog.e("Facebook bridge activity: session opened");
				final String accessToken = session.getAccessToken();
				Set<String> permissions = new HashSet<String>();
				permissions.addAll(session.getPermissions());
				NextpeerCocos2DXFacebookBridge.invokeCallback(new NextpeerFacebookSession(accessToken, permissions));
				finish();
				return;
			}

			// Wait for next event.
		}
    }
}
