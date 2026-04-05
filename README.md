# Space Exploration Simulation

A comprehensive simulation framework for planning interplanetary missions. This project models **celestial bodies**, **spacecraft**, and **missions**, allowing dynamic calculation of travel times, fuel requirements, and risk assessments.  

---

## Overview

This framework provides:

- A **database of celestial destinations** including planets, moons, and space stations.  
- A variety of **spacecraft types** for different mission profiles.  
- A **mission planning system** that calculates travel times, fuel requirements, and risk scores.  
- **Service utilities** for physics calculations and mission briefings.  

---

## Celestial Bodies

### CelestialBody (Abstract)
The base blueprint for every celestial destination.  
**Properties:** `name`, `distanceFromEarth`, `gravity`, `description`  
**Abstract Methods:** `getType()`, `getHazardLevel()`  
> Cannot be instantiated directly.

### Planet
Extends `CelestialBody`.  
**Adds:** `atmosphere`, `atmosphericPressure`  
**Hazard Calculation:** Based on gravity and breathable atmosphere.  
**Preloaded:** Mars, Venus, Jupiter, Mercury

### Moon
Extends `CelestialBody`.  
**Adds:** `parentPlanet`, `hasIce`  
**Hazard:** Generally high due to low gravity and lack of atmosphere.  
**Preloaded:** Luna, Europa, Titan, Io

### SpaceStation
Extends `CelestialBody`.  
**Adds:** `crewCapacity`, `operationalStatus`, `orbitingBody`  
**Hazard:** Non-operational stations are highly hazardous.  
**Preloaded:** ISS, Gateway, Derelict-7

### BodyRegistry
A centralized database of celestial bodies.  
- Preloads known destinations on initialization.  
- Supports case-insensitive lookup via `findByName`.  
- Allows adding custom bodies.

---

## Spacecraft

### Spacecraft (Abstract)
Base blueprint for all ships.  
**Properties:** `name`, `fuelCapacity`, `payloadCapacity`, `crew`  
**Abstract Methods:** `getSpeed()`, `getFuelEfficiency()`, `calculateFuelNeeded()`  
**Behavior:** Ships start with a full fuel tank.

### RocketShip
- Fast but fuel-intensive.  
- Speed and efficiency affected by booster count.  
- Best for short-to-medium range missions.  
- Delta-V budget via Tsiolkovsky rocket equation approximation.

### IonDrive
- Medium speed, highly fuel efficient.  
- Speed depends on thruster power.  
- Suited for long-range deep space missions.  
- High delta-V budget relative to fuel load.

### SolarSailer
- Fuel-free; uses solar radiation pressure.  
- Speed depends on sail area and efficiency.  
- Always feasible but slow.  
- `calculateFuelNeeded()` always returns zero.

---

## Missions

### Mission (Abstract)
Links a `Spacecraft` to a `CelestialBody`.  
**Shared Methods:** `calculateTravelTime()`, `calculateFuelNeeded()`  
**Abstract Methods:** `getMissionType()`, `calculateRiskScore()`, `getMinCrewRequired()`

### CargoMission
- Handles goods transport.  
- Tracks cargo weight and type.  
- Risk increases near payload limits.  
- Minimum crew: 2

### CrewMission
- Handles human transport.  
- Tracks crew count, life support, and duration.  
- Highest risk; lack of life support adds +3.0 risk.  
- Minimum crew: 3

### ResearchMission
- Scientific exploration.  
- Tracks research topics, sample collection, EVA requirements.  
- Risk slightly lower than crew missions; EVA adds danger.  
- Minimum crew: 2

### MissionLog
- Stores planned and completed missions.  
- Supports adding, listing, and filtering missions.  
- Acts as the mission history system.

---

## Services

### NavigationSuite
Static physics engine for mission validation.  
- Calculates feasibility using real orbital mechanics: Hohmann transfer, delta-V, Tsiolkovsky equation.  
- Handles inner planets, outer planets, and deep space differently.

### MissionAnalyst
Static mission briefing generator.  
- Produces propulsion analysis, trajectory evaluation, and risk assessment.  
- Output dynamically adjusts to spacecraft, destination, and mission parameters.

---