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

In this project I have built two different executables, which are:

    1) one simulating the solar system (the Sun with the 8 planets in the correct order)
    2) one simulating a system of N particles, where N is passed by command-line

1) Solar System

In order to run the solar system simulator, the command-line to execute should be

" ./build/solarSystemSimulator <dt> time <total_time> " or " ./build/solarSystemSimulator <dt> steps <number_of_steps> ". 

where:

-> solarSystemSimulator is the name of the executable

-> <dt> is a real number, and it will be the increment in time in the simulations (it must be a positive number)

-> The third argument should be either "time" or "steps", otheriwse we would get an error. If it is "time", the program will run until a final time for the integration has been reached (argument #4).
    If the argument is "steps", the simulation will run until a specified number of steps has been made (passed through argument #4)

-> The fourth argument should be a total time of integration if the third argument is "time", otherwise the number of steps to do if the third argument is "steps".

If -h or --help is inserted at the end of the command-line call, an help message should be printed. 
This program initialise the planets' masses and distance from the sun in the following way:

Sun: 
-> mass = 1.
-> distance from Origin of system = 0.

Mercury: 
-> mass = 1./6023600
-> distance from Origin of system = 0.4

Venus: 
-> mass = 1./408524
-> distance from Origin of system = 0.7

Earth: 
-> mass = 1./332946.038
-> distance from Origin of system = 1.

Mars: 
-> mass = 1./3098710
-> distance from Origin of system = 1.5

Jupiter: 
-> mass = 1./1047.55
-> distance from Origin of system = 5.2

Saturn: 
-> mass = 1./3499
-> distance from Origin of system = 9.5

Uranus: 
-> mass = 1./22962
-> distance from Origin of system = 19.2

Neptune: 
-> mass = 1./19352
-> distance from Origin of system = 30.1

The coordinates for the initial position and velocity of the sun are:

positionSun = (0., 0., 0.)
velocitySun = (0., 0., 0.)

The coordinates of the 8 planets for initial position and velocity are set through the relations displayed on page 5 of the Assignment instruction.

The program will print the initial positions of the planets in the system with their initial velocities, and the initial energy of the system.
After the execution, the positions and the velocities of the planets in the system will be printed, with the final energy of the system as well. 
At the end of the simulation, the execution time (measured around the evolution part of the system) and the average time required for a step will be printed.

A good simulation should be tested in the following way:
    
    -> after an integration time of 2 * pi, using a proper dt, the Earth should return close to the initial position.
    -> after the integration, the total energy of the system should remain the same

2) N Body System

In order to run the solar system simulator, the command-line to execute should be

" ./build/nBodySystemSimulator <dt> time <total_time> <numberOfParticles> <epsilon> " or " ./build/nBodySystemSimulator <dt> steps <numberOfSteps> <numberOfParticles> <epsilon> ". 

where:

-> nBodySystemSimulator is the name of the executable

-> <dt> is a real number, and it will be the increment in time in the simulations (it must be a positive number)

-> The third argument should be either "time" or "steps", otheriwse we would get an error. If it is "time", the program will run until a final time for the integration has been reached (argument #4).
    If the argument is "steps", the simulation will run until a specified number of steps has been made (passed through argument #4)

-> The fourth argument should be a total time of integration if the third argument is "time", otherwise the number of steps to do if the third argument is "steps".

-> The fifth argument is the number of particles N in the system

-> The sixth argument is the softening factor epsilon for the calculation of the accelerations for the particles.

If -h or --help is inserted at the end of the command-line call, an help message should be printed.

This program initialises the mass, position and velocity of the first particle (i.e. the central star) as it follows:

centralStar:
-> mass = 1.
-> position = (0., 0., 0.)
-> velocity = (0., 0., 0.)

The other particles N-1 will be initialised in the following way as described by page 7-8 of the assignemnt pdf.

The executable should print:

-> Total energy of the system prior the evolution

-> Total energy of the system after the evolution

-> Elapsed time and average time required per step


## Results from simulating the solar system

------------------------------------------- Simulating the solar system (2 * M_PI Integration time) -----------------------------------------

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

---------------------------------- Evaluating the change in total energy (100* 2 * M_PI Integration time) -----------------------------------

Here only the energies and the execution times will be reported

----> Run #1: dt = 0.00001

-> Total energy of the system before the update: -0.000112443 J

-> Running the simulation with dt = 1e-05 s with an integration time of 628.318 s

-> Total energy of the system after the update: -0.000112327 J

-> Time elapsed: 99.6572 s

----> Run #2: dt = 0.0001

-> Total energy of the system before the update: -0.000112459 J

-> Running the simulation with dt = 0.0001 s with an integration time of 628.318 s

-> Total energy of the system after the update: -0.000111737 J

-> Time elapsed: 9.95426 s

----> Run #3: dt = 0.001

-> Total energy of the system before the update: -0.000112419 J

-> Running the simulation with dt = 0.001 s with an integration time of 628.318 s

-> Total energy of the system after the update: -0.000109815 J

-> Time elapsed: 1.02806 s

----> Run #4: dt = 0.01

-> Total energy of the system before the update: -0.000112444 J

-> Running the simulation with dt = 0.01 s with an integration time of 628.318 s

-> Total energy of the system after the update: -0.000102515 J

-> Time elapsed: 0.105936 s

----> Run #5: dt = 0.1

-> Total energy of the system before the update: -0.000112417 J

-> Running the simulation with dt = 0.1 s with an integration time of 628.318 s

-> Total energy of the system after the update: -7.48926e-05 J

-> Time elapsed: 0.0254622 s

----> Run #6: dt = 1

-> Total energy of the system before the update: -0.000112456 J

-> Running the simulation with dt = 1 s with an integration time of 628.318 s

-> Total energy of the system after the update: -2.7099e-05 J

-> Time elapsed: 0.003021 s

----> Run #7: dt = 10

-> Total energy of the system before the update: -0.000112417 J

-> Running the simulation with dt = 10 s with an integration time of 628.318 s

-> Total energy of the system after the update: 0.00106872 J

-> Time elapsed: 0.000266584 s

----> Run #8: dt = 50

-> Total energy of the system before the update: -0.000112415 J

-> Running the simulation with dt = 50 s with an integration time of 628.318 s

-> Total energy of the system after the update: 0.0264539 J

-> Time elapsed: 6.0792e-05 s

----------------------------------------- Benchmarking the program (100 * 2 * M_PI Integration time) ----------------------------------------

Here we will print only the time required for the execution (with and without the optimisation flags) and the average time per step.

----> Run #1 dt = 0.000005

Optimisation: -O0

-> Time elapsed: 199.436 s

-> Average timestep: 1.58706e-06 s/step

Optimisation: -O2

-> Time elapsed: 199.932 s

-> Average timestep: 1.59101e-06 s/step

----> Run #2 dt = 0.00001

Optimisation: -O0

-> Time elapsed: 100.356 s

-> Average timestep: 1.59721e-06 s/step

Optimisation: -O2

-> Time elapsed: 100.384 s

-> Average timestep: 1.59766e-06 s/step

----> Run #3 dt = 0.0001

Optimisation: -O0

-> Time elapsed: 9.96795 s

-> Average timestep: 1.58645e-06 s/step

Optimisation: -O2

-> Time elapsed: 10.0557 s

-> Average timestep: 1.60042e-06 s/step

----> Run #4 dt = 0.001

Optimisation: -O0

-> Time elapsed: 1.00994 s

-> Average timestep: 1.60736e-06 s/step

Optimisation: -O2

-> Time elapsed: 1.03691 s

-> Average timestep: 1.6503e-06 s/step

----> Run #5 dt = 0.01

Optimisation: -O0

-> Time elapsed: 0.132996 s

-> Average timestep: 2.11669e-06 s/step

Optimisation: -O2

-> Time elapsed: 0.133748 s

-> Average timestep: 2.12866e-06 s/step

----> Run #6 dt = 0.1

Optimisation: -O0

-> Time elapsed: 0.0271114 s

-> Average timestep: 4.31436e-06 s/step

Optimisation: -O2

-> Time elapsed: 0.0241363 s

-> Average timestep: 3.84091e-06 s/step

----> Run #7 dt = 1

Optimisation: -O0

-> Time elapsed: 0.003062 s

-> Average timestep: 4.86804e-06 s/step

Optimisation: -O2

-> Time elapsed: 0.00321667 s

-> Average timestep: 5.11394e-06 s/step

----> Run #8 dt = 5

Optimisation: -O0

-> Time elapsed: 0.000528125 s

-> Average timestep: 4.19147e-06 s/step

Optimisation: -O2

-> Time elapsed: 0.000595667 s

-> Average timestep: 4.72752e-06 s/step



## Credits

This project is maintained by Dr. Jamie Quinn as part of UCL ARC's course, Research Computing in C++.
