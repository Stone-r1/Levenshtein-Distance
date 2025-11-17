cmake_minimum_required(VERSION 3.12)
project(Levenshtein CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

set(SOURCES
    main.cpp

    models/LevenshteinModel.cpp

    models/storage/naiveMatrix.cpp
    models/storage/flattenedMatrix.cpp
    models/storage/rollingMatrix.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE 
    data
    models
    models/storage
)
