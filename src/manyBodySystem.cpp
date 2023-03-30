#include "manyBodySystem.hpp"

/* Gives the distance between two particles */

double getDistance(Particle *p1, Particle *p2)
{
    Eigen::Vector3d vectorDifference(p1->getPosition() - p2->getPosition());
    return vectorDifference.norm();
}

/* Calculates the acceleration betwen two particles. The softening factor is different from 0 only when particles are really close (chosen under a distance of 0.01) */

Eigen::Vector3d calcAcceleration(Particle *p1, Particle *p2, double epsilon)
{
    double d = getDistance(p1, p2);
    Eigen::Vector3d accelerationOnP1 = (p2->getMass() * (p2->getPosition() - p1->getPosition())) / ( sqrt((d * d + epsilon * epsilon) * (d * d + epsilon * epsilon) * (d * d + epsilon * epsilon)) );
    return accelerationOnP1;
}

/* solarSystemGenerator for the solar system with the sun and 8 planets */

void solarSystemGenerator::generateInitialConditions(int numberOfParticles)
{
    Particle sun(1.);
    Particle mercury(1./6023600);
    Particle venus(1./408524);
    Particle earth(1./332946.038);
    Particle mars(1./3098710);
    Particle jupiter(1./1047.55);
    Particle saturn(1./3499);
    Particle uranus(1./22962);
    Particle neptune(1./19352);
    systemOfParticles.push_back(sun);
    systemOfParticles.push_back(mercury);
    systemOfParticles.push_back(venus);
    systemOfParticles.push_back(earth);
    systemOfParticles.push_back(mars);
    systemOfParticles.push_back(jupiter);
    systemOfParticles.push_back(saturn);
    systemOfParticles.push_back(uranus);
    systemOfParticles.push_back(neptune);
    distanceFromCentralStar.push_back(0.0);
    distanceFromCentralStar.push_back(0.4);
    distanceFromCentralStar.push_back(0.7);
    distanceFromCentralStar.push_back(1.);
    distanceFromCentralStar.push_back(1.5);
    distanceFromCentralStar.push_back(5.2);
    distanceFromCentralStar.push_back(9.5);
    distanceFromCentralStar.push_back(19.2);
    distanceFromCentralStar.push_back(30.1);
    namesParticles.push_back("Sun");
    namesParticles.push_back("Mercury");
    namesParticles.push_back("Venus");
    namesParticles.push_back("Earth");
    namesParticles.push_back("Mars");
    namesParticles.push_back("Jupiter");
    namesParticles.push_back("Saturn");
    namesParticles.push_back("Uranus");
    namesParticles.push_back("Neptune");
    sun.setPosition(Eigen::Vector3d(0., 0., 0.));
    sun.setVelocity(Eigen::Vector3d(0., 0., 0.));

    for(int i = 1; i < 9; i++)
    {
        double theta = randomValueGenerator(0., 2 * M_PI);
        systemOfParticles.at(i).setPosition( Eigen::Vector3d( distanceFromCentralStar.at(i) * std::sin(theta) , distanceFromCentralStar.at(i) * std::cos(theta) , 0.0 ) );
        systemOfParticles.at(i).setVelocity( Eigen::Vector3d( ((-1) * (std::cos(theta))) / std::sqrt(distanceFromCentralStar.at(i)) , (std::sin(theta)) / std::sqrt(distanceFromCentralStar.at(i)) , 0.0 ) );
    }
}

/* Get the vector of particles (i.e. systemOfParticles) */

std::vector<Particle> InitialConditionGenerator::getSystemInformations()
{
    return systemOfParticles;
}

/* Get the vector of strings with the names of the planets for printing purposes */

std::vector<std::string> solarSystemGenerator::getIdentifierParticles()
{
    return namesParticles;
}

/* This function returns the number of iterations needed for the evolution of the system */

int InitialConditionGenerator::getIterations()
{
    return iterations;
}

/* Evolution of the system through the calculation of the total acceleration for each particle and through the update function. */

void InitialConditionGenerator::evolutionOfSystem(std::string method, double upperLimit, double dt, double epsilon)
{
    if(method == "time")
    {
        double t = 0;
        while(t < upperLimit)
        {
            for(int i = 0; i < systemOfParticles.size(); i++)
            {
                systemOfParticles.at(i).calcTotalAcceleration(systemOfParticles, epsilon);
            }
            for(int i = 0; i < systemOfParticles.size(); i++)
            {
                systemOfParticles.at(i).update(dt);
            }
            t = t + dt;
            iterations++;
        }
    }
    else
    {
        int steps = (int)upperLimit;
        for(int j = 0; j < steps; j++)
        {
            for(int i = 0; i < systemOfParticles.size(); i++)
            {
                systemOfParticles.at(i).calcTotalAcceleration(systemOfParticles, epsilon);
            }
            for(int i = 0; i < systemOfParticles.size(); i++)
            {
                systemOfParticles.at(i).update(dt);
            }
            iterations++;
        }
    }
}

/* Function that calculates the total energy of a system of particles */

double calculateTotalEnergy(std::vector<Particle> particlesInTheSystem)
{
    double totalKineticEnergy = 0.;
    double totalPotentialEnergy = 0.;
    for(int i = 0; i < particlesInTheSystem.size(); i++)
    {
        totalKineticEnergy = totalKineticEnergy + particlesInTheSystem.at(i).calculateKineticEnergy();
        totalPotentialEnergy = totalPotentialEnergy + particlesInTheSystem.at(i).calculatePotentialEnergy(particlesInTheSystem);
    }
    return totalKineticEnergy + totalPotentialEnergy; 
}

void nBodySystemGenerator::generateInitialConditions(int numberOfParticles)
{
    systemOfParticles.push_back(Particle(1.));
    systemOfParticles.at(0).setPosition(Eigen::Vector3d(0., 0., 0.));
    systemOfParticles.at(0).setVelocity(Eigen::Vector3d(0., 0., 0.));
    distanceFromCentralStar.push_back(0);

    for(int i = 1; i < numberOfParticles; i++)
    {
        systemOfParticles.push_back(Particle(randomValueGenerator(1./6000000, 1./1000)));
        double theta = randomValueGenerator(0., 2 * M_PI);
        distanceFromCentralStar.push_back(randomValueGenerator(0.4, 30.));
        systemOfParticles.at(i).setPosition( Eigen::Vector3d( distanceFromCentralStar.at(i) * std::sin(theta) , distanceFromCentralStar.at(i) * std::cos(theta) , 0.0 ) );
        systemOfParticles.at(i).setVelocity( Eigen::Vector3d( ((-1) * (std::cos(theta))) / std::sqrt(distanceFromCentralStar.at(i)) , (std::sin(theta)) / std::sqrt(distanceFromCentralStar.at(i)) , 0.0 ) );
    }
}