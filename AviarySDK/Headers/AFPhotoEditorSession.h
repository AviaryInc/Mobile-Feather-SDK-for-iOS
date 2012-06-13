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

- (AFPhotoEditorContext *)createContext;
- (AFPhotoEditorContext *)createContextWithSize:(CGSize)size;

@end
