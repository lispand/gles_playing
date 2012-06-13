LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := XOandroid
### Add all source file names to be included in lib separated by a whitespace
LOCAL_SRC_FILES := \
	XOandroid.cpp\
	SimpleGlFuncs.cpp\
	GLTriangle.cpp\
	FrameDrawer.cpp\
	IDrawable.cpp\
	Application.cpp\
	DrawConfig.cpp\
	DrawConfigPrivate.cpp

### Load additional libs 
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2
### Link NativeActivity support
LOCAL_STATIC_LIBRARIES := android_native_app_glue


include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)