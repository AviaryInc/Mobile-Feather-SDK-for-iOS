//
//  AFPhotoEditorSession.h
//  AviarySDK
//
//  Created by Cameron Spickert on 3/6/12.
//  Copyright (c) 2012 Aviary, Inc. All rights reserved.
//

@class AFPhotoEditorContext;

@interface AFPhotoEditorSession : NSObject

@property (nonatomic, assign, readonly, getter=isOpen) BOOL open;

- (AFPhotoEditorContext *)createContext;
- (AFPhotoEditorContext *)createContextWithSize:(CGSize)size;

@end
