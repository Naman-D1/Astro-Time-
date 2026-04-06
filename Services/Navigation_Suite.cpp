#include "Navigation_Suite.hpp"
#include "../Models/SolarSailor.hpp"
#include "../Models/RocketShip.hpp"
#include "../Models/IonDrive.hpp"
#include <iostream>
#include <cmath>

PhysicsValidation NavigationSuite::validateMission(const std::shared_ptr<Mission>& mission) {
    PhysicsValidation report;
    auto ship   = mission->getSpacecraft();
    auto target = mission->getDestination();

    double distanceMillionKm = target->getDistanceFromEarth();

    // -------------------------------------------------------
    // 1. DELTA-V CALCULATION
    //    Use proper AU-based distances for orbital mechanics
    // -------------------------------------------------------
    double r_earth  = 1.496e11; // Earth orbit radius in meters (1 AU)
    double r_target = r_earth + (distanceMillionKm * 1e9); // add destination offset

    // For destinations very close to Earth (Moon, ISS),
    // use a fixed realistic delta-v instead of Hohmann formula
    if (distanceMillionKm < 1.0) {
        // Close Earth orbit / lunar transfer
        report.deltaVRequired = 3200.0 + (distanceMillionKm * 1000.0); // m/s
    } else {
        report.deltaVRequired = calculateTransferDeltaV(r_earth, r_target);
    }

    // -------------------------------------------------------
    // 2. SHIP CAPABILITY CHECK
    //    Each ship type has a realistic delta-v budget
    // -------------------------------------------------------
    double shipDeltaVBudget = 0.0;

    if (std::dynamic_pointer_cast<SolarSailer>(ship)) {
        // Solar sailers have unlimited range but are very slow
        report.canReachDestination = true;
        report.flightNotes = "Propelled by radiation pressure. Continuous low acceleration.";
        report.deltaVRequired = 0.0; // not applicable
        return report;

    } else if (std::dynamic_pointer_cast<RocketShip>(ship)) {
        // Rockets have high thrust but burn fuel fast
        // Delta-v budget based on fuel capacity (Tsiolkovsky rocket equation approximation)
        double massRatio = 1.0 + (ship->getMaxFuelCapacity() / 50.0);
        shipDeltaVBudget = 4500.0 * std::log(massRatio); // m/s

    } else if (std::dynamic_pointer_cast<IonDrive>(ship)) {
        // Ion drives are very efficient — much higher delta-v budget
        double massRatio = 1.0 + (ship->getMaxFuelCapacity() / 5.0);
        shipDeltaVBudget = 30000.0 * std::log(massRatio); // m/s
    }

    // -------------------------------------------------------
    // 3. FEASIBILITY CHECK
    // -------------------------------------------------------
    if (shipDeltaVBudget >= report.deltaVRequired) {
        report.canReachDestination = true;
        double reserve = shipDeltaVBudget - report.deltaVRequired;

        if (reserve > 5000.0)
            report.flightNotes = "Trajectory nominal. Excellent delta-v reserve.";
        else if (reserve > 1000.0)
            report.flightNotes = "Trajectory nominal. Adequate delta-v reserve.";
        else
            report.flightNotes = "Trajectory feasible but delta-v margins are tight.";

    } else {
        report.canReachDestination = false;
        report.flightNotes = "INSUFFICIENT DELTA-V: Ship cannot reach this destination.";
    }

    return report;
}

double NavigationSuite::calculateTransferDeltaV(double r1, double r2) {
    double v1      = std::sqrt(MU_SUN / r1);
    double v_trans = std::sqrt(MU_SUN / r1) * std::sqrt((2.0 * r2) / (r1 + r2));
    return std::abs(v_trans - v1);
}