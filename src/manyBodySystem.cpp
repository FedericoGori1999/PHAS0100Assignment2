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
    if (d < 0.01)
    {
        epsilon = 0.1;
    }
    Eigen::Vector3d accelerationOnP1 = (p2->getMass() * (p2->getPosition() - p1->getPosition())) / ( sqrt((d * d + epsilon * epsilon) * (d * d + epsilon * epsilon) * (d * d + epsilon * epsilon)) );
    return accelerationOnP1;
}

/* Calculate the total acceleration on a particle. The particle excludes itself from the calculation through a check that involves the mass and the distance with a particle (i.e. if two particles have the
same mass and are really close in terms of distance, then the program treat them as the same particle). */

void Particle::calcTotalAcceleration(std::vector<Particle> particlesInTheSystem)
{
    Eigen::Vector3d totalAcceleration(0, 0, 0);
    for(int i = 0; i < particlesInTheSystem.size(); i++)
    {
        if(getDistance(this, &(particlesInTheSystem.at(i))) != 0 || (this->getMass() != particlesInTheSystem.at(i).getMass()))
        {
            totalAcceleration = totalAcceleration + calcAcceleration(this, &(particlesInTheSystem.at(i)), 0.0);
        }    
    }
    accelerationParticle = totalAcceleration;
}

/* initialConditionGenerator for the solar system with the sun and 8 planets */

initialConditionGenerator::initialConditionGenerator()
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
    planets.push_back(sun);
    planets.push_back(mercury);
    planets.push_back(venus);
    planets.push_back(earth);
    planets.push_back(mars);
    planets.push_back(jupiter);
    planets.push_back(saturn);
    planets.push_back(uranus);
    planets.push_back(neptune);
    distanceFromSun.push_back(0.0);
    distanceFromSun.push_back(0.4);
    distanceFromSun.push_back(0.7);
    distanceFromSun.push_back(1.);
    distanceFromSun.push_back(1.5);
    distanceFromSun.push_back(5.2);
    distanceFromSun.push_back(9.5);
    distanceFromSun.push_back(19.2);
    distanceFromSun.push_back(30.1);
    namesPlanets.push_back("Sun");
    namesPlanets.push_back("Mercury");
    namesPlanets.push_back("Venus");
    namesPlanets.push_back("Earth");
    namesPlanets.push_back("Mars");
    namesPlanets.push_back("Jupiter");
    namesPlanets.push_back("Saturn");
    namesPlanets.push_back("Uranus");
    namesPlanets.push_back("Neptune");
    sun.setPosition(Eigen::Vector3d(0., 0., 0.));
    sun.setVelocity(Eigen::Vector3d(0., 0., 0.));

    for(int i = 1; i < 9; i++)
    {
        double theta = randomValueGenerator(0., 2 * M_PI);
        planets.at(i).setPosition( Eigen::Vector3d( distanceFromSun.at(i) * std::sin(theta) , distanceFromSun.at(i) * std::cos(theta) , 0.0 ) );
        planets.at(i).setVelocity( Eigen::Vector3d( ((-1) * (std::cos(theta))) / std::sqrt(distanceFromSun.at(i)) , (std::sin(theta)) / std::sqrt(distanceFromSun.at(i)) , 0.0 ) );
    }
}

/* Get the vector of particles (i.e. planets) */

std::vector<Particle> initialConditionGenerator::getSolarSystemInformations()
{
    return planets;
}

/* Get the vector of strings with the names of the planets for printing purposes */

std::vector<std::string> initialConditionGenerator::getNamesPlanets()
{
    return namesPlanets;
}

/* Evolution of the system through the calculation of the total acceleration for each particle and through the update function. */

void initialConditionGenerator::evolutionOfSystem(std::string method, double upperLimit, double dt)
{
    if(method == "time")
    {
        double t = 0;
        while(t < upperLimit)
        {
            for(int i = 0; i < planets.size(); i++)
            {
                planets.at(i).calcTotalAcceleration(planets);
            }
            for(int i = 0; i < planets.size(); i++)
            {
                planets.at(i).update(dt);
            }
            t = t + dt;
        }
    }
    else
    {
        int steps = (int)upperLimit;
        for(int j = 0; j < steps; j++)
        {
            for(int i = 0; i < planets.size(); i++)
            {
                planets.at(i).calcTotalAcceleration(planets);
            }
            for(int i = 0; i < planets.size(); i++)
            {
                planets.at(i).update(dt);
            }
        }
    }
}