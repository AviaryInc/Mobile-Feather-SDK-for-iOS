//
//  AFPhotoEditorController.h
//  AviarySDK
//
//  Copyright (c) 2012 Aviary, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <Accelerate/Accelerate.h>

#import "AFPhotoEditorControllerOptions.h"

@class AFPhotoEditorController;

/**
 * Implement this protocol to be notified when the user is done using the editor. You are
 * responsible for dismissing the editor when you (and/or your user) are finished with it.
 */
@protocol AFPhotoEditorControllerDelegate <NSObject>
@optional

/**
 * Implement this method to be notified when the user presses the "Done" button. The
 * edited image is passed via the `image` parameter.
 *
 * @param editor The photo editor controller.
 * @param image The edited image.
 *
 * @note The size of this image may not be equivalent to the size of the input image,
 * if the input image is larger than the maximum image size supported by the SDK.
 * Currently (as of 1/17/12), the maximum size is {960.0, 960.0} pixels on all devices.
 */
- (void)photoEditor:(AFPhotoEditorController *)editor finishedWithImage:(UIImage *)image;

/**
 * Implement this method to be notified when the user presses the "Cancel" button.
 *
 * @param editor The photo editor controller.
 */
- (void)photoEditorCanceled:(AFPhotoEditorController *)editor;

@end

@interface AFPhotoEditorController : UIViewController

@property (nonatomic, assign) id<AFPhotoEditorControllerDelegate> delegate;

/**
 * Initialize the photo editor controller with an image and configuration options. This
 * is the designated initializer for this class.
 *
 * @param image The image to edit.
 * @param options (optional) Additional configuration options. See
 * AFPhotoEditorControllerOptions.h for more information.
 *
 * @note As mentioned above, the dimensions of the edited image may be smaller than the
 * input image.
 * @see AFPhotoEditorControllerOptions.h
 * @see photoEditor:finishedWithImage:
 */
- (id)initWithImage:(UIImage *)image options:(NSDictionary *)options;

/**
 * Initialize the photo editor controller with an image and the default options.
 *
 * @param image The image to edit.
 *
 * @see initWithImage:options:
 */
- (id)initWithImage:(UIImage *)image;

@end
