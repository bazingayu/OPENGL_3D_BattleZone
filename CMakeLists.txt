cmake_minimum_required(VERSION 3.15)
project(BattleZone)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_DIR "D:/Projects/Graphics/BattleZone")
include_directories(${PROJECT_DIR})
include_directories(${PROJECT_DIR}/SourceCode)
include_directories(${PROJECT_DIR}/war_src)
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
        war_src/CollisionSquare.cpp
        SourceCode/Camera.cpp
        war_src/GLMetaseq.c
        war_src/AutoBomb.cpp
        war_src/AutoWarObject.cpp
        SourceCode/Bomb.cpp
        war_src/BombArray.cpp
        war_src/BombTank.cpp
        war_src/CollisionBox.cpp
        war_src/CollisionBoxArray.cpp
        war_src/ControlWarObject.cpp
        war_src/Explosion.cpp
        SourceCode/MqoObject.cpp
        SourceCode/Tank.cpp
        SourceCode/AutoTank.cpp
        war_src/AutoWarControl.cpp
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










