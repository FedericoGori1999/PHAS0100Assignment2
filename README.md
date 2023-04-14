### A Virtual Solar System

This is the starting repository for assignment 2 of PHAS0100: Research Computing with C++. You may add or remove C++ files in any directory. You should organise the files as you see fit but do read the Folder Structure section below to understand the intended use of the existing folders.

### Installing dependencies

We are using the package manager Conan to install the dependencies Catch2 and Eigen. In order to use CMake's `Release` target for performance and `Debug` for debugging, the libraries must be installed twice with:

```
conan install . --output-folder=build --build=missing -s build_type=Debug
conan install . --output-folder=build --build=missing -s build_type=Release
```

If you delete the `build` directory to clean your build, you may have to install the dependencies again.

### Building

To build from the project root directory you should run:

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

If you wish to debug your code, you should replace `Release` with `Debug`. For performance measurements, ensure you have built with the `Release` target.

### Testing

Once the project has been built, it can be tested by running:

```
cd build
ctest
```

### Folder structure

The project is split into four main parts aligning with the folder structure described in [the relevant section in Modern CMake](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html):

- `app/` contains all code implementing the command-line application.
- `lib/` contains all non-app code. Only code in this directory can be accessed by the unit tests.
- `include/` contains all `.hpp` files.
- `test/` contains all unit tests.

You are expected to edit the `CMakeLists.txt` file in each folder to add or remove sources as necessary. For example, if you create a new file `test/particle_test.cpp`, you must add `particle_test.cpp` to the line `add_executable(tests test.cpp)` in `test/CMakeLists.txt`. Please ensure you are comfortable editing these files well before the submission deadline. If you feel you are struggling with the CMake files, please see the Getting Help section of the assignment instructions.

### Usage Instructions

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
After the execution, the positions and the velocities of the planets in the system will be printed, with the final energy, the energy loss, the elapsed time and the average timestep as well. 

A good simulation should be tested in the following way:
    
    -> after an integration time of 2 * pi, using a proper dt, the Earth should return close to the initial position.
    -> after the integration, the total energy of the system should remain the same

2) N Body System

In order to run the solar system simulator, the command-line to execute should be

-> Strong scaling (i.e. number of particles is the argument passed by command line)

"./build/nBodySystemSimulator <dt> time <total_time> <numberOfParticles> <epsilon> strong" 

if you want to iterate until the <totalTime> is reached

or

"./build/nBodySystemSimulator <dt> steps <numberOfSteps> <numberOfParticles> <epsilon> strong" 

if you want to iterate until the number of steps done in the evolution is <numberOfSteps>

-> Weak scaling (i.e. number of Particles multiplied by the number of used threads)

"OMP_NUM_THREADS=<numberOfThreads> OMP_SCHEDULE=<scheduleType> ./build/nBodySystemSimulator <dt> time <total_time> <numberOfParticles>
<epsilon> weak" 

if you want to iterate until the <totalTime> is reached

or

"OMP_NUM_THREADS=<numberOfThreads> OMP_SCHEDULE=<scheduleType> ./build/nBodySystemSimulator <dt> steps <numberOfSteps> <numberOfParticles>
<epsilon> weak" 

if you want to iterate until the number of steps done in the evolution is <numberOfSteps>

Keywords meaning:

-> nBodySystemSimulator is the name of the executable

-> <dt> is a real number, and it will be the increment in time in the simulations (it must be a positive number)

-> The third argument should be either "time" or "steps", otheriwse we would get an error. If it is "time", the program will run until a final time for the integration has been reached (argument #4).
    If the argument is "steps", the simulation will run until a specified number of steps has been made (passed through argument #4)

-> The fourth argument should be a total time of integration if the third argument is "time", otherwise the number of steps to do if the third argument is "steps".

-> The fifth argument is the number of particles N in the system

-> The sixth argument is the softening factor epsilon for the calculation of the accelerations for the particles.

-> The seventh argument ("strong" or "weak") is used to specify if the number of particles passed should be multiplied by the number of particles used (as requested by the weak scaling experiment).

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

-> Energy loss of the system

-> Elapsed time and average time required per step


### Results from simulating the solar system

## --> Simulating the solar system (2 * M_PI Integration time)

-> Initial positions and velocities of the planets in the system.

Planet Sun:
Position: (0, 0, 0)
Velocity: (0, 0, 0)

Planet Mercury:
Position: (-0.00707497967750317, 0.399937425933811, 0)
Velocity: (-1.58089148436967, -0.0279663127253919, 0)

Planet Venus:
Position: (-0.0123812144356305, 0.69989049538417, 0)
Velocity: (-1.19504163354912, -0.021140545302528, 0)

Planet Earth:
Position: (-0.0176874491937579, 0.999843564834529, 0)
Velocity: (-0.999843564834529, -0.0176874491937579, 0)

Planet Mars:
Position: (-0.0265311737906369, 1.49976534725179, 0)
Velocity: (-0.816368852149982, -0.0144417417920362, 0)

Planet Jupiter:
Position: (-0.0919747358075412, 5.19918653713955, 0)
Velocity: (-0.438460408295325, -0.00775645957823551, 0)

Planet Saturn:
Position: (-0.1680307673407, 9.49851386592802, 0)
Velocity: (-0.32439208799181, -0.00573856628877914, 0)

Planet Uranus:
Position: (-0.339599024520152, 19.196996444823, 0)
Velocity: (-0.228182031015104, -0.00403658954506157, 0)

Planet Neptune:
Position: (-0.532392220732113, 30.0952913015193, 0)
Velocity: (-0.182242140604181, -0.00322390293468718, 0)


-> Running the simulation with dt = 0.0001 s with an integration time of 6.28219 s


-> Elapsed time: 0.419307 s


-> Average timestep: 6.67453e-06 s/step


-> Total energy of the system before the update: -0.000112461 J


-> Total energy of the system after the update: -0.000112448 J


-> Energy loss: 1.30459e-08 J


-> Energy loss in percentage compared to the initial energy: 0.0116003 %


-> Final positions and velocities of the planets in the system.

Planet Sun:
Position: (-0.000181463329034856, 0.000746304771166758, 0)
Velocity: (-6.79582143062626e-05, 0.000228201771965802, 0)

Planet Mercury:
Position: (0.242546082736124, 0.328515642896096, 0)
Velocity: (-1.25807346946848, 0.932050672356973, 0)

Planet Venus:
Position: (0.675231668434955, -0.19313384524076, 0)
Velocity: (0.329428033315709, 1.14662831733384, 0)

Planet Earth:
Position: (-0.0111648741518527, 1.00193642678152, 0)
Velocity: (-0.999380397506435, -0.0107529450223829, 0)

Planet Mars:
Position: (0.436596780353123, -1.43453786265712, 0)
Velocity: (0.781075549799552, 0.237820290580873, 0)

Planet Jupiter:
Position: (-2.70679117470999, 4.44024004431576, 0)
Velocity: (-0.374422297217062, -0.228194752689365, 0)

Planet Saturn:
Position: (-2.18650526563813, 9.24398520874684, 0)
Velocity: (-0.315746633141647, -0.0749763895132581, 0)

Planet Uranus:
Position: (-1.7708074586393, 19.1180195452582, 0)
Velocity: (-0.227246017043481, -0.021094741667548, 0)

Planet Neptune:
Position: (-1.67661249063358, 30.0532183502719, 0)
Velocity: (-0.181987803295937, -0.0101688823355443, 0)


It is possible to see that the Earth returns very close to its initial position after an integration time of 2*PI with dt = 0.0001

Planet Earth:

Before:
Position: (-0.0176874491937579, 0.999843564834529, 0)
Velocity: (-0.999843564834529, -0.0176874491937579, 0)

After:
Position: (-0.0111648741518527, 1.00193642678152, 0)
Velocity: (-0.999380397506435, -0.0107529450223829, 0)



## --> Evaluating the change in total energy (100* 2 * M_PI Integration time)

Here only the energies and the execution times will be reported

# ----> Run #1: dt = 0.0001

-> Running the simulation with dt = 0.0001 s with an integration time of 628.218 s


-> Elapsed time: 36.7683 s


-> Average timestep: 5.85278e-06 s/step


-> Total energy of the system before the update: -0.000112461 J


-> Total energy of the system after the update: -0.00011174 J


-> Energy loss: 7.21588e-07 J


-> Energy loss in percentage compared to the initial energy: 0.641634 %

# ----> Run #2: dt = 0.001

-> Running the simulation with dt = 0.001 s with an integration time of 628.218 s


-> Elapsed time: 3.88699 s


-> Average timestep: 6.18731e-06 s/step


-> Total energy of the system before the update: -0.000112461 J


-> Total energy of the system after the update: -0.000109855 J


-> Energy loss: 2.60565e-06 J


-> Energy loss in percentage compared to the initial energy: 2.31693 %

# ----> Run #3: dt = 0.01

-> Running the simulation with dt = 0.01 s with an integration time of 628.218 s


-> Elapsed time: 0.395928 s


-> Average timestep: 6.30238e-06 s/step


-> Total energy of the system before the update: -0.000112461 J


-> Total energy of the system after the update: -0.000102526 J


-> Energy loss: 9.93467e-06 J


-> Energy loss in percentage compared to the initial energy: 8.83387 %

# ----> Run #4: dt = 0.1

-> Running the simulation with dt = 0.1 s with an integration time of 628.218 s


-> Elapsed time: 0.0700599 s


-> Average timestep: 1.11507e-05 s/step


-> Total energy of the system before the update: -0.000112461 J


-> Total energy of the system after the update: -7.49205e-05 J


-> Energy loss: 3.75406e-05 J


-> Energy loss in percentage compared to the initial energy: 33.381 %

# ----> Run #5: dt = 1

-> Running the simulation with dt = 1 s with an integration time of 628.218 s


-> Elapsed time: 0.1228 s


-> Average timestep: 0.000195231 s/step


-> Total energy of the system before the update: -0.000112461 J


-> Total energy of the system after the update: -2.71155e-05 J


-> Energy loss: 8.53456e-05 J


-> Energy loss in percentage compared to the initial energy: 75.889 %

# ----> Run #6: dt = 10

-> Running the simulation with dt = 10 s with an integration time of 628.218 s


-> Elapsed time: 0.00137937 s


-> Average timestep: 2.18948e-05 s/step


-> Total energy of the system before the update: -0.000112461 J


-> Total energy of the system after the update: 0.00106874 J


-> Energy loss: 0.0011812 J


-> Energy loss in percentage compared to the initial energy: 1050.32 %

# ----> Run #7: dt = 50

-> Running the simulation with dt = 50 s with an integration time of 628.218 s


-> Elapsed time: 0.00359221 s


-> Average timestep: 0.000276324 s/step


-> Total energy of the system before the update: -0.000112461 J


-> Total energy of the system after the update: 0.0264527 J


-> Energy loss: 0.0265652 J


-> Energy loss in percentage compared to the initial energy: 23621.6 %

# ----> Run #8: dt = 100

-> Running the simulation with dt = 100 s with an integration time of 628.218 s


-> Elapsed time: 0.000584959 s


-> Average timestep: 8.35656e-05 s/step


-> Total energy of the system before the update: -0.000112461 J


-> Total energy of the system after the update: 0.105548 J


-> Energy loss: 0.105661 J


-> Energy loss in percentage compared to the initial energy: 93953.2 %


As we can see, the energy loss increases if we increase the interval dt

dt = 0.0001 -> Energy loss = 7.21588e-07 J (0.641634 %)
dt = 0.001 -> Energy loss = 2.60565e-06 J (2.31693 %)
dt = 0.01 -> Energy loss = 9.93467e-06 J (8.83387 %)
dt = 0.1 -> Energy loss = 3.75406e-05 J (33.381 %)
dt = 1 -> Energy loss = 8.53456e-05 J (75.889 %)
dt = 10 -> Energy loss = 0.0011812 J (1050.32 %)
dt = 50 -> Energy loss = 0.0265652 J (23621.6 %)
dt = 100 -> Energy loss = 0.105661 J (93953.2 %)

## --> Benchmarking the program (100 * 2 * M_PI Integration time)

Here we will print only the time required for the execution (with and without the optimisation flags) and the average time per step.

# ----> Run #1 dt = 0.00001


Optimisation: -O0 (single run requested from the assignment)

-> Elapsed time: 385.172 s


-> Average timestep: 6.13117e-06 s/step

Optimisation: -O2

-> Elapsed time: 374.272 s


-> Average timestep: 5.95767e-06 s/step

# ----> Run #2 dt = 0.00005


Optimisation: -O2

-> Elapsed time: 73.9785 s


-> Average timestep: 5.88796e-06 s/step

# ----> Run #3 dt = 0.0001


Optimisation: -O2

-> Elapsed time: 37.3826 s


-> Average timestep: 5.95058e-06 s/step

# ----> Run #4 dt = 0.0005


Optimisation: -O2

-> Elapsed time: 7.64731 s


-> Average timestep: 6.0865e-06 s/step

# ----> Run #5 dt = 0.001


Optimisation: -O2

-> Elapsed time: 3.69859 s


-> Average timestep: 5.88743e-06 s/step

# ----> Run #6 dt = 0.005


Optimisation: -O2

-> Elapsed time: 0.764715 s


-> Average timestep: 6.08637e-06 s/step

# ----> Run #7 dt = 0.01


Optimisation: -O2

-> Elapsed time: 0.409379 s


-> Average timestep: 6.51649e-06 s/step

# ----> Run #8 dt = 0.05


Optimisation: -O2

-> Elapsed time: 0.113087 s


-> Average timestep: 9.00017e-06 s/step


As we can see, the average timestep is quite similar in the runs, with the exception of Run #8 


## --> Increasing the scale of the system

# ----> 8 particles

-> Running the simulation with dt = 0.001 s with an integration time of 6.28219 s


-> Elapsed time: 0.0584907 s


-> Average timestep: 9.30935e-06 s/step


-> Total energy of the system before the update: -0.000116662 J


-> Total energy of the system after the update: -0.000116662 J


-> Energy loss: 5.4942e-11 J


-> Energy loss in percentage compared to the initial energy: 4.70949e-05 %

# ----> 64 particles

-> Running the simulation with dt = 0.001 s with an integration time of 6.28219 s


-> Elapsed time: 0.280598 s


-> Average timestep: 4.46599e-05 s/step


-> Total energy of the system before the update: -0.00104996 J


-> Total energy of the system after the update: -0.00104996 J


-> Energy loss: 5.08266e-10 J


-> Energy loss in percentage compared to the initial energy: 4.84081e-05 %

# ----> 256 particles

-> Running the simulation with dt = 0.001 s with an integration time of 6.28219 s


-> Elapsed time: 2.19174 s


-> Average timestep: 0.000348837 s/step


-> Total energy of the system before the update: -0.00424984 J


-> Total energy of the system after the update: -0.00424984 J


-> Energy loss: 2.24862e-09 J


-> Energy loss in percentage compared to the initial energy: 5.29107e-05 %

# ----> 1024 particles

-> Running the simulation with dt = 0.001 s with an integration time of 6.28219 s


-> Elapsed time: 28.9917 s


-> Average timestep: 0.00461431 s/step


-> Total energy of the system before the update: -0.0170494 J


-> Total energy of the system after the update: -0.0170494 J


-> Energy loss: 1.20916e-08 J


-> Energy loss in percentage compared to the initial energy: 7.09209e-05 %

# ----> 2048 particles

-> Running the simulation with dt = 0.001 s with an integration time of 6.28219 s


-> Elapsed time: 121.22 s


-> Average timestep: 0.0192933 s/step


-> Total energy of the system before the update: -0.0341154 J


-> Total energy of the system after the update: -0.0341154 J


-> Energy loss: 3.23873e-08 J


-> Energy loss in percentage compared to the initial energy: 9.49347e-05 %

The execution time becomes larger when the number of particles increases. With 2048 particles and dt = 0.001 we get an execution time of 2 minutes, integrating over a time of 2 * PI

## --> Testing schedule command for loops and collapse

----> Testing the type of schedule: here we use the increment dt = 0.001, with a final time to reach of 2 * PI for a system of 2048 particles. By running the simulation without parallelism, the execution time of this program requires 130.937 s (i.e. between 1 and 5 minutes time of execution) --

# ./build/nBodySystemSimulator 0.001 time 6.282185 2048 0.001 strong

-> Elapsed time: 120.908 s


-> Average timestep: 0.0192437 s/step


-> Total energy of the system before the update: -0.0341154 J


-> Total energy of the system after the update: -0.0341154 J


-> Energy loss: 3.23873e-08 J


-> Energy loss in percentage compared to the initial energy: 9.49347e-05 %

# OMP_NUM_THREADS=1 OMP_SCHEDULE=static ./build/nBodySystemSimulator 0.001 time 6.282185 2048 0.001 strong

-> Elapsed time: 175.874 s


-> Average timestep: 0.0279921 s/step


-> Total energy of the system before the update: -0.0341154 J


-> Total energy of the system after the update: -0.0341154 J


-> Energy loss: 3.23873e-08 J


-> Energy loss in percentage compared to the initial energy: 9.49347e-05 %

# OMP_NUM_THREADS=1 OMP_SCHEDULE=dynamic ./build/nBodySystemSimulator 0.001 time 6.282185 2048 0.001 strong

-> Elapsed time: 405.019 s


-> Average timestep: 0.0644627 s/step


-> Total energy of the system before the update: -0.0341154 J


-> Total energy of the system after the update: -0.0341154 J


-> Energy loss: 3.23873e-08 J


-> Energy loss in percentage compared to the initial energy: 9.49347e-05 %

# OMP_NUM_THREADS=1 OMP_SCHEDULE=guided ./build/nBodySystemSimulator 0.001 time 6.282185 2048 0.001 strong

-> Elapsed time: 174.181 s


-> Average timestep: 0.0277225 s/step


-> Total energy of the system before the update: -0.0341154 J


-> Total energy of the system after the update: -0.0341154 J


-> Energy loss: 3.23873e-08 J


-> Energy loss in percentage compared to the initial energy: 9.49347e-05 %

-- As we can see, by specifying to use 1 thread and the static type of schedule the program slows down in execution time to 175.874 s compared to the required time 120.908 s in the case of non-parallelisation. If we use the schedule types "dynamic" and "guided" we get 405.019 s and 174.181 s respectively. So, it is better to do not give parallelism instructions to the program if one ends up using 1 thread. --

# OMP_NUM_THREADS=2 OMP_SCHEDULE=static ./build/nBodySystemSimulator 0.001 time 6.282185 2048 0.001 strong

-> Elapsed time: 98.7667 s


-> Average timestep: 0.0157197 s/step


-> Total energy of the system before the update: -0.0341154 J


-> Total energy of the system after the update: -0.0341154 J


-> Energy loss: 3.23873e-08 J


-> Energy loss in percentage compared to the initial energy: 9.49347e-05 %

# OMP_NUM_THREADS=2 OMP_SCHEDULE=dynamic ./build/nBodySystemSimulator 0.001 time 6.282185 2048 0.001 strong

-> Elapsed time: 215.007 s


-> Average timestep: 0.0342205 s/step


-> Total energy of the system before the update: -0.0341154 J


-> Total energy of the system after the update: -0.0341154 J


-> Energy loss: 3.23873e-08 J


-> Energy loss in percentage compared to the initial energy: 9.49347e-05 %

# OMP_NUM_THREADS=2 OMP_SCHEDULE=guided ./build/nBodySystemSimulator 0.001 time 6.282185 2048 0.001 strong

-> Elapsed time: 102.157 s


-> Average timestep: 0.0162592 s/step


-> Total energy of the system before the update: -0.0341154 J


-> Total energy of the system after the update: -0.0341154 J


-> Energy loss: 3.23873e-08 J


-> Energy loss in percentage compared to the initial energy: 9.49347e-05 %

-- In using 2 threads, we get the times 98.7667 s for the static schedule (x 1.22 speed-up compared to single thread result without parallelism instructions), 215.007 s for the dynamic schedule (x 0.56 (slower!) speed-up compared to single thread result without parallelism instructions) and 102.157 s for the guided schedule (x 1.18 speed-up compared to single thread result without parallelism instructions). The static schedule is the best method to reduce the execution time here. --


# OMP_NUM_THREADS=4 OMP_SCHEDULE=static ./build/nBodySystemSimulator 0.001 time 6.282185 2048 0.001 strong

-> Elapsed time: 59.3779 s


-> Average timestep: 0.00945056 s/step


-> Total energy of the system before the update: -0.0341154 J


-> Total energy of the system after the update: -0.0341154 J


-> Energy loss: 3.23873e-08 J


-> Energy loss in percentage compared to the initial energy: 9.49347e-05 %

# OMP_NUM_THREADS=4 OMP_SCHEDULE=dynamic ./build/nBodySystemSimulator 0.001 time 6.282185 2048 0.001 strong

-> Elapsed time: 131.909 s


-> Average timestep: 0.0209946 s/step


-> Total energy of the system before the update: -0.0341154 J


-> Total energy of the system after the update: -0.0341154 J


-> Energy loss: 3.23873e-08 J


-> Energy loss in percentage compared to the initial energy: 9.49347e-05 %

# OMP_NUM_THREADS=4 OMP_SCHEDULE=guided ./build/nBodySystemSimulator 0.001 time 6.282185 2048 0.001 strong

-> Elapsed time: 58.2103 s


-> Average timestep: 0.00926473 s/step


-> Total energy of the system before the update: -0.0341154 J


-> Total energy of the system after the update: -0.0341154 J


-> Energy loss: 3.23873e-08 J


-> Energy loss in percentage compared to the initial energy: 9.49347e-05 %

-- In using 4 threads, we get the times 59.3779 s for the static schedule (x 2.04 speed-up compared to single thread result without parallelism instructions), 131.909 s for the dynamic schedule (x 0.92 (slower!) speed-up compared to single thread result without parallelism instructions) and 58.2103 s for the guided schedule (x 2.08 speed-up compared to single thread result without parallelism instructions). The guided schedule is the best method to reduce the execution time here. --

# OMP_NUM_THREADS=8 OMP_SCHEDULE=static ./build/nBodySystemSimulator 0.001 time 6.282185 2048 0.001 strong

-> Elapsed time: 66.5475 s


-> Average timestep: 0.0105917 s/step


-> Total energy of the system before the update: -0.0341154 J


-> Total energy of the system after the update: -0.0341154 J


-> Energy loss: 3.23873e-08 J


-> Energy loss in percentage compared to the initial energy: 9.49347e-05 %

# OMP_NUM_THREADS=8 OMP_SCHEDULE=dynamic ./build/nBodySystemSimulator 0.001 time 6.282185 2048 0.001 strong

-> Elapsed time: 128.341 s


-> Average timestep: 0.0204268 s/step


-> Total energy of the system before the update: -0.0341154 J


-> Total energy of the system after the update: -0.0341154 J


-> Energy loss: 3.23873e-08 J


-> Energy loss in percentage compared to the initial energy: 9.49347e-05 %

# OMP_NUM_THREADS=8 OMP_SCHEDULE=guided ./build/nBodySystemSimulator 0.001 time 6.282185 2048 0.001 strong

-> Elapsed time: 66.2382 s


-> Average timestep: 0.0105424 s/step


-> Total energy of the system before the update: -0.0341154 J


-> Total energy of the system after the update: -0.0341154 J


-> Energy loss: 3.23873e-08 J


-> Energy loss in percentage compared to the initial energy: 9.49347e-05 %

-- In using 8 threads, we get the times 66.5475 s for the static schedule (x 1.82 speed-up compared to single thread result without parallelism instructions), 128.341 s for the dynamic schedule (x 0.94 speed-up compared to single thread result without parallelism instructions) and 66.2382 s for the guided schedule (x 1.83 speed-up compared to single thread result without parallelism instructions). The guided schedule is the best method to reduce the execution time here. --

-- As we can see from the results above, the schedule types "guided" and "static" are the one that save the biggest amount of time. The "guided" schedule type has performed better with 4 and 8 threads, whereas the "static" schedule type has performed better in the case of 1 thread. The "dynamic" schedule is the worst schedule type. --


## --> Strong scaling experiment

PC Specs: MacBook Air M1 (8 total cores: 4 performance, 4 "efficiency")
2048 particles simulated with an integration time of 2 * PI, dt = 0.001, epsilon 0.001, schedule type = static vs guided 

# ----> Static schedule

| `OMP_NUM_THREADS | Time (s) | Speedup |
|                 1|   178.054|       --|
|                 2|   99.8015|    x1.78|
|                 3|   75.9492|    x2.34|
|                 4|   57.8949|    x3.08|
|                 5|   80.9347|    x2.20|
|                 6|   75.9544|    x2.34|
|                 7|   72.0711|    x2.47|
|                 8|   70.4103|    x2.53|
|                16|   70.9219|    x2.51|

# ----> Guided schedule

| `OMP_NUM_THREADS | Time (s) | Speedup |
|                 1|   178.304|       --|
|                 2|   102.635|    x1.74|
|                 3|   73.5562|    x2.42|
|                 4|   54.2772|    x3.29|
|                 5|   60.0403|    x2.97|
|                 6|   59.1319|    x3.02|
|                 7|   65.9624|    x2.70|
|                 8|   61.0965|    x2.92|
|                16|   62.1228|    x2.87|

It is possible to see that the schedule type "guided" has approximately the same performance of the schedule type "static" up to 4 threads, and it becomes better for scaling beyond the 4 threads limit. The better result obtained is the one related to 4 threads, with a speed-up factor of x 3.29. The scaling is quasi-linear up to 4 threads, whereas for more than 4 threads the scaling remains almost the same.

## --> Weak scaling experiment

MacBook Air M1 (8 total cores: 4 performance, 4 "efficiency")
1024 * numThreadparticles simulated with an integration time of 2 * PI, dt = 0.01 (otherwise the execution time required would be too large), epsilon 0.001, schedule type = guided (most efficient one overall as demonstrated in the strong scaling experiment). The time increment is the ratio timeWithMultipleThreads/timeWithSingleThread. Up to number of threads = 4, the scaling is quasi-linear.

| `OMP_NUM_THREADS | Num Particles | Time (s) | Time increment |
|                 1|           1024|   4.76602|              --|
|                 2|           2048|   9.69934|          x 2.04|
|                 3|           3072|   15.1006|          x 3.17|
|                 4|           4096|   23.0266|          x 4.83|
|                 5|           5120|   38.9777|          x 8.18|
|                 6|           6144|   60.3803|         x 12.67|
|                 7|           7168|   80.7928|         x 16.95|
|                 8|           8192|   94.2489|         x 19.78|
|                16|          16384|   391.346|         x 82.11|


### Credits

This project is maintained by Dr. Jamie Quinn as part of UCL ARC's course, Research Computing in C++.
