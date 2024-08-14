//
// Created by goodc on 13/08/2024.
//

#ifndef KEIIMGUI_DRAWUI_H
#define KEIIMGUI_DRAWUI_H

#include "imgui.h"

int screenWidth = 0;
int screenHeight = 0;

bool g_Initialized = false;
ImGuiWindow* g_window = nullptr;

std::vector<ImGuiWindow*> g_windows;
void addWindow(ImGuiWindow* window) {
    g_windows.push_back(window);
}



void BeginDraw(){

    ImGui::Begin("test");

    g_window = ImGui::GetCurrentWindow();
    addWindow(g_window);
    ImGui::Text("yeaaa");
    ImGui::ShowDemoWindow();
    g_window = ImGui::FindWindowByName("Dear ImGui Demo");
    addWindow(g_window);

    ImGui::End();

}

#endif //KEIIMGUI_DRAWUI_H
