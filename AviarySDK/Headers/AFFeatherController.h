//
//  AFFeatherController.h
//
//  Copyright 2011 Aviary INC. All rights reserved.
//

// Note 1.1: we are continuing to update/clean up this file, so please don't rely
// on any properties, methods or protocols marked "don't use."

#import <UIKit/UIKit.h>
#import "AFFeatherConstants.h"

@class AFFeatherController;

#pragma mark -
#pragma mark AFFeatherPluginButton protocol

@protocol AFInterfaceElement <NSObject>
@required
@property (nonatomic, retain) UIColor *tintColor;
@property (nonatomic, retain) UIImage *backgroundImage;
@end

@protocol AFFeatherPluginButton <AFInterfaceElement>
@end

#pragma mark -
#pragma mark AFFeatherPlugin protocol

@protocol AFFeatherPlugin <NSObject>

@property (nonatomic, readonly) NSString *pluginId;
@property (nonatomic, readonly) NSString *localizedName;
@property (nonatomic, readonly) UIImage *icon;
@property (nonatomic, readonly) UIButton<AFFeatherPluginButton> *button;

@end

#pragma mark -
#pragma mark AFFeatherDelegate protocol

@protocol AFFeatherDelegate <NSObject>
@optional

#pragma mark -
#pragma mark New delegate methods (use these)

- (void)feather:(AFFeatherController *)featherController finishedWithImage:(UIImage *)image;
- (void)featherCanceled:(AFFeatherController *)featherController;

- (UIButton *)feather:(AFFeatherController *)featherController buttonForPlugin:(id<AFFeatherPlugin>)plugin;

- (BOOL)featherShouldConfirmCancel:(AFFeatherController *)featherController;

#pragma mark -
#pragma mark Old delegate methods (don't use)

// These methods were removed in 1.1. Please use the methods above instead.

// - (void)afFinishedWithImage:(UIImage *)image;
// - (void)afCanceled;

@end

@class AFToolbar;
@class AFTaskBar;
@class AFImageView;
@class AFPlugin;

@interface AFFeatherController : UIViewController {
@private
    IBOutlet AFToolbar *toolbar;
    IBOutlet UIBarButtonItem *toolbarCancel;
    IBOutlet UIBarButtonItem *toolbarBack;
    IBOutlet UIBarButtonItem *toolbarTitle;
    IBOutlet UIBarButtonItem *toolbarLogo;
    IBOutlet UIBarButtonItem *toolbarDone;
    IBOutlet UIBarButtonItem *toolbarSave;
    IBOutlet UIActivityIndicatorView *activityWheel;
    
    IBOutlet AFTaskBar *taskBar;
    IBOutlet AFImageView *imageView, *imageViewTmp;
}

#pragma mark -
#pragma mark Public methods

@property (nonatomic, assign) id<AFFeatherDelegate> delegate;
@property (nonatomic, retain, readonly) id<AFInterfaceElement> topBar;
@property (nonatomic, retain, readonly) id<AFInterfaceElement> bottomBar;
@property (nonatomic, retain, readonly) id<AFInterfaceElement> paramsBar;

- (id)initWithImage:(UIImage *)image;
- (id)initWithImage:(UIImage *)image andTools:(NSArray *)tools;

#pragma mark -
#pragma mark Deprecated methods

// These methods will be removed in the future. Use the
// AFInterfaceElement-compliant properties above instead.

- (void)setTitleBarTintColor:(UIColor *)color;
- (void)setPluginBarTintColor:(UIColor *)color;
- (void)setPluginParametersBarTintColor:(UIColor *)color;

#pragma mark -
#pragma mark Internal methods (don't use)

+ (AFPlugin *)pluginByPluginId:(NSString *)pluginId;

- (IBAction)handleLogoPressed:(id)sender;
- (IBAction)toolbarCancel:(id)sender;
- (IBAction)toolbarSave:(id)sender;
- (IBAction)toolbarDone:(id)sender;
- (IBAction)toolbarBack:(id)sender;

@end
