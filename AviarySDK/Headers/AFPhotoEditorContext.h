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

- (void)renderInputImage:(UIImage *)image completion:(void (^)(UIImage *result))completion;
- (void)cancelRendering;

@end
