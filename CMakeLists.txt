cmake_minimum_required(VERSION 3.10)
project(gtkProject)

set(CMAKE_CXX_STANDARD 17)

# GTK 설정
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

# 헤더 및 라이브러리 경로 포함
include_directories(${PKG_CONFIG_PATH})  # GTK 헤더 파일 경로 포함
link_directories(${LD_LIBRARY_PATH})     # GTK 라이브러리 경로 포함
add_definitions(${GTK_CFLAGS_OTHER})     # GTK 추가 설정




set(LIBRARIES
	Packet.h
	State.h
)


set(SOURCES
        main.cpp
        GtkButton.cpp
        IOHandler.cpp
)

# 실행파일 빌드
add_executable(gtkProject ${SOURCES})
target_link_libraries(gtkProject PkgConfig::GTK4)

