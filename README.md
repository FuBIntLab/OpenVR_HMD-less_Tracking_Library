# OpenVR HMD-less Tracking Library

This repository contains an openVR Tracking library that uses the HTC Vive Base Stations and Trackers for 3D tracking without the need of the HMD or the controllers at any point.
There is also a Base Unity project that demonstrates the use of the library inside unity that can also be used as a template for custom projects that want to use this tracking.

## Library

CMake project that compiles the tracking library as a dll

|Exposed Functions by tracking.dll|
|---|
| void startTracking() |
| void stopTracking() |
| void updatePositions(int size, float *data, bool invertX, bool invertY, bool flipXY )|
| int getNumberOfPlayers() |
| int getNumberOfBaseStations() |

## Unity Tracking Base Project

Unity project that implements all the necessary functions to use the tracking inside unity
