python_add_module(${PROJECT_NAME}_circular_buffer circular_buffer.cpp)
target_link_libraries(${PROJECT_NAME}_circular_buffer ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
set_target_properties(${PROJECT_NAME}_circular_buffer PROPERTIES CXX_EXTENSIONS OFF)
