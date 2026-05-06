#pragma once
#include "datastructs/DynamicArray.h"
#include "entities/Vehicle.h"
#include "utilities/CustomString.h"

class FleetController {
private:
    DynamicArray<Vehicle*> m_vehicles;

    FleetController() = default;

    // Prevent copying — Singleton must never be copied
    FleetController(const FleetController&) = delete;
    FleetController& operator=(const FleetController&) = delete;

    void saveToFile();
    void loadFromFile();

public:
    static FleetController& getInstance();

    // Destructor — deletes all Vehicle* to prevent memory leaks
    ~FleetController() {
        for (int i = 0; i < m_vehicles.size(); i++) {
            delete m_vehicles[i];
            m_vehicles[i] = nullptr;
        }
    }

    void initialize();

    void addVehicle(Vehicle* v);
    Vehicle* getVehicle(int index);
    DynamicArray<Vehicle*>& getAllVehicles();
    void removeVehicle(int index);
    int getVehicleCount() const;

    // Search helpers
    Vehicle* findByRegistration(const CustomString& regNo);
    DynamicArray<Vehicle*> getByCategory(const CustomString& category);

    // Polymorphic helpers — dynamic_cast required (POLY-5)
    void checkRefrigeratedTrucks();
    void applySurge(int vehicleId, double multiplier);
    int  getMetroCarriageCount(int vehicleId);
    int  getScooterBatteryLevel(int vehicleId);
    Vehicle* findById(int id);
};
