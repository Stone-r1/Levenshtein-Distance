cmake_minimum_required(VERSION 3.12)
project(Levenshtein CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

set(SOURCES
    src/main.cpp
    
    models/model1.cpp
    models/model2.cpp
    models/model3.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE 
    src
    data
    models
)
