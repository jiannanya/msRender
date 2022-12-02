#include "windows.hh"
#include <iostream>
#include <assert.h>
#include <Windows.h>

namespace msr{



LRESULT CALLBACK ProcessMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    window* tempWindow = (window*)GetProp(hWnd, WINDOW_ENTRY_NAME);
    
    if (tempWindow == NULL) {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    OperateRecord *operateRecord = tempWindow->getOperateRecord();
    
    if (uMsg == WM_CLOSE) {
        operateRecord->close = true;
        return 0;
    } else if (uMsg == WM_LBUTTONDOWN) {
        operateRecord->isLeftBtnDown = true;
        return 0;
    } else if (uMsg == WM_LBUTTONUP) {
        operateRecord->isLeftBtnDown = false;
        return 0;
    } else {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
};


window::window(const char *title, framebuffer *fb) {
    if(!fb){
        std::cerr<<"unvalid frambuffer"<<std::endl;
        return;
    }
    m_OperateRecord = new OperateRecord();
    m_Width = fb->getWidth();
    m_Height = fb->getHeight();
    m_FrameBuffer = fb;
    m_ColorBuffer = fb->getColorBuffer();
    RegisterWindowClass();
    createWindow(title);
    createWindowBuffer();
    showWindow();
    
    SetProp(m_Handle, WINDOW_ENTRY_NAME, this);
};

window::~window() {
    if (m_FrameBuffer) delete m_FrameBuffer;
    if (m_OperateRecord) delete m_OperateRecord;
    m_FrameBuffer = nullptr;
    m_OperateRecord = nullptr;
};

void window::RegisterWindowClass() {
    ATOM class_atom;
    WNDCLASS window_class;
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = ProcessMessage;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance = GetModuleHandle(NULL);
    window_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    window_class.lpszMenuName = NULL;
    window_class.lpszClassName = WINDOW_CLASS_NAME;
    class_atom = RegisterClass(&window_class);
    assert(class_atom != 0);
    // UNUSED_VAR(class_atom);
};

void window::createWindow(const char *title_) {
    DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    RECT rect;
    HWND handle;
    rect.left = 0;
    rect.top = 0;
    rect.right = m_Width;
    rect.bottom = m_Height;
    AdjustWindowRect(&rect, style, 0);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

#ifdef UNICODE
    wchar_t title[256];
    mbstowcs(title, title_, 256);
#else
    const char *title = title_;
#endif

    handle = CreateWindow(WINDOW_CLASS_NAME, title, style,
                          CW_USEDEFAULT, CW_USEDEFAULT, width, height,
                          NULL, NULL, GetModuleHandle(NULL), NULL);
    
    m_Handle = handle;
    assert(handle != NULL);
};


void window::createWindowBuffer() {
    BITMAPINFOHEADER bi_header;
    HBITMAP dib_bitmap;
    HBITMAP old_bitmap;
    HDC window_dc;
    HDC memory_dc;

    window_dc = GetDC(m_Handle);
    memory_dc = CreateCompatibleDC(window_dc);
    ReleaseDC(m_Handle, window_dc);

    memset(&bi_header, 0, sizeof(BITMAPINFOHEADER));
    bi_header.biSize = sizeof(BITMAPINFOHEADER);
    bi_header.biWidth = m_Width;
    bi_header.biHeight = -m_Height;  /* top-down */
    bi_header.biPlanes = 1;
    bi_header.biBitCount = 32;
    bi_header.biCompression = BI_RGB;
    dib_bitmap = CreateDIBSection(memory_dc, (BITMAPINFO*)&bi_header,
                                  DIB_RGB_COLORS, (void**)&m_ColorBuffer,
                                  NULL, 0);
    assert(dib_bitmap != NULL);
    old_bitmap = (HBITMAP)SelectObject(memory_dc, dib_bitmap);
    DeleteObject(old_bitmap);

    m_MemoryDC = memory_dc;

};

void window::drawBuffer() {
   
    m_ColorBuffer = m_FrameBuffer->getColorBuffer();

    HDC window_dc = GetDC(m_Handle);
    HDC memory_dc = m_MemoryDC;

    BitBlt(window_dc, 0, 0, m_Width, m_Height, memory_dc, 0, 0, SRCCOPY);
    ReleaseDC(m_Handle, window_dc);
};

void window::showWindow() {
    if (!m_Handle) {
        return;
    }
    ShowWindow(m_Handle, SW_SHOW);
    UpdateWindow(m_Handle);
};

void window::hideWindow() {
    if (!m_Handle) {
        return;
    }
    ShowWindow(m_Handle, SW_HIDE);
};

bool window::shouldClose() {
    return m_OperateRecord->close;
};

void window::updateOperateRecord() {
    POINT point;
    GetCursorPos(&point);
    ScreenToClient(m_Handle, &point);
    m_OperateRecord->x = point.x;
    m_OperateRecord->y = point.y;
};

};