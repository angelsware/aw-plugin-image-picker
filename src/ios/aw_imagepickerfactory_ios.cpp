#include <imagepicker/aw_imagepickerfactory.h>
#include "aw_imagepicker_ios.h"

namespace ImagePicker {
	IImagePicker* CImagePickerFactory::create() {
		return new CImagePicker_Ios();
	}

	void CImagePickerFactory::destroy(IImagePicker* imagePicker) {
		delete imagePicker;
	}
}
