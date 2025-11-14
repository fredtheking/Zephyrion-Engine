#pragma once
#pragma warning(disable: 4003)

#include <SDL3/SDL.h>
#include "vendor/include/glad/glad.h"
#include <SDL3/SDL_opengl.h>
#include <imgui.h>
#include <ImGuizmo.h>
#include <magic_enum_all.hpp>
#include "vendor/stb_image.h"
#include <fmt/args.h>
#include <fmt/color.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3.h>

#include <iostream>
#include <uuid.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <memory>
#include <chrono>
#include <any>
#include <functional>
#include <queue>
#include <mutex>
#include <atomic>
#include <thread>
#include <stdexcept>
#include <initializer_list>
#include <filesystem>
#include <utility>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <optional>

#include "zephyrion/utils/Macros.hpp"
#include "zephyrion/utils/Global.hpp"
