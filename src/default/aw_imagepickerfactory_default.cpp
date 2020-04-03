#include <imagepicker/aw_imagepickerfactory.h>
#include "aw_imagepicker_default.h"

namespace ImagePicker {
	IImagePicker* CImagePickerFactory::create() {
		return new CImagePicker_Default();
	}

	void CImagePickerFactory::destroy(IImagePicker* imagePicker) {
		delete imagePicker;
	}
}
