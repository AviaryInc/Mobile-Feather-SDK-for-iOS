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
    * [GPU Acceleration](#high-resolution-gpu-acceleration)
	* [Example](#high-resolution-example)
* [Customization](#customization)

<a name="overview"></a>
Overview
--------

This document will guide you through the process of integrating the Aviary iOS SDK into your app, as well as configuring its interface and managing its resources.

<a name="prerequisites"></a>
### Prerequisites

In order to follow this guide, you must have the iOS 6.0 SDK and Xcode 4.5 installed on your system. For the latest versions, please visit Apple's [iOS Dev Center](http://developer.apple.com/devcenter/ios/).

**Build time requirements**

In order to use the Aviary SDK, you must be using the latest version of Apple's LLVM compiler. You should not have a problem if you're using a fresh install of Xcode 4.x, which uses this compiler by default. However, if you are working on an older project, or you have upgraded from an older version of Xcode, make sure you're not using GCC.

**Run time requirements**

The minimum iOS version supported by the SDK is iOS 4.0. The many reasons for this choice include our use of ARC ([Automatic Reference Counting](http://developer.apple.com/library/ios/#releasenotes/ObjectiveC/RN-TransitioningToARC/Introduction/Introduction.html)) and our reliance on a number of Apple frameworks and libraries which require iOS 4, including [libdispatch](http://libdispatch.macosforge.org/).

<a name="package-contents"></a>
### Package Contents

The SDK consists of a static library, Objective-C header files, and one or more resource bundles containing configuration files and images. The static library is a universal binary for use on iOS device and simulator architectures (armv7/7s and i386).

    AviarySDK/
    |-- Headers/
    |   |-- AFPhotoEditorContext.h
    |   |-- AFPhotoEditorController.h
    |   |-- AFPhotoEditorControllerOptions.h
    |   |-- AFPhotoEditorSession.h
    |   |-- AFPhotoEditorStyle.h
    |-- Resources/
    |   |-- AviarySDKResources.bundle
    |-- libAviarySDK.a

Note: you can view the contents of the `.bundle` files we distribute, although we do not recommend or support modifying their contents.

<a name="quick-start"></a>
Quick Start
-----------

<a name="setup"></a>
### Setup

In order to use the SDK in an existing app, you must do the following:

0. **Project setup**

	Make sure you're running the latest version of Xcode and Apple's LLVM compiler.

1. **Add files**
	
	Copy the AviarySDK folder into your project (select "Create groups for any added folders" if needed).

2. **Link against libraries**

	Check your target's "Link Binary With Libraries" build phase. Make sure your app is being linked against `libAviarySDK.a`.
	
	Link against the following libraries and frameworks:

        Accelerate.framework
        CoreData.framework
        CoreGraphics.framework
        Foundation.framework
        libsqlite3.0.dylib
        libz.1.2.5.dylib
        QuartzCore.framework
        StoreKit.framework
        UIKit.framework
        CoreText.framework
        OpenGLES.framework

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
		[self presentViewController:editorController animated:YES completion:nil];
	}
	
You may instead choose to display the controller in other ways, such as by presenting it within a `UIPopoverController` or by manually adding it to the view hierarchy. If you choose to present the controller in such a way, you are responsible for making sure it receives the standard view controller lifecycle methods, including `viewDidLoad`, `viewWillAppear:`, etc. The controller may be displayed full-screen, or you may display it in a smaller portion of the screen.

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

The Aviary SDK offers the ability to produce output images with resolutions up to 3 megapixels (approximately 3 times larger than the maximum output resolution provided by the `AFPhotoEditorControllerDelegate` methods). Two utility classes support this functionality: `AFPhotoEditorSession` and `AFPhotoEditorContext`.

### AFPhotoEditorSession

Each instance of AFPhotoEditorController creates a session object upon initialization, which can be accessed via the readonly `session` property:

	AFPhotoEditorController *photoEditor = [[AFPhotoEditorController alloc] initWithImage:image];
	AFPhotoEditorSession *session = [photoEditor session];
	
A session object is always in one of two states: open or closed. A session is open when the SDK is initialized, and closed when the user presses the "Done" or "Cancel" button in the user interface.

*Note*: If you intend to use an AFPhotoEditorController's session instance, be sure to obtain a reference to the session before the controller is deallocated. Session objects do not strongly reference the controller from which they were generated, so it is okay to retain a reference to a session after the controller is no longer needed.

Session objects can be used to create instances of `AFPhotoEditorContext` (see below), which can be used to replay the session onto an input image, with an optional maximum output size.

### AFPhotoEditorContext

A photo editor context is an object that can be used to "replay" an editing session onto an input image. A context can be created from an instance of `AFPhotoEditorSession` with an image:

    AFPhotoEditorContext *context = [session createContextWithImage:image];

Or, when a maximum output size (for example, 1024x1024) is desired:
    
    AFPhotoEditorContext *context = [session createContextWithImage:image maxSize:CGSizeMake(1024, 1024)];

The first line above creates a context that can render the session onto an input image at full resolution if the dimensions of the input image are less than or equal to 1500px on each side and the input image is no larger than 3 megapixels. If the image is larger than this size, the output image will be downscaled to fit according to the aspect ratio of the input image.

The second line above imposes a tighter restriction on the output size. If the dimensions of the image are greater than 1024px on a side, the image will be downscaled before processing.

Once you have created a context from a session object, you can use it to render the session onto an input image like so:

	[context render:^(UIImage *result) {
		// Handle the result image here.
	}];

**New in 2.5.0**: `AFPhotoEditorContext` can take advantage of [GPU acceleration](#high-resolution-gpu-acceleration) when the input image is small enough to be represented as an OpenGL texture. An attempt to render an image that is too big to be represented as a texture will cause the context to fall back to CPU-based rendering.

If the context is created from an open session (i.e. after initializing an `AFPhotoEditorController` but before displaying it) and `-render:` is called, one of two things will happen:

1. If the context is [able to use the GPU](#high-resolution-gpu-acceleration), it will wait until the session is closed before rendering the output image. This is much faster and more efficient than the old CPU-based behavior.

2. If the context falls back to using the CPU, it will render operations onto the image in the background as the user applies them in the SDK (by pressing the "Apply" button).

The completion block you supply to the method above will execute regardless of whether or not the user presses the "Cancel" button. If the user successfully completed his or her session, the `UIImage` passed to the completion block will be the rendered image. If the user cancels the SDK, the `UIImage` passed to the block will be `nil`.

Some things to note about using contexts:

1. We recommend choosing a maximum output resolution that suits the purposes of your application to provide the best experience for your users.

2. Processing large images can consume a lot of memory and time. It may be necessary to free up resources and/or display an activity indicator while a context is executing.

3. To calculate the approximate maximum amount of memory a context could use, multiply the dimensions of the output size and multiply the result by 4. For example, a context with a maximum output size of 1500x1500 will consume approximately 9mb of memory for the processing duration.

<a name="high-resolution-gpu-acceleration"></a>
### GPU Acceleration

As of version 2.5.0, the SDK can seamlessly use the GPU to render high-resolution images much more quickly. In order to invoke the GPU-based code path, input images passed to `AFPhotoEditorContext` must be smaller than the maximum OpenGL texture size supported on the device. Here are the [approximate maximum supported texture sizes](http://www.uchidacoonga.com/2012/04/quick-tip-max-texture-size/) for each iOS device model:

<table border="1">
<tbody>
    <tr>
        <th>Texture size</th>
        <th>Device types</th>
    <tr>
        <td>2048x2048</td>
        <td>iPhone 3GS, iPhone 4, iPad</td>
    </tr>
    <tr>
        <td>4096x4096</td>
        <td>iPhone 5, iPhone 4S, iPad 3, iPad 2</td>
    </tr>
</tbody>
</table>

<a name="high-resolution-example"></a>
### Example

Below is some sample code for rendering a user session at the maximum supported output resolution:

	AFPhotoEditorController *photoEditor = [[AFPhotoEditorController alloc] initWithImage:image];

	// Capture the user's session and store it in an array
    __block AFPhotoEditorSession *session = [photoEditor session];
    [[self sessions] addObject:session];
    
    // Create a context with the maximum output resolution
    AFPhotoEditorContext *context = [session createContextWithImage:image];
    
    [context render:^(UIImage *result) {
    	// `result` will be nil if the session is canceled, or non-nil if the session was closed successfully and rendering completed
    	[[self sessions] removeObject:session];
    }];
<a name="customization"></a>
## Customization

The editor is customizable at runtime using four class methods of `AFPhotoEditorCustomization`.
	
	+ (void)setOptionValue:(id)obj forKey:(NSString *)key;
	+ (void)setOptionValueWithBlock:(id(^)(void))block forKey:(NSString *) key;
	+ (void)setOptionWithImageNamed:(NSString *)name forKey:(NSString *)key;
	+ (void)removeOptionValueForKey:(NSString *)key;
	
The customization system is based on a cascading key system, where it is possible to set an option value for the editor as a whole and also provide different values for specific tools. Each key consists of two mandatory parts, key path and option name, and an optional modifier. A valid key takes the form `<key path>.<option name>-<optional modifier>`. The option name defines the item in the editor that is affected by setting a value to the key. For example, `accentColor` is an option name that represents the accent color used in the editor's various tools. The key path defines the scope of the effect that the key's value has in the editor. The list of valid key paths are as follows:

* `editor`
* `editor.tool`
* `editor.tool.wheel`
* `editor.tool.meme`
* `editor.tool.orientation`
* `editor.tool.text`
* `editor.tool.crop`
* `editor.tool.effects`
* `editor.tool.enhance`
* `editor.tool.stickers`
* `editor.tool.brush`
* `editor.tool.brush.draw`
* `editor.tool.brush.blemish`
* `editor.tool.brush.whiten`
* `editor.tool.brush.redeye`
* `editor.tool.wheel.saturation`
* `editor.tool.wheel.sharpness`
* `editor.tool.wheel.contrast`
* `editor.tool.wheel.brightness`

The key path `editor` defines the global scope for the editor and setting values using it will apply everywhere in the editor. Key paths are refined by appending `.<new key path component>`, which narrows the scope of where the option will take effect. For example, values set with the key path `editor.tool.crop` will apply only in the crop tool. If values are set with keys that contain the same option name with different key paths, ie, `editor.accentColor` and `editor.tool.crop.accentColor`, then the value set to the key with the more refined key path will override the values from keys with more general scope. By appending a modifier to a key, you can specify the options value in a given state. Currently, only the `highlighted` modifier is supported to customize UI elements when they are in their highlighted state.
	
Values for a given key can be given in one of three ways. Using `+setOptionValue:forKey:` sets the value for the key with a concrete object value. `+setOptionValueWithBlock:forKey:` sets the value for the key by evaluating the block that is given. The block is lazily evaluated, making it useful for specifying options with values that require loading information from disk. The third method, `+setOptionWithImageNamed:forKey:` is a convenience method that lazily sets the value of the key to the image with the name provided. It is also possible to remove a custom value for a given key using `+removeOptionValueForKey:`.

	[AFPhotoEditorCustomization setOptionValue:[UIColor redColor] forKey:@"editor.accentColor"]; // sets the global accent color to red
	[AFPhotoEditorCustomization setOptionValueWithBlock:^{return [UIColor blueColor];} forKey:@"editor.tool.crop.accentColor"]; // sets the crop tool's accent color to blue
	[AFPhotoEditorCustomization setOptionWithImageNamed:@"enhanceIcon.png" forKey:@"editor.tool.enhance.icon"]; // sets the enhance tool's icon
	[AFPhotoEditorCustomization removeOptionValueForKey:@"editor.too.crop.accentColor"]; // Removes the crop tool specific accent color
	
Values for a given option are required to be of a specific type. The requirements for each option are enumerated in the list of keys below. If the value provided for a given key do not meet the requirements, it has no effect.

In addition to defining the scope of a key's effect, the key path also defines the set of options that are available to customize. In the list of keys below, options listed under **inheritable** are inherited by refined key paths and those listed under **non-inheritable** can only be modified with the given key path.

<h3>editor</h3>
<ul>
    <li>
        <h4>Inheritable</h4>
        <ul>
            <li>
                <p><code>UIColor *navigationBarCancelColor</code></p>
                <p>No type restrictions. This key sets the background color of the editor's navigation bar cancel button</p>
            </li>
            <li>
                <p><code>UIColor *navigationBarBackgroundColor</code></p>
                <p>No type restrictions. This key sets the background color of the editor's navigation bar.</p>
            </li>
            <li>
                <p><code>UIColor *navigationBarCancelTextColor</code></p>
                <p>No type restrictions. This key sets the text color of the editor's navigation bar cancel button.</p>
            </li>
            <li>
                <p><code>UIColor *accentColor</code></p>
                <p>No type restrictions. This key sets the accent color of the tool views.</p>
            </li>
            <li>
                <p><code>UIColor *backgroundColor</code></p>
                <p>No type restrictions. This key sets the background color of the tool views.</p>
            </li>
            <li>
                <p><code>UIColor *navigationBarTextColor</code></p>
                <p>No type restrictions. This key sets the text color of the editor's navigation bar title.</p>
            </li>
        </ul>
    </li>
    <li>
        <h4>Non-inheritable</h4>
        <ul>
            <li>
                <p><code>UIColor *bottomBarButtonTextColor</code></p>
                <p>No type restrictions. This key sets the color of the text of the tool names in the editor's bottom bar.</p>
            </li>
            <li>
                <p><code>NSNumber *disableLocalization</code></p>
                <p>An <code>NSNumber</code> represeting a <code>BOOL</code> value. Setting this key to <code>YES</code> will disable localization of text in the editor. Defaults to <code>NO</code>.</p>
            </li>
            <li>
                <p><code>UIColor *canvasColor</code></p>
                <p>No type restrictions. This key sets the background color behind the photo being editted in the editor.</p>
            </li>
            <li>
                <p><code>UIColor *pageControlUnselectedColor</code></p>
                <p>No type restrictions. This key sets the color of the editor's page controls unselected state.</p>
            </li>
            <li>
                <p><code>NSString *leftNavigationBarButtonTitle</code></p>
                <p>An <code>NSString</code> value represented by one of the three <code>kAFLeftNavigationTitlePreset</code> keys. This key sets the text of the editor's left navigation bar button.</p>
            </li>
            <li>
                <p><code>NSString *rightNavigationBarButtonTitle</code></p>
                <p>An <code>NSString</code> value represented by one of the three <code>kAFRightNavigationTitlePreset</code> keys. This key sets the text of the editor's right navigation bar button.</p>
            </li>
            <li>
                <p><code>NSArray *toolOrder</code></p>
                <p>An <code>NSArray</code> containing <code>NSString</code> values represented by one of the tool keys. This key sets the availablity and the display order of tools in the editor.</p>
            </li>
            <li>
                <p><code>UIColor *bottomBarButtonIconColor</code></p>
                <p>A non-pattern image <code>UIColor</code>. This key sets the color of each of the tool icons in the editor's bottom bar.</p>
            </li>
            <li>
                <p><code>NSArray *supportedOrientations</code></p>
                <p>An <code>NSArray</code> containing <code>NSNumbers</code> each represening a valid /UIInterfaceOrientation</code>. This key sets the user interface orienations that the editor will support.</p>
            </li>
        </ul>
    </li>
</ul>
<h3>editor.tool.crop</h3>
<ul>
    <li>
        <h4>Non-inheritable</h4>
        <ul>
            <li>
                <p><code>NSNumber *cellWidth</code></p>
                <p>An <code>NSNumber</code> representing a <code>Float</code> with value greater than or equal to 20.0 and less than or equal to 120.0. This key sets the width of the crop preset selection cells.</p>
            </li>
            <li>
                <p><code>NSNumber *enableInvert</code></p>
                <p>An <code>NSNumber</code> represeting a <code>BOOL</code> value. Setting this key to <code>NO</code> will prevent crop presets to be inverted. Defaults to <code>YES</code>. Presets with names, ie. <code>Square</code>, are not invertable, regardless of whether this key is set to <code>YES</code>.</p>
            </li>
            <li>
                <p><code>NSArray *presets</code></p>
                <p>An <code>NSArray</code> containing <code>NSDictionaries</code> with the following key-value pairs:<br/><ul> <li><code>kAFCropPresetWidth</code> represents the preset's width. A valid value for this key is an <code>NSNumber</code> instance representing a float.</li><li><code>kAFCropPresetHeight</code> represents the preset's height. A valid value for this key is an <code>NSNumber</code> instance representing a float.</li><li><code>kAFCropPresetName</code> represents the preset's name. A valid value for this key is an <code>NSString</code> instance. This key is optional, and when not present the preset will be named "width x height". If inverted crop is enabled, the width and height values will correspond to those of the aspect ratio being displayed.</li></ul> This key sets the availablity and order of crop preset options. If Original and/or Custom options are enabled, then they will preceed the presets defined here. If this key is not set, then the default options are <code>Square</code>, <code>3x2</code>, <code>5x3</code>, <code>4x3</code>, <code>6x4</code>, and <code>7x5</code>.</p>
            </li>
            <li>
                <p><code>NSNumber *enableOriginal</code></p>
                <p>An <code>NSNumber</code> represeting a <code>BOOL</code> value. Setting this key to <code>NO</code> will disable the <code>Original</code> crop preset. Defaults to <code>YES</code>. The <code>Original</code> crop preset constrains the crop area to photo's original aspect ratio.</p>
            </li>
            <li>
                <p><code>NSNumber *enableCustom</code></p>
                <p>An <code>NSNumber</code> represeting a <code>BOOL</code> value. Setting this key to <code>NO</code> will disable the <code>Original</code> crop preset. Defaults to <code>YES</code>. The <code>Custom</code> crop preset does not contrain the crop area to any specific aspect ratio.</p>
            </li>
        </ul>
    </li>
</ul>
