
add_library(simpleLibrary
  csvjsonTest_main.cpp
)

find_library(M_LIB m)
target_link_libraries(simpleLibrary ${M_LIB})

