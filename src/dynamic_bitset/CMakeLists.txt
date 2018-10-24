python_add_module(${PROJECT_NAME}_dynamic_bitset dynamic_bitset.cpp)
target_link_libraries(${PROJECT_NAME}_dynamic_bitset ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
set_target_properties(${PROJECT_NAME}_dynamic_bitset PROPERTIES CXX_EXTENSIONS OFF)
