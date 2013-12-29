Nextpeer iOS SDK Setup Guide
==========================

Contents
--------

* [Overview]
	* [Prerequisites]
	* [Package Contents]
* [Quick Start]
	* [Setup]
	* [Basic Usage]
	
Overview
--------

This document will guide you through the process of integrating the Nextpeer iOS SDK into your game.

### Prerequisites

In order to follow this guide, you must have the iOS 5.0 SDK and Xcode 4.4 installed on your system. For the latest versions, please visit Apple's iOS Dev Center (http://developer.apple.com/devcenter/ios/).

**Run time requirements**

The minimum iOS version supported by the SDK is iOS 5.0.

### Package Contents

The SDK consists of a static library, Objective-C header files, and resource bundles containing configuration files and images. The static library is a universal binary for use on iOS device and simulator architectures (armv7/7s and i386).

	Nextpeer SDK/
	|-- Nextpeer.framework/
	|   |-- Headers/
	|   |-- | -- Nextpeer.h
	|   |-- | -- Nextpeer+Social.h
	|   |-- | -- Nextpeer+Tournament.h
	|   |-- | -- Nextpeer+Feed.h
	|   |-- | -- NextpeerDelegate.h
	|   |-- | -- NextpeerSettings.h
	|   |-- | -- NPCurrencyDelegate.h
	|   |-- | -- NPDelegatesContainer.h
	|   |-- | -- NPNotificationContainer.h
	|   |-- | -- NPNotificationDelegate.h
	|   |-- | -- NPSocialContainers.h
	|   |-- | -- NPTournamentContainers.h
	|   |-- | -- NPTournamentDelegate.h
	|   |-- Nextpeer
	|-- Resources/
	|   |-- NPResources_iPad_iPhone_Landscape.bundle
	|   |-- NPResources_iPad_iPhone_Portrait.bundle
	|   |-- NPResources_iPad.bundle
	|   |-- NPResources_iPhone_Landscape.bundle
	|   |-- NPResources_iPhone_Portrait.bundle
	
Quick Start
-----------

### Setup

In order to use the SDK in an existing game, you must do the following:

0. **Project setup**

	Make sure you're running Xcode 4.4+ and compiling with Apple's LLVM compiler (3.0+).

1. **Add files**
	
	Copy the 'Nextpeer.framework' folder into your project (select "Create groups for any added folders" if needed).

2. **Link against libraries**

	Check your target's "Link Binary With Libraries" build phase. Make sure your app is being linked against `Nextpeer.Framework`.
	
	Link against the following libraries and frameworks:
		AdSupport.framework **
		OpenGLES.framework
		CoreText.framework
		Security.framework
		StoreKit.framework
		libz.dylib
		libsqlite3.dylib
		MobileCoreServices.framework
		SystemConfiguration.framework
		CFNetwork.framework
		MessageUI.framework
		QuartzCore.framework
		UIKit.framework
		CoreGraphics.framework
		Foundation.framework

**  Note: AdSupport.framework is not required for Nextpeer integration. However, without this framework certain unique user-based reports will be less accurate

If added, change the AdSupport.framework library from “Required” to “Optional”. This will provide backwards compatibility for pre-iOS 6 targets where the framework does not exist.

4. **Copy resources**

	Select the matching bundle for your game design:
	
	* NPResources_iPhone_Landscape.bundle : For iPhone only games in landscape mode
	* NPResources_iPhone_Portrait.bundle : For iPhone only games in portrait mode
	* NPResources_iPad.bundle : For iPad only games in landscape mode
	* NPResources_iPad_iPhone_Landscape.bundle: For universal (iPad+iPhone) games in landscape mode
	* NPResources_iPad_iPhone_Portrait.bundle: For universal (iPad+iPhone) games in portrait mode

	Make sure the selected bundle is included in your target's "Copy Bundle Resources" build phase.

5. **Add linker flags**

	Update your target's (or project's) build settings to include the following "Other Linker Flags:"
		
		-ObjC -all_load

6. **Import headers**

	Include the following line to make the library available to your code:

		#import "Nextpeer/Nextpeer.h"

### Basic Usage

1. Initialize Nextpeer 
 	In your AppDelegate's applicationDidFinishLaunching place a call to [Nextpeer initializeWithProductKey:andDelegates:].
	* ProductKey is a string obtained by registering your game using the developer dashboard.
	* Delegates is a container object that allows you to provide delegate objects pertaining to specific Nextpeer features.

2. Implementing NextpeerDelegate
	
	* -(void)nextpeerDidTournamentStartWithDetails:
  	This method will be called when a tournament is about to start. You should start the single player level at this point.
  	You can use the passed parameter to get some details on the tournament which is about to be played.
  	
	* -(void)nextpeerDidTournamentEnd
  	This method is invoked whenever the current tournament has finished. In here you can place some cleanup code. 
  	For example, you can use this method to recycle the game scene.

3. Open Nextpeer dashboard
	In your 'Play with Friends' button action method place a call to [Nextpeer launchDashboard].
	
4. Reporting scores
	In tournament, Nextpeer has to track each player score in realtime, hence every time that score has changed you should call:
	[Nextpeer reportScoreForCurrentTournament:]

5. Exit tournament
 	If the user wishes to exit a running tournament (for example back to the game's main menu), invoke the method:
 	[Nextpeer reportForfeitForCurrentTournament]


For more see http://developers.nextpeer.com/documentation/docs.
We love to hear your feedback so feel free to send us email to support@nextpeer.com

Happy gaming!
 Nextpeer team