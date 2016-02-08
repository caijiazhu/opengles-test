#ifndef ANDROID_UI_EGLUTILS_H
#define ANDROID_UI_EGLUTILS_H

#include <stdint.h>
#include <stdlib.h>

//#include <system/window.h>
//#include <utils/Errors.h>
#include <EGL/egl.h>

// ----------------------------------------------------------------------------
namespace android {
// ----------------------------------------------------------------------------

class EGLUtils
{
public:
    static inline const char* strerror(EGLint err);    
};

// ----------------------------------------------------------------------------

const char* EGLUtils::strerror(EGLint err)
{
    switch (err){
        case EGL_SUCCESS:             return "EGL_SUCCESS";
        case EGL_NOT_INITIALIZED:     return "EGL_NOT_INITIALIZED";
        case EGL_BAD_ACCESS:          return "EGL_BAD_ACCESS";
        case EGL_BAD_ALLOC:           return "EGL_BAD_ALLOC";
        case EGL_BAD_ATTRIBUTE:       return "EGL_BAD_ATTRIBUTE";
        case EGL_BAD_CONFIG:          return "EGL_BAD_CONFIG";
        case EGL_BAD_CONTEXT:         return "EGL_BAD_CONTEXT";
        case EGL_BAD_CURRENT_SURFACE: return "EGL_BAD_CURRENT_SURFACE";
        case EGL_BAD_DISPLAY:         return "EGL_BAD_DISPLAY";
        case EGL_BAD_MATCH:           return "EGL_BAD_MATCH";
        case EGL_BAD_NATIVE_PIXMAP:   return "EGL_BAD_NATIVE_PIXMAP";
        case EGL_BAD_NATIVE_WINDOW:   return "EGL_BAD_NATIVE_WINDOW";
        case EGL_BAD_PARAMETER:       return "EGL_BAD_PARAMETER";
        case EGL_BAD_SURFACE:         return "EGL_BAD_SURFACE";
        case EGL_CONTEXT_LOST:        return "EGL_CONTEXT_LOST";
        default: return "UNKNOWN";
    }
}

}

#endif /* ANDROID_UI_EGLUTILS_H */