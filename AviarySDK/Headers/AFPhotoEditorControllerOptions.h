//
//  AFPhotoEditorControllerOptions.h
//  AviarySDK
//
//  Copyright (c) 2012 Aviary, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

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

extern NSString *const kAFEnhance;      /* Enhance */
extern NSString *const kAFEffects;      /* Effects */
extern NSString *const kAFStickers;     /* Stickers */
extern NSString *const kAFOrientation;  /* Orientation */
extern NSString *const kAFCrop;         /* Crop */
extern NSString *const kAFBrightness;   /* Brightness */
extern NSString *const kAFContrast;     /* Contrast */
extern NSString *const kAFSaturation;   /* Saturation */
extern NSString *const kAFSharpness;    /* Sharpness */
extern NSString *const kAFDraw;         /* Draw */
extern NSString *const kAFText;         /* Text */
extern NSString *const kAFRedeye;       /* Redeye */
extern NSString *const kAFWhiten;       /* Whiten */
extern NSString *const kAFBlemish;      /* Blemish */

/**
    Use this key to define the interface orientations you want to allow in
    `-shouldAutorotateToInterfaceOrientation`. The value for this key should be
    a NSArray of NSNumber objects wrapping UIInterfaceOrientation values. For
    example, if you only want to support the portrait orientation, set the
    following value for this key: `[NSArray arrayWithObject:[NSNumber
    numberWithUnsignedInt:UIInterfaceOrientationPortrait]]`.
 */
extern NSString *const kAFPhotoEditorControllerSupportedOrientationsKey;

/** @} */
