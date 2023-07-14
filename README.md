# gmath

A 3D math and linear algebra library for games written by Kevin Chin (https://kevch.in/)

Features:
- Vectors & vector operations
- Matrices & matrix operations
- Quaternions & quaternion operations
- Methods to create transformation matrices
- Methods to create projection matrices
- Method to create view matrix
- Spherical linear interpolation & vector linear interpolation

Testing:
This library has almost complete test coverage. Currently missing tests for like 2 functions. Some tests are verified against https://github.com/g-truc/glm results. Tests built with https://android.googlesource.com/platform/external/catch2/+/8a7df8b8732c7615d16d3d0a9d0cb9e4466e4719/single_include/catch2/catch.hpp.
- cd tests
- build with CMakeLists.txt
- run test executable
