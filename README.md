C++ library for api.ai
==============

* [Overview](#overview)
* [Prerequisites](#prerequisites)
* [Building and Installing](#buildingandinstalling)
* [Examples](#examples)
* [Third Party Libraries](#thirdpartylibraries)

## <a name="overview"></a>Overview
The API.AI C++ library makes it easy to integrate speech recognition with API.AI natural language processing API. API.AI allows using voice commands and integration with dialog scenarios defined for a particular agent in API.AI.

## <a name="prerequisites"></a>Prerequsites
* Create an [API.AI account](http://api.ai)

## <a name="buildingandinstalling"></a>Building and Installing
### Configuring the submodules
The project contains submodules for some dependencies and some libraries. Once you have cloned cpp-netlib, you must update the submodules:

```Bash
$ cd ~/libapiai
$ git submodule init
$ git submodule update
```

### Building with CMake
To build the libraries and run the tests with CMake, you will need to have CMake version 3.0 or higher installed appropriately in your system.

```Bash
$ cd ~/libapiai
$ mkdir build
$ cd build
$ cmake ../
```

Once CMake is done with generating the Makefiles and configuring the project, you can now build and install library:
```Bash
$ make
$ sudo make install
```

### If your use CMake in your project.

Use library as submodule.

```Bash
$ git submodule init
$ git submodule add git@github.com:api-ai/libapiai.git
```

In your CMakeLists.txt add 
```
add_subdirectory(libapiai)
```

## <a name="examples"></a>Examples
Your can see [examples](examples) for more information about how to use library.

## <a name="thirdpartylibraries"></a>Third Party Libraries
* cjson (http://sourceforge.net/projects/cjson/)
* libcurl (http://libcurl.org/)