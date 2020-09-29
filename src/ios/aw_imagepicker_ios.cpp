#include "aw_imagepicker_ios.h"

extern "C" {
	void* ImagePicker_create();
	void ImagePicker_destroy(void* ptr);
	void ImagePicker_addListener(void* ptr, long long listener);
	void ImagePicker_removeListener(void* ptr, long long listener);
	void ImagePicker_clearAllListeners(void* ptr);
	void ImagePicker_onCreate(void* ptr);
	void ImagePicker_onDestroy(void* ptr);
	bool ImagePicker_hasPermission(void* ptr);
	bool ImagePicker_shouldShowPermissionDescription(void* ptr);
	void ImagePicker_requestPermission(void* ptr);
	void ImagePicker_pickImageFromGallery(void* ptr);
	void ImagePicker_captureImageFromCamera(void* ptr);
}

namespace ImagePicker {
	CImagePicker_Ios::CImagePicker_Ios() {
		mImagePicker = ImagePicker_create();
	}

	CImagePicker_Ios::~CImagePicker_Ios() {
		ImagePicker_destroy(mImagePicker);
	}

	void CImagePicker_Ios::addListener(IImagePickerListener* listener) {
		ImagePicker_addListener(mImagePicker, reinterpret_cast<long long>(listener));
	}

	void CImagePicker_Ios::removeListener(IImagePickerListener* listener) {
		ImagePicker_removeListener(mImagePicker, reinterpret_cast<long long>(listener));
	}

	void CImagePicker_Ios::clearAllListeners() {
		ImagePicker_clearAllListeners(mImagePicker);
	}

	void CImagePicker_Ios::onCreate() {
		ImagePicker_onCreate(mImagePicker);
	}

	void CImagePicker_Ios::onDestroy() {
		ImagePicker_onDestroy(mImagePicker);
	}

	bool CImagePicker_Ios::hasPermission() {
		return ImagePicker_hasPermission(mImagePicker);
	}

	bool CImagePicker_Ios::shouldShowPermissionDescription() {
		return ImagePicker_shouldShowPermissionDescription(mImagePicker);
	}

	void CImagePicker_Ios::requestPermission() {
		ImagePicker_requestPermission(mImagePicker);
	}

	void CImagePicker_Ios::pickImageFromGallery() {
		ImagePicker_pickImageFromGallery(mImagePicker);
	}

	void CImagePicker_Ios::captureImageFromCamera() {
		ImagePicker_captureImageFromCamera(mImagePicker);
	}
}
