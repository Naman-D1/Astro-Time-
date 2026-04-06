#ifndef CARGOMISSION_H
#define CARGOMISSION_H
using namespace std;

#include "Mission.hpp"

class CargoMission : public Mission {
private:
    double cargoWeightTonnes;
    string cargoType; // e.g. "Supplies", "Equipment", "Fuel"

public:
    CargoMission(string missionName,
                 shared_ptr<Spacecraft> spacecraft,
                 shared_ptr<CelestialBody> destination,
                 double cargoWeightTonnes,
                 string cargoType);

    // Getters
    double      getCargoWeight() const;
    string getCargoType() const;

    // Setters
    void setCargoWeight(double weight);
    void setCargoType(string type);

    // Overrides
    string getMissionType() const override;
    double      calculateRiskScore() const override;
    int         getMinCrewRequired() const override;

    void displaySummary() const override;
};

#endif