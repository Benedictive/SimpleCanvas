set(HEADER_LIST "${SimpleCanvas_SOURCE_DIR}/include/simplecanvas/simple_canvas.hpp")

add_library(SimpleCanvas_library simple_canvas.cpp ${HEADER_LIST})

target_include_directories(SimpleCanvas_library PUBLIC ../include)

# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(SimpleCanvas_library PRIVATE SDL2::SDL2main)
endif()

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
target_link_libraries(SimpleCanvas_library PRIVATE SDL2::SDL2)

target_compile_features(SimpleCanvas_library PUBLIC cxx_std_20)