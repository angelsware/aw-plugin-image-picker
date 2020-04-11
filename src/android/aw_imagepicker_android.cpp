#include "aw_imagepicker_android.h"
#include <imagepicker/aw_imagepickerlistener.h>
#include <imagepicker/aw_source.h>
#include <platform/android/aw_jniclass.h>
#include <platform/android/aw_jni.h>
#include <platform/android/aw_jninativestring.h>
#include <log/aw_log.h>
#include <type/aw_vector.h>

static Type::CVector<ImagePicker::IImagePickerListener*> sListeners;

JNIEXPORT void JNICALL Java_com_angelsware_imagepicker_ImagePicker_onRequestImagePickerPermissionResult(JNIEnv* env, jclass clazz, jboolean granted) {
	for (unsigned int i = 0; i < sListeners.getSize(); ++i) {
		sListeners[i]->onRequestImagePickerPermissionResult(granted);
	}
}

JNIEXPORT void JNICALL Java_com_angelsware_imagepicker_ImagePicker_onImagePicked(JNIEnv* env, jclass clazz, jstring filename, jint source, jint width, jint height, jint rotation) {
	Platform::CJniNativeString filenameStr(filename);
	ImagePicker::ESource eSource = ImagePicker::ESource::GALLERY;
	if (source == 1) {
		eSource = ImagePicker::ESource ::CAMERA;
	}

	for (unsigned int i = 0; i < sListeners.getSize(); ++i) {
		sListeners[i]->onImagePicked(filenameStr.getText(), eSource, width, height, rotation);
	}
}

namespace ImagePicker {
	CImagePicker_Android::CImagePicker_Android() {
		mImagePicker = new Platform::CJniClass("com/angelsware/imagepicker/ImagePicker", "()V");
	}

	CImagePicker_Android::~CImagePicker_Android() {
		delete mImagePicker;
	}

	void CImagePicker_Android::addListener(IImagePickerListener* listener) {
		sListeners.pushBack(listener);
	}

	void CImagePicker_Android::removeListener(IImagePickerListener* listener) {
		for (unsigned int i = 0; i < sListeners.getSize(); ++i) {
			if (sListeners[i] == listener) {
				sListeners.eraseAndReplaceWithLast(i);
				break;
			}
		}
	}

	void CImagePicker_Android::clearAllListeners() {
		sListeners.clear();
	}

	void CImagePicker_Android::onCreate() {
		mImagePicker->callVoidMethod("create", "()V");
	}

	void CImagePicker_Android::onDestroy() {
		mImagePicker->callVoidMethod("destroy", "()V");
	}

	bool CImagePicker_Android::hasPermission() {
		return mImagePicker->callBooleanMethod("hasPermission", "()Z");
	}

	bool CImagePicker_Android::shouldShowPermissionDescription() {
		return mImagePicker->callBooleanMethod("shouldShowRequestPermissionRationale", "()Z");
	}

	void CImagePicker_Android::requestPermission() {
		mImagePicker->callVoidMethod("requestPermission", "()V");
	}

	void CImagePicker_Android::pickImageFromGallery() {
		mImagePicker->callVoidMethod("pickImageFromGallery", "()V");
	}

	void CImagePicker_Android::captureImageFromCamera() {
		mImagePicker->callVoidMethod("captureImageFromCamera", "()V");
	}
}
