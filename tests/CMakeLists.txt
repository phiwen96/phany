# Testing library
set (${self} testlib_${PROJECT_NAME})
ph_fetch (catch2)
file(GLOB_RECURSE HEADER_LIST "include/*.hpp")
file(GLOB SOURCE_LIST *.cpp)
add_executable (testlib_${PROJECT_NAME} ${SOURCE_LIST} ${HEADER_LIST})
target_link_libraries (testlib_${PROJECT_NAME} PRIVATE ph::time ph::macros ph::type_list ph::type_list ${PROJECT_NAME} Catch2::Catch2)
target_include_directories (testlib_${PROJECT_NAME} PRIVATE include)
ph_precompile (TARGET testlib_${PROJECT_NAME} PRIVATE PCH ${std_pch})
add_test (NAME testtestlib_${PROJECT_NAME} COMMAND ${self}) 
 






