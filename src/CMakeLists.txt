cmake_minimum_required(VERSION 3.0.0)

project(${PROJECT_NAME})

set(SOURSES
        main.cpp
        radioData.cpp
)

set(HEADERS
        radioData.h
)

add_executable(${PROJECT_NAME} ${SOURSES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)
