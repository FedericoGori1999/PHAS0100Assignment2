#include "particle.hpp"

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

/* Generates a random real number in the interval [minRandomValue, maxRandomValue] following a uniform distribution */

double randomValueGenerator(double minRandomValue, double maxRandomValue)
{
    std::uniform_real_distribution<> uniformReal(minRandomValue, maxRandomValue);
    std::mt19937 rng;
    std::random_device trueRandomNumber;
    rng.seed(trueRandomNumber());
    auto randomValue = std::bind(uniformReal, rng);
    double result = randomValue();
    return result;
}