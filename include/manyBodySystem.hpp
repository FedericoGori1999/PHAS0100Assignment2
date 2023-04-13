#pragma once
#include <Eigen/Core>
#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include "omp.h"
#include "particle.hpp"

/* See .cpp file for explanation and comments */

double getDistance(Particle *p1, Particle *p2);

Eigen::Vector3d calcAcceleration(Particle *p1, Particle *p2, double epsilon = 0.);

double calculateTotalEnergy(std::vector<Particle> particlesInTheSystem);

/* Virtual class InitialConditionGenerator with the virtual function generateInitialConditions. The other functions are inherited from the 
subclasses. */

class InitialConditionGenerator
{
    public:
    virtual void generateInitialConditions(int particlesInTheSystem) = 0;
    std::vector<Particle> getSystemInformations();
    void evolutionOfSystem(std::string method, double upperLimit, double dt, double epsilon);
    int getIterations();
    int getNumberOfParticles();
    void copySystem(std::vector<Particle> *toCopy);
    
    protected:

    /* The protected variables here stored are systemOfParticles (a vector that contains every particle object in the system), 
    distanceFromCentralStar (a vector that need to be read with the same index as systemOfParticles, it stores the distance between the
    particle at position i with the central particle of the system), iterations (it counts the number of iterations made during the 
    evolution of the system) and numberOfParticles. */

    std::vector<Particle> systemOfParticles{};
    std::vector<double> distanceFromCentralStar {};
    int iterations = 0;
    int numberOfParticles = 0;
};

class solarSystemGenerator : public InitialConditionGenerator
{
    public:

    void generateInitialConditions(int numberOfParticles);
    std::vector<std::string> getIdentifierParticles();

    private:

    /* namesParticles is a vector that needs to be read following the same index as the vector systemOfParticles, it contains the names
    of the planets */
    
    std::vector<std::string> namesParticles {};
};

class nBodySystemGenerator : public InitialConditionGenerator
{
    public:
    void generateInitialConditions(int numberOfParticles);
};