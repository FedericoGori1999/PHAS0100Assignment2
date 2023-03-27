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

/* Function used mainly for testing, it sets the position of the particle */

void Particle::setPosition(Eigen::Vector3d position)
{
    positionParticle = position;
}

/* Function used mainly for testing, it sets the velocity of the particle */

void Particle::setVelocity(Eigen::Vector3d velocity)
{
    velocityParticle = velocity;
}

/* Function used mainly for testing, it sets the acceleration of the particle */

void Particle::setAcceleration(Eigen::Vector3d acceleration)
{
    accelerationParticle = acceleration;
}

double Particle::randomValueGenerator()
{
    std::uniform_real_distribution<> uniformReal(minRandomValue, maxRandomValue);
    std::mt19937 rng;
    std::random_device trueRandomNumber;
    rng.seed(trueRandomNumber());
    auto randomValue = std::bind(uniformReal, rng);
    double result = randomValue();
    return result;
}

/* Function used mainly for testing, it sets the position of the particle randomly */

void Particle::setRandomPosition()
{
    double x = randomValueGenerator();
    double y = randomValueGenerator();
    double z = randomValueGenerator();
    positionParticle << x, y, z;
}

/* Function used mainly for testing, it sets the velocity of the particle randomly */

void Particle::setRandomVelocity()
{
    double vx = randomValueGenerator();
    double vy = randomValueGenerator();
    double vz = randomValueGenerator();
    velocityParticle << vx, vy, vz;
}

/* Function used mainly for testing, it sets the acceleration of the particle randomly */

void Particle::setRandomAcceleration()
{
    double ax = randomValueGenerator();
    double ay = randomValueGenerator();
    double az = randomValueGenerator();
    accelerationParticle << ax, ay, az;
}

void Particle::update(double dt)
{
    Eigen::Vector3d newPositionParticle(3);
    Eigen::Vector3d newVelocityParticle(3);
    positionParticle = this->getPosition() + dt * this->getVelocity();
    velocityParticle = this->getVelocity() + dt * this->getAcceleration();
}