//
// Created by MMK on 2021/8/29.
//

#include "Application.h"

#include <windows.h>
#include "matoya.h"
#include "imgui_impl_win32.h"

struct TApplicationInfo{
    MTY_App *app = nullptr;
    bool quit = false;
    HWND main_win_handle = NULL;
    CApplication* application;
};

bool MatoyaAppFunc(void *opaque)
{
    TApplicationInfo *ctx = static_cast<TApplicationInfo*>(opaque);
    for (auto &index : ctx->application->m_vtWindows)
    {
        index.wraper.Rendering(index.funcRenderEvent);
    }

    return true;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void MatoyaEventFunc(const MTY_Event *evt, void *opaque)
{
    TApplicationInfo *ctx = static_cast<TApplicationInfo*>(opaque);

    if (evt->type == MTY_EVENT_BUTTON)
    {
        ImGui_ImplWin32_WndProcHandler(ctx->main_win_handle,  evt->button.pressed ? WM_LBUTTONDOWN : WM_LBUTTONUP, evt->button.button, 0);
    }
    MTY_PrintEvent(evt);

    if (evt->type == MTY_EVENT_CLOSE)
        ctx->quit = true;
}

CApplication::CApplication() : m_pApplicationInfo(new TApplicationInfo){
    m_pApplicationInfo->application = this;
    m_pApplicationInfo->app = MTY_AppCreate(MatoyaAppFunc, MatoyaEventFunc, m_pApplicationInfo.get());
}

CApplication::~CApplication() {
    MTY_AppDestroy(&(m_pApplicationInfo->app));
}

void CApplication::CreateNewDialog(MTY_WindowDesc desc, std::function<void()> func){
    MTY_Window WindowId = MTY_WindowCreate(m_pApplicationInfo->app, &desc);
    HWND handle = (HWND) MTY_GetWindowHandle(m_pApplicationInfo->app, WindowId);

    TDialog dialog;
    dialog.window_id = WindowId;
    dialog.wraper.SetWindowId(handle);
    dialog.funcRenderEvent = func;
    m_vtWindows.push_back(dialog);
}

void CApplication::Run() {
    MTY_AppRun(m_pApplicationInfo->app);
}