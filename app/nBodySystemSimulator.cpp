#include "manyBodySystem.hpp"
#include "particle.hpp"
#include <chrono>

/* Suggested call of the program:

-> Strong scaling (i.e. number of particles is the argument passed by command
line)

"./build/nBodySystemSimulator <dt> time <total_time> <numberOfParticles>
<epsilon> strong" if you want to iterate until the <totalTime> is reached

or

"./build/nBodySystemSimulator <dt> steps <numberOfSteps> <numberOfParticles>
<epsilon> strong" if you want to iterate until the number of steps done in the
evolution is <numberOfSteps>

-> Weak scaling (i.e. number of Particles multiplied by the number of used
threads)

"OMP_NUM_THREADS=<numberOfThreads> OMP_SCHEDULE=<scheduleType>
./build/nBodySystemSimulator <dt> time <total_time> <numberOfParticles>
<epsilon> weak" if you want to iterate until the <totalTime> is reached

or

"OMP_NUM_THREADS=<numberOfThreads> OMP_SCHEDULE=<scheduleType>
./build/nBodySystemSimulator <dt> steps <numberOfSteps> <numberOfParticles>
<epsilon> weak" if you want to iterate until the number of steps done in the
evolution is <numberOfSteps>

If -h or --help is displayed at the end of the string, an help message should be
printed */

typedef std::chrono::high_resolution_clock Clock;

/* Function to time the execution of the program */

double tSeconds(std::chrono::time_point<Clock> t1,
    std::chrono::time_point<Clock> t2)
{
    return (t2 - t1).count() / 1e9;
}

int main(int argc, char** argv)
{
    try {
        int count = 0;
        std::string helpString = argv[argc - 1];
        if (helpString == "-h" || helpString == "--help" || argc == 1) {
            /* Prints help message */

            throw std::invalid_argument(
                "\nSuggested call of the program:\n\n-> Strong "
                "scaling\n\n\"./build/nBodySystemSimulator <dt> time <total_time> "
                "<numberOfParticles> <epsilon> strong\" if you want to iterate until "
                "the <totalTime> is reached \n\nor\n\n\"./build/nBodySystemSimulator "
                "<dt> steps <numberOfSteps> <numberOfParticles> <epsilon> strong\" "
                "if you want to iterate until the number of steps done in the "
                "evolution is <numberOfSteps>\n\n-> Weak "
                "scaling\n\n\"OMP_NUM_THREADS=<numberOfThreads> "
                "OMP_SCHEDULE=<scheduleType> ./build/nBodySystemSimulator <dt> time "
                "<total_time> <numberOfParticles> <epsilon> weak\" if you want to "
                "iterate until the <totalTime> is "
                "reached\n\nor\n\n\"OMP_NUM_THREADS=<numberOfThreads> "
                "OMP_SCHEDULE=<scheduleType> ./build/nBodySystemSimulator <dt> steps "
                "<numberOfSteps> <numberOfParticles> <epsilon> weak\" if you want to "
                "iterate until the number of steps done in the evolution is "
                "<numberOfSteps>\n\n\nIf -h or --help is displayed at the end of the "
                "string, this message will be printed\n");
        }
        if (argc != 7) {
            /* Wrong number of arguments passed by command line */

            throw std::invalid_argument(
                "\nError in calling the program: run '-h' or \"--help\" at the end "
                "of the command line to see how the program should be launched.\n");
        }
        nBodySystemGenerator nBodySystem;
        std::string dtString = argv[1];
        std::string methodRun = argv[2];
        std::string timeString = argv[3];
        std::string stepsString = argv[3];
        std::string numberOfParticlesString = argv[4];
        std::string epsilonString = argv[5];
        std::string methodRunningString = argv[6];
        int numberThreads = 0;
        if (methodRunningString != "strong" && methodRunningString != "weak") {
            throw std::invalid_argument(
                "\nPlease select:\n\n-> \"strong\" if you want to run the program "
                "for the strong scaling experiment\n\n-> \"weak\" if you want to run "
                "the program for the weak scaling experiment\n\nRun the program with "
                "the options -h or --help to see how the program should be "
                "launched\n");
        } else {
            if (methodRunningString == "strong") {
                numberThreads = 1;
            } else {
                numberThreads = omp_get_max_threads();
            }
        }
        double dt = std::stod(dtString);
        if (dt <= 0) {
            throw std::logic_error("\nThe increment dt must be a positive value.\n");
        }
        double epsilon = std::stod(epsilonString);
        if (epsilon <= 0) {
            throw std::logic_error(
                "\nThe softening factor epsilon must be a positive value.\n");
        }
        int numberOfParticles = std::stoi(numberOfParticlesString) * numberThreads;
        if (numberOfParticles <= 0) {
            throw std::logic_error(
                "\nThe number of particles should be higher than 0\n");
        }
        nBodySystem.generateInitialConditions(numberOfParticles);
        double energyBeforeUpdate = 0.;
        double energyAfterUpdate = 0.;

        /* If we choose to use the time of integration to compute the evolution of
         * the system */

        if (methodRun == "time") {
            double t = std::stod(timeString);
            if (t <= 0) {
                throw std::logic_error("\nThe time t must be a positive value.\n");
            }
            if (t <= dt) {
                throw std::logic_error(
                    "\nThe time t should be higher than the increment dt\n");
            }
            std::cout << "\n-> Beginning of the simulation for " << numberOfParticles
                      << " particles\n"
                      << std::endl;
            std::cout << "\n-> Running the simulation with dt = " << dt
                      << " s with an integration time of " << t << " s\n"
                      << std::endl;
            auto t1 = Clock::now();
            energyBeforeUpdate = calculateTotalEnergy(nBodySystem.getSystemInformations());
            nBodySystem.evolutionOfSystem(methodRun, t, dt, epsilon);
            energyAfterUpdate = calculateTotalEnergy(nBodySystem.getSystemInformations());
            auto t2 = Clock::now();
            std::cout << "\n-> Elapsed time: " << tSeconds(t1, t2)
                      << " s\n\n\n-> Average timestep: "
                      << tSeconds(t1, t2) / nBodySystem.getIterations() << " s/step\n"
                      << std::endl;
            std::cout << "\n-> Total energy of the system before the update: "
                      << energyBeforeUpdate << " J\n"
                      << std::endl;
            std::cout << "\n-> Total energy of the system after the update: "
                      << energyAfterUpdate << " J\n\n\n-> Energy loss: "
                      << energyAfterUpdate - energyBeforeUpdate
                      << " J\n\n\n-> Energy loss in percentage compared to the "
                         "initial energy: "
                      << std::abs(((energyAfterUpdate - energyBeforeUpdate) / energyBeforeUpdate)) * 100
                      << " %\n"
                      << std::endl;
        }

        /* If we choose to use the number of steps to compute the evolution of the
           system */

        else if (methodRun == "steps") {
            int steps = std::stoi(stepsString);
            if (steps <= 0) {
                throw std::logic_error(
                    "\nThe number of steps should be a positive number\n");
            }
            std::cout << "\n-> Beginning of the simulation for " << numberOfParticles
                      << " particles\n"
                      << std::endl;
            std::cout << "\n-> Running the simulation with dt = " << dt << " s over "
                      << steps << " steps\n"
                      << std::endl;
            auto t1 = Clock::now();
            energyBeforeUpdate = calculateTotalEnergy(nBodySystem.getSystemInformations());
            nBodySystem.evolutionOfSystem(methodRun, steps, dt, epsilon);
            energyAfterUpdate = calculateTotalEnergy(nBodySystem.getSystemInformations());
            auto t2 = Clock::now();
            std::cout << "\n-> Elapsed time: " << tSeconds(t1, t2)
                      << " s\n\n\n-> Average timestep: "
                      << tSeconds(t1, t2) / nBodySystem.getIterations() << " s/step\n"
                      << std::endl;
            std::cout << "\n-> Total energy of the system before the update: "
                      << energyBeforeUpdate << " J\n"
                      << std::endl;
            std::cout << "\n-> Total energy of the system after the update: "
                      << energyAfterUpdate << " J\n\n\n-> Energy loss: "
                      << energyAfterUpdate - energyBeforeUpdate
                      << " J\n\n\n-> Energy loss in percentage compared to the "
                         "initial energy: "
                      << std::abs(((energyAfterUpdate - energyBeforeUpdate) / energyBeforeUpdate)) * 100
                      << " %\n"
                      << std::endl;
        } else {
            throw std::invalid_argument(
                "\nError in selecting the method for running the simulations. Run "
                "'-h' or \"--help\" at the end of the command line to see how the "
                "program should be launched.\n");
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}