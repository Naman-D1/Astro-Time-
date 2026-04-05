#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include <string>

class CelestialBody {
private:
    std::string name;
    double distanceFromEarth; // in million km
    double gravity;           // in m/s²
    std::string description;

public:
    // Constructor
    CelestialBody(std::string name, double distanceFromEarth, double gravity, std::string description);

    // Virtual destructor (important for inheritance!)
    virtual ~CelestialBody() = default;

    // Getters
    std::string getName() const;
    double getDistanceFromEarth() const;
    double getGravity() const;
    std::string getDescription() const;

    // Setters
    void setName(std::string name);
    void setDistanceFromEarth(double distance);
    void setGravity(double gravity);
    void setDescription(std::string description);

    // Pure virtual methods (makes this class abstract)
    virtual std::string getType() const = 0;
    virtual double getHazardLevel() const = 0;

    // Regular virtual method (can be overridden)
    virtual void displayInfo() const;
};

#endif