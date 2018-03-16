add_executable(basic_test basic_test.cpp)

target_link_libraries(basic_test 
    DateTimeGrammars 
    ${Boost_LIBRARIES}
    Qt5::Core
)

add_test(basic_test basic_test)