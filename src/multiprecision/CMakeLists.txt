python_add_module(${PROJECT_NAME}_multiprecision multiprecision.cpp)
target_link_libraries(${PROJECT_NAME}_multiprecision ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
set_target_properties(${PROJECT_NAME}_multiprecision PROPERTIES CXX_EXTENSIONS OFF)
