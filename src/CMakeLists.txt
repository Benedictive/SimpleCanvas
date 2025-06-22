set(HEADER_LIST "${SimpleCanvas_SOURCE_DIR}/include/simplecanvas/simple_canvas.hpp")

add_library(SimpleCanvas_library simple_canvas.cpp ${HEADER_LIST})

target_include_directories(SimpleCanvas_library PUBLIC ../include)

target_link_libraries(SimpleCanvas_library PRIVATE SDL3::SDL3)

target_compile_features(SimpleCanvas_library PUBLIC cxx_std_23)