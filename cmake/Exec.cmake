add_executable(timeseries-timeserie ${CMAKE_CURRENT_SOURCE_DIR}/tests/timeserie.cpp)
target_link_libraries(timeseries-timeserie PUBLIC core-timeseries)