#import "ImagePickerDelegate.h"
#import <imagepicker/aw_imagepickerlistener.h>
#import <imagepicker/aw_source.h>

@implementation ImagePickerDelegate

+(void) onRequestImagePickerPermissionResult:(int64_t) id granted:(bool) granted {
	reinterpret_cast<ImagePicker::IImagePickerListener*>(id)->onRequestImagePickerPermissionResult(granted);
}

+(void) onImagePicked:(int64_t) id filename:(NSString*) filename source:(int) source width:(int) width height:(int) height rotation:(int) rotation {
	reinterpret_cast<ImagePicker::IImagePickerListener*>(id)->onImagePicked([filename UTF8String], ImagePicker::ESource(source), width, height, rotation);
}

@end
