1.6.10
======

* Bug fixes.

1.6.9
=====

* Bug fixes and usability improvements.
* Removed welcome banner from the SDK.

1.6.8
=====

* __Minimum supported iOS version is now 5.1.1!__
* arm64 support added - __please see our [arm64 guide](https://developers.nextpeer.com/docs/view/arm64) for transition instructions__!

1.6.7
=====

* UDP (unreliable) communication now also transmits directly to the other devices. Will use a local network to transmit whenever possible.


1.6.6 (internal version, not released publicly)
=====

1.6.5 (internal version, not released publicly)
=====

1.6.4
=====

* Server communication improvements.

1.6.3
=====

* Added leaderboards button in the dashboard.

1.6.2
=====

* Added information about all the tournament participants to NPTournamentStartDataContainer (player IDs, names, avatars).
* Added player ID property to NPGamePlayerContainer, that keeps information about the current user.

1.6.1
=====

* Bugfix - ranks would be displayed incorrectly in a certain scenario in ranking display
  view.

1.6.0
=====

* Introduced in-game ranking display, which replaces the old in-game notifications,
  which are now deprecated.
* Added tournament status updates, to track player scores and positions during a
  tournament. See -[NPNotificaitonDelegate nextpeerDidReceiveTournamentStatus:].

1.5.5
=====

* Fixed UI issues in iOS 7 when compiled with SDK 7.0.

1.5.4
=====

* Added UDP support (see +[Nextpeer unreliablePushDataToOtherPlayers:] in Nextpeer+Tournament.h and -[NPTournamentDelegate nextpeerDidReceiveUnreliableTournamentCustomMessage:] in NPTournamentDelegate.h).

1.5.3
=====

* **Minimum supported version is now iOS 5.0!**
* **armv6 no longer supported!**
* Fixes for the upcoming iOS 7.
* Fixed rare race condition which could cause disconnections from server.

1.5.2
=====

* Fixed rare crash bug on sudden disconnection from server.
* Now 100% accepted by the Apple Review Team!

1.5.1
=====

* Removed all usage of OpenUDID.

1.5.0
=====

* Now supporting iOS 7.
* Addressed Apple privacy concerns.

1.4.17
======

* Fixed another issue with webserver communication level.

1.4.16
======

* Fixed an issue with server communication.

1.4.15
======

* Fixed minor integration issue with 3rd party libraries.

1.4.14
======

* Fixed integration issue with external Facebook library.
* Fixed Game Center integration issue.

1.4.13
======

* Fixed rare crash in “loading game” screen.
* Fixed orientation issue in iPad-only resource bundle and iOS 5.

1.4.12
======

* Minor bug fixes, including a rare server disconnection issue when trying to start a tournament.

1.4.11
======

* Minor performance improvements to the image cache system and updating some web url paths.

1.4.10
======

* **Minimum supported iOS version has increased to 4.3!**
* Integrated the new Facebook SDK. **The previous Facebook SDK will stop working in June!**
* Stability bug fixes in case of network issues.

1.4.9
=====

* Bug fix: when the device is disconnected during a tournament for any reason, the player is notified and the tournament ends gracefully.