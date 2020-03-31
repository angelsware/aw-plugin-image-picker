#ifndef __AW_IMAGE_PICKER_FACTORY_H__
#define __AW_IMAGE_PICKER_FACTORY_H__

namespace ImagePicker {
	class IImagePicker;

	class CImagePickerFactory
	{
	public:
		static IImagePicker* create();
		static void destroy(IImagePicker* imagePicker);
	};
}

#endif
