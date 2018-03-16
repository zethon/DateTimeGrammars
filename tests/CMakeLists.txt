# if(NOT MSVC)
#     add_compile_options(-fno-access-control)
    
#     add_executable(io_test io_test.cpp)
#     target_link_libraries(io_test simple-web-server)
#     add_test(io_test io_test)

#     add_executable(parse_test parse_test.cpp)
#     target_link_libraries(parse_test simple-web-server)
#     add_test(parse_test parse_test)
# endif()

# if(OPENSSL_FOUND)
#     add_executable(crypto_test crypto_test.cpp)
#     target_link_libraries(crypto_test simple-web-server)
#     add_test(crypto_test crypto_test)
# endif()

add_executable(basic_test basic_test.cpp)
target_link_libraries(basic_test DateTimeGrammars ${Boost_LIBRARIES})
add_test(basic_test basic_test)