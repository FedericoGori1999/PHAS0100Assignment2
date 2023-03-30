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

/* Function used mainly for testing, it sets the position of the particle randomly */

void Particle::setRandomPosition(double minRandomValue, double maxRandomValue)
{
    double x = randomValueGenerator(minRandomValue, maxRandomValue);
    double y = randomValueGenerator(minRandomValue, maxRandomValue);
    double z = randomValueGenerator(minRandomValue, maxRandomValue);
    positionParticle << x, y, z;
}

/* Function used mainly for testing, it sets the velocity of the particle randomly */

void Particle::setRandomVelocity(double minRandomValue, double maxRandomValue)
{
    double vx = randomValueGenerator(minRandomValue, maxRandomValue);
    double vy = randomValueGenerator(minRandomValue, maxRandomValue);
    double vz = randomValueGenerator(minRandomValue, maxRandomValue);
    velocityParticle << vx, vy, vz;
}

/* Function used mainly for testing, it sets the acceleration of the particle randomly */

void Particle::setRandomAcceleration(double minRandomValue, double maxRandomValue)
{
    double ax = randomValueGenerator(minRandomValue, maxRandomValue);
    double ay = randomValueGenerator(minRandomValue, maxRandomValue);
    double az = randomValueGenerator(minRandomValue, maxRandomValue);
    accelerationParticle << ax, ay, az;
}

void Particle::update(double dt)
{
    Eigen::Vector3d newPositionParticle(3);
    Eigen::Vector3d newVelocityParticle(3);
    positionParticle = this->getPosition() + dt * this->getVelocity();
    velocityParticle = this->getVelocity() + dt * this->getAcceleration();
}

/* Calculate the total acceleration on a particle. The particle excludes itself from the calculation through a check that involves the mass and the distance with a particle (i.e. if two particles have the
same mass and are really close in terms of distance, then the program treat them as the same particle). */

void Particle::calcTotalAcceleration(std::vector<Particle> particlesInTheSystem, double epsilon)
{
    Eigen::Vector3d totalAcceleration(0, 0, 0);
    for(int i = 0; i < particlesInTheSystem.size(); i++)
    {
        if(getDistance(this, &(particlesInTheSystem.at(i))) != 0 || (this->getMass() != particlesInTheSystem.at(i).getMass()))
        {
            totalAcceleration = totalAcceleration + calcAcceleration(this, &(particlesInTheSystem.at(i)), epsilon);
        }    
    }
    accelerationParticle = totalAcceleration;
}

/* Generates a random real number in the interval [minRandomValue, maxRandomValue] following a uniform distribution */

double randomValueGenerator(double minRandomValue, double maxRandomValue)
{
    std::uniform_real_distribution<> uniformReal(minRandomValue, maxRandomValue);
    std::mt19937 rng;
    std::random_device trueRandomNumber;

    /* Explain how to change the seed (see 2.3) */

    rng.seed(trueRandomNumber());
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
    for(int i = 0; i < particlesInTheSystem.size(); i++)
    {
        if(getDistance(this, &(particlesInTheSystem.at(i))) != 0 || (this->getMass() != particlesInTheSystem.at(i).getMass()))
        {
           potentialEnergy = potentialEnergy - 0.5 * ( (this->getMass() * particlesInTheSystem.at(i).getMass()) / (getDistance(this, &(particlesInTheSystem.at(i)))) );
        }
    }
    return potentialEnergy;
}