Aviary iOS SDK Setup Guide
==============================

Contents
--------

* [Overview](#overview)
	* [Prerequisites](#prerequisites)
	* [Download & Support](#download-support)
	* [Package Contents](#package-contents)
* [Quick Start](#quick-start)
	* [Setup](#setup)
	* [Basic Usage](#basic-usage)
* [Plugin Selection](#plugin-selection)
	* [Run-time selection](#run-time)
	* [Compile-time selection](#compile-time)
* [Interface Customization](#customization)
	* [Colors and Background Images](#colors-images)
		* [Colors](#colors)
		* [Background Images](#background-images)
	* [Buttons](#buttons)
    	* [iPad Interface Options](#ipad)

<a name="overview"></a>
Overview
--------

This document will guide you through the process of integrating the Aviary Feather iOS SDK into your app, as well as customizing its interface and managing its resources.

<a name="prerequisites"></a>
### Prerequisites

In order to follow this guide, you must have the iOS 4.3 SDK (or newer) and Xcode 4 installed on your system. For the latest versions, please visit Apple's [iOS Dev Center](http://developer.apple.com/devcenter/ios/).

<a name="download-support"></a>
### Download

Visit [our Github repository](https://github.com/AviaryInc/Mobile-Feather-SDK-for-iOS) to get the latest copy of the SDK, and to stay up to date with future releases.

### Support & Feedback

If you encounter any bugs, report them using [our repository's issue tracker](https://github.com/AviaryInc/Mobile-Feather-SDK-for-iOS/issues) to ensure a quick response.

If there's a feature you'd like to see in the SDK that isn't currently available, please post it on [our feedback page](/mobile-feedback).

<a name="package-contents"></a>
### Package Contents

The SDK consists of a static library, Objective-C header files, and one or more resource bundles containing configuration files and images. The static library is a universal binary for use on iOS device and simulator architectures (armv6/7 and i386).

	AviarySDK/
	|-- Headers/
	|   |-- AFFeatherController.h
	|   |-- AFFeatherConstants.h
	|-- Resources/
	|   |-- AviarySDK-Core.bundle
	|   |-- AviarySDK-Plugins.bundle
	|-- libAviarySDK-universal.a
	
Note: you can view the contents of the `.bundle` files we distribute. In general, we do not recommend modifying their contents, with the exception of `AviarySDK-Plugins.bundle` (see below).

<a name="quick-start"></a>
Quick Start
-----------

<a name="setup"></a>
### Setup

In order to use the SDK in an existing app, you must do the following:

1. **Add files**
	
	Copy the SDK folder into your project (select "Create groups for any added folders").

2. **Link against libraries**

	Check your target's "Link Binary With Libraries" build phase. Make sure your app is being linked against `libAviarySDK-universal.a`.
	
	Link against the following frameworks (in addition to `Foundation.framework` and `UIKit.framework`):

		QuartzCore.framework
		CoreGraphics.framework
		CoreText.framework

4. **Copy resources**

	Make sure `AviarySDK-Core.bundle` and `AviarySDK-Plugins.bundle` are included in your target's "Copy Bundle Resources" build phase.

	Note: you may modify the contents of `AviarySDK-Plugins.bundle` by removing individual plugin bundles you don't want to use in your app. For example, if you don't plan to use the Stickers plugin, you can remove `AviarySDK-Stickers.bundle` from the plugins bundle to save space in your app package.

5. **Add linker flags**

	Update your target's (or project's) build settings to include the following "Other Linker Flags:"
		
		-ObjC -all_load

6. **Import headers**

	Include the following line to make the library available to your code:

		#import "AFFeatherController.h"

<a name="basic-usage"></a>
### Basic Usage

The simplest way to use the SDK is to create and display an instance of `AFFeatherController` (a `UIViewController` subclass). You should present it modally, like so:

	- (void)displayEditorForImage:(UIImage *)image
	{
		AFFeatherController *featherController = [[[AFFeatherController alloc] initWithImage:imageToEdit] autorelease];
		[featherController setDelegate:self];
		[self presentModalViewController:featherController animated:YES];
	}

At minimum, you should implement the following `AFFeatherDelegate` methods in your view controller:

	- (void)feather:(AFFeatherController *)featherController finishedWithImage:(UIImage *)image
	{
		// Handle the result image here
	}
	
	- (void)featherCanceled:(AFFeatherController *)featherController
	{
		// Handle cancelation here
	}

You don't need to worry about dismissing the `AFFeatherController` in these delegate methods.

<a name="plugin-selection"></a>
Plugin Selection
----------------

You may select which plugins are available to the user, either at compile time or at run time.

<a name="run-time"></a>
### Run-time selection

To control which plugins are displayed in the SDK's interface at run time, use the following method to initialize the `AFFeatherController` instance:

	- (id)initWithImage:(UIImage *)image andTools:(NSArray *)tools
	
`tools` should be an array of top-level plugin constants, which are defined in `AFFeatherConstants.h`. For example, here is an example of initializing a controller to only display the Effects, Crop, Rotate and Flip modules:

	- (void)displayEditorForImage:(UIImage *)image
	{
		NSArray *tools = [NSArray arrayWithObjects:kAFEffects, kAFCrop, kAFRotate, kAFFlip, nil];
		AFFeatherController *featherController = [[[AFFeatherController alloc] initWithImage:image andTools:tools] autorelease];
		[featherController setDelegate:self];
		[self displayModalViewController:featherController animated:YES];
	}

<a name="compile-time"></a>
### Compile-time Selection

To control which plugins are available to your app at compile time, you may choose to modify the contents of `AviarySDK-Plugins.bundle`. This bundle contains a separate bundle for each plugin; removing a plugin's bundle will omit its resources from your app, and will prevent the plugin's code from loading.

Note: if you remove a plugin's resource bundle, you will not be able to load it at run time, even when using the run-time selection method above.

<a name="customization"></a>
Interface Customization
-----------------------

To make our interface look more at home in your app, the SDK offers basic interface customization capabilities, including changing the colors of various elements on screen, as well as the ability to provide entirely custom images and buttons.

In general, customizations are implemented in the following ways:

1. Setting attributes after initializing the controller, but before displaying it to the user
2. Implementing one or more customization-related delegate methods

See below for details.

<a name="colors-images"></a>
### Colors and Background Images

You may set the tint color or background image of any object that responds to the `AFInterfaceElement` protocol, defined as follows:

	@protocol AFInterfaceElement <NSObject>
	
	@required
	@property (nonatomic, retain) UIColor *tintColor;
	@property (nonatomic, retain) UIImage *backgroundImage;
	
	@end
	
The `AFFeatherController` class includes the following properties that respond to this protocol:

	// The title bar (at the top of the screen)
	@property (...) id<AFInterfaceElement> topBar;
	
	// The button bar (at the bottom of the screen)
	@property (...) id<AFInterfaceElement> bottomBar;
	
	// The "parameters" bar (at the bottom of the screen when a plugin is active):
	@property (...) id<AFInterfaceElement> paramsBar;

<a name="colors"></a>
#### Colors

You may set the `tintColor` property to a `UIColor` object in the device RGB color space (i.e. as returned by the `CGColorSpaceCreateDeviceRGB()` function). The behavior of this property when used with a color object in another color space, for example one created with UIColor's `colorWithPatternImage:` method, is undefined. Use the `backgroundImage` property to apply your pattern image instead.

<a name="background-images"></a>
#### Background Images

The `backgroundImage` property allows background images and textures to be applied to different views in the SDK. In most cases, it is implemented by using `+[UIColor colorWithPatternImage:]`, and setting the resulting color to the `backgroundColor` property of a view, with the following exceptions:

* The title bar (accessed via AFFeatherController's `topBar` property) draws the image within its bounds, stretching it instead of tiling.
* `UIButton` instances responding to the `AFFeatherPluginButton` protocol, which pass the image to UIButton's `-setBackgroundImage:forState:` with `UIControlStateNormal` as the second argument.

The `backgroundImage` and `tintColor` properties may be used simultaneously, although a full alpha `tintColor` will obscure the background image. You may want to experiment with the alpha channel, or disable a view's `tintColor` entirely by setting it to `[UIColor clearColor]`. Again, there is an exception for `topBar`: setting a `backgroundImage` will obscure the `tintColor` of the bar, although its buttons will be tinted.

All tint colors and background images should be set after initializing the `AFFeatherController`, but **before** displaying it to the user.

<a name="buttons"></a>
### Buttons

You may customize the appearance of the plugin buttons displayed at the bottom of the screen by implementing the following delegate method:

	- (UIButton *)feather:(AFFeatherController *)featherController buttonForPlugin:(id<AFFeatherPlugin>)plugin
	
The `plugin` parameter provides access to some useful information about each plugin, including:

* `pluginId` - its identifier, as defined in `AFFeatherConstants.h` (e.g. `kAFRedeye`)
* `localizedName` - its localized name (e.g. "Redeye"); currently English-only
* `icon` - a UIImage representation of the default icon (foreground image)
* `button` - a reference to the default button instance

Note in particular the `button` property. This is the default button instance. Returning this object unchanged will result in the same behavior as leaving this method unimplemented. Alternatively, you may use the button's `tintColor` property to assign it a tint color.

Returning your own UIButton instance will enable you to more fully customize the look and feel of the interface, with one minor caveat: the button you provide may be resized. Be sure to take this into account when creating your buttons.

Here is a partial example implementation of this method:

	- (UIButton *)feather:(AFFeatherController *)controller buttonForPlugin:(id<AFFeatherPlugin>)plugin
	{
		UIButton *button = [plugin button];
		if ([[plugin pluginId] isEqualToString:kAFEffects]) {
			// Set up the effects button
		} else {
			// Set up other buttons
		}
		return button;
	}

<a name="ipad"></a>
### iPad Interface Options

By default, the interface provided by the `AFFeatherController` will match the form factor of the current device. For example, if the app is running on an iPad, the default behavior of the SDK will be to display an interface that makes use of the entire screen. However, iPad app developers may want to use the iPhone/iPod interface instead (for example, presenting the `AFFeatherController` within a `UIPopoverController`). As of version 1.2.0, the following init method allows you to choose between the two:

    - (id)initWithImage:(UIImage *)image andTools:(NSArray *)tools andUserInterfaceIdiom:(UIUserInterfaceIdiom)idiom;
    
Currently, there are only two possible values for `idiom`:

    UIUserInterfaceIdiomPhone
    UIUserInterfaceIdiomPad

The former will cause the interface to match the screen dimensions of iPhone/iPod devices, while the latter will display an interface tailored for the iPad. Note: the iPad interface should only be displayed within apps running on iPad devices and the iPad simulator. Displaying the iPad interface on other devices may result in undefined behavior.

If you want to display the default tool set, use the `AFDefaultTools()` function defined in `AFFeatherConstants.h`. For example:

    AFFeatherController *controller = [[[AFFeatherController alloc] initWithImage:anImage andTools:AFDefaultTools() andUserInterfaceIdiom:UIUserInterfaceIdiomPhone] autorelease];
