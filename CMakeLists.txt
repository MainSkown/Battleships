cmake_minimum_required(VERSION 3.24)
project(Battleships)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

set(CMAKE_CXX_STANDARD 23)

add_executable(Battleships main.cpp src/GameEngine.h src/GameEngine.cpp src/Map.h src/Map.cpp src/TextureManager.h src/UI/Button.h src/UI/Button.cpp src/UI/UI.h src/UI/UIElements.h src/TextureManager.cpp src/UI/UI.cpp src/BattleshipAI.cpp src/BattleshipAI.h src/UI/Sprite.h src/UI/Sprite.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image)
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${SDL2_CFLAGS_OTHER})