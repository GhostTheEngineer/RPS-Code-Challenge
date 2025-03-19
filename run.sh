#!/bin/bash

@echo off
setlocal

@REM Require build flag
if not "%1"=="Release" if not "%1"=="Debug" (
    echo Usage: build.bat Release or Debug
    exit /b 1
)

set BUILD_TYPE=%1

if exist out/%BUILD_TYPE%/RPS.exe (
    start out/%BUILD_TYPE%/RPS.exe
) else (
    echo Could not find executable, run ./build BUILD_TYPE in ./example directory.
)