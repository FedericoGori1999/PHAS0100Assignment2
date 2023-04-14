#include "manyBodySystem.hpp"
#include "particle.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using Catch::Matchers::WithinRel;

/* Testing mass initialisation */

TEST_CASE("Particle sets mass correctly", "[particle]")
{
    Particle p { 3.14 };
    REQUIRE_THAT(p.getMass(), WithinRel(3.14, 0.01));
}

/* Testing motion when the acceleration is 0 (random initial position and
 * velocity) */

TEST_CASE("Motion in case of zero acceleration", "[noAcceleration]")
{
    Particle p(3.14);
    double dt = 0.001;
    double t = 0.0;
    p.setRandomPosition(-50.0, 50.0);
    p.setRandomVelocity(-50.0, 50.0);
    Eigen::Vector3d positionBeforeUpdate = p.getPosition();
    Eigen::Vector3d velocityBeforeUpdate = p.getVelocity();
    while (t < 2 * M_PI) {
        p.update(dt);
        t = t + dt;
    }
    bool comparisonPosition = p.getPosition().isApprox(
        positionBeforeUpdate + velocityBeforeUpdate * t, 0.01);
    bool comparisonVelocity = p.getVelocity().isApprox(velocityBeforeUpdate, 0.01);
    REQUIRE(comparisonPosition);
    REQUIRE(comparisonVelocity);
}

/* Testing motion when the acceleration is constant (random initial position,
 * velocity and acceleration) */

TEST_CASE("Motion in case of constant acceleration", "[constantAcceleration]")
{
    Particle p(3.14);
    double dt = 0.001;
    double t = 0.0;
    p.setRandomPosition(-50.0, 50.0);
    p.setRandomVelocity(-50.0, 50.0);
    p.setRandomAcceleration(-50.0, 50.0);
    Eigen::Vector3d positionBeforeUpdate = p.getPosition();
    Eigen::Vector3d velocityBeforeUpdate = p.getVelocity();
    while (t < 2 * M_PI) {
        p.update(dt);
        t = t + dt;
    }
    bool comparisonPosition = p.getPosition().isApprox(positionBeforeUpdate + velocityBeforeUpdate * t + 0.5 * p.getAcceleration() * t * t,
        0.01);
    bool comparisonVelocity = p.getVelocity().isApprox(
        velocityBeforeUpdate + p.getAcceleration() * t, 0.01);
    REQUIRE(comparisonPosition);
    REQUIRE(comparisonVelocity);
}

/* Testing motion when the acceleration is minus the position after each update
 * (random initial position and velocity) */

TEST_CASE("Motion in case of acceleration equal to minus the position",
    "[oppositeAcceleration]")
{
    Particle p(3.14);
    double dt = 0.001;
    double t = 0.0;
    p.setPosition(Eigen::Vector3d(1, 0, 0));
    p.setVelocity(Eigen::Vector3d(0, 1, 0));
    p.setAcceleration(p.getPosition() * (-1));
    Eigen::Vector3d positionBeforeUpdate = p.getPosition();
    Eigen::Vector3d velocityBeforeUpdate = p.getVelocity();
    while (t < 2 * M_PI) {
        p.update(dt);
        p.setAcceleration(p.getPosition() * (-1));
        t = t + dt;
    }
    bool comparisonPosition = p.getPosition().isApprox(positionBeforeUpdate, 0.01);
    bool comparisonVelocity = p.getVelocity().isApprox(velocityBeforeUpdate, 0.01);
    REQUIRE(comparisonPosition);
    REQUIRE(comparisonVelocity);
}

/* Testing the distance calculator between two particles */

TEST_CASE("Get the distance between two particles", "[distance]")
{
    Particle p1(1);
    Particle p2(1);
    p1.setPosition(Eigen::Vector3d(1, 0, 0));
    p2.setPosition(Eigen::Vector3d(0, 1, 1));
    double d = getDistance(&p1, &p2);
    REQUIRE(d == std::sqrt(3));
}

/* Testing the distance calculator between two particles in the same position */

TEST_CASE("Get the distance between two particles located in the same position",
    "[distanceSamePosition]")
{
    Particle p1(1);
    Particle p2(1);
    p1.setPosition(Eigen::Vector3d(1, 0, 0));
    p2.setPosition(Eigen::Vector3d(1, 0, 0));
    double d = getDistance(&p1, &p2);
    REQUIRE(d == 0);
}

/* Testing calcAcceleration for softeting factor = 0 */

TEST_CASE("Calculate the acceleration of one particle due to the presence of "
          "another one at normal/long distance",
    "[calcAccEps0]")
{
    Particle p1(1);
    Particle p2(2);
    p1.setPosition(Eigen::Vector3d(0, 0, 0));
    p2.setPosition(Eigen::Vector3d(1, 0, 0));
    Eigen::Vector3d accelerationFinal = calcAcceleration(&p1, &p2, 0.0);
    bool accelerationComparison(
        accelerationFinal.isApprox(Eigen::Vector3d(2, 0, 0)));
    REQUIRE(accelerationComparison);
}

/* Testing calcAcceleration for softening factor != 0 */

TEST_CASE("Calculate the acceleration of one particle due to the presence of "
          "another one at short distance",
    "[calcAccEpsNot0]")
{
    Particle p1(1);
    Particle p2(2);
    p1.setPosition(Eigen::Vector3d(0, 0, 0));
    p2.setPosition(Eigen::Vector3d(0.001, 0, 0));
    Eigen::Vector3d accelerationFinal = calcAcceleration(&p1, &p2, 0.1);
    bool accelerationComparison(
        accelerationFinal.isApprox(Eigen::Vector3d(1.9997, 0, 0), 0.01));
    REQUIRE(accelerationComparison);
}

/* Testing calcTotalAcceleration for a system of 3 particles with no spatial
 * symmetry */

TEST_CASE("Calculating total acceleration of one particle",
    "[totalAcceleration]")
{
    Particle p1(1);
    Particle p2(2);
    Particle p3(1);
    p1.setPosition(Eigen::Vector3d(0, 0, 0));
    p2.setPosition(Eigen::Vector3d(2, 0, 0));
    p3.setPosition(Eigen::Vector3d(-1, 0, 0));
    std::vector<Particle> particlesInTheSystem { p1, p2, p3 };
    p1.calcTotalAcceleration(particlesInTheSystem, 0.0);
    bool accelerationComparison(
        p1.getAcceleration().isApprox(Eigen::Vector3d(-0.5, 0, 0), 0.01));
    REQUIRE(accelerationComparison);
}

/* Testing calcTotalAcceleration for a system of 1 particle */

TEST_CASE("Calculating total acceleration of one particle when there is no "
          "other particle",
    "[totalAccelerationOnlyOne]")
{
    Particle p1(1);
    p1.setPosition(Eigen::Vector3d(0, 0, 0));
    std::vector<Particle> particlesInTheSystem { p1 };
    p1.calcTotalAcceleration(particlesInTheSystem, 0.0);
    bool accelerationComparison(
        p1.getAcceleration().isApprox(Eigen::Vector3d(0, 0, 0), 0.01));
    REQUIRE(accelerationComparison);
}

/* Testing calcTotalAcceleration for a system of 3 particles with spatial
 * symmetry */

TEST_CASE("Calculating total acceleration of one particle in case of spatial "
          "symmetry",
    "[totalAccelerationSymmetry]")
{
    Particle p1(1);
    Particle p2(1);
    Particle p3(1);
    p1.setPosition(Eigen::Vector3d(0., 0., 0.));
    p2.setPosition(Eigen::Vector3d(1., 1., 0.));
    p3.setPosition(Eigen::Vector3d(-1., -1., 0.));
    std::vector<Particle> particlesInTheSystem { p1, p2, p3 };
    p1.calcTotalAcceleration(particlesInTheSystem, 0.0);
    bool accelerationComparison(
        p1.getAcceleration().isApprox(Eigen::Vector3d(0., 0., 0.), 0.01));
    REQUIRE(accelerationComparison);
}

/* Unit test of the solarSystemGenerator for the solar system with 8 planets */

TEST_CASE("Testing the initialisation of the solarSystemGenerator for the "
          "solar system with 8 planets",
    "[testingInitialGenerator]")
{
    solarSystemGenerator systemOne;
    systemOne.generateInitialConditions(9);
    std::vector<Particle> solarSystem = systemOne.getSystemInformations();
    REQUIRE(solarSystem.at(0).getMass() == 1.);
    REQUIRE(solarSystem.at(1).getMass() == 1. / 6023600);
    REQUIRE(solarSystem.at(2).getMass() == 1. / 408524);
    REQUIRE(solarSystem.at(3).getMass() == 1. / 332946.038);
    REQUIRE(solarSystem.at(4).getMass() == 1. / 3098710);
    REQUIRE(solarSystem.at(5).getMass() == 1. / 1047.55);
    REQUIRE(solarSystem.at(6).getMass() == 1. / 3499);
    REQUIRE(solarSystem.at(7).getMass() == 1. / 22962);
    REQUIRE(solarSystem.at(8).getMass() == 1. / 19352);
    REQUIRE(systemOne.getNumberOfParticles() == 9);
    REQUIRE(
        solarSystem.at(0).getPosition().isApprox(Eigen::Vector3d(0., 0., 0.)));
    REQUIRE(
        solarSystem.at(0).getVelocity().isApprox(Eigen::Vector3d(0., 0., 0.)));
}

/* Testing the motion of the solar system after a time of 2 * PI, where the
 * Earth should return at the same initial position */

TEST_CASE(
    "Testing the motion of the solar system over an integration time of 2 * PI",
    "[earthReturning]")
{
    double t = 2 * M_PI;
    double dt = 0.0001;
    double epsilon = 0.;
    solarSystemGenerator systemOne;
    systemOne.generateInitialConditions(9);
    std::vector<Particle> systemBeforeEvolution = systemOne.getSystemInformations();
    systemOne.evolutionOfSystem("time", t, dt, epsilon);
    REQUIRE(systemBeforeEvolution.at(3).getPosition().isApprox(
        systemOne.getSystemInformations().at(3).getPosition(), 0.01));
}

TEST_CASE("Simulating one timeStep for one body orbiting around the Sun",
    "[oneBodySimulation]")
{
    Particle sun(1.);
    Particle planet(0.1);
    double dt = 0.1;
    sun.setPosition(Eigen::Vector3d(0., 0., 0.));
    sun.setVelocity(Eigen::Vector3d(0., 0., 0.));
    planet.setPosition(Eigen::Vector3d(1., 0., 0.));
    planet.setVelocity(Eigen::Vector3d(0., 1., 0.));
    std::vector<Particle> system { sun, planet };
    sun.calcTotalAcceleration(system, 0.0);
    planet.calcTotalAcceleration(system, 0.0);
    sun.update(dt);
    planet.update(dt);
    REQUIRE(sun.getPosition().isApprox(Eigen::Vector3d(0., 0., 0.), 0.01));
    REQUIRE(sun.getVelocity().isApprox(Eigen::Vector3d(0.01, 0., 0.), 0.01));
    REQUIRE(planet.getPosition().isApprox(Eigen::Vector3d(1., 0.1, 0.), 0.01));
    REQUIRE(planet.getVelocity().isApprox(Eigen::Vector3d(-0.1, 1., 0.), 0.01));
}

/* Testing the function that calculates the kinetic energy of a particle */

TEST_CASE("Calculate the kinetic energy of a particle", "[kineticParticle]")
{
    Particle p(1);
    p.setVelocity(Eigen::Vector3d(1., 1., 0));
    REQUIRE(p.calculateKineticEnergy() == 1.);
}

/* Testing the function that calculates the potential energy in a system of 3
 * particles */

TEST_CASE("Calculate the potential energy in a system of 3 particles",
    "[potentialParticle]")
{
    Particle p1(1);
    Particle p2(2);
    Particle p3(4);
    p1.setPosition(Eigen::Vector3d(0., 0., 0.));
    p2.setPosition(Eigen::Vector3d(1., 0., 0.));
    p3.setPosition(Eigen::Vector3d(-2., 0., 0.));
    std::vector<Particle> particles { p1, p2, p3 };
    REQUIRE(p1.calculatePotentialEnergy(particles) == -2.);
}

/* Testing the function that calculates the total energy over a system with 2
 * particles */

TEST_CASE("Calculate the total energy of a system of 2 particles",
    "[totalEnergy]")
{
    Particle p1(1);
    Particle p2(2);
    p1.setPosition(Eigen::Vector3d(0., 0., 0.));
    p2.setPosition(Eigen::Vector3d(2., 0., 0.));
    p1.setVelocity(Eigen::Vector3d(1., 1., 0.));
    p2.setVelocity(Eigen::Vector3d(0., 0., 1.));
    std::vector<Particle> particles { p1, p2 };
    REQUIRE(calculateTotalEnergy(particles) == 1.);
}

/* Testing the initialConditionGenerator for a system of N particles */

TEST_CASE("Testing the initialConditionGenerator for a system of N particles",
    "[nPartcilesGenerator]")
{
    nBodySystemGenerator system;
    int N = 1000;
    system.generateInitialConditions(N);
    REQUIRE(system.getSystemInformations().size() == N);
}

/* Testing the correct parsing of the softening factor epsilon */

TEST_CASE("Testing the correct parsing of the softening factor epsilon",
    "[parsingEpsilon]")
{
    nBodySystemGenerator system;
    system.generateInitialConditions(2);
    std::vector<Particle> vectorToSet = system.getSystemInformations();
    vectorToSet.at(0).setMass(1.);
    vectorToSet.at(1).setMass(1.);
    vectorToSet.at(0).setPosition(Eigen::Vector3d(0., 0., 0.));
    vectorToSet.at(1).setPosition(Eigen::Vector3d(1., 0., 0.));
    vectorToSet.at(0).setVelocity(Eigen::Vector3d(0., 0., 0.));
    vectorToSet.at(1).setVelocity(Eigen::Vector3d(0., 0., 0.));
    system.copySystem(&vectorToSet);
    system.evolutionOfSystem("step", 1, 0.1, 0.1);
    REQUIRE(system.getSystemInformations().at(0).getAcceleration().isApprox(
        Eigen::Vector3d(0.985, 0., 0.), 0.01));
}