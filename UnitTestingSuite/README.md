# ModelViewer Testing Guide

## Overview
This guide provides information on testing the `ModelViewer` application using Google Test. It covers the purpose of the tests, their location, and steps to integrate the testing tool.

## 1. What you are testing
The tests focus on verifying the functionality and behavior of the `ModelViewer` application. The primary objectives include testing the `readObjFileData` method, the `updateRenderingData` method, various methods of `Geometry dll` and `ObjReader Dll` and other relevant functionalities.

## 2. Test location
The test cases are organized using Google Test framework. Test files are structured as follows:
- All the Test Cases are available at this location [Test Suite Location](https://github.com/UmeshEkhande/3D_Model_Viewer/tree/Umesh_dev/UnitTestingSuite/src)

## 3. Steps to Integrate Testing Tool (Google Test)

### Prerequisites
Make sure you have Google Test installed on your system. If not, you can follow the [Google Test Installation Guide](https://github.com/google/googletest/blob/main/googletest/README.md).
or follow the steps mentioned below
- Right click on the project
- Click on add and select new project
- Select Google test as project type and provide appropriate location
- Create the test suite under this project
