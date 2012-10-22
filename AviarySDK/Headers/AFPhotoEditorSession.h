//
//  AFPhotoEditorSession.h
//  AviarySDK
//
//  Created by Cameron Spickert on 3/6/12.
//  Copyright (c) 2012 Aviary, Inc. All rights reserved.
//

@class AFPhotoEditorContext;

extern NSString *const AFPhotoEditorSessionCancelledNotification;

@interface AFPhotoEditorSession : NSObject

@property (nonatomic, assign, readonly, getter=isOpen) BOOL open;
@property (nonatomic, assign, readonly, getter=isCancelled) BOOL cancelled;
@property (nonatomic, assign, readonly, getter=isModified) BOOL modified;

/*
 These methods should be called from the main thread. Behavior when calling from a background thread is 
 undefined.
 */
- (AFPhotoEditorContext *)createContextWithImage:(UIImage *)image;
- (AFPhotoEditorContext *)createContextWithImage:(UIImage *)image maxSize:(CGSize)size;

/*
 AFPhotoEditorSession's `-createContext` and `-createContextWithSize:` are deprecated. Please use `-createContextWithImage:`
 or `-createContextWithImage:maxSize:` instead.
 */
- (AFPhotoEditorContext *)createContext DEPRECATED_ATTRIBUTE;
- (AFPhotoEditorContext *)createContextWithSize:(CGSize)size DEPRECATED_ATTRIBUTE;

@end
