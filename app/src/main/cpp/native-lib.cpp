
#include "main.h"
#include "drawUI.h"
#include <fonts/Roboto-Regular.h>
#include <style.h>

extern "C" {
JNIEXPORT void JNICALL Java_com_keiaxiro_keiimgui_GLES3JNIView_init(JNIEnv* env, jclass cls);
JNIEXPORT void JNICALL Java_com_keiaxiro_keiimgui_GLES3JNIView_resize(JNIEnv* env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_com_keiaxiro_keiimgui_GLES3JNIView_step(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_keiaxiro_keiimgui_GLES3JNIView_imgui_Shutdown(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_keiaxiro_keiimgui_GLES3JNIView_MotionEventClick(JNIEnv* env, jobject obj,jboolean down,jfloat PosX,jfloat PosY);
JNIEXPORT jstring JNICALL Java_com_keiaxiro_keiimgui_GLES3JNIView_getWindowRect(JNIEnv *env, jobject thiz);
JNIEXPORT void JNICALL Java_com_keiaxiro_keiimgui_GLES3JNIView_real(JNIEnv* env, jobject obj, jint width, jint height);
};

JNIEXPORT void JNICALL
Java_com_keiaxiro_keiimgui_GLES3JNIView_init(JNIEnv* env, jclass cls) {

    //SetUpImGuiContext
    if(g_Initialized) return ;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();



    //Set ImGui Style
    //ImGui::StyleColorsDark();
    SetupImGuiStyle();

    // Setup Platform/Renderer backends
    ImGui_ImplAndroid_Init();
    ImGui_ImplOpenGL3_Init("#version 300 es");

    io.Fonts->AddFontFromMemoryTTF(&Roboto_Regular, 48, 28);

    ImGui::GetStyle().ScaleAllSizes(3.0f);
    io.FontGlobalScale = 1.f;

    g_Initialized=true;
}

JNIEXPORT void JNICALL
Java_com_keiaxiro_keiimgui_GLES3JNIView_resize(JNIEnv* env, jobject obj, jint width, jint height) {
    screenWidth = (int) width;
    screenHeight = (int) height;
    glViewport(0, 0, width, height);
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigWindowsMoveFromTitleBarOnly = true;
    io.IniFilename = nullptr;
    ImGui::GetIO().DisplaySize = ImVec2((float)width *1.5f, (float)height);

}

JNIEXPORT void JNICALL
Java_com_keiaxiro_keiimgui_GLES3JNIView_step(JNIEnv* env, jobject obj) {

    ImGuiIO& io = ImGui::GetIO();
    ImFontConfig font_cfg;
    font_cfg.SizePixels = 48.0f;
    static bool show_MainMenu_window = true;


    //Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(screenWidth,  screenHeight);//？Settings window
    ImGui::NewFrame();


    if (show_MainMenu_window) {
        BeginDraw();
        //DrawESP(ImGui::GetBackgroundDrawList(), screenWidth, screenHeight);
    }
    ImGui::EndFrame();
    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

JNIEXPORT void JNICALL Java_com_keiaxiro_keiimgui_GLES3JNIView_imgui_Shutdown(JNIEnv* env, jobject obj){
    if (!g_Initialized)
        return;
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
    g_Initialized=false;
}

JNIEXPORT void JNICALL Java_com_keiaxiro_keiimgui_GLES3JNIView_MotionEventClick(JNIEnv* env, jobject obj,jboolean down,jfloat PosX,jfloat PosY){
    ImGuiIO & io = ImGui::GetIO();
    io.MouseDown[0] = down;
    io.MousePos = ImVec2(PosX,PosY);
}

JNIEXPORT jstring JNICALL Java_com_keiaxiro_keiimgui_GLES3JNIView_getWindowRect(JNIEnv *env, jobject thiz) {
    //get drawing window
    // TODO: accomplish getWindowSizePos()
    /* in drawui.h
    ImGuiWindow* g_window = ImGui::GetCurrentWindow(); // main window

    ImGuiWindow* g_window1 = ImGui::GetCurrentWindow(); // another imgui window
    */
    char result[256] = "0|0|0|0";

    // Periksa jika ada setidaknya satu g_window
    if (!g_windows.empty()) {
        // Inisialisasi nilai container dengan nilai g_window pertama
        int containerMinX = g_windows[0]->Pos.x;
        int containerMinY = g_windows[0]->Pos.y;
        int containerMaxX = g_windows[0]->Pos.x + g_windows[0]->Size.x;
        int containerMaxY = g_windows[0]->Pos.y + g_windows[0]->Size.y;

        // Iterasi melalui g_windows untuk menemukan nilai maksimum dan minimum
        for (size_t i = 1; i < g_windows.size(); ++i) {
            containerMinX = fmin(containerMinX, g_windows[i]->Pos.x);
            containerMinY = fmin(containerMinY, g_windows[i]->Pos.y);
            containerMaxX = fmax(containerMaxX, g_windows[i]->Pos.x + g_windows[i]->Size.x);
            containerMaxY = fmax(containerMaxY, g_windows[i]->Pos.y + g_windows[i]->Size.y);
        }

        // Hitung ukuran container
        int containerSizeX = containerMaxX - containerMinX;
        int containerSizeY = containerMaxY - containerMinY;

        // Format nilai container menjadi string
        sprintf(result, "%d|%d|%d|%d", containerMinX, containerMinY, containerSizeX, containerSizeY);
    }

    // Kembalikan string hasil format
    return env->NewStringUTF(result);
}
