#include <iostream>

#include <tchar.h>
#include "imgui.h"
#include "Application.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    CApplication app;

    MTY_WindowDesc desc;
    desc.title = "My Window";
    desc.origin = MTY_ORIGIN_CENTER;
    desc.api = MTY_GFX_NONE;
    desc.width = 800;
    desc.height = 600;
    desc.minWidth = 0;
    desc.minWidth = 0;
    desc.x = 0;
    desc.y = 0;
    desc.maxHeight = 0;
    desc.fullscreen = false;
    desc.hidden = false;
    desc.vsync = false;

    app.CreateNewDialog(desc, [](){
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    });

    app.Run();
    return 0;
}
