#ifndef __AW_IMAGE_PICKER_IOS_H__
#define __AW_IMAGE_PICKER_IOS_H__

#include <imagepicker/aw_imagepicker.h>

namespace ImagePicker {
	class CImagePicker_Ios
		: public IImagePicker
	{
	public:
		CImagePicker_Ios();
		~CImagePicker_Ios();

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

		void* mImagePicker;
	};
}

#endif
