#!/bin/bash

@echo off
setlocal

:: Require build flag
if not "%1"=="Release" if not "%1"=="Debug" (
    echo Usage: build.bat Release or Debug
    exit /b 1
)
set BUILD_TYPE=%1
set BUILD_DIR=bin/%BUILD_TYPE%

:: Create build directory if it does not exist
if not exist %BUILD_DIR% (
    echo Creating build directory..
    mkdir "%BUILD_DIR%"
)

:: Change directory to build folder
cd /d "%BUILD_DIR%"

:: Build the project
echo Building in %BUILD_TYPE% mode...
cmake -S ../.. -B . -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
cmake --build .