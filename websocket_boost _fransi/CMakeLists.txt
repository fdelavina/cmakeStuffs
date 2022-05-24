cmake_minimum_required(VERSION 3.0.0)
project(websocket_boost VERSION 0.1.0)


find_package(Boost 1.79.0 REQUIRED COMPONENTS system filesystem thread)
set (CMAKE_CXX_STANDARD 11)
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")

include_directories(${Boost_INCLUDE_DIRS}
                    ${PROJECT_SOURCE_DIR}/SooWSLib
                    ${PROJECT_SOURCE_DIR}/Trinity) 

set (LIB_WS_SOURCE
    SooWSLib/client.cpp
    SooWSLib/server.cpp
    )

set (LIB_TRINITY_SOURCE
    Trinity/trinity.cpp
    )



if(Boost_FOUND)
    #option(TESTI "Testing websocket" OFF) #OFF by default
    #if(TESTI)
        #add some compilation flags
        message(STATUS "PROJECT_SOURCE_DIR/Trinity: ${PROJECT_SOURCE_DIR}/Trinity")

      #  add_executable(websocket_test_exe test_main.cpp)
       # add_executable(websocket_test_server_exe test_main_server.cpp)
        add_executable(trinity_test_exe test_trinity.cpp )
      #  add_library(websocket_soo_lib SHARED ${LIB_WS_SOURCE})
        add_library(trinity_soo_lib SHARED ${LIB_TRINITY_SOURCE})
        
      #  target_link_libraries(websocket_soo_lib ${Boost_LIBRARIES} )
      #  target_link_libraries(websocket_test_exe ${Boost_LIBRARIES} websocket_soo_lib)
       # target_link_libraries(websocket_test_server_exe ${Boost_LIBRARIES} websocket_soo_lib)
        
        target_link_libraries(trinity_test_exe trinity_soo_lib oaris_msg_ws_lib)

    #else()
        #add some other compilation flags
     #   add_executable(websocket_boost main.cpp)
     #   target_link_libraries(websocket_boost ${Boost_LIBRARIES})
   # endif(TESTI)
  #  unset(TESTI CACHE) # <---- this is the important!
endif()

