#pragma once
#include <Eigen/Core>
#include <random>

/* See .cpp file for explanation and comments */

class Particle {
    public:
        Particle(double in_mass);
        
        double getMass() const;
        Eigen::Vector3d getPosition();
        Eigen::Vector3d getVelocity();
        Eigen::Vector3d getAcceleration();

        void setRandomPosition(double minRandomValue, double maxRandomValue);
        void setRandomVelocity(double minRandomValue, double maxRandomValue);
        void setRandomAcceleration(double minRandomValue, double maxRandomValue);
        void setPosition(Eigen::Vector3d position);
        void setVelocity(Eigen::Vector3d velocity);
        void setAcceleration(Eigen::Vector3d acceleration);

        void update(double dt);

        void calcTotalAcceleration(std::vector<Particle> particlesInTheSystem, double epsilon);
        double calculateKineticEnergy();
        double calculatePotentialEnergy(std::vector<Particle> particlesInTheSystem);

    private:
        double mass;
        Eigen::Vector3d positionParticle = Eigen::Vector3d(0, 0, 0);
        Eigen::Vector3d velocityParticle = Eigen::Vector3d(0, 0, 0);
        Eigen::Vector3d accelerationParticle = Eigen::Vector3d(0, 0, 0);
};

/* Random generator used for initialisation purposes */

double randomValueGenerator(double minRandomValue, double maxRandomValue);


