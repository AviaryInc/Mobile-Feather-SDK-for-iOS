//
//  AFPhotoEditorContext.h
//  AviarySDK
//
//  Created by Cameron Spickert on 3/6/12.
//  Copyright (c) 2012 Aviary, Inc. All rights reserved.
//

@class AFPhotoEditorSession;

@interface AFPhotoEditorContext : NSObject

@property (nonatomic, assign, readonly) AFPhotoEditorSession *session;
@property (nonatomic, assign, readonly) CGSize size;
@property (nonatomic, assign, readonly, getter=isCanceled) BOOL canceled;
@property (nonatomic, assign, readonly, getter=isModified) BOOL modified;

/*
 These methods should be called from the main thread. Behavior when calling from a background thread is
 undefined.
 */
- (void)render:(void (^)(UIImage *result))completion;
- (void)cancelRendering;

/*
 AFPhotoEditorContext's `renderInputImage:completion:` is deprecated. Please create a context with AFPhotoEditorSession's `createContextWithImage:maxSize:` and use `render:` instead.
 */
- (void)renderInputImage:(UIImage *)image completion:(void (^)(UIImage *result))completion DEPRECATED_ATTRIBUTE;

@end
