import AVFoundation
import UIKit
import Photos

class ImagePicker: ImagePickerDelegate, UIImagePickerControllerDelegate & UINavigationControllerDelegate {
	private var listeners: Set<Int64> = Set()

	func addListener(listener: Int64) {
		listeners.insert(listener)
	}

	func removeListener(listener: Int64) {
		listeners.remove(listener)
	}

	func clearAllListeners() {
		listeners.removeAll()
	}

	func onCreate() {}

	func onDestroy() {}

	func hasPermission() -> Bool {
        return AVCaptureDevice.authorizationStatus(for: .video) == .authorized
	}

	func shouldShowPermissionDescription() -> Bool {
		return false
	}

	func requestPermission() {
        if AVCaptureDevice.authorizationStatus(for: .video) !=  .authorized {
            AVCaptureDevice.requestAccess(for: .video, completionHandler: { (granted: Bool) in
                self.listeners.forEach { listener in
                    ImagePickerDelegate.onRequestImagePickerPermissionResult(listener, granted: granted)
                }
            })
        }
	}

	func pickImageFromGallery() {
        if UIImagePickerController.isSourceTypeAvailable(UIImagePickerControllerSourceType.photoLibrary){
            let imagePicker = UIImagePickerController()
            imagePicker.delegate = self
            imagePicker.allowsEditing = true
            imagePicker.sourceType = UIImagePickerControllerSourceType.photoLibrary
            UIApplication.shared.keyWindow?.rootViewController?.present(imagePicker, animated: true, completion: nil)
        }
	}

	func captureImageFromCamera() {

	}
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [String : Any]) {
        if let pickedImage = info[UIImagePickerControllerOriginalImage] as? UIImage {
            var filename = ""
            if let url = info[UIImagePickerControllerImageURL] as? URL {
                filename = url.path
            }
            var rotation: Int32 = 0
            switch (pickedImage.imageOrientation) {
            case .up, .upMirrored:
                rotation = 0
            case .left, .leftMirrored:
                rotation = -90
            case .right, .rightMirrored:
                rotation = 90
            case .down, .downMirrored:
                rotation = 180
            }
            self.listeners.forEach { listener in
                ImagePickerDelegate.onImagePicked(listener, filename: filename, source: 0, width: Int32(pickedImage.size.width * pickedImage.scale), height: Int32(pickedImage.size.height * pickedImage.scale), rotation: rotation)
            }
        }
        picker.dismiss(animated: true, completion: nil)
    }
}

@_cdecl("ImagePicker_create")
func ImagePicker_create() -> UnsafeMutablePointer<ImagePicker> {
	let imagePicker = UnsafeMutablePointer<ImagePicker>.allocate(capacity: 1)
	imagePicker.initialize(to: ImagePicker())
	return imagePicker
}

@_cdecl("ImagePicker_destroy")
func ImagePicker_destroy(ptr: UnsafeRawPointer) {
	ptr.deallocate()
}

@_cdecl("ImagePicker_addListener")
func ImagePicker_addListener(ptr: UnsafeMutablePointer<ImagePicker>, listener: Int64) {
	ptr.pointee.addListener(listener: listener)
}

@_cdecl("ImagePicker_removeListener")
func ImagePicker_removeListener(ptr: UnsafeMutablePointer<ImagePicker>, listener: Int64) {
	ptr.pointee.removeListener(listener: listener)
}

@_cdecl("ImagePicker_clearAllListeners")
func ImagePicker_clearAllListeners(ptr: UnsafeMutablePointer<ImagePicker>) {
	ptr.pointee.clearAllListeners()
}

@_cdecl("ImagePicker_onCreate")
func ImagePicker_onCreate(ptr: UnsafeMutablePointer<ImagePicker>) {
	ptr.pointee.onCreate()
}

@_cdecl("ImagePicker_onDestroy")
func ImagePicker_onDestroy(ptr: UnsafeMutablePointer<ImagePicker>) {
	ptr.pointee.onDestroy()
}

@_cdecl("ImagePicker_hasPermission")
func ImagePicker_hasPermission(ptr: UnsafeMutablePointer<ImagePicker>) -> Bool {
	return ptr.pointee.hasPermission()
}

@_cdecl("ImagePicker_shouldShowPermissionDescription")
func ImagePicker_shouldShowPermissionDescription(ptr: UnsafeMutablePointer<ImagePicker>) -> Bool {
	return ptr.pointee.shouldShowPermissionDescription()
}

@_cdecl("ImagePicker_requestPermission")
func ImagePicker_requestPermission(ptr: UnsafeMutablePointer<ImagePicker>) {
	ptr.pointee.requestPermission()
}

@_cdecl("ImagePicker_pickImageFromGallery")
func ImagePicker_pickImageFromGallery(ptr: UnsafeMutablePointer<ImagePicker>) {
	ptr.pointee.pickImageFromGallery()
}

@_cdecl("ImagePicker_captureImageFromCamera")
func ImagePicker_captureImageFromCamera(ptr: UnsafeMutablePointer<ImagePicker>) {
	ptr.pointee.captureImageFromCamera()
}