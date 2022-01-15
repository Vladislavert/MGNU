cmake_minimum_required(VERSION 3.10)
project(booleanMatrix)
set(CMAKE_CXX_STANDARD 17 )

set(COMMON_FLAGS "-g -Wall -Wextra -Werror")

set(CMAKE_CXX_FLAGS "${COMMON_FLAGS}")

include_directories(
		inc
		src/boolean_matrix
 		${CMAKE_CURRENT_SOURCE_DIR}
 		${EIGEN3_INCLUDE_DIR}
	)

set(CPP_FILES 
	src/boolean_matrix/BooleanMatrix.cpp
)

add_library(booleanMatrix STATIC ${CPP_FILES})

add_executable(main main.cpp)

target_link_libraries(main booleanMatrix ${CMAKE_THREAD_LIBS_INIT})