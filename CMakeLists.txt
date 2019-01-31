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
)

if(WIN32)
	target_link_libraries(hitboxEditor wxmsw31u)
else()
	target_link_libraries(hitboxEditor ${wxWidgets_LIBRARIES})
endif()



