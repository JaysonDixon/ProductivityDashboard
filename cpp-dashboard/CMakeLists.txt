cmake_minimum_required(VERSION 3.16)
project(ProductivityDashboard)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_EXE_LINKER_FLAGS "-static")

find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

# Main dashboard application with menu and navigation (T1 & T2)
add_executable(ProductivityDashboard main_dashboard.cpp)

target_link_libraries(ProductivityDashboard 
    sfml-graphics 
    sfml-window 
    sfml-system
)

# Original version with all features
add_executable(ProductivityDashboardFull main.cpp)

target_link_libraries(ProductivityDashboardFull 
    sfml-graphics 
    sfml-audio 
    sfml-window 
    sfml-system
)

if(WIN32)
    target_link_libraries(ProductivityDashboard winmm)
    target_link_libraries(ProductivityDashboardFull winmm)
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
