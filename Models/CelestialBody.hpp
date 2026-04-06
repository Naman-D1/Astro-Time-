#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H
using namespace std;

#include <string>

class CelestialBody {
private:
    string name;
    double distanceFromEarth; // in million km
    double gravity;           // in m/s²
    string description;

public:
    // Constructor
    CelestialBody(string name, double distanceFromEarth, double gravity, string description);

    // Virtual destructor (important for inheritance!)
    virtual ~CelestialBody() = default;

    // Getters
    string getName() const;
    double getDistanceFromEarth() const;
    double getGravity() const;
    string getDescription() const;

    // Setters
    void setName(string name);
    void setDistanceFromEarth(double distance);
    void setGravity(double gravity);
    void setDescription(string description);

    // Pure virtual methods (makes this class abstract)
    virtual string getType() const = 0;
    virtual double getHazardLevel() const = 0;

    // Regular virtual method (can be overridden)
    virtual void displayInfo() const;
};

#endif