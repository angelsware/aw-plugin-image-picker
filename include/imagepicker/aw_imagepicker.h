#ifndef __AW_IMAGE_PICKER_H__
#define __AW_IMAGE_PICKER_H__

namespace ImagePicker {
	class IImagePickerListener;

	class IImagePicker
	{
	public:
		virtual ~IImagePicker() {}

		virtual void addListener(IImagePickerListener* listener) = 0;
		virtual void removeListener(IImagePickerListener* listener) = 0;
		virtual void clearAllListeners() = 0;
		virtual void onCreate() = 0;
		virtual void onDestroy() = 0;
		virtual bool hasPermission() = 0;
		virtual bool shouldShowPermissionDescription() = 0;
		virtual void requestPermission() = 0;
		virtual void pickImageFromGallery() = 0;
		virtual void captureImageFromCamera() = 0;
	};
}

#endif
