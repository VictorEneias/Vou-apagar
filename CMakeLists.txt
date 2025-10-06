# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(IDJ_Trabalho2 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE SRC_FILES "src/*.cpp")
add_executable(game ${SRC_FILES})
target_include_directories(game PRIVATE include)


find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)


# Includes/libs
target_include_directories(game PRIVATE
${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS}
)


# Link
if (APPLE)
target_link_libraries(game PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})
else()
target_link_libraries(game PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})
endif()


# Copiar Recursos para a pasta do binário após build
add_custom_command(TARGET game POST_BUILD
COMMAND ${CMAKE_COMMAND} -E remove_directory $<TARGET_FILE_DIR:game>/Recursos
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Recursos $<TARGET_FILE_DIR:game>/Recursos
)