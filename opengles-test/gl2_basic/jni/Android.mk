LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

# Enable PIE manually. Will get reset on $(CLEAR_VARS).
# This is what enabling PIE translates to behind the scenes
LOCAL_CFLAGS += -fPIE
LOCAL_LDFLAGS += -fPIE -pie
                   
LOCAL_C_INCLUDES := \
                    $(JNI_H_INCLUDES) \
                    $(LOCAL_PATH)/../../include \
                    
LOCAL_SRC_FILES := \
                   gl2_basic.cpp \
                   
LOCAL_LDLIBS := -lEGL

LOCAL_MODULE := test-opengl-gl2_basic

                   
include $(BUILD_EXECUTABLE)