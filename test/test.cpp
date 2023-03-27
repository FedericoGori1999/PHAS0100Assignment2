#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "particle.hpp"

using Catch::Matchers::WithinRel;

TEST_CASE( "Particle sets mass correctly", "[particle]" ) {
    Particle p{3.14};
    REQUIRE_THAT( p.getMass(), WithinRel(3.14, 0.01) );
}

TEST_CASE("Motion in case of zero acceleration", "[noAcceleration]"){
    Particle p(3.14);
    double dt = 0.001;
    double t = 0.0;
    p.setRandomPosition();
    p.setRandomVelocity();
    Eigen::Vector3d positionBeforeUpdate = p.getPosition();
    Eigen::Vector3d velocityBeforeUpdate = p.getVelocity();
    while(t < 2 * M_PI)
    {
        p.update(dt);
        t = t + dt;
    }
    bool comparisonPosition = p.getPosition().isApprox(positionBeforeUpdate + velocityBeforeUpdate * t, 0.01);
    bool comparisonVelocity = p.getVelocity().isApprox(velocityBeforeUpdate, 0.01);
    REQUIRE(comparisonPosition);
    REQUIRE(comparisonVelocity);
}

TEST_CASE("Motion in case of constant acceleration", "[constantAcceleration]"){
    Particle p(3.14);
    double dt = 0.001;
    double t = 0.0;
    p.setRandomPosition();
    p.setRandomVelocity();
    p.setRandomAcceleration();
    Eigen::Vector3d positionBeforeUpdate = p.getPosition();
    Eigen::Vector3d velocityBeforeUpdate = p.getVelocity();
    while(t < 2 * M_PI)
    {
        p.update(dt);
        t = t + dt;
    }
    bool comparisonPosition = p.getPosition().isApprox(positionBeforeUpdate + velocityBeforeUpdate * t + 0.5 * p.getAcceleration() * t * t, 0.01);
    bool comparisonVelocity = p.getVelocity().isApprox(velocityBeforeUpdate + p.getAcceleration() * t, 0.01);
    REQUIRE(comparisonPosition);
    REQUIRE(comparisonVelocity);
}

TEST_CASE("Motion in case of acceleration equal to minus the position", "[oppositeAcceleration]"){
    Particle p(3.14);
    double dt = 0.001;
    double t = 0.0;
    Eigen::Vector3d positionInit(1, 0, 0);
    Eigen::Vector3d velocityInit(0, 1, 0);
    p.setPosition(positionInit);
    p.setVelocity(velocityInit);
    p.setAcceleration(p.getPosition() * (-1));
    Eigen::Vector3d positionBeforeUpdate = p.getPosition();
    Eigen::Vector3d velocityBeforeUpdate = p.getVelocity();
    while(t < 2 * M_PI)
    {
        p.update(dt);
        p.setAcceleration(p.getPosition() * (-1));
        t = t + dt;
    }
    bool comparisonPosition = p.getPosition().isApprox(positionBeforeUpdate, 0.01);
    bool comparisonVelocity = p.getVelocity().isApprox(velocityBeforeUpdate, 0.01);
    REQUIRE(comparisonPosition);
    REQUIRE(comparisonVelocity);
}
