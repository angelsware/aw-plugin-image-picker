#ifndef __AW_IMAGE_PICKER_LISTENER_H__
#define __AW_IMAGE_PICKER_LISTENER_H__

namespace ImagePicker {
	enum class ESource;

	class IImagePickerListener
	{
	public:
		virtual void onRequestImagePickerPermissionResult(bool granted) = 0;
		virtual void onImagePicked(const char* filename, ESource source, int rotation) = 0;

	protected:
		virtual ~IImagePickerListener() {}
	};
}

#endif
