#ifndef CARGOMISSION_H
#define CARGOMISSION_H

#include "Mission.hpp"

class CargoMission : public Mission {
private:
    double cargoWeightTonnes;
    std::string cargoType; // e.g. "Supplies", "Equipment", "Fuel"

public:
    CargoMission(std::string missionName,
                 std::shared_ptr<Spacecraft> spacecraft,
                 std::shared_ptr<CelestialBody> destination,
                 double cargoWeightTonnes,
                 std::string cargoType);

    // Getters
    double      getCargoWeight() const;
    std::string getCargoType() const;

    // Setters
    void setCargoWeight(double weight);
    void setCargoType(std::string type);

    // Overrides
    std::string getMissionType() const override;
    double      calculateRiskScore() const override;
    int         getMinCrewRequired() const override;

    void displaySummary() const override;
};

#endif