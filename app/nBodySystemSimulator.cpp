#include "particle.hpp"
#include "manyBodySystem.hpp"
#include <chrono>

/* Expected call of the program: ./build/nBodySystemSimulator <dt> time <total_time> <numberOfParticles> <epsilon> || ./build/nBodySystemSimulator <dt> steps <numberOfSteps> <numberOfParticles> <epsilon>. If -h or --help is displayed at the end
of the string, an help message should be printed */

/* IMPLEMENT EXCEPTIONS FOR BAD READ OF DOUBLE NUMBERS */

/* Function to time the execution of the program */

typedef std::chrono::high_resolution_clock Clock;

double tSeconds(std::chrono::time_point<Clock> t1, std::chrono::time_point<Clock> t2)
{
  return (t2 - t1).count() / 1e9;
}

int main(int argc, char **argv) 
{
  int count = 0;
  Eigen::IOFormat CommaInitFmt(Eigen::FullPrecision, Eigen::DontAlignCols, ",", ", ");
  std::string helpString = argv[argc-1];
  if(helpString == "-h" || helpString == "--help" || argc == 1)
  {
    std::cout << "To call the programs you can:\n\nRun ./build/nBodySystemSimulator <dt> time <total_time> if you want to run it until a certain time t has been reached\n\nRun ./build/nBodySystemSimulator <dt> steps <number_of_steps> if you want to simulate a certain number of steps.\n\nBy placing '-h' or \"--help\" at the end of the command line this message will appear again.\n" << std::endl;
    return 1;
  }
  else
  {
    if(argc != 6)
    {
      std::cout << "\nError in calling the program: run '-h' or \"--help\" at the end of the command line to see how the program should be launched.\n" << std::endl;
      return 1;
    }
    else
    {
      nBodySystemGenerator nBodySystem;
      std::string dtString = argv[1];
      std::string methodRun = argv[2];
      std::string timeString = argv[3];
      std::string stepsString = argv[3];
      std::string numberOfParticlesString = argv[4];
      std::string epsilonString = argv[5];
      double dt = std::stod(dtString);
      double epsilon = std::stod(epsilonString);
      int numberOfParticles = std::stoi(numberOfParticlesString);
      nBodySystem.generateInitialConditions(numberOfParticles);
      std::vector<Particle> informationsToPrint = nBodySystem.getSystemInformations();

      /* If we choose to set a total limit of integration */

      if(methodRun == "time")
      {
        double t = std::stod(timeString);
        std::cout << "\n-> Beginning of the simulation for " << numberOfParticles << " particles\n" << std::endl;
        std::cout << "\n-> Total energy of the system before the update: " << calculateTotalEnergy(informationsToPrint) << " J\n" << std::endl;
        std::cout << "\n-> Running the simulation with dt = " << dt << " s with an integration time of " << t << " s\n" << std::endl;
        auto t1 = Clock::now();
        nBodySystem.evolutionOfSystem(methodRun, t, dt, epsilon);
        auto t2 = Clock::now();
        informationsToPrint = nBodySystem.getSystemInformations();
        std::cout << "\n-> Total energy of the system after the update: " << calculateTotalEnergy(informationsToPrint) << " J\n" << std::endl;
        std::cout << "\n-> Time elapsed: " << tSeconds(t1, t2) << " s\n\n\n-> Average timestep: " << tSeconds(t1, t2)/nBodySystem.getIterations() << " s/step\n" << std::endl;
        return 0;
      }

      /* If we choose to set a total number of steps for the integration */

      else if(methodRun == "steps")
      {
        int steps = std::stoi(stepsString);
        std::cout << "\n-> Beginning of the simulation for " << numberOfParticles << " particles\n" << std::endl;
        std::cout << "\n-> Total energy of the system before the update: " << calculateTotalEnergy(informationsToPrint) << " J\n" << std::endl;
        std::cout << "\n-> Running the simulation with dt = " << dt << " s over " << steps << " steps\n" << std::endl;
        auto t1 = Clock::now();
        nBodySystem.evolutionOfSystem(methodRun, steps, dt, epsilon);
        auto t2 = Clock::now();
        informationsToPrint = nBodySystem.getSystemInformations();
        std::cout << "\n-> Total energy of the system after the update: " << calculateTotalEnergy(informationsToPrint) << " J\n" << std::endl;
        std::cout << "\n-> Time elapsed: " << tSeconds(t1, t2) << " s\n\n\n-> Average timestep: " << tSeconds(t1, t2)/nBodySystem.getIterations() << " s/step\n" << std::endl;
        return 0;
      }
      else
      {
        std::cout << "\nError in selecting the method for running the simulations. Run '-h' or \"--help\" at the end of the command line to see how the program should be launched.\n" << std::endl;
        return 1;
      }  
    }
  }
}