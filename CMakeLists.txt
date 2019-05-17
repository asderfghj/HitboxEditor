cmake_minimum_required(VERSION 2.6)
project (HITBOXEDITOR)

if(WIN32)
	include_directories(
		${PROJECT_SOURCE_DIR}/contrib/wxwidgets/msvc/include
		${PROJECT_SOURCE_DIR}/contrib/jsonserialiser
		${PROJECT_SOURCE_DIR}/contrib/images
	)
		
	link_directories(
		${PROJECT_SOURCE_DIR}/contrib/wxwidgets/msvc/lib
	)
	
	add_definitions(-DWXUSINGDLL)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	
else()
	#set(wxWidgets_ROOT_DIR / usr/local)
	find_package(wxWidgets REQUIRED core base)
	include(${wxWidgets_USE_FILE})
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MD")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")

add_executable(hitboxEditor WIN32
	src/main.cpp
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
	src/HitboxData.cpp
	src/HitboxData.h
)

if(WIN32)
	target_link_libraries(hitboxEditor wxmsw31u)
else()
	target_link_libraries(hitboxEditor ${wxWidgets_LIBRARIES})
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MD")

