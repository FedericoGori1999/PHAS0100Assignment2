#include "particle.hpp"
#include "manyBodySystem.hpp"

Particle::Particle(double massArgument)
{
    mass = massArgument;
}

double Particle::getMass() const
{
    return mass;
}

Eigen::Vector3d Particle::getPosition()
{
    return positionParticle;
}

Eigen::Vector3d Particle::getVelocity()
{
    return velocityParticle;
}

Eigen::Vector3d Particle::getAcceleration()
{
    return accelerationParticle;
}

/* Function used mainly for testing, it sets the position of the particle manually */

void Particle::setPosition(Eigen::Vector3d position)
{
    positionParticle = position;
}

/* Function used mainly for testing, it sets the velocity of the particle manually */

void Particle::setVelocity(Eigen::Vector3d velocity)
{
    velocityParticle = velocity;
}

/* Function used mainly for testing, it sets the acceleration of the particle manually */

void Particle::setAcceleration(Eigen::Vector3d acceleration)
{
    accelerationParticle = acceleration;
}

void Particle::setMass(double massArgument)
{
    mass = massArgument;
}

/* Function that sets the position of the particle randomly */

void Particle::setRandomPosition(double minRandomValue, double maxRandomValue)
{
    double x = randomValueGenerator(minRandomValue, maxRandomValue);
    double y = randomValueGenerator(minRandomValue, maxRandomValue);
    double z = randomValueGenerator(minRandomValue, maxRandomValue);
    /*#pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                x = randomValueGenerator(minRandomValue, maxRandomValue);
            }
            #pragma omp section
            {
                y = randomValueGenerator(minRandomValue, maxRandomValue);
            }
            #pragma omp section
            {
                z = randomValueGenerator(minRandomValue, maxRandomValue);
            }
        }
    }*/
    positionParticle << x, y, z;
}

/* Function that sets the velocity of the particle randomly */

void Particle::setRandomVelocity(double minRandomValue, double maxRandomValue)
{
    double vx = randomValueGenerator(minRandomValue, maxRandomValue);
    double vy = randomValueGenerator(minRandomValue, maxRandomValue);
    double vz = randomValueGenerator(minRandomValue, maxRandomValue);
    /*#pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                vx = randomValueGenerator(minRandomValue, maxRandomValue);
            }
            #pragma omp section
            {
                vy = randomValueGenerator(minRandomValue, maxRandomValue);
            }
            #pragma omp section
            {
                vz = randomValueGenerator(minRandomValue, maxRandomValue);
            }
        }
    }*/
    velocityParticle << vx, vy, vz;
}

/* Function that sets the acceleration of the particle randomly */

void Particle::setRandomAcceleration(double minRandomValue, double maxRandomValue)
{
    double ax = randomValueGenerator(minRandomValue, maxRandomValue);
    double ay = randomValueGenerator(minRandomValue, maxRandomValue);
    double az = randomValueGenerator(minRandomValue, maxRandomValue);
    /*#pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                ax = randomValueGenerator(minRandomValue, maxRandomValue);
            }
            #pragma omp section
            {
                ay = randomValueGenerator(minRandomValue, maxRandomValue);
            }
            #pragma omp section
            {
                az = randomValueGenerator(minRandomValue, maxRandomValue);
            }
        }
    }*/
    accelerationParticle << ax, ay, az;
}

/* Function that updates the positions and velocities of the particles */

void Particle::update(double dt)
{
    positionParticle = this->getPosition() + dt * this->getVelocity();
    velocityParticle = this->getVelocity() + dt * this->getAcceleration();
}

/* Calculate the total acceleration on a particle. The particle excludes itself from the calculation through a check that involves the
mass and the distance with a particle (i.e. if two particles have the same mass and are in the same position, then the program treat them
as the same particle). */

void Particle::calcTotalAcceleration(std::vector<Particle> particlesInTheSystem, double epsilon)
{
    /* Variable that stores the acceleration to copy to the private member "accelerationParticle" of the Particle class */

    Eigen::Vector3d totalAcceleration(0., 0., 0.);
    #pragma omp parallel 
    {
        /* "accelerationPrivateInCycle" is a private variable created for each loop. No default reduction exists for the type
        Eigen::Vector3d() */

        Eigen::Vector3d accelerationPrivateInCycle(0., 0., 0.);
        #pragma omp for schedule(runtime)
        for(int i = 0; i < particlesInTheSystem.size(); i++)
        {
            /* Check to exclude interactions of particles with themselves */

            if(getDistance(this, &(particlesInTheSystem.at(i))) != 0 || (this->getMass() != particlesInTheSystem.at(i).getMass()))
            {
                accelerationPrivateInCycle = accelerationPrivateInCycle + calcAcceleration(this, &(particlesInTheSystem.at(i)), epsilon);
            }    
        }

        /* Putting together the private variables created for each loop */

        #pragma omp critical
        {
            totalAcceleration = totalAcceleration + accelerationPrivateInCycle;
        }
    }
    /* Copying the totalAcceleration variable to the private member "accelerationParticle" of the class Particle */

    accelerationParticle = totalAcceleration;
}

/* Generates a random real number in the interval [minRandomValue, maxRandomValue] following a uniform distribution */

double randomValueGenerator(double minRandomValue, double maxRandomValue, bool seedIsRandom)
{
    std::uniform_real_distribution<> uniformReal(minRandomValue, maxRandomValue);
    std::mt19937 rng;

    /* By default, the value of the seed is set in the function declaration as a bool variable. By changing it in the .hpp file one 
    is able to select between a manual or a random seed. */

    if(seedIsRandom)
    {
        std::random_device trueRandomNumber;
        rng.seed(trueRandomNumber());
    }
    else
    {
        rng.seed(1);
    }
    auto randomValue = std::bind(uniformReal, rng);
    double result = randomValue();
    return result;
}

/* This function returns the kinetic energy of the particle */

double Particle::calculateKineticEnergy()
{
    return 0.5 * this->getMass() * this->getVelocity().dot(this->getVelocity());
}

/* This function calculates the potential energy acting on a particle */

double Particle::calculatePotentialEnergy(std::vector<Particle> particlesInTheSystem)
{
    double potentialEnergy = 0.;
    #pragma omp parallel for reduction(-:potentialEnergy)
    for(int i = 0; i < particlesInTheSystem.size(); i++)
    {
        /* Check to exclude interactions of particles with themselves */

        if(getDistance(this, &(particlesInTheSystem.at(i))) != 0 || (this->getMass() != particlesInTheSystem.at(i).getMass()))
        {
           potentialEnergy = potentialEnergy - 0.5 * ( (this->getMass() * particlesInTheSystem.at(i).getMass()) / (getDistance(this, &(particlesInTheSystem.at(i)))) );
        }
    }
    return potentialEnergy;
}