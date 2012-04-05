Aviary iOS SDK Setup Guide
==========================

Contents
--------

* [Overview](#overview)
	* [Prerequisites](#prerequisites)
	* [Package Contents](#package-contents)
* [Quick Start](#quick-start)
	* [Setup](#setup)
	* [Basic Usage](#usage)
* [High Resolution](#high-resolution)
	* [Example](#high-resolution-example)
* [Customization](#customization)
	* [Tool Selection and Ordering](#tool-selection-and-ordering)
	* [Colors](#color-customization)
	* [Example](#customization-example)

<a name="overview"></a>
Overview
--------

This document will guide you through the process of integrating the Aviary iOS SDK into your app, as well as configuring its interface and managing its resources.

<a name="prerequisites"></a>
### Prerequisites

In order to follow this guide, you must have the iOS 5.0 SDK and Xcode 4.2 installed on your system. For the latest versions, please visit Apple's [iOS Dev Center](http://developer.apple.com/devcenter/ios/).

**Build time requirements**

In order to use the Aviary SDK, you must be using the latest version of Apple's LLVM compiler. You should not have a problem if you're using a fresh install of Xcode 4.2+, which uses this compiler by default. However, if you are working on an older project, or you have upgraded from an older version of Xcode, make sure you're not using GCC.

**Run time requirements**

The minimum iOS version supported by the SDK is iOS 4.0. The many reasons for this choice include our use of ARC ([Automatic Reference Counting](http://developer.apple.com/library/ios/#releasenotes/ObjectiveC/RN-TransitioningToARC/Introduction/Introduction.html)) and our reliance on a number of Apple frameworks and libraries which require iOS 4, including [Accelerate](http://developer.apple.com/library/ios/#documentation/Accelerate/Reference/AccelerateFWRef/_index.html) and [libdispatch](http://libdispatch.macosforge.org/).

<a name="package-contents"></a>
### Package Contents

The SDK consists of a static library, Objective-C header files, and one or more resource bundles containing configuration files and images. The static library is a universal binary for use on iOS device and simulator architectures (armv6/7 and i386).

	AviarySDK/
	|-- Headers/
	|   |-- AFPhotoEditorController.h
	|-- Resources/
	|   |-- AviarySDKResources.bundle
	|-- libAviarySDK.a
	
Note: you can view the contents of the `.bundle` files we distribute. In general, we do not recommend or support modifying their contents.

<a name="quick-start"></a>
Quick Start
-----------

<a name="setup"></a>
### Setup

In order to use the SDK in an existing app, you must do the following:

0. **Project setup**

	Make sure you're running Xcode 4.2+ and compiling with Apple's LLVM compiler (3.0+).

1. **Add files**
	
	Copy the AviarySDK folder into your project (select "Create groups for any added folders" if needed).

2. **Link against libraries**

	Check your target's "Link Binary With Libraries" build phase. Make sure your app is being linked against `libAviarySDK.a`.
	
	Link against the following libraries and frameworks:

		Foundation.framework
		UIKit.framework
		CoreGraphics.framework
		QuartzCore.framework
		Accelerate.framework
		StoreKit.framework
		libz.1.2.5.dylib
		libsqlite3.0.dylib
		CoreData.framework

4. **Copy resources**

	Make sure `AviarySDKResources.bundle` is included in your target's "Copy Bundle Resources" build phase.

5. **Add linker flags**

	Update your target's (or project's) build settings to include the following "Other Linker Flags:"
		
		-ObjC -all_load -fobjc-arc
		
	Note: `-fobjc-arc` is only required if you are targeting iOS 4.x.

6. **Import headers**

	Include the following line to make the library available to your code:

		#import "AFPhotoEditorController.h"

<a name="usage"></a>
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

<a name="high-resolution"></a>
## High Resolution

The iOS SDK now offers the ability to produce output images with resolutions up to 3 megapixels (approximately 3 times larger than the former maximum output resolution). Two new utility classes have been added in order to support this functionality: `AFPhotoEditorSession` and `AFPhotoEditorContext`.

### AFPhotoEditorSession

Each instance of AFPhotoEditorController creates a session object upon initialization, which can be accessed via the readonly `session` property:

	AFPhotoEditorController *photoEditor = [[AFPhotoEditorController alloc] initWithImage:image];
	
	AFPhotoEditorSession *session = [photoEditor session];
	
A session object is a little like a file handle, in that it can be in either of two states: open or closed. A session is open when the SDK is initialized, and closed when the user presses the "Done" or "Cancel" button in the user interface.

*Note*: If you intend to use an AFPhotoEditorController's session instance, be sure to obtain a reference to the session before the controller is deallocated.

Session objects can be used to create instances of `AFPhotoEditorContext` (see below), which can be used to replay the session onto an input image.

### AFPhotoEditorContext

A photo editor context is an object that can be used to "replay" an editing session onto an input image. A context can be created from an instance of `AFPhotoEditorSession` with a maximum output size:

	AFPhotoEditorContext *context = [session createContextWithSize:CGSizeMake(1500, 1500)];
	
The line above creates a context that can render the session onto an input image at full resolution if the dimensions of the input image are less than or equal to 1500px on each side and the input image is no larger than 3 megapixels. If the image is larger than this size, the output image will be downscaled to fit  according to the aspect ratio of the input image. To remove restrictions on dimensions, either pass `CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX)` as the size parameter, or use `-[AFPhotoEditorSession createContext]`.

Once you have created a context from a session object, you can use it to render the session onto an input image like so:

	[context renderInputImage:image completion:^(UIImage *result) {
		// Handle the result image here.
	}];

If the context is created from an open session (i.e. after initializing an `AFPhotoEditorController` but before displaying it) and `-renderInputImage:completion:` is called, the context will render operations onto the image in the background as the user applies them in the SDK (by pressing the "Apply" button).

The completion block you supply to the method above will execute regardless of whether or not the user presses the "Cancel" button. If the user successfully completed his or her session, the `UIImage` passed to the completion block will be the rendered image. If the user cancels the SDK, the `UIImage` passed to the block will be `nil`.

Some things to note about using contexts:

1. We recommend choosing a maximum output resolution that suits the purposes of your application to provide the best experience for your users.

2. Processing large images can consume a lot of memory and time. It may be necessary to free up resources and/or display an activity indicator while a context is executing.

3. To calculate the approximate maximum amount of memory a context could use, multiply the dimensions of the output size and multiply the result by 4. For example, a context with a maximum output size of 1500x1500 will consume approximately 9mb of memory for the processing duration.

<a name="high-resolution-example"></a>
### Example

Below is some sample code for rendering a user session at the maximum supported output resolution:

	AFPhotoEditorController *photoEditor = [[AFPhotoEditorController alloc] initWithImage:image];

	// Capture the user's session and store it in an array
    __block AFPhotoEditorSession *session = [photoEditor session];
    [[self sessions] addObject:session];
    
    // Create a context with the maximum output resolution
    AFPhotoEditorContext *context = [session createContext];
    
    [context renderInputImage:image completion:^(UIImage *result) {
    	// `result` will be nil if the session is canceled, or non-nil if the session was closed successfully and rendering completed
    	[[self sessions] removeObject:session];
    }];


<a name="customization"></a>
## Customization

The editor can be customized at runtime by passing options to the `-initWithImage:options:` method (which is also the designated initializer of `AFPhotoEditorController`). This section describes valid keys and values that may be passed in a dictionary to the second parameter of this method. All of the valid options keys are instances of `NSString`. More information can be found in `AFPhotoEditorControllerOptions.h`.

<a name="tool-selection-and-ordering"></a>
### Tool Selection and Ordering

* `kAFPhotoEditorControllerToolsKey`

	 This key allows developers to customize the visibility of, and order in which tools appear in the SDK interface. A valid value for this key is a NSArray containing NSString instances whose values match the constants below. The order of the constants below also represents the default tool order, when this option is unspecified.
	 
	 	kAFEnhance      /* Enhance */
		kAFEffects      /* Effects */
		kAFOrientation  /* Orientation */
		kAFCrop         /* Crop */
		kAFBrightness   /* Brightness */
		kAFContrast     /* Contrast */
		kAFSaturation   /* Saturation */
		kAFSharpness    /* Sharpness */
		kAFDraw         /* Draw */
		kAFText         /* Text */
		kAFRedeye       /* Redeye */
		kAFWhiten       /* Whiten */
		kAFBlemish      /* Blemish */
		
<a name="color-customization"></a>
### Colors

The iOS SDK now provides the ability to override the default colors for the following properties (from `AFPhotoEditorStyle.h`):

	@property (...) UIColor *backgroundColor;
	@property (...) UIColor *accentColor;
	
	@property (...) UIColor *topBarBackgroundColor;
	@property (...) UIColor *topBarTextColor;
	@property (...) UIColor *topBarLeftButtonTextColor;
	@property (...) UIColor *topBarLeftButtonBackgroundColor;
	
	@property (...) UIColor *buttonIconColor;
	@property (...) UIColor *buttonTextColor;
	
	@property (...) UIColor *pageControlUnselectedColor;

See the [sample code below](#customization-example) for an example of full customization.

### Color Guidelines

Here are some important notes for customizing colors:

1. In general, choosing colors that closely resemble the SDK defaults (i.e. a light background color and darker accent color) will produce the best results.

2. All customization properties should be set after initializing and *before displaying* the photo editor. Modifying these properties after displaying the editor may result in undefined behavior.

3. For best results, all colors should be in the *device RGB color space*. If you are unsure what this means, use `-[UIColor colorWithRed:green:blue:alpha:]` to create your colors. For more information on color spaces, see the [UIColor class reference](http://developer.apple.com/library/ios/#documentation/uikit/reference/UIColor_Class/Reference/Reference.html) and [Quartz 2D Programming Guide](https://developer.apple.com/library/ios/#documentation/graphicsimaging/conceptual/drawingwithquartz2d/dq_color/dq_color.html#//apple_ref/doc/uid/TP30001066-CH205-TPXREF101).

<a name="customization-example"></a>
### Example

The code sample below illustrates how to pass options to a controller instance on initialization, and provides an example of full color customization via `AFPhotoEditorStyle`.

	- (void)displayEditorForImage:(UIImage *)imageToEdit
	{
		// Only display the Enhance, Effects, Orientation, Crop and Draw tools
		NSArray *tools = [NSArray arrayWithObjects:kAFEnhance, kAFEffects, kAFOrientation, kAFCrop, kAFDraw, nil];
		
		AFPhotoEditorController *editorController = [[AFPhotoEditorController alloc] initWithImage:imageToEdit options:[NSDictionary dictionaryWithObject:tools forKey:kAFPhotoEditorControllerToolsKey]];
		
		[editorController setDelegate:self];
		
		AFPhotoEditorStyle *style = [editorController style];
		
		UIColor *backgroundColor = [UIColor colorWithRed:0.5 green:0.5 blue:0.5 alpha:1.0];
		UIColor *foregroundColor = [UIColor colorWithRed:1.0 green:1.0 blue:1.0 alpha:1.0];
		UIColor *accentColor = [UIColor colorWithRed:204/255.0 green:102/255.0 blue:103/255.0 alpha:1.0];
		
		[style setBackgroundColor:backgroundColor];
		[style setAccentColor:accentColor];
		
		[style setTopBarBackgroundColor:backgroundColor];
		[style setTopBarTextColor:foregroundColor];
		[style setTopBarLeftButtonBackgroundColor:backgroundColor];
		[style setTopBarLeftButtonTextColor:foregroundColor];
		
		[style setButtonIconColor:foregroundColor];
		[style setButtonTextColor:foregroundColor];
		
		[self presentModalViewController:editorController animated:YES];
	}
