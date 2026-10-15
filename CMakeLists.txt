cmake_minimum_required(VERSION 3.10)

project(PNGSteganography LANGUAGES C)

# Use C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find libpng
find_package(PNG REQUIRED)

# Create library from source files
add_library(steganography_lib
    src/cli.c
    src/file_reader.c
    src/main_functions.c
    src/otp.c
    src/png_reader.c
)

# Include header files
target_include_directories(steganography_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link libpng to the library
target_link_libraries(steganography_lib PUBLIC PNG::PNG)

# Create executable
add_executable(app src/main.c)

# Link library to executable
target_link_libraries(app PRIVATE steganography_lib)

# Place executable in project root
set_target_properties(app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
