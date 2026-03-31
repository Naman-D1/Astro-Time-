#include <iostream>
#include <memory>
#include <vector>
#include "models/BodyRegistry.hpp"
#include "models/IonDrive.hpp"
#include "models/RocketShip.hpp"
#include "models/SolarSailor.hpp"
#include "models/CargoMission.hpp"
#include "Services/Navigation_Suite.hpp"
#include "Services/MissionAnalyst.hpp"

using namespace std;

int main() {
    // 1. Initialize our Registry
    BodyRegistry registry;
    
    std::cout << "--- SPACE TRAVEL VISUALIZER & PLANNER ---\n";
    registry.listAll();

    // 2. Select a Destination
    std::string targetName;
    std::cout << "\nEnter Destination Name: ";
    std::cin >> targetName;
    auto destination = registry.findByName(targetName);

    if (!destination) {
        std::cerr << "Target not found in registry!\n";
        return 1;
    }

    // 3. Configure a Ship (Let's use an Ion Drive for this test)
    // Name, Fuel, Payload, Max Crew, Thruster Power
    auto myShip = std::make_shared<IonDrive>("Odyssey-1", 500.0, 200.0, 6, 8000.0);

    // 4. Create a Mission
    auto myMission = std::make_shared<CargoMission>(
        "Supply Run to " + targetName, 
        myShip, 
        destination, 
        150.0, // 150 tonnes of cargo
        "Medical Supplies"
    );

 // 5. RUN THE PHYSICS ENGINE (The "Real World" Check)
std::cout << "\n[RUNNING PHYSICS SIMULATION...]\n";

// Tell the compiler the function lives inside NavigationSuite
PhysicsValidation report = NavigationSuite::validateMission(myMission);

    // 6. Display Results
    /*myMission->displaySummary();
    std::cout << "\n--- PHYSICS ENGINE REPORT ---\n";
    std::cout << "Status        : " << (report.canReachDestination ? "FEASIBLE" : "FAILED") << "\n";
    std::cout << "Delta-V Req   : " << report.deltaVRequired << " m/s\n";
    std::cout << "Flight Notes  : " << report.flightNotes << "\n";
    std::cout << "------------------------------\n";*/
    // After getting the report from NavigationSuite
    MissionAnalyst::printFullBriefing(myMission, report);

    // After the Physics Report in main.cpp
    std::cout << "\n=== FLIGHT DIRECTOR'S ANALYSIS ===\n";

    if (myShip->getType() == "Ion Drive") {
     std::cout << "> PROPULSION: Ion Drive selected for high-efficiency deep space transit.\n";
     std::cout << "  Benefit: Uses 90% less fuel than chemical rockets for this trajectory.\n";
     std::cout << "  Drawback: Longer travel time compared to traditional rockets.\n";}

    if (report.deltaVRequired < (myShip->getSpeed() * 1000.0)) {
     std::cout << "> NAVIGATION: Trajectory is stable. We have " 
              << (myShip->getSpeed() * 1000.0) - report.deltaVRequired 
              << " m/s of fuel reserve for emergencies.\n";
    }

    if (myMission->calculateRiskScore() < 3.0) {
        std::cout << "> SAFETY: Low risk confirmed. Payload is secure and destination is stable.\n";
    }

    return 0;
}