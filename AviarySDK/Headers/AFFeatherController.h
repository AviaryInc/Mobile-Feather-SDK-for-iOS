//
//  AFFeatherController.h
//  AviarySDK
//
//  Created by Cameron Spickert on 9/16/11.
//  Copyright 2011 Aviary INC. All rights reserved.
//

@class AFFeatherController;

#pragma mark -
#pragma mark AFInterfaceElement protocol

@protocol AFInterfaceElement <NSObject>
@required

@property (nonatomic, retain) UIColor *tintColor;
@property (nonatomic, retain) UIImage *backgroundImage;

@end

#pragma mark -
#pragma mark AFFeatherPluginButton protocol

@protocol AFFeatherPluginButton <AFInterfaceElement>
@end

#pragma mark -
#pragma mark AFFeatherPlugin protocol

@protocol AFFeatherPlugin <NSObject>
@required

@property (nonatomic, readonly) NSString *pluginId;
@property (nonatomic, readonly) NSString *localizedName;
@property (nonatomic, readonly) UIImage *icon;
@property (nonatomic, readonly) UIButton<AFFeatherPluginButton> *button;

@end

@protocol AFFeatherDelegate <NSObject>
@optional

#pragma mark -
#pragma mark Delegate methods

- (void)feather:(AFFeatherController *)featherController finishedWithImage:(UIImage *)image;
- (void)featherCanceled:(AFFeatherController *)featherController;
- (BOOL)featherShouldConfirmCancel:(AFFeatherController *)featherController;

- (UIButton *)feather:(AFFeatherController *)featherController buttonForPlugin:(id<AFFeatherPlugin>)plugin;

- (BOOL)featherShouldConfirmCancel:(AFFeatherController *)featherController;

@end

@interface AFFeatherController : UIViewController

@property (nonatomic, assign) id<AFFeatherDelegate> delegate;
@property (nonatomic, retain) id<AFInterfaceElement> topBar, bottomBar, paramsBar;

- (id)initWithImage:(UIImage *)image;
- (id)initWithImage:(UIImage *)image andTools:(NSArray *)tools;
- (id)initWithImage:(UIImage *)image andTools:(NSArray *)tools andUserInterfaceIdiom:(UIUserInterfaceIdiom)idiom;

@end
