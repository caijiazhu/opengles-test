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
        if (configs)
        {
            free(configs);
            configs = NULL;
        }
        return false;
    }
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
    
    printEGLConfigurations(dpy);
    
    return 0;
}