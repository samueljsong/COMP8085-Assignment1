# Read Me

## Requirements
The following dependencies are required to build and run the application
- CMake 3.10 +
- C Compiler (GCC or Clang)
- libpng

## Installing Dependencies
Ubuntu/Debian 
```
sudo apt update
sudo apt install build-essential cmake libpng-dev
```

macOS
```
brew install cmake libpng
```

## Commands

|Command|Purpose|
|---|---|
|`cmake -S . -B build`|Configure Project|
|`cmake --build build`|Compile Project|
|`./app`|Run program|
|`cmake --build build --target clean`|Remove compiled outputs|
|`rm -rf build && rm -f app`|Completely remove generated build files and executables|

## How to run the app

**Ensure you ran the command to configure and compile project using commands above**

|Command|Function|
|---|---|
|`./app -e <image file> <message.txt> <secret \| secret.txt>`|Encodes message in message.txt using key in secret.txt using the image file as the carrier|
|`./app -d <image file> <secret \| secret.txt>`|Decodes message that has been encoded into the carrier image and prints out the decoded message|
