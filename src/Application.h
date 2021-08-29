//
// Created by MMK on 2021/8/29.
//

#ifndef SRC_APPLICATION_H
#define SRC_APPLICATION_H

#include <memory>
#include <functional>
#include <vector>
#include "matoya.h"
#include "imgui_wraper.h"

struct TApplicationInfo;
class CApplication {
public:
    CApplication();
    ~CApplication();

    void CreateNewDialog(MTY_WindowDesc desc, std::function<void()> func);
    void Run();

private:
    friend bool MatoyaAppFunc(void *opaque);

private:
    struct TDialog{
        MTY_Window  window_id;
        CImguiWraper wraper;
        std::function<void()> funcRenderEvent;
    };

private:
    std::unique_ptr<TApplicationInfo> m_pApplicationInfo;
    std::vector<TDialog> m_vtWindows;
};

#endif //SRC_APPLICATION_H
