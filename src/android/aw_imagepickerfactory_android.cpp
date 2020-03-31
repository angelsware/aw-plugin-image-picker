#include <imagepicker/aw_imagepickerfactory.h>
#include "aw_imagepicker_android.h"

namespace ImagePicker {
	IImagePicker* CImagePickerFactory::create() {
		return new CImagePicker_Android();
	}

	void CImagePickerFactory::destroy(IImagePicker* imagePicker) {
		delete imagePicker;
	}
}
