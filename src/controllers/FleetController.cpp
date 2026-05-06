#include "controllers/FleetController.h"
#include "entities/CityBus.h"
#include <fstream>

FleetController& FleetController::getInstance() {
    static FleetController instance;
    return instance;
}

void FleetController::initialize() {
    loadFromFile();
}

void FleetController::addVehicle(Vehicle* v) {
    if (v) {
        m_vehicles.append(v);
        saveToFile();
    }
}

DynamicArray<Vehicle*>& FleetController::getAllVehicles() {
    return m_vehicles;
}

void FleetController::removeVehicle(int index) {
    if (index >= 0 && index < m_vehicles.size()) {
        delete m_vehicles[index];
        m_vehicles.remove(index);
        saveToFile();
    }
}

// 🔥 SAVE
void FleetController::saveToFile() {
    std::ofstream file("fleet.txt");

    for (int i = 0; i < m_vehicles.size(); i++) {
        Vehicle* v = m_vehicles[i];
        if (!v) continue;

        file << v->getPassengerCapacity() << "\n";
    }

    file.close();
}

// 🔥 LOAD
void FleetController::loadFromFile() {
    std::ifstream file("fleet.txt");

    if (!file.is_open()) return;

    int capacity;
    while (file >> capacity) {
        auto* bus = new CityBus();
        bus->setPassengerCapacity(capacity);
        m_vehicles.append(bus);
    }

    file.close();
}
// --- BUG 6 FIX: 4 dynamic_cast locations required by POLY-5 ---
#include "entities/RefrigeratedTruck.h"
#include "entities/RideHailCar.h"
#include "entities/MetroTrain.h"
#include "entities/ElectricScooter.h"
#include "exceptions/TransitExceptions.h"

Vehicle* FleetController::findById(int id) {
    for (int i = 0; i < m_vehicles.size(); i++)
        if (m_vehicles[i] && m_vehicles[i]->getId() == id)
            return m_vehicles[i];
    return nullptr;
}

Vehicle* FleetController::findByRegistration(const CustomString& regNo) {
    for (int i = 0; i < m_vehicles.size(); i++)
        if (m_vehicles[i] && m_vehicles[i]->getEntityType() == regNo)
            return m_vehicles[i];
    return nullptr;
}

int FleetController::getVehicleCount() const { return m_vehicles.size(); }

Vehicle* FleetController::getVehicle(int index) {
    if (index >= 0 && index < m_vehicles.size()) return m_vehicles[index];
    return nullptr;
}

DynamicArray<Vehicle*> FleetController::getByCategory(const CustomString& category) {
    DynamicArray<Vehicle*> result;
    for (int i = 0; i < m_vehicles.size(); i++)
        if (m_vehicles[i] && m_vehicles[i]->getVehicleCategory() == category)
            result.append(m_vehicles[i]);
    return result;
}

// dynamic_cast location 1: RefrigeratedTruck temperature alert
void FleetController::checkRefrigeratedTrucks() {
    for (int i = 0; i < m_vehicles.size(); i++) {
        try {
            auto* rt = dynamic_cast<RefrigeratedTruck*>(m_vehicles[i]);
            if (rt) rt->checkTempAlert();
        } catch (const CargoCriticalException&) {
            // alert would be dispatched via INotifiable in production
        }
    }
}

// dynamic_cast location 2: RideHailCar surge multiplier (reference cast)
void FleetController::applySurge(int vehicleId, double multiplier) {
    Vehicle* v = findById(vehicleId);
    if (!v) throw VehicleNotFoundException(
        CustomString("Vehicle not found"), CustomString("FleetController"), 2001);
    try {
        RideHailCar& car = dynamic_cast<RideHailCar&>(*v);
        car.setSurgeMultiplier(multiplier);
    } catch (const std::bad_cast&) {
        throw VehicleNotFoundException(
            CustomString("Not a RideHailCar"), CustomString("FleetController"), 2002);
    }
}

// dynamic_cast location 3: MetroTrain carriage count
int FleetController::getMetroCarriageCount(int vehicleId) {
    Vehicle* v = findById(vehicleId);
    if (!v) throw VehicleNotFoundException(
        CustomString("Vehicle not found"), CustomString("FleetController"), 2003);
    auto* metro = dynamic_cast<MetroTrain*>(v);
    if (!metro) throw VehicleNotFoundException(
        CustomString("Not a MetroTrain"), CustomString("FleetController"), 2004);
    return metro->getCarriageCount();
}

// dynamic_cast location 4: ElectricScooter battery level
int FleetController::getScooterBatteryLevel(int vehicleId) {
    Vehicle* v = findById(vehicleId);
    if (!v) throw VehicleNotFoundException(
        CustomString("Vehicle not found"), CustomString("FleetController"), 2005);
    auto* scooter = dynamic_cast<ElectricScooter*>(v);
    if (!scooter) throw VehicleNotFoundException(
        CustomString("Not an ElectricScooter"), CustomString("FleetController"), 2006);
    return scooter->getBatteryLevelPercent();
}
