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

/** @} */
