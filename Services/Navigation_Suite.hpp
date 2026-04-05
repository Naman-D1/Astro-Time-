#ifndef NAVIGATION_SUITE_HPP
#define NAVIGATION_SUITE_HPP

#include "Mission.hpp"
#include <cmath>
#include <vector>

struct PhysicsValidation {
    bool canReachDestination;
    double deltaVRequired;   // Change in velocity needed (m/s)
    double travelTimeSeconds;
    double captureBurn;      // Fuel needed to slow down at arrival
    std::string flightNotes;
};

class NavigationSuite {
public:
    static constexpr double G = 6.67430e-11;
    static constexpr double MU_SUN = 1.327e20; // Standard gravitational parameter

    // The main entry point for "Real Physics"
    static PhysicsValidation validateMission(const std::shared_ptr<Mission>& mission);

private:
    // Calculates Hohmann Transfer delta-v
    static double calculateTransferDeltaV(double r1, double r2);
};

#endif