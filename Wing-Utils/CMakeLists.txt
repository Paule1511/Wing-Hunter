set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


add_library(GLAD "${CMAKE_SOURCE_DIR}/external/GLAD/src/glad.c")
add_library(Wing-Utils SHARED "${CMAKE_SOURCE_DIR}/Wing-Utils/Wing-Utils.cpp")

target_link_libraries(Wing-Utils PRIVATE GLAD glfw)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Wing-Utils PROPERTY CXX_STANDARD 20)
endif()