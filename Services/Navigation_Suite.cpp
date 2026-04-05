#include "Navigation_Suite.hpp"
#include "../models/SolarSailor.hpp"
#include <iostream>

PhysicsValidation NavigationSuite::validateMission(const std::shared_ptr<Mission>& mission) {
    PhysicsValidation report;
    auto ship = mission->getSpacecraft();
    auto target = mission->getDestination();

    // 1. Convert distances (Your models use Million KM, Physics needs Meters)
    double r_earth = 1.496e11; // 1 AU
    double r_target = r_earth + (target->getDistanceFromEarth() * 1e9);

    // 2. Delta-V Calculation (Real-world requirement)
    report.deltaVRequired = calculateTransferDeltaV(r_earth, r_target);

    // 3. Capability Check
    // We convert your 'Speed' (km/s) into a Delta-V capability
    double shipDeltaV = ship->getSpeed() * 1000.0; 

    // 4. Special Case: Solar Sailers
    if (std::dynamic_pointer_cast<SolarSailer>(ship)) {
        report.canReachDestination = true; // Sunlight is infinite!
        report.flightNotes = "Propelled by radiation pressure. Constant acceleration.";
    } else {
        // Rocket/Ion logic: Do we have enough 'oomph'?
        if (shipDeltaV >= report.deltaVRequired) {
            report.canReachDestination = true;
            report.flightNotes = "Trajectory is nominal.";
        } else {
            report.canReachDestination = false;
            report.flightNotes = "INSUFFICIENT DELTA-V: Ship cannot break Earth orbit.";
        }
    }

    return report;
}

double NavigationSuite::calculateTransferDeltaV(double r1, double r2) {
    // Velocity of start orbit (Earth)
    double v1 = std::sqrt(MU_SUN / r1);
    // Velocity needed at perihelion of transfer orbit
    double v_trans = std::sqrt(MU_SUN / r1) * std::sqrt((2 * r2) / (r1 + r2));
    
    return std::abs(v_trans - v1);
}
