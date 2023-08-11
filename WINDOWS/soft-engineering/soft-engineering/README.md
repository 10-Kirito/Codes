# A Small Demo to Show How A C++ Project Works

## Dependencies

To run this demo, you need to install:

- gcc
- make
- cmake

## Structure of Demo

```
.
├── CMakeLists.txt
├── README.md
├── source
│   ├── Node.h
│   └── main.cpp
└── test
    ├── GlobalTest.cpp
    ├── NodeTest.cpp
    └── main.cpp
```

+ CMakeLists.txt: A file to guide cmake to generate Makefile
+ source: This directory contains source files
+ test: This directory contains unit test files
+ third-party-lib: This directory contains third-party libraries, in this demo, it's google test frame.

## How to run the project

You can run the following command to generate Makefile in directory `test`:

```shell
cmake -B build
```

And you can generate all executable files in the project with the following command:

```shell
cmake --build build
```

After that, you can find two executable files under directory `test`:

1. soft_engineering: This is the release executable file.
2. soft_engineering_tests: This is the unit test executable file.