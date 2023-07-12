# OpenVR HMD-less Tracking Library

This repository contains an openVR Tracking library that uses the HTC Vive Base Stations and Trackers for 3D tracking without the need of the HMD or the controllers at any point.
There is also a Base Unity project that demonstrates the use of the library inside unity that can also be used as a template for custom projects that want to use this tracking.

This library was developed as a UPF Bachelor's Final Project for FubIntLab and its interactive interaction Mixed Meality space and is now being released as an open source project "as is".

![FubIntLab](https://www.upf.edu/documents/8512687/0/FubIntLab.jpg/a5f726e4-2cdd-099b-98ae-04c76f221b63?t=1552667793987)

[FubIntLab Website](https://www.upf.edu/web/fubintlab)

[UPF Website](https://www.upf.edu/)
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

Unity project that implements all the necessary functions to use the tracking inside unity. This project can be used as a example to create custom applications or used as a template.
