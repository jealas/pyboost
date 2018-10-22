python_add_module(${PROJECT_NAME}_crc crc.cpp)
target_link_libraries(${PROJECT_NAME}_crc ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
set_target_properties(${PROJECT_NAME}_crc PROPERTIES CXX_EXTENSIONS OFF)
