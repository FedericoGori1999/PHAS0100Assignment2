#pragma once
#include <Eigen/Core>
#include <iostream>
#include <string>
#include <cmath>
#include "particle.hpp"

/* See .cpp file for explanation and comments */

double getDistance(Particle *p1, Particle *p2);

Eigen::Vector3d calcAcceleration(Particle *p1, Particle *p2, double epsilon);

class initialConditionGenerator
{
    public:
    initialConditionGenerator();
    std::vector<Particle> getSolarSystemInformations();
    std::vector<std::string> getNamesPlanets();
    void evolutionOfSystem(std::string method, double upperLimit, double dt);

    private:
    std::vector<Particle> planets{};
    std::vector<double> distanceFromSun {};
    std::vector<std::string> namesPlanets {};
};