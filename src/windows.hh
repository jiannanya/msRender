#ifndef WINDOWS_HH
#define WINDOWS_HH

#include <windows.h>
#include <minwindef.h>
#include "camera.hh"
#include "framebuffer.hh"

namespace msr{

#ifdef UNICODE
    static const wchar_t* WINDOW_CLASS_NAME = L"Class";
    static const wchar_t* WINDOW_ENTRY_NAME = L"Entry";
#else
    static const char* WINDOW_CLASS_NAME = "Class";
    static const char* WINDOW_ENTRY_NAME = "Entry";
#endif

struct OperateRecord {
    float x, y;
    boolean isLeftBtnDown = false;
    boolean close = false;
};

class window {
public:
    static void RegisterWindowClass();

    window(){}
    window(const char *title, framebuffer *fb);
    ~window();
    bool shouldClose();
    void drawBuffer();
    void updateOperateRecord();
    OperateRecord *getOperateRecord() {return m_OperateRecord;};
private:    
    HWND m_Handle;
    HDC m_MemoryDC;
    BYTE *m_ColorBuffer;
    framebuffer *m_FrameBuffer;
    OperateRecord *m_OperateRecord;
    int m_Width, m_Height;
    
    void createWindow(const char *title);
    void createWindowBuffer();
    void showWindow();
    void hideWindow();
};

}

#endif