Aviary iOS SDK Setup Guide
==========================

Contents
--------

* Overview
	* Prerequisites
	* Package Contents
* Quick Start
	* Setup
	* Usage

Overview
--------

This document will guide you through the process of integrating the Aviary iOS SDK into your app, as well as configuring its interface and managing its resources.

### Prerequisites

In order to follow this guide, you must have the iOS 5.0 SDK and Xcode 4.2 installed on your system. For the latest versions, please visit Apple's [iOS Dev Center](http://developer.apple.com/devcenter/ios/).

### Package Contents

The SDK consists of a static library, Objective-C header files, and one or more resource bundles containing configuration files and images. The static library is a universal binary for use on iOS device and simulator architectures (armv6/7 and i386).

	AviarySDK/
	|-- Headers/
	|   |-- AFPhotoEditorController.h
	|-- Resources/
	|   |-- AviarySDKResources.bundle
	|-- libAviarySDK.a
	
Note: you can view the contents of the `.bundle` files we distribute. In general, we do not recommend or support modifying their contents.

Quick Start
-----------

### Setup

In order to use the SDK in an existing app, you must do the following:

1. **Add files**
	
	Copy the AviarySDK folder into your project (select "Create groups for any added folders").

2. **Link against libraries**

	Check your target's "Link Binary With Libraries" build phase. Make sure your app is being linked against `libAviarySDK.a`.
	
	Link against the following frameworks (in addition to `Foundation.framework` and `UIKit.framework`):

		CoreGraphics.framework  (Required)
		QuartzCore.framework    (Required)
		Accelerate.framework    (Required)
		CoreImage.framework     (Optional)

4. **Copy resources**

	Make sure `AviarySDKResources.bundle` is included in your target's "Copy Bundle Resources" build phase.

5. **Add linker flags**

	Update your target's (or project's) build settings to include the following "Other Linker Flags:"
		
		-ObjC -all_load -fobjc-arc
		
	Note: `-fobjc-arc` is only required if you are targeting iOS 4.x.

6. **Import headers**

	Include the following line to make the library available to your code:

		#import "AFPhotoEditorController.h"

### Basic Usage

The simplest way to use the SDK is to create and display an instance of `AFPhotoEditorController` (a `UIViewController` subclass). You can present it modally, like so:

	- (void)displayEditorForImage:(UIImage *)imageToEdit
	{
		AFPhotoEditorController *editorController = [[AFPhotoEditorController alloc] initWithImage:imageToEdit];
		[editorController setDelegate:self];
		[self presentModalViewController:editorController animated:YES];
	}
	
You may instead choose to display the controller in other ways, such as by presenting it within a `UIPopoverController` or by manually adding it to the view hierarchy. If you choose to present the controller in such a way, you are responsible for making sure it receives the standard view controller lifecycle methods, including `viewDidLoad`, `viewWillAppear:`, etc. The controller may be displayed at full resolution, or you may display it in a smaller portion of the screen.

At minimum, you should implement the following `AFPhotoEditorControllerDelegate` methods in your presenting view controller:

	- (void)photoEditor:(AFPhotoEditorController *)editor finishedWithImage:(UIImage *)image
	{
		// Handle the result image here
	}
	
	- (void)photoEditorCanceled:(AFPhotoEditorController *)editor
	{
		// Handle cancelation here
	}

You are responsible for dismissing the `AFPhotoEditorController`, which should typically be done in these delegate methods.
