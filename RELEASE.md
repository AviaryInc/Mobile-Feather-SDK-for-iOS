# Aviary iOS SDK Release Notes

Subscribe to updates: [RSS](https://github.com/AviaryInc/Mobile-Feather-SDK-for-iOS/commits/master.atom) | [Twitter](http://twitter.com/aviarychangelog)

## Version 2.6.0 - January 28, 2013

IMPORTANT: The Aviary iOS SDK will no longer be distributed via GitHub, please visit [http://www.aviary.com/ios](http://www.aviary.com/ios) to download the latest version. Starting with v2.6.0 the Aviary iOS SDK will no longer support iOS 4.3. If your app supports iOS 4.3, you should not update to v2.6.0 as it may result in crashes for your iOS 4.3 users. Release v2.5.8 is the last version to support iOS 4.3. Please contact us if you need a copy.

* Overhauled Effects and Stickers tools with completely redesigned UI
* Updated default effects: effects are now more subtle and generally usable, based on your feedback
* Added brand new Frames Tool
* Improved the Text and Meme tools to support multiple lines
* Improved performance
* Due to lack of partner demand, we've removed support for landscape mode on the iPhone and iPod Touch for this release. If your integration relies on landscape mode, we suggest you do not update to this version and contact us to discuss your options.

---

## Version 2.5.8 - January 22, 2013

IMPORTANT: v2.5.8 is the last version of the Aviary iOS SDK which will support iOS 4.3+. Every new release starting with the upcoming v2.6 will require iOS 5.0+. If your app supports iOS 4.3, you should not update to v2.6+ as it may result in crashes for your iOS 4.3 users.

* iOS 4 bug fixes

---

## Version 2.5.7 - January 18, 2013

* iOS 4 bug fixes

---

## Version 2.5.6 - January 2, 2013

* iOS 4 bug fixes, including a crash in the text tool
* Fixed a bug preventing RTL languages (Hebrew, Arabic) from working properly in the text tool
* Fixed some Meme tool bugs related to very small images
* New customization option: remove shadows from toolbar buttons (Premium partners only)

---

## Version 2.5.5 - November 16, 2012

* Fixed a potential crash in some apps caused by the Meme tool
* Fixed customization API validation for boxed booleans
* Fixed typo in customization docs

---

## Version 2.5.4 - November 12, 2012

* Fixed missing translation for "Enter text here" in the Text tool
* Fixed an issue in the Whiten tool causing it to turn images black
* Fixed editor.bottomBarButtonIconColor in iOS 4.3
* Added "Next" as a right navigation button text preset option

---

## Version 2.5.3 - November 1, 2012

* Fixed an issue causing a crash when pressing the Done button before the image loads
* Fixed output UIImage `scale` and `size` property values
* Improved UI responsiveness while loading the SDK for the first time

---

## Version 2.5.2 - October 29, 2012

* Fixed issue causing AFPhotoEditorController's `style` attribute to always return nil
* Fixed crash in the Meme tool caused by a missing resource file

---

## Version 2.5.1 - October 23, 2012

* Fixed a bug preventing customization of the SDK's navigation bar text color

---

## Version 2.5.0 - October 22, 2012

### Changes

* Added tons of new customization options for our premium partners! Email us at partners@aviary.com if you're interested in deeper customization for your integration.
* New in-app purchase for our premium partners: Mustache sticker pack
* Added "Restore" button for screens with in-app purchases
* iPhone 5 / iOS 6 optimization
* It's now possible to disable localization
* Customizable crop presets (and specify whether or not you want users to be able to invert them)
* Bumped editing resolution up to 1024x1024
* Added GL support for faster effects and enhance filters processing and much faster hires processing for all tools.
* Enabled zoom for more tools
* Added Meme tool
* Stickers can now be dragged onto the photo

### Updating

Version 2.5.0 is a big update to the SDK, including GPU-based image processing, a new tool, and many improvements to existing user and developer-facing features. To support these great additions, we've added a couple of framework dependencies, namely:

    OpenGLES.framework
    CoreText.framework

For the full list of frameworks, see README.md.

In order to continue evolving the SDK, we've also deprecated a few high-res API methods in `AFPhotoEditorSession` and `AFPhotoEditorContext`:

    // AFPhotoEditorSession.h
    - (AFPhotoEditorContext *)createContext DEPRECATED_ATTRIBUTE;
    - (AFPhotoEditorContext *)createContextWithSize:(CGSize)size DEPRECATED_ATTRIBUTE;
    
    // AFPhotoEditorContext.h
    - (void)renderInputImage:(UIImage *)image completion:(void (^)(UIImage *result))completion DEPRECATED_ATTRIBUTE;

We've provided new methods to better support GPU-based image processing, one of the biggest features introduced in this update. These deprecated methods will continue to provide CPU-based processing for now, but expect them to be removed in 3.0.

This version also includes a completely new, dynamic visual customization and configuration API, provided via class methods in `AFPhotoEditorCustomization`. We've wired up the old visual customization API in `AFPhotoEditorStyle` to use the new one, so it should continue to function as expected.

If you run into any problems with the upgrade, let us know!

---

## Version 2.4.4.2 - October 4, 2012

* Moved downloaded content and data files to /Library/Application Support/App Name/AviaryContentPacks[.sqlite]

---

## Version 2.4.4.1 - September 28, 2012

* Fixed missing icons in slider-based tools (Brightness, Contrast, Saturation, Sharpness)
* Fixed an issue causing incorrect high-res images edited using the Brightness tool to be incorrect in rare situations

---

## Version 2.4.4 - September 17, 2012

* Improved the high-res rendering speed of the Orientation tool

---

## Version 2.4.3 - September 13, 2012

* Added armv7s architecture
* Fixed iOS 4.0 compatibility issue
* Updated language translations

---

## Version 2.4.2 - July 17, 2012

* New: straighten photos in the Orientation tool!
* Fixed a potential crash in Effects/Stickers tools
* Fixed bugs in the Crop UI

---

## Version 2.4.0 - June 13, 2012

* New redeye, whiten and blemish tool implementations
* New brightness and contrast tool implementations
* New B&W and Sepia effects
* New tool icons and improved editor visuals
* Fixed a crash related to the high-res API
* Added the ability to set valid interface orientations via a new runtime option (in AFPhotoEditorControllerOptions.h)
* Many other bug fixes and improvements

---

## Version 2.3.6 - May 10, 2012

* Fixed an issue where Stickers archives in the user's Documents directory caused apps to be rejected by Apple. These archives now include an extended attribute to prevent them being backed up by iCloud.

---

## Version 2.3.5 - April 5, 2012

* Resolved a duplicate symbol linker error for apps that include MiniZip

---

## Version 2.3.4 - April 2, 2012

This is the first public release of 2.3.x. We've added a few new features and fixed a number of issues since the last 2.2.x release, all of which are documented below. Enjoy!

---

## Version 2.3.3 - March 29, 2012

* Updated analytics code

---

## Version 2.3.2 - March 26, 2012

* Improved memory conservation: memory for high-res output is only allocated if needed (it is not allocated if the user does not perform any actions in the editor).

* The image passed to an `AFPhotoEditorContext` render call will now be `nil` if the user does nothing in the editor (instead of a non-nil, but empty `UIImage` object). The same behavior occurs if the user taps "Cancel" in the editor.

* Fixed a minor bug in the "Auto" action inside the  Enhance tool.

* Added sound to the Brightness, Contrast and Saturation tools (the same sound played by the iOS keyboard; the sound will play if the user has "Keyboard Clicks" enabled in the Settings app).

---

## Version 2.3.1 - March 23, 2012

* Minor changes and bug fixes

---

## Version 2.3.0 - March 22, 2012

* Added three new classes:

		AFPhotoEditorStyle
		AFPhotoEditorSession
		AFPhotoEditorContext

	These classes allow developers to control the appearance of an `AFPhotoEditorController` instance, obtain high-resolution output from the editor, and more. See the "High Resolution" and "Customization" sections in the README for more information.

* Added the "Viewfinder" effect pack for in-app purchase partners.
* Bug fixes and other incremental improvements.

---

## Version 2.2.4 - March 21, 2012

* Fixed a crash triggered by multiple launches of the editor.

---

## Version 2.2.3 - March 20, 2012

* Added the Viewfinder pack for in-app purchase.

---

## Version 2.2.2 - March 20, 2012

* Fixed missing in-app purchase reporting.

---

## Version 2.2.1 - February 28, 2012

* Fixed UI-related bug affecting in-app purchase partners.

---

## Version 2.2.0 - February 28, 2012

* Added the Stickers tool, giving users the ability to add stickers to their photos! The Original pack is available to all users free of charge.
* Added infrastructure for current and future downloadable content packs.
* Updated the Night function in the Enhance tool.

**Note**: this update adds a dependency on `CoreData.framework`. Information about downloadable content packs, as well as information about purchases if in-app purchase is enabled, is stored in a database in the app's user documents directory.

---

## Version 2.1.6 - February 14, 2012

* Fixed the interaction between our analytics library and in-app purchase receipts

---

## Version 2.1.5 - February 10, 2012

* Fixed memory leaks

---

## Version 2.1.4 - February 9, 2012

* Added a missing analytics call in Effects tool

---

## Version 2.1.3 - February 2, 2012

* Fixed a potential crash when restoring in-app purchases

---

## Version 2.1.2 - February 2, 2012

* Disabled analytics debug logging
* Updated translations

---

## Version 2.1.1 - February 1, 2012

* Updated translations in the Effects tool

---

## Version 2.1 - January 31, 2012

* New feature: in-app purchases for the Effects tool! This feature is disabled by default and only available to select partners. Please contact us at api@aviary.com for more information about selling Effect packs in your app.
* Updated translations
* Updated analytics library
* Minor bug fixes and improvements

**Note**: the addition of in-app purchase functionality and our updated analytics code now requires apps integrating the SDK to link against the following libraries:

* StoreKit.framework
* libz1.2.5.dylib
* libsqlite3.0.dylib

Please update your build settings accordingly.

---

## Version 2.0.1 - January 18, 2012

* Added a new initialization method to `AFPhotoEditorController` allowing selection and reordering of tools in the SDK interface. Please see the "Customization" section of the README for more information.
* Added missing translations in Crop tool.
* Updated Traditional Chinese language files.

---

## Version 2.0 - January 17, 2012

Welcome to the new and improved Aviary editor! This is a ground-up redesign, including a completely new user interface, updated effects, and a few new tools. We'll be following up with new features and bug fixes on a regular basis, so check back soon for updates.

---

## Version 1.3.3 - November 20, 2011

* Fixed a layout bug when using fewer than 15 tools in the iPad interface.

---

## Version 1.3.2 - November 20, 2011

* Minor internal change

---

## Version 1.3.1 - November 18, 2011

* Minor bug fixes and improvements
* Changed the text of "Save" to "Done"

---

## Version 1.3.0 - October 28, 2011

The Meme tool has been restored as a beta feature. It is disabled by default, but you can enable it by passing the following constant (defined in `AFFeatherConstants.h`) when creating your `AFFeatherController` instance:

	extern NSString *const kAFMeme;
	
As a result of adding this tool, we have also introduced a dependency on Core Text. Please add this framework to your "Link Binary With Libraries" build phase, **regardless of whether or not you're using the meme tool**:

	CoreText.framework
	
We may periodically release more of these beta tools in the future, so stay tuned!

---

## Version 1.2.3 - October 17, 2011

Follow-up fix for the resizing bug affecting images smaller than 960x960.

---

## Version 1.2.2 - October 11, 2011

Fixes a resizing error causing images with certain `imageOrientation` property values to become distorted.

---

## Version 1.2.1 - October 11, 2011

This release aims to resolve a duplicate symbol error encountered when using [MBProgressHUD](https://github.com/jdg/MBProgressHUD) with the Aviary SDK.

---

## Version 1.2.0 - October 10, 2011

This release features many bug fixes and a new (optional) iPad interface. We're also now building against the iOS 5 SDK with Xcode 4.2 GM.

### Features

We've cleaned up the public interface to `AFFeatherController`, and added an init method allowing iPad apps to display an interface tailored to the iPad form factor:

    - (id)initWithImage:(UIImage *)image andTools:(NSArray *)tools andUserInterfaceIdiom:(UIUserInterfaceIdiom)idiom;
    
There are currently two possible values you can pass via the `idiom` parameter:

    UIUserInterfaceIdiomPhone
    UIUserInterfaceIdiomPad
    
Passing the first will initialize the controller with the iPhone interface, while the latter will initialize with the iPad interface. Note: `UIUserInterfaceIdiomPad` will only work correctly on iPad devices.

The standard init methods are still present, and will display the interface associated with the current device's user interface idiom:

    - (id)initWithImage:(UIImage *)image;
    - (id)initWithImage:(UIImage *)image andTools:(NSArray *)tools;

### Bug fixes

A number of issues with 1.1.x have been reported. Here are a few of the changes we've made:

1. Fixed an issue where image orientation was not preserved after applying plugins.
2. Fixed an intermittent crash caused by a zero geometry bug.
3. Fixed a number of substantial memory leaks.

---

## Version 1.1.9 - October 7, 2011

This is a minor update. A much more significant update is coming shortly.

* Built library against the iOS 5 GM SDK with Xcode 4.2
* Fixed a divide by zero error in -calculateMinMaxZoom (Issue #2)

---

## Version 1.1.8 - September 14, 2011

This update includes important fixes related to App Store submission:

* Fixed some internal methods that conflicted with private APIs.
* Updated all targets to allow integration with universal (iPhone/iPad) apps.

---

## Version 1.1.7 - September 12, 2011

The text of the cancellation confirmation dialog has been updated.

---

## Version 1.1.6 - September 12, 2011

This update adds the following methods to the `AFFeatherDelegate` protocol:

	- (BOOL)featherShouldConfirmCancel:(AFFeatherController *)featherController;
	
Implement this method to control whether or not a confirmation dialog is presented to the user upon dismissing the SDK interface without saving.

---

## Version 1.1.5 - September 8, 2011

This update resolves two issues in the 1.1.4 build:

1. Running the Cinematic effect resulted in an all-white image.
2. Applying empty text with the text tool caused a crash.

---

## Version 1.1.4 - September 7, 2011

This update resolves a display issue caused by hiding the status bar.

---

## Version 1.1.3 - August 23, 2011

### New effects

This update adds the following filter effects to the Effects plugin:

* Always Sunny
* Code Red
* Negative

### Modularized plugin resources

This update additionally makes it easier to select which plugins (tools and effects) are enabled in your distribution, at compile time and at run time.

#### Compile time customization

Each plugin has its own bundle, containing resources used only by that individual plugin. These bundles are packaged within `AviarySDK-Plugins.bundle`. For now, the best way to omit a plugin and its resources entirely from your application is to remove that plugin's bundle from `AviarySDK-Plugins.bundle`. We are working on better ways to accomplish this, but if you only want to use a few plugins, simply remove the ones you don't intend to use.

#### Run time customization

A number of constants have been added to `AFFeatherConstants.h`, which correspond to values passed to `AFFeatherController`'s `-initWithImage:andTools:` method, and the `pluginId` property of `AFFeatherPlugin` objects (used in conjunction with the `-feather:buttonForPlugin:` delegate method).

An example of initializing the `AFFeatherController` instance is as follows:

	- (void)displayEditorForImage:(UIImage *)image
	{
		NSArray *tools = [NSArray arrayWithObjects:kAFEffects, kAFCrop, kAFRotate, kAFFlip, nil];
		AFFeatherController *featherController = [[AFFeatherController alloc] initWithImage:image andTools:tools];
		[featherController setDelegate:self];
		[self displayModalViewController:featherController animated:YES];
		[featherController release];
	}

And here is an example of customizing buttons:

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

New plugin ID constants:

	// Top-level plugin constants:

	extern NSString *const kAFBlemish;
	extern NSString *const kAFBlur;
	extern NSString *const kAFBrightness;
	extern NSString *const kAFColors;
	extern NSString *const kAFContrast;
	extern NSString *const kAFCrop;
	extern NSString *const kAFDrawing;
	extern NSString *const kAFEffects;
	extern NSString *const kAFFlip;
	extern NSString *const kAFMeme;
	extern NSString *const kAFRedeye;
	extern NSString *const kAFRotate;
	extern NSString *const kAFSaturation;
	extern NSString *const kAFSharpen;
	extern NSString *const kAFStickers;
	extern NSString *const kAFText;
	extern NSString *const kAFWhiten;

	// Effects plugin constants:

	extern NSString *const kAFAlwaysSunny;
	extern NSString *const kAFAutoEnhance;
	extern NSString *const kAFCinematic;
	extern NSString *const kAFCodeRed;
	extern NSString *const kAFDaydream;
	extern NSString *const kAFHeatwave;
	extern NSString *const kAFIndiglow;
	extern NSString *const kAFNegative;
	extern NSString *const kAFOriginal;

---

## Version 1.1.2 - August 16, 2011

This update mainly provides better interface customization support, particularly for applying images to different interface elements. A new protocol and three new properties have been added to `AFFeatherController`.

It also resolves the presentation animation lag issue introduced in 1.1.0.

### AFInterfaceElement

Future updates to the SDK will provide customization options via this new protocol.

	@protocol AFInterfaceElement <NSObject>
	@required
	@property (...) UIColor *tintColor;
	@property (...) UIImage *backgroundImage;
	@end

AFInterfaceElement objects provide an entry point for customizing different views within the SDK. Three read-only references to objects have been provided in `AFFeatherController.h`:

	@interface AFFeatherController : UIViewController {
		// ...
	}
	// ...
	@property (...) id<AFInterfaceElement> topBar;
	@property (...) id<AFInterfaceElement> bottomBar;
	@property (...) id<AFInterfaceElement> paramsBar;
	// ...
	@end
	
Note that these objects are not necessarily subclasses of `UIView`. They are proxy objects created before their corresponding views in order to support customization prior to displaying the user interface.

### The backgroundImage property

This property allows background images and textures to be applied to different views in the SDK. In most cases, it is implemented by using `+[UIColor colorWithPatternImage:]`, and setting the resulting color to the `backgroundColor` property of a view, **except** for the top bar (`topBar`), which draws the image within its bounds, stretching it instead of tiling.

`backgroundImage` and `tintColor` may be used simultaneously, although a full alpha `tintColor` will obscure the background image. You may want to experiment with the alpha channel, or disable a view's `tintColor` entirely by setting it to `[UIColor clearColor]`. Again, there is an exception for `topBar`: setting a `backgroundImage` will obscure the `tintColor` of the bar, although the buttons will remain tinted.

---

## Version 1.1.1 - August 12, 2011

This update resolves two issues:

* Unnecessary log messages no longer show up in the release build of the SDK.
* The debug slider should no longer appear in the AFFeatherController's view.

There is a known issue that didn't make it into this release, but will be resolved shortly:

* When displaying the AFFeatherController modally, the animation lags. This is a result of color customization support in 1.1 and will be resolved in the next release.

---

## Version 1.1.0 - August 10, 2011

This is a significant update to the Feather iOS SDK, and will require you to change your code slightly.

The following interfaces have changed:

* The `AFWidgetController` class has been renamed to `AFFeatherController`.
* The following changes have been made to the AFFeatherDelegate protocol:
	* Removed `-afFinishedWithImage:` and `-afCanceled`
	* Removed all preexisting interface customization delegate methods
	* Added `-feather:finishedWithImage:` and `-featherCanceled:`
	* Added `-feather:buttonForPlugin:`

Please update your code accordingly. This one-time change is necessary for ongoing improvement of the SDK.

## Interface Customization

### AFFeatherController properties

Several methods have been added to the `AFFeatherController` class to enable customization of the top and bottom bars:

* `-setTitleBarTintColor:`
* `-setPluginBarTintColor:`
* `-setPluginParametersBarTintColor:`

Each method takes one UIColor object as input. The UIColor must be in the device RGB color space--you cannot use a pattern, for example (though we aim to provide this functionality in a future update). You should call these methods after initializing and before displaying the `AFFeatherController` to the user.

### The -feather:buttonForPlugin: delegate method

This method has been added to help support more advanced customization of the Feather interface. Here is the full method signature:

	-(UIButton *)feather:(AFFeatherController *)featherController buttonForPlugin:(id<AFFeatherPlugin>)plugin
	
You should implement this method if you want to customize the buttons at the bottom of the main interface. The `plugin` parameter provides access to some useful information about each plugin, including:

* `pluginId` - its identifier (e.g. "redeye")
* `localizedName` - its localized name (e.g. "Redeye"--currently English only)
* `icon` - a UIImage representation of the default icon
* `button` - a reference to the default button instance

Note in particular the `button` property. This is the default button instance. Returning this object unchanged will result in the same behavior as leaving this method unimplemented. Alternatively, you may use the button's `-setTintColor:` method to assign it a tint color.

Providing your own UIButton instance will enable you to more fully customize the look and feel of the interface, with one minor caveat: the button you provide may be resized. Be sure to take this into account when creating your buttons.

---

## Version 1.0 - August 2011

Initial release.
