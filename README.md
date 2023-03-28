# A Virtual Solar System

This is the starting repository for assignment 2 of PHAS0100: Research Computing with C++. You may add or remove C++ files in any directory. You should organise the files as you see fit but do read the Folder Structure section below to understand the intended use of the existing folders.

## Installing dependencies

We are using the package manager Conan to install the dependencies Catch2 and Eigen. In order to use CMake's `Release` target for performance and `Debug` for debugging, the libraries must be installed twice with:

```
conan install . --output-folder=build --build=missing -s build_type=Debug
conan install . --output-folder=build --build=missing -s build_type=Release
```

If you delete the `build` directory to clean your build, you may have to install the dependencies again.

## Building

To build from the project root directory you should run:

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

If you wish to debug your code, you should replace `Release` with `Debug`. For performance measurements, ensure you have built with the `Release` target.

## Testing

Once the project has been built, it can be tested by running:

```
cd build
ctest
```

## Folder structure

The project is split into four main parts aligning with the folder structure described in [the relevant section in Modern CMake](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html):

- `app/` contains all code implementing the command-line application.
- `lib/` contains all non-app code. Only code in this directory can be accessed by the unit tests.
- `include/` contains all `.hpp` files.
- `test/` contains all unit tests.

You are expected to edit the `CMakeLists.txt` file in each folder to add or remove sources as necessary. For example, if you create a new file `test/particle_test.cpp`, you must add `particle_test.cpp` to the line `add_executable(tests test.cpp)` in `test/CMakeLists.txt`. Please ensure you are comfortable editing these files well before the submission deadline. If you feel you are struggling with the CMake files, please see the Getting Help section of the assignment instructions.

## Usage Instructions

You should fill in the instructions for using the app here.

## Results from simulating the solar system


-> Initial positions and velocities of the planets in the system.

Planet Sun:
Position: (0, 0, 0)
Velocity: (0, 0, 0)

Planet Mercury:
Position: (0.250139449578292, -0.312138199784437, 0)
Velocity: (1.23383457007937, 0.988762991660311, 0)

Planet Venus:
Position: (0.175531289897419, -0.677634684964508, 0)
Velocity: (1.15704051735268, 0.299714313598235, 0)

Planet Earth:
Position: (0.293945153796542, 0.955822288168427, 0)
Velocity: (-0.955822288168427, 0.293945153796542, 0)

Planet Mars:
Position: (1.19283630453277, 0.90947322697735, 0)
Velocity: (-0.495054520181541, 0.649297842838316, 0)

Planet Jupiter:
Position: (-1.848291433781, 4.86043401105414, 0)
Velocity: (-0.409892560260352, -0.155871040770587, 0)

Planet Saturn:
Position: (5.29690714667944, 7.88623957786322, 0)
Velocity: (-0.269329892989187, 0.180899327354112, 0)

Planet Uranus:
Position: (16.2791729956091, 10.1798097516128, 0)
Velocity: (-0.121000682119562, 0.193499788785244, 0)

Planet Neptune:
Position: (27.2033065027134, -12.8837151210134, 0)
Velocity: (0.0780173814921475, 0.164729716648925, 0)


-> Running the simulation


-> Final positions and velocities of the planets in the system.

Planet Sun:
Position: (-0.000318550398340727, 0.000659627050499053, 0)
Velocity: (-0.000116172353763551, 0.000199385681215652, 0)

Planet Mercury:
Position: (0.00969058111826708, -0.407078754276654, 0)
Velocity: (1.56494049493098, 0.038481937055114, 0)

Planet Venus:
Position: (-0.702381369501527, 0.0302869652582275, 0)
Velocity: (-0.0508031485045335, -1.19154847701778, 0)

Planet Earth:
Position: (0.299478420769534, 0.955969516223414, 0)
Velocity: (-0.953634299720491, 0.299467755203987, 0)

Planet Mars:
Position: (-0.898846433417105, -1.20149623009215, 0)
Velocity: (0.653597560037456, -0.488489092086229, 0)

Planet Jupiter:
Position: (-4.05136682262687, 3.25972114564049, 0)
Velocity: (-0.274859716996054, -0.341673260203578, 0)

Planet Saturn:
Position: (3.49585633136505, 8.83318057806429, 0)
Velocity: (-0.301746207464682, 0.11935551240584, 0)

Planet Uranus:
Position: (15.4741280053299, 11.3660944115564, 0)
Velocity: (-0.135128651269303, 0.183923813896181, 0)

Planet Neptune:
Position: (27.6736878005275, -11.8395809805756, 0)
Velocity: (0.0716888001058482, 0.167582246585876, 0)


-> Time elapsed: 0.118648 s

## Credits

This project is maintained by Dr. Jamie Quinn as part of UCL ARC's course, Research Computing in C++.
