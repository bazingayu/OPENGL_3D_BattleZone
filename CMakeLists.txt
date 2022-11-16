cmake_minimum_required(VERSION 3.15)
project(BattleZone)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_DIR "D:/Projects/Graphics/BattleZone")
include_directories(${PROJECT_DIR})
include_directories(${PROJECT_DIR}/SourceCode)
include_directories(${PROJECT_DIR}/freeglut/include)
include_directories(${PROJECT_DIR}/glew-1.10.0/include)
include_directories(${PROJECT_DIR}/glm)
include_directories(${PROJECT_DIR}/assimp/include)

LINK_DIRECTORIES("${PROJECT_DIR}/freeglut/lib")
LINK_DIRECTORIES("${PROJECT_DIR}/glew-1.10.0/lib/Release/Win32")
LINK_DIRECTORIES("${PROJECT_DIR}/assimp/lib/Debug")

add_executable(BattleZone
        main.cpp
        SourceCode/maths_funcs.cpp
        SourceCode/Terrain.cpp
        SourceCode/Texture.cpp
        SourceCode/Tvector.cpp
        SourceCode/Tray.cpp
        SourceCode/CollisionSquare.cpp
        SourceCode/Camera.cpp
        SourceCode/GLMetaseq.c
        SourceCode/AutoBomb.cpp
        SourceCode/AutoWarObject.cpp
        SourceCode/Bomb.cpp
        SourceCode/BombArray.cpp
        SourceCode/BombTank.cpp
        SourceCode/CollisionBox.cpp
        SourceCode/CollisionBoxArray.cpp
        SourceCode/ControlWarObject.cpp
        SourceCode/Explosion.cpp
        SourceCode/MqoObject.cpp
        SourceCode/Tank.cpp
        SourceCode/AutoTank.cpp
        SourceCode/AutoWarControl.cpp
        )

target_link_libraries(${PROJECT_NAME} "freeglut.lib")
target_link_libraries(${PROJECT_NAME} "glew32.lib")
target_link_libraries(${PROJECT_NAME} "assimp.lib")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assimp/bin/Assimp32d.dll
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/freeglut/bin/freeglut.dll
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/glew-1.10.0/bin/Release/Win32/glew32.dll
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})










