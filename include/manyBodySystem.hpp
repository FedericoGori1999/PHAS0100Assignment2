#pragma once
#include <Eigen/Core>
#include <iostream>
#include <string>
#include <cmath>
#include "particle.hpp"

/* See .cpp file for explanation and comments */

double getDistance(Particle *p1, Particle *p2);

Eigen::Vector3d calcAcceleration(Particle *p1, Particle *p2, double epsilon);

double calculateTotalEnergy(std::vector<Particle> particlesInTheSystem);

class InitialConditionGenerator
{
    public:
    virtual void generateInitialConditions(int numberOfParticles) = 0;
    std::vector<Particle> getSystemInformations();
    void evolutionOfSystem(std::string method, double upperLimit, double dt, double epsilon);
    int getIterations();
    
    protected:

    std::vector<Particle> systemOfParticles{};
    std::vector<double> distanceFromCentralStar {};
    int iterations = 0;
};

class solarSystemGenerator : public InitialConditionGenerator
{
    public:

    void generateInitialConditions(int numberOfParticles);
    std::vector<std::string> getIdentifierParticles();

    private:

    std::vector<std::string> namesParticles {};
};

class nBodySystemGenerator : public InitialConditionGenerator
{
    public:
    void generateInitialConditions(int numberOfParticles);
};