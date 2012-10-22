//
//  AFOption.h
//  AFOptions
//
//  Created by Michael Vitrano on 9/5/12.
//  Copyright (c) 2012 Aviary. All rights reserved.
//

/** @defgroup AFPhotoEditorControllerOptions AFPhotoEditorController Option Dictionary Keys */

/** @addtogroup AFPhotoEditorControllerOptions
 @{
 */

/**
 This key allows developers to customize the visibility of, and order in which
 tools appear in the SDK interface. A valid value for this key is a NSArray
 containing NSString instances whose values match the constants below.
 */
extern NSString *const kAFPhotoEditorControllerToolsKey;

extern NSString *const kAFEnhance;     /* Enhance */
extern NSString *const kAFEffects;     /* Effects */
extern NSString *const kAFStickers;    /* Stickers */
extern NSString *const kAFOrientation; /* Orientation */
extern NSString *const kAFCrop;        /* Crop */
extern NSString *const kAFBrightness;  /* Brightness */
extern NSString *const kAFContrast;    /* Contrast */
extern NSString *const kAFSaturation;  /* Saturation */
extern NSString *const kAFSharpness;   /* Sharpness */
extern NSString *const kAFDraw;        /* Draw */
extern NSString *const kAFText;        /* Text */
extern NSString *const kAFRedeye;      /* Redeye */
extern NSString *const kAFWhiten;      /* Whiten */
extern NSString *const kAFBlemish;     /* Blemish */
extern NSString *const kAFMeme;        /* Meme */

/**
 Use this key to define the interface orientations you want to allow in
 `-shouldAutorotateToInterfaceOrientation`. The value for this key should be
 a NSArray of NSNumber objects wrapping UIInterfaceOrientation values. For
 example, if you only want to support the portrait orientation, set the
 following value for this key: `[NSArray arrayWithObject:[NSNumber
 numberWithUnsignedInt:UIInterfaceOrientationPortrait]]`.
 */
extern NSString *const kAFPhotoEditorControllerSupportedOrientationsKey;

/**
 Use this key to define the background color for the photo editor (behind the
 image being edited). The value for this key should be a UIColor object. Any
 color space supported by UIKit should work, including patterns created with
 `+colorWithPatternImage:`. Use `[UIColor clearColor]` to make the background
 transparent.
 */
extern NSString *const kAFPhotoEditorControllerBackgroundColorKey;

extern NSString *const kAFLeftNavigationTitlePresetCancel; /* Cancel */
extern NSString *const kAFLeftNavigationTitlePresetBack;   /* Back */
extern NSString *const kAFLeftNavigationTitlePresetExit;   /* Exit */

extern NSString *const kAFRightNavigationTitlePresetDone;  /* Done */
extern NSString *const kAFRightNavigationTitlePresetSave;  /* Save */

extern NSString *const kAFCropPresetName;   /* Name */
extern NSString *const kAFCropPresetWidth;  /* Width */
extern NSString *const kAFCropPresetHeight; /* Height */

extern NSString *const kAFTextBorderColors; /* Text Tool Text Border Colors */
extern NSString *const kAFTextFillColors;   /* Text Tool Text Fill Colors */

/** @} */

@interface AFPhotoEditorCustomization : NSObject

+ (void)setOptionValue:(id)obj forKey:(NSString *)key;
+ (void)setOptionValueWithBlock:(id (^)(void))block forKey:(NSString *)key;
+ (void)setOptionWithImageNamed:(NSString *)name forKey:(NSString *)key;
+ (void)removeOptionValueForKey:(NSString *)key;

@end
