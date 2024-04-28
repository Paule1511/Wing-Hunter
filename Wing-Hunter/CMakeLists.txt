# CMakeList.txt: CMake-Projekt für "Wing-Hunter". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.

add_executable (Wing-Hunter "Wing-Hunter.cpp")

target_link_libraries(Wing-Hunter PRIVATE Wing-Utils)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Wing-Hunter PROPERTY CXX_STANDARD 20)
endif()

add_custom_command(
    TARGET Wing-Hunter POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy  # which executes "cmake - E copy_if_different..."
        $<TARGET_RUNTIME_DLLS:Wing-Hunter>      # <--this is in-file
        $<TARGET_FILE_DIR:Wing-Hunter>   # <--this is out-file path
)
# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.