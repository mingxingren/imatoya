//
// Created by MMK on 2021/8/27.
//

#ifndef SRC_IMGUI_WRAPER_H
#define SRC_IMGUI_WRAPER_H

#include <functional>
#include <mutex>
#include <d3d11.h>

class CImguiWraper {
public:
    CImguiWraper();
    ~CImguiWraper();

    bool SetWindowId(HWND handle);
    void Rendering(std::function<void()> func);

private:
    bool _CreateDeviceD3D(HWND handle);
    void _CreateRenderTarget();
    void _CleanupRenderTarget();

private:
    ID3D11Device*            m_pd3dDevice;
    ID3D11DeviceContext*     m_pd3dDeviceContext = nullptr;
    IDXGISwapChain*          m_pSwapChain = nullptr;
    ID3D11RenderTargetView*  m_mainRenderTargetView = nullptr;

    static std::once_flag m_initFlag;
};

#endif //SRC_IMGUI_WRAPER_H
