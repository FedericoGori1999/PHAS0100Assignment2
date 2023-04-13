#include "particle.hpp"
#include "manyBodySystem.hpp"
#include <chrono>

/* Expected call of the program: 

"./build/solarSystemSimulator <dt> time <totalTime>" if you want to iterate until the <totalTime> is reached

or

"./build/solarSystemSimulator <dt> steps <numberOfSteps>" if you want to iterate until the number of steps done in the evolution is
<numberOfSteps>

If -h or --help is displayed at the end of the string, an help message should be printed */

typedef std::chrono::high_resolution_clock Clock;

/* Function to time the execution of the program */

double tSeconds(std::chrono::time_point<Clock> t1, std::chrono::time_point<Clock> t2)
{
  return (t2 - t1).count() / 1e9;
}

int main(int argc, char **argv) 
{
  int count = 0;

  /* Printing format for vectors from Eigen Library */

  Eigen::IOFormat CommaInitFmt(Eigen::FullPrecision, Eigen::DontAlignCols, ",", ", ");
  std::string helpString = argv[argc-1];
  try
  {
      if(helpString == "-h" || helpString == "--help" || argc == 1)
    {
      /* Prints help message */

      throw std::invalid_argument("\nTo call the programs you can:\n\nRun ./build/solarSystemSimulator <dt> time <total_time> if you want to run it until a certain time t has been reached\n\nRun ./build/solarSystemSimulator <dt> steps <number_of_steps> if you want to simulate a certain number of steps.\n\nBy placing '-h' or \"--help\" at the end of the command line this message will appear again.\n");
    }
    if(argc != 4)
    {
      /* Wrong number of arguments passed by command line */

      throw std::invalid_argument("\nError in calling the program: run '-h' or \"--help\" at the end of the command line to see how the program should be launched.\n");
    }
    solarSystemGenerator solarSystem;
    solarSystem.generateInitialConditions(9);
    std::string dtString = argv[1];
    std::string methodRun = argv[2];
    std::string timeString = argv[3];
    std::string stepsString = argv[3];
    double dt = std::stod(dtString);
    if(dt <= 0)
    {
      throw std::logic_error("\nThe increment dt must be a positive value.\n");
    }
    double energyBeforeUpdate = 0.;
    double energyAfterUpdate = 0.;

    /* If we choose to use the time of integration to compute the evolution of the system */

    if(methodRun == "time")
    {
      double t = std::stod(timeString);
      if(t <= 0)
      {
        throw std::logic_error("\nThe time t must be a positive value.\n");
      }
      if(t <= dt)
      {
        throw std::logic_error("\nThe time t should be higher than the increment dt\n");
      }
      std::cout << "\n-> Initial positions and velocities of the planets in the system.\n" << std::endl;
      for(int i = 0; i < 9; i++)
      {
        /* Printing system's informations */

        std::cout << "Planet " << solarSystem.getIdentifierParticles().at(i) << ":\nPosition: (" << solarSystem.getSystemInformations().at(i).getPosition().format(CommaInitFmt) << ")\nVelocity: (" << solarSystem.getSystemInformations().at(i).getVelocity().format(CommaInitFmt) << ")\n" << std::endl;
      }
      auto t1 = Clock::now();
      energyBeforeUpdate = calculateTotalEnergy(solarSystem.getSystemInformations());
      std::cout << "\n-> Total energy of the system before the update: " << energyBeforeUpdate << " J\n" << std::endl;
      std::cout << "\n-> Running the simulation with dt = " << dt << " s with an integration time of " << t << " s\n" << std::endl;
      solarSystem.evolutionOfSystem(methodRun, t, dt, 0.0);
      energyAfterUpdate = calculateTotalEnergy(solarSystem.getSystemInformations());
      auto t2 = Clock::now();
      std::cout << "\n-> Total energy of the system after the update: " << energyAfterUpdate << " J\n\n\n-> Energy loss: " << energyAfterUpdate - energyBeforeUpdate << " J\n" << std::endl;
      std::cout << "\n-> Elapsed time: " << tSeconds(t1, t2) << " s\n\n\n-> Average timestep: " << tSeconds(t1, t2)/solarSystem.getIterations() << " s/step\n" << std::endl;
      std::cout << "\n-> Final positions and velocities of the planets in the system.\n" << std::endl;
      for(int i = 0; i < 9; i++)
      {
        /* Printing system's informations */

        std::cout << "Planet " << solarSystem.getIdentifierParticles().at(i) << ":\nPosition: (" << solarSystem.getSystemInformations().at(i).getPosition().format(CommaInitFmt) << ")\nVelocity: (" << solarSystem.getSystemInformations().at(i).getVelocity().format(CommaInitFmt) << ")\n" << std::endl;
      } 
    }
    /* If we choose to use the number of steps to compute the evolution of the system */

    else if(methodRun == "steps")
    {
      int steps = std::stoi(stepsString);
      if(steps <= 0)
      {
        throw std::logic_error("\nThe number of steps should be a positive number\n");
      }
      std::cout << "\n-> Initial positions and velocities of the planets in the system.\n" << std::endl;
      for(int i = 0; i < 9; i++)
      {
        /* Printing system's informations */

        std::cout << "Planet " << solarSystem.getIdentifierParticles().at(i) << ":\nPosition: (" << solarSystem.getSystemInformations().at(i).getPosition().format(CommaInitFmt) << ")\nVelocity: (" << solarSystem.getSystemInformations().at(i).getVelocity().format(CommaInitFmt) << ")\n" << std::endl;
      }
      auto t1 = Clock::now();
      energyBeforeUpdate = calculateTotalEnergy(solarSystem.getSystemInformations());
      std::cout << "\n-> Total energy of the system before the update: " << energyBeforeUpdate << " J\n" << std::endl;
      std::cout << "\n-> Running the simulation with dt = " << dt << " s over " << steps << " steps\n" << std::endl;
      solarSystem.evolutionOfSystem(methodRun, steps, dt, 0.0);
      energyAfterUpdate = calculateTotalEnergy(solarSystem.getSystemInformations());
      auto t2 = Clock::now();
      std::cout << "\n-> Total energy of the system after the update: " << energyAfterUpdate << " J\n\n\n-> Energy loss: " << energyAfterUpdate - energyBeforeUpdate << " J\n" << std::endl;
      std::cout << "\n-> Elapsed time: " << tSeconds(t1, t2) << " s\n\n\n-> Average timestep: " << tSeconds(t1, t2)/solarSystem.getIterations() << " s/step\n" << std::endl;
      std::cout << "\n-> Final positions and velocities of the planets in the system.\n" << std::endl;
      for(int i = 0; i < 9; i++)
      {
        /* Printing system's informations */

        std::cout << "Planet " << solarSystem.getIdentifierParticles().at(i) << ":\nPosition: (" << solarSystem.getSystemInformations().at(i).getPosition().format(CommaInitFmt) << ")\nVelocity: (" << solarSystem.getSystemInformations().at(i).getVelocity().format(CommaInitFmt) << ")\n" << std::endl;
      }
    }
    else
    {
      throw std::invalid_argument("\nError in selecting the method for running the simulations. Run '-h' or \"--help\" at the end of the command line to see how the program should be launched.\n");
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }  
  return 0;
}