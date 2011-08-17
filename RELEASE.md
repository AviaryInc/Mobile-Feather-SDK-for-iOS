# Feather iOS Release Notes

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
