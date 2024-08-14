//
// Created by goodc on 13/08/2024.
//

#ifndef KEIIMGUI_MAIN_H
#define KEIIMGUI_MAIN_H

#include <jni.h>
#include <errno.h>

#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <thread>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <sys/uio.h>

#include <fcntl.h>
#include <android/log.h>
#include <pthread.h>
#include <dirent.h>
#include <list>
#include <libgen.h>

#include <sys/mman.h>
#include <sys/wait.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>

#include <codecvt>
#include <chrono>
#include <queue>


//#include "KittyMemory/MemoryPatch.h"


//#include "ByNameModding/Tools.h"
//#include "ByNameModding/fake_dlfcn.h"
//#include "ByNameModding/Il2Cpp.h"
//
//#include "Unity/Vector3.hpp"
//#include "Unity/Vector2.hpp"
//#include "Unity/Rect.h"
//#include "Unity/Quaternion.h"
//#include "Unity/Color.h"

#include <imgui.h>
#include <imgui_impl_android.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
//#include "ImGui/fonts/Roboto-Regular.h"


//#include "bools.h"
//#include "drawing.h"
//#include "Includes/obfuscate.h"
//#include "Includes/Utils.h"

#include <EGL/egl.h>
#include <GLES3/gl3.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <sys/system_properties.h>

//uintptr_t sliderIntToUintPtr(int sliderValue) {
//    // Melakukan konversi langsung ke uintptr_t
//    uintptr_t uintptrValue = static_cast<uintptr_t>(sliderValue);
//    return uintptrValue;
//}




#endif //KEIIMGUI_MAIN_H
