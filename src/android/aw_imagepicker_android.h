#ifndef __AW_IMAGE_PICKER_ANDROID_H__
#define __AW_IMAGE_PICKER_ANDROID_H__

#include <imagepicker/aw_imagepicker.h>
#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif
	JNIEXPORT void JNICALL Java_com_angelsware_imagepicker_ImagePicker_onRequestImagePickerPermissionResult(JNIEnv* env, jclass clazz, jboolean granted);
	JNIEXPORT void JNICALL Java_com_angelsware_imagepicker_ImagePicker_onImagePicked(JNIEnv* env, jclass clazz, jstring filename, jint source, jint rotation);
#ifdef __cplusplus
}
#endif

namespace Platform {
	class CJniClass;
}

namespace ImagePicker {
	class CImagePicker_Android
		: public IImagePicker
	{
	public:
		CImagePicker_Android();
		~CImagePicker_Android();

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

		Platform::CJniClass* mImagePicker;
	};
}

#endif
