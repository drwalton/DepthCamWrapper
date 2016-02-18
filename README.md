# DepthCamWrapper
Wrapper library designed to abstract a variety of RGB-D (depth) cameras.

# Requirements

* OpenNI2

For Windows Only:
* Kinect 1.8 SDK

This requires some C++11 support (specifically `std::unique_ptr`).

# Building

## Windows

* Clone repository
* Open Cmake-Gui application
* Under "Where is the source code: ", set the root of the repository.
* Under "Where to build the binaries: ", set a suitable directory (I used a subdirectory called "build").
* Click Configure
* Click Generate
* Open the Visual Studio solution that has been created in the build directory.
* Build for desired target (libraries will be placed in the "lib" subdirectory).

