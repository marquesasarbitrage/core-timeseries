add_library(
    core-timeseries 
    STATIC 
        src/errors/base.cpp
        src/errors/timeserie.cpp

        src/timeserie.cpp)
target_link_libraries(core-timeseries PUBLIC core-datetime)
target_link_libraries(core-timeseries PUBLIC core-math)
target_include_directories(core-timeseries  PUBLIC include)
