## Introduction
`cpp-template` is a simple cross-platform command-line tool that prints out "Hello World!".

## Usage
On Linux, run:
```
$ ./cpp-template
What up world!
```
On Windows, run:
```
$ ./cpp-template.exe
What up world!
```

## Config
### Install build tools
#### Linux
Install python and run the following:
```
python3 -m pip install -r build_requirments.txt --upgrade --user
```
#### Windows
Install python and run the following:
```
python -m pip install -r build_requirments.txt --upgrade --user
```
### Setup Conan profile
```
conan profile detect --force
```

## Build
```
conan install . -b missing -s build_type=Debug
conan install . -b missing -s build_type=Release
cmake --preset conan-default
```
Debug
```
cmake --build --preset conan-debug
ctest --preset conan-debug
```
Release
```
cmake --build --preset conan-release
ctest --preset conan-release
```
### Notes:
To build without units tests, run conan install command instead:
```
conan install . -b missing -s build_type=<config> -c tools.build:skip_test=True
```
where `<config>` is the configuration to build (ex. `Release``).
To generate conanbuild script in powershell on Windows run the following command:
```
conan install . -b missing -s build_type=Debug -g VirtualBuildEnv -c tools.env.virtualenv:powershell=True -c tools.cmake.cmaketoolchain:generator="Ninja Multi-Config"
./build/generators/conanbuild.ps1
```
