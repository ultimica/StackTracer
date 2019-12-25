cmake_minimum_required(VERSION 3.0)

SET(PROJ_NAME "PPPROJ")
PROJECT(${PROJ_NAME})



# Define lib List
add_subdirectory(PrintLib)
add_subdirectory(boost_stacktrace)

list(APPEND EXTRA_LIBS PrintLib boost_stacktrace)
# list(APPEND EXTRA_INC PrintLib boost_stacktrace)


add_executable(${PROJ_NAME} stacktraceparser.cpp)

target_link_libraries(${PROJ_NAME} PUBLIC ${EXTRA_LIBS})
target_include_directories(${PROJECT_NAME}
                    PUBLIC ${PROJECT_SOURCE_DIR}/PrintLib ${PROJECT_SOURCE_DIR}/boost_stacktrace 
                    )


# Configuration types
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)

SET(${PROJ_NAME}_PATH_INSTALL "${PROJECT_SOURCE_DIR}/output/" CACHE PATH "This directory contains installation Path")
SET(CMAKE_DEBUG_POSTFIX "d")

# include_directories(${PROJECT_SOURCE_DIR})


INSTALL(TARGETS ${PROJ_NAME} DESTINATION "${${PROJ_NAME}_PATH_INSTALL}/")

