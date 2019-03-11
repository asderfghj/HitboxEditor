cmake_minimum_required(VERSION 2.6)
project (HITBOXEDITOR)

if(WIN32)
	include_directories(
		${PROJECT_SOURCE_DIR}/contrib/wxwidgets/msvc/include
	)
		
	link_directories(
		${PROJECT_SOURCE_DIR}/contrib/wxwidgets/msvc/lib
	)
	
	add_definitions(-DWXUSINGDLL)
	
else()
	#set(wxWidgets_ROOT_DIR / usr/local)
	find_package(wxWidgets REQUIRED core base)
	include(${wxWidgets_USE_FILE})
endif()


add_executable(hitboxEditor WIN32
	src/main.cpp
	src/Headers.h
	src/Application.cpp
	src/Application.h
	src/Frame.cpp
	src/Frame.h
	src/ImageTab.cpp
	src/ImageTab.h
	src/Image.cpp
	src/Image.h
	src/HitboxTab.cpp
	src/HitboxTab.h
	src/ImagesContainer.cpp
	src/ImagesContainer.h
	src/Canvas.cpp
	src/Canvas.h
	src/CanvasView.cpp
	src/CanvasView.h
	src/Hitbox.cpp
	src/Hitbox.h
)

if(WIN32)
	target_link_libraries(hitboxEditor wxmsw31u)
else()
	target_link_libraries(hitboxEditor ${wxWidgets_LIBRARIES})
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MD")

