#pragma once
#include <Eigen/Core>
#include <iostream>
#include <random>

class Particle {
    public:
        Particle(double in_mass);

        Eigen::Vector3d getPosition();
        Eigen::Vector3d getVelocity();
        Eigen::Vector3d getAcceleration();
        void setRandomPosition();
        void setRandomVelocity();
        void setRandomAcceleration();
        void setPosition(Eigen::Vector3d position);
        void setVelocity(Eigen::Vector3d velocity);
        void setAcceleration(Eigen::Vector3d acceleration);
        double randomValueGenerator();

        double getMass() const;
        void update(double dt);

    private:
        double mass;
        Eigen::Vector3d positionParticle = Eigen::Vector3d(0, 0, 0);
        Eigen::Vector3d velocityParticle = Eigen::Vector3d(0, 0, 0);
        Eigen::Vector3d accelerationParticle = Eigen::Vector3d(0, 0, 0);

        /* Boundary terms for generating numbers according to a uniform distribution */
        
        double minRandomValue = -50.0;
        double maxRandomValue = 50.0;
};