#ifndef __AW_IMAGE_PICKER_DEFAULT_H__
#define __AW_IMAGE_PICKER_DEFAULT_H__

#include <imagepicker/aw_imagepicker.h>

namespace ImagePicker {
	class CImagePicker_Default
		: public IImagePicker
	{
	private:
		// IImagePicker
		void addListener(IImagePickerListener* listener);
		void removeListener(IImagePickerListener* listener);
		void clearAllListeners();
		void onCreate();
		void onDestroy();
		bool hasPermission();
		bool shouldShowPermissionDescription();
		void requestPermission();
		void pickImageFromGallery();
		void captureImageFromCamera();
	};
}

#endif
