add_library(boost_stacktrace linux_stacktrace.cpp)



target_include_directories(
        boost_stacktrace
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../boost_1_72_0
        )

target_link_directories(boost_stacktrace PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../boost_1_72_0/stage/lib/)
