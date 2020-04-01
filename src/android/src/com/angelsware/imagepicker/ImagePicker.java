package com.angelsware.imagepicker;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.net.Uri;
import android.provider.MediaStore;

import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.core.content.FileProvider;

import com.angelsware.engine.ActivityResultListener;
import com.angelsware.engine.RequestPermissionResultListener;
import com.angelsware.engine.AppActivity;

import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class ImagePicker implements ActivityResultListener, RequestPermissionResultListener {
	private String[] mPermissions = new String[] { Manifest.permission.WRITE_EXTERNAL_STORAGE,
			Manifest.permission.READ_EXTERNAL_STORAGE,
			Manifest.permission.CAMERA };
	private String mLastStoragePath;
	private final int PERMISSION_REQUEST_CODE = 8000;
	private final int GALLERY_REQUEST_CODE = 8001;
	private final int CAMERA_REQUEST_CODE = 8002;

	public static native void onRequestImagePickerPermissionResult(boolean granted);
	public static native void onImagePicked(String filename, int source);

	public void create() {
		AppActivity appActivity = (AppActivity)AppActivity.getActivity();
		appActivity.addActivityResultListener(this);
		appActivity.addRequestPermissionResultListener(this);
	}

	public void destroy() {
		AppActivity appActivity = (AppActivity)AppActivity.getActivity();
		appActivity.removeActivityResultListener(this);
		appActivity.removeRequestPermissionResultListener(this);
	}

	public boolean hasPermission() {
		for (String permission : mPermissions) {
			if (ContextCompat.checkSelfPermission(AppActivity.getActivity(),
					permission) != PackageManager.PERMISSION_GRANTED)
				return false;

		}
		return true;
	}

	public boolean shouldShowRequestPermissionRationale() {
		return AppActivity.getActivity().shouldShowRequestPermissionRationale(Manifest.permission.WRITE_EXTERNAL_STORAGE) ||
				AppActivity.getActivity().shouldShowRequestPermissionRationale(Manifest.permission.CAMERA);
	}

	public void requestPermission() {
		ActivityCompat.requestPermissions(AppActivity.getActivity(), mPermissions, PERMISSION_REQUEST_CODE);
	}

	public void pickImageFromGallery() {
		String[] mimeTypes = {"image/jpg", "image/png"};
		Intent intent = new Intent(Intent.ACTION_PICK);
		intent.setType("image/*");
		intent.putExtra(Intent.EXTRA_MIME_TYPES, mimeTypes);
		AppActivity.getActivity().startActivityForResult(intent, GALLERY_REQUEST_CODE);
	}

	public void captureImageFromCamera() {
		try {
			Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
			intent.putExtra(MediaStore.EXTRA_OUTPUT, FileProvider.getUriForFile(AppActivity.getActivity(),
					AppActivity.getActivity().getPackageName() + ".provider", createTemporaryImageFile()));
			AppActivity.getActivity().startActivityForResult(intent, CAMERA_REQUEST_CODE);
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}

	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (resultCode == Activity.RESULT_OK) {
			switch (requestCode) {
				case GALLERY_REQUEST_CODE:
					Uri selectedImage = data.getData();
					String[] filePathColumn = { MediaStore.Images.Media.DATA };
					Cursor cursor = AppActivity.getActivity().getContentResolver().query(selectedImage, filePathColumn,
							null, null, null);
					cursor.moveToFirst();
					int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
					mLastStoragePath = cursor.getString(columnIndex);
					cursor.close();
					onImagePicked(this.mLastStoragePath, 0);
					break;
				case CAMERA_REQUEST_CODE:
					onImagePicked(this.mLastStoragePath, 1);
					break;
			}
		}
	}

	private File createTemporaryImageFile() throws IOException {
		File storageDir = new File(AppActivity.getActivity().getCacheDir() + "/portraits");
		if (!storageDir.exists()) {
			if (!storageDir.mkdirs()) {
				throw new IOException("could not create directory for pictures");
			}
		}

		String timeStamp = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
		String imageFileName = "photo_" + timeStamp + "_";

		File image = File.createTempFile(imageFileName, ".jpg", storageDir);
		mLastStoragePath = image.getAbsolutePath();
		return image;
	}

	@Override
	public void onRequestPermissionsResult(
			int requestCode,
			String[] permissions,
			int[] grantResults
	) {
		if (requestCode == PERMISSION_REQUEST_CODE && permissions.length > 0) {
			for (int result : grantResults) {
				if (grantResults[result] != PackageManager.PERMISSION_GRANTED) {
					onRequestImagePickerPermissionResult(false);
					return;
				}
			}
			onRequestImagePickerPermissionResult(true);
		}
	}
}
