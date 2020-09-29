#import <Foundation/Foundation.h>

@interface ImagePickerDelegate : NSObject

+(void) onRequestImagePickerPermissionResult:(int64_t) id granted:(bool) granted;
+(void) onImagePicked:(int64_t) id filename:(NSString*) filename source:(int) source width:(int) width height:(int) height rotation:(int) rotation;

@end
