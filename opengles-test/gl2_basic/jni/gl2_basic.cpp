#include <stdio.h>

#include <EGL/egl.h>
#include <EGLUtils.h>

using namespace android;

static void checkEglError(const char* op, EGLBoolean returnVal = EGL_TRUE)
{
    if (returnVal != EGL_TRUE)
    {
        fprintf(stderr, "%s() returned %d\n", op, returnVal);
    }
    
    for (EGLint error = eglGetError(); error != EGL_SUCCESS; error = eglGetError())
    {
        fprintf(stderr, "after %s() eglError %s (0x%x)\n", op, EGLUtils::strerror(error), error);
    }
}


void printEGLConfiguration(EGLDisplay dpy, EGLConfig config)
{
#define X(VAL) {VAL, #VAL}
    struct { EGLint attribute; const char* name; } names[] = {
        X(EGL_BUFFER_SIZE),
        X(EGL_ALPHA_SIZE),
        X(EGL_BLUE_SIZE),
        X(EGL_GREEN_SIZE),
        X(EGL_RED_SIZE),
        X(EGL_DEPTH_SIZE),
        X(EGL_STENCIL_SIZE),
        X(EGL_CONFIG_CAVEAT),
        X(EGL_CONFIG_ID),
        X(EGL_LEVEL),
        X(EGL_MAX_PBUFFER_HEIGHT),
        X(EGL_MAX_PBUFFER_WIDTH),
        X(EGL_MAX_PBUFFER_PIXELS),
        X(EGL_NATIVE_RENDERABLE),
        X(EGL_NATIVE_VISUAL_ID),
        X(EGL_NATIVE_VISUAL_TYPE),
        X(EGL_SAMPLES),
        X(EGL_SAMPLE_BUFFERS),
        X(EGL_SURFACE_TYPE),
        X(EGL_TRANSPARENT_TYPE),
        X(EGL_TRANSPARENT_RED_VALUE),
        X(EGL_TRANSPARENT_GREEN_VALUE),
        X(EGL_TRANSPARENT_BLUE_VALUE),
        X(EGL_BIND_TO_TEXTURE_RGB),
        X(EGL_BIND_TO_TEXTURE_RGBA),
        X(EGL_MIN_SWAP_INTERVAL),
        X(EGL_MAX_SWAP_INTERVAL),
        X(EGL_LUMINANCE_SIZE),
        X(EGL_ALPHA_MASK_SIZE),
        X(EGL_COLOR_BUFFER_TYPE),
        X(EGL_RENDERABLE_TYPE),
        X(EGL_CONFORMANT),
    };
#undef X
    
    for (size_t j = 0; j < sizeof(names) / sizeof(names[0]); ++j)
    {
        EGLint value = -1;
        EGLint returnVal = eglGetConfigAttrib(dpy, config, names[j].attribute, &value);
        EGLint error = eglGetError();
        if (returnVal && EGL_SUCCESS == error)
        {
            printf(" %s: ", names[j].name);
            printf("%d (0x%x)", value, value);
        }
    }
    
    printf("\n");
}

int printEGLConfigurations(EGLDisplay dpy)
{
    EGLint numConfig = 0;
    EGLint returnVal = eglGetConfigs(dpy, NULL, 0, &numConfig);
    if (EGL_FALSE == returnVal)
    {
        return false;
    }
    
    printf("Number of EGL configuration : %d\n", numConfig);
    
    EGLConfig* configs = (EGLConfig*)malloc(numConfig * sizeof(EGLConfig));
    if (!configs)
    {
        printf("Could not allocate configs.\n");
        return false;
    }
    
    returnVal = eglGetConfigs(dpy, configs, numConfig, &numConfig);
    checkEglError("eglGetConfigs", returnVal);
    if (EGL_FALSE == returnVal)
    {
        free(configs);
        return false;
    }
    
    for (int i = 0; i < numConfig; ++i)
    {
        printf("Configuration %d\n", i);
        printEGLConfiguration(dpy, configs[i]);
    }
    
    free(configs);
    return true;
}

int main()
{
    EGLDisplay dpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (EGL_NO_DISPLAY == dpy)
    {
        printf("eglGetDisplay returned EGL_NO_DISPLAY.\n");
        return 0;
    }
    
    EGLint majorVersion, minorVersion;
    EGLBoolean returnValue = eglInitialize(dpy, &majorVersion, &minorVersion);
    if (EGL_FALSE == returnValue)
    {
        printf("eglInitialize failed.\n");
        return 0;    
    }
    
    if (!printEGLConfigurations(dpy))
    {
        printf("printEGLConfigurations failed.\n");
        return 0;
    }
    
    return 0;
}