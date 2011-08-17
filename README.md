Aviary Feather iOS Setup Guide
==============================

Overview
--------

This document will guide you through the basic process of integrating the Aviary Feather iOS SDK into your app.

For additional information, please check RELEASE.md for the latest release notes.

Prerequisites
-------------

In order to follow this guide, you must have the iOS 4.3 SDK (or newer) and Xcode 4 installed on your system. For the latest versions, please visit Apple's [iOS Dev Center](http://developer.apple.com/devcenter/ios/).

Package Contents
----------------

The SDK consists of a static library, Objective-C header files, and one or more resource bundles containing configuration files and images. The static library is a universal binary for use on iPhone, iPad and iOS Simulator architectures.

	AviarySDK
	├── Headers
	│   └── AFFeatherController.h
	├── Resources
	│   └── AviarySDKResources_iPhone.bundle
	│   └── AviarySDKResources_Stickers.bundle
	└── libAviarySDK-universal.a
	
Note that you can view the contents of the `.bundle` files we distribute, although we do not support modifying their contents.

Quick Start
-----------

### Setup

In order to use the SDK in an existing app, you must do the following:

1. **Add files**
	
	Copy the SDK folder into your project (select "Create groups for any added folders").

2. **Link against libraries**

	Check your target's "Link Binary With Libraries" build phase. Make sure your app is being linked against `libAviarySDK-universal.a`.
	
	Link against the following frameworks (in addition to `Foundation.framework` and `UIKit.framework`):

		QuartzCore.framework
		CoreGraphics.framework

4. **Copy resources**

	Make sure `AviarySDKResources_iPhone.bundle` is included in your target's "Copy Bundle Resources" build phase.

	Include `AviarySDKResources_Stickers.bundle` in your "Copy Bundle Resources" phase if you want to enable the Stickers feature of the SDK. Excluding this bundle will disable Stickers, but will decrease your app's file size.

5. **Add linker flags**

	Update your target's (or project's) build settings to include the following "Other Linker Flags:"
		
		-ObjC -all_load

6. **Import headers**

	Include the following line to make the library available to your code:

		#import "AFFeatherController.h"

### Usage

The simplest way to use the SDK is to create and display an instance of `AFFeatherController` (a `UIViewController` subclass). You should present it modally, like so:

	UIImage *imageToEdit = /* your image here */;
	AFFeatherController *featherController = [[[AFFeatherController alloc] initWithImage:imageToEdit] autorelease];
	[featherController setDelegate:self];
	[self presentModalViewController:featherController animated:YES];

At minimum, you should implement the following `AFFeatherDelegate` methods in your view controller:

	- (void)feather:(AFFeatherController *)featherController finishedWithImage:(UIImage *)image {
		// Handle the result image here
	}
	
	- (void)featherCanceled:(AFFeatherController *)featherController {
		// Handle cancelation here
	}

You don't need to worry about dismissing the `AFFeatherController` in your delegate methods.
