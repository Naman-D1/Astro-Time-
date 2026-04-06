#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <limits>
#include "Models/BodyRegistry.hpp"
#include "Models/IonDrive.hpp"
#include "Models/RocketShip.hpp"
#include "Models/SolarSailor.hpp"
#include "Models/CargoMission.hpp"
#include "Models/CrewMission.hpp"
#include "Models/ResearchMission.hpp"
#include "Models/Spacecraft.hpp"
#include "Services/Navigation_Suite.hpp"
#include "Services/MissionAnalyst.hpp"
#include "Services/MissionValidator.hpp"
#include "Services/ReportExporter.hpp"
#include "Services/SpaceException.hpp"
#include "Services/MissionLog.hpp"
#include "Services/AnimationUtils.hpp"
using namespace std;

using namespace std;

int main() {
    // Force terminal to flush immediately (fixes animation on Windows)
    setvbuf(stdout, NULL, _IONBF, 0);

    MissionLog missionLog;

    try {
        shared_ptr<Mission> myMission;
        BodyRegistry registry;

        cout << "--- SPACE TRAVEL VISUALIZER & PLANNER ---\n";

        AnimationUtils::spinningPlanet("Scanning known star systems");

        registry.listAll();

        // 2. Select destination
        string targetName;
        cout << "\nEnter Destination Name: ";
        cin >> targetName;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        auto destination = registry.findByName(targetName);
        AnimationUtils::spinningPlanet("Locking onto " + targetName);

        // 3. Select ship
        cout << "\nSelect Ship Type:\n";
        cout << "1. Ion Drive\n2. Rocket Ship\n3. Solar Sailer\n";
        cout << "Enter choice (1-3): ";
        int shipChoice;
        if (!(cin >> shipChoice))
            throw InvalidMissionException("Invalid ship selection input.");

        shared_ptr<Spacecraft> myShip;
        if (shipChoice == 1)
            myShip = make_shared<IonDrive>("Odyssey-1", 500.0, 200.0, 6, 8000.0);
        else if (shipChoice == 2)
            myShip = make_shared<RocketShip>("Titan-V", 800.0, 300.0, 4, 3);
        else if (shipChoice == 3)
            myShip = make_shared<SolarSailer>("Helios-1", 150.0, 2, 50000.0, 0.85);
        else
            throw InvalidMissionException("Ship choice must be 1, 2 or 3.");

        AnimationUtils::spinningPlanet("Initialising " + myShip->getName());

        // 4. Select mission type
        cout << "\nSelect Mission Type:\n";
        cout << "1. Cargo Mission\n2. Crew Mission\n3. Research Mission\n";
        cout << "Enter choice (1-3): ";
        int missionChoice;
        if (!(cin >> missionChoice))
            throw InvalidMissionException("Invalid mission type input.");

        if (missionChoice == 1) {
            cout << "Enter cargo weight (tonnes): ";
            double cargoWeight;
            if (!(cin >> cargoWeight) || cargoWeight < 0)
                throw InvalidMissionException("Cargo weight must be a positive number.");
            cout << "Enter cargo type: ";
            string cargoType;
            cin >> cargoType;
            myMission = make_shared<CargoMission>(
                "Cargo Run to " + targetName,
                myShip, destination, cargoWeight, cargoType
            );

        } else if (missionChoice == 2) {
            cout << "Enter crew count: ";
            int crewCount;
            if (!(cin >> crewCount) || crewCount < 1)
                throw InvalidCrewException("Crew count must be at least 1.");
            cout << "Life support? (1 = Yes, 0 = No): ";
            bool lifeSupport;
            cin >> lifeSupport;
            double travelDays = (destination->getDistanceFromEarth() * 1e6)
                                / (myShip->getSpeed() * 86400.0);
            myMission = make_shared<CrewMission>(
                "Crew Mission to " + targetName,
                myShip, destination, crewCount, lifeSupport, (int)travelDays
            );

        } else if (missionChoice == 3) {
            // Clear buffer fully before getline
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter research topic: ";
            string topic;
            getline(cin, topic);

            cout << "Enter sample collection target (at least 1): ";
            int samples;
            // ✅ FIX: blocks 0 and negatives, retries on bad input
            while (!(cin >> samples) || samples <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter a number of at least 1: ";
            }

            cout << "Requires EVA? (1 = Yes, 0 = No): ";
            bool eva;
            cin >> eva;

            double travelDays = (destination->getDistanceFromEarth() * 1e6)
                                / (myShip->getSpeed() * 86400.0);
            myMission = make_shared<ResearchMission>(
                "Research Mission to " + targetName,
                myShip, destination, topic, samples, eva
            );

        } else {
            throw InvalidMissionException("Mission choice must be 1, 2 or 3.");
        }

        AnimationUtils::spinningPlanet("Calculating mission parameters");

        // 5. Validate mission
        ValidationResult validation = MissionValidator::validate(myMission);
        MissionValidator::printValidationReport(validation);
        if (!validation.passed) {
            cout << "\n>> Launch aborted. Fix errors and try again.\n";
            cout << "\nView mission log? (1 = Yes, 0 = No): ";
            int logChoice;
            cin >> logChoice;
            if (logChoice == 1) {
                missionLog.displayAll();
                missionLog.displaySummary();
            }
            return 0;
        }

        // 6. Run physics engine
        cout << "\n[RUNNING PHYSICS SIMULATION...]\n";
        PhysicsValidation report = NavigationSuite::validateMission(myMission);

        AnimationUtils::spinningPlanet("Compiling mission briefing");

        // 7. Print briefing
        MissionAnalyst::printFullBriefing(myMission, report);

        // 8. Flight director analysis
        cout << "\n=== FLIGHT DIRECTOR'S ANALYSIS ===\n";
        if (myShip->getType() == "Ion Drive") {
            cout << "> PROPULSION: Ion Drive selected for high-efficiency deep space transit.\n";
            cout << "  Benefit: Uses 90% less fuel than chemical rockets.\n";
            cout << "  Drawback: Longer travel time.\n";
        } else if (myShip->getType() == "Rocket Ship") {
            cout << "> PROPULSION: Chemical Rocket selected for high-thrust operations.\n";
            cout << "  Benefit: Fastest transit time.\n";
            cout << "  Drawback: High fuel consumption.\n";
        } else if (myShip->getType() == "Solar Sailer") {
            cout << "> PROPULSION: Solar Sail — zero fuel consumption.\n";
            cout << "  Benefit: Unlimited range.\n";
            cout << "  Drawback: Very slow acceleration.\n";
        }

        if (report.canReachDestination)
            cout << "> NAVIGATION: Trajectory stable. Delta-V reserve: "
                      << (myShip->getSpeed() * 1000.0) - report.deltaVRequired << " m/s.\n";
        else
            cout << "> NAVIGATION: WARNING — " << report.flightNotes << "\n";

        double riskScore = myMission->calculateRiskScore();
        if (riskScore < 3.0)
            cout << "> SAFETY: Low risk confirmed.\n";
        else if (riskScore < 6.0)
            cout << "> SAFETY: Moderate risk. Additional precautions recommended.\n";
        else
            cout << "> SAFETY: HIGH RISK. Proceed with extreme caution.\n";

        // 9. Export report
        cout << "\nExport mission report to file? (1 = Yes, 0 = No): ";
        int exportChoice;
        cin >> exportChoice;
        if (exportChoice == 1) {
            string filename = myMission->getMissionName();
            replace(filename.begin(), filename.end(), ' ', '_');
            filename += "_report.txt";
            ReportExporter::exportReport(myMission, report, validation, filename);
        }

        // 10. Log completed mission
        myMission->setStatus("Completed");
        missionLog.addMission(myMission);

    // -------------------------------------------------------
    // CATCH BLOCKS
    // -------------------------------------------------------
    } catch (const DestinationNotFoundException& e) {
        cerr << "\n[ERROR] " << e.what() << "\n";
        cerr << "Tip: Check spelling or run the program again to see available destinations.\n";
        return 1;

    } catch (const InvalidFuelException& e) {
        cerr << "\n[ERROR] " << e.what() << "\n";
        cerr << "Tip: Check spacecraft fuel configuration.\n";
        return 1;

    } catch (const InvalidCrewException& e) {
        cerr << "\n[ERROR] " << e.what() << "\n";
        cerr << "Tip: Ensure crew count is valid for this mission type.\n";
        return 1;

    } catch (const InvalidMissionException& e) {
        cerr << "\n[ERROR] " << e.what() << "\n";
        cerr << "Tip: Review mission parameters and try again.\n";
        return 1;

    } catch (const PhysicsException& e) {
        cerr << "\n[PHYSICS ERROR] " << e.what() << "\n";
        return 1;

    } catch (const SpaceException& e) {
        cerr << "\n[SPACE ERROR] " << e.what() << "\n";
        return 1;

    } catch (const exception& e) {
        cerr << "\n[UNEXPECTED ERROR] " << e.what() << "\n";
        return 1;
    }

    // 11. View mission log
    cout << "\nView mission log? (1 = Yes, 0 = No): ";
    int logChoice;
    cin >> logChoice;
    if (logChoice == 1) {
        missionLog.displayAll();
        missionLog.displaySummary();
    }

    return 0;
}