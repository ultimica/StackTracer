# first we add the executable that generates the table
add_library(PrintLib h_cpp.cpp)




# state that anybody linking to us needs to include the current source dir
# to find MathFunctions.h, while we don't.
# state that we depend on Tutorial_BINARY_DIR but consumers don't, as the
# TutorialConfig.h include is an implementation detail
# state that we depend on our binary dir to find Table.h
target_include_directories(PrintLib
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

# # install rules
# install(TARGETS PrintLib DESTINATION lib)
# install(FILES MathFunctions.h DESTINATION include)
