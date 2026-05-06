#pragma once
#include "utilities/CustomString.h"
#include "utilities/CustomDate.h"
#include <fstream>

class IReportGenerator {
public:
    virtual ~IReportGenerator() = default;
    virtual CustomString generateReport() = 0;
    virtual bool exportCSV(const CustomString& path) = 0;
    virtual CustomString getTitle() const = 0;
    virtual void getDateRange(CustomDate& from, CustomDate& to) const = 0;
};

class FleetUtilisationReport : public IReportGenerator {
public:
    CustomString generateReport() override {
        return CustomString(
            "=== FLEET UTILISATION REPORT ===\n"
            "Generated: Novaris City Transit Authority\n\n"
            "Vehicle Category    | Count | Avg Occupancy | Status\n"
            "--------------------+-------+---------------+--------\n"
            "CityBus             |    12 |         78.3% | Active\n"
            "MetroTrain          |     4 |         91.2% | Active\n"
            "RideHailCar         |    25 |         62.7% | Active\n"
            "FreightTruck        |     8 |         55.0% | Active\n"
            "ElectricScooter     |    40 |         43.1% | Active\n\n"
            "Total Fleet: 89 vehicles\n"
            "Overall Utilisation: 66.1%\n");
    }
    bool exportCSV(const CustomString& path) override {
        std::ofstream f(path.c_str());
        if (!f.is_open()) return false;
        f << "Category,Count,AvgOccupancy,Status\n"
          << "CityBus,12,78.3,Active\n"
          << "MetroTrain,4,91.2,Active\n"
          << "RideHailCar,25,62.7,Active\n"
          << "FreightTruck,8,55.0,Active\n"
          << "ElectricScooter,40,43.1,Active\n";
        return true;
    }
    CustomString getTitle() const override { return CustomString("Fleet Utilisation"); }
    void getDateRange(CustomDate& from, CustomDate& to) const override {
        from = CustomDate::today(); to = CustomDate::today();
    }
};

class RevenueReport : public IReportGenerator {
public:
    CustomString generateReport() override {
        return CustomString(
            "=== REVENUE REPORT ===\n"
            "Generated: Novaris City Transit Authority\n\n"
            "Service Type        | Tickets | Revenue (PKR)\n"
            "--------------------+---------+--------------\n"
            "Bus (Flat Fare)     |    1840 |    3,864,000\n"
            "Metro (Zone Based)  |    3210 |    9,630,000\n"
            "RideHail (Surge)    |     920 |    7,360,000\n"
            "Freight (Weight)    |      45 |    2,250,000\n"
            "Scooter (Micro)     |     680 |      680,000\n\n"
            "Total Revenue: PKR 23,784,000\n"
            "Collection Rate: 98.3%\n");
    }
    bool exportCSV(const CustomString& path) override {
        std::ofstream f(path.c_str());
        if (!f.is_open()) return false;
        f << "ServiceType,Tickets,Revenue_PKR\n"
          << "Bus,1840,3864000\n"
          << "Metro,3210,9630000\n"
          << "RideHail,920,7360000\n"
          << "Freight,45,2250000\n"
          << "Scooter,680,680000\n";
        return true;
    }
    CustomString getTitle() const override { return CustomString("Revenue"); }
    void getDateRange(CustomDate& from, CustomDate& to) const override {
        from = CustomDate::today(); to = CustomDate::today();
    }
};

class EmissionsReport : public IReportGenerator {
public:
    CustomString generateReport() override {
        return CustomString(
            "=== EMISSIONS REPORT ===\n"
            "Generated: Novaris City Transit Authority\n\n"
            "Vehicle Type        | CO2 (kg/km) | Total km  | Total CO2 (kg)\n"
            "--------------------+-------------+-----------+---------------\n"
            "CityBus (Diesel)    |        1.20 |    12,400 |        14,880\n"
            "CityBus (CNG)       |        0.80 |     8,200 |         6,560\n"
            "MetroTrain          |        0.00 |    45,000 |             0\n"
            "RideHailCar         |        0.21 |    18,300 |         3,843\n"
            "FreightTruck        |        2.80 |     5,100 |        14,280\n"
            "ElectricScooter     |        0.00 |     9,600 |             0\n\n"
            "Total CO2 Saved vs All-Diesel: 48,320 kg\n"
            "Green Fleet %: 61.2%\n");
    }
    bool exportCSV(const CustomString& path) override {
        std::ofstream f(path.c_str());
        if (!f.is_open()) return false;
        f << "VehicleType,CO2_per_km,TotalKm,TotalCO2_kg\n"
          << "CityBus_Diesel,1.20,12400,14880\n"
          << "CityBus_CNG,0.80,8200,6560\n"
          << "MetroTrain,0.00,45000,0\n"
          << "RideHailCar,0.21,18300,3843\n"
          << "FreightTruck,2.80,5100,14280\n"
          << "ElectricScooter,0.00,9600,0\n";
        return true;
    }
    CustomString getTitle() const override { return CustomString("Emissions"); }
    void getDateRange(CustomDate& from, CustomDate& to) const override {
        from = CustomDate::today(); to = CustomDate::today();
    }
};

class IncidentReport : public IReportGenerator {
public:
    CustomString generateReport() override {
        return CustomString(
            "=== INCIDENT REPORT ===\n"
            "Generated: Novaris City Transit Authority\n\n"
            "ID     | Vehicle  | Severity | Status   | Description\n"
            "-------+----------+----------+----------+------------------\n"
            "INC-01 | BUS-003  | HIGH     | Resolved | Engine breakdown\n"
            "INC-02 | TAXI-011 | LOW      | Resolved | Minor collision\n"
            "INC-03 | BUS-007  | MEDIUM   | Open     | GPS signal lost\n"
            "INC-04 | FRT-002  | CRITICAL | Open     | Cargo temp alert\n\n"
            "Total Incidents: 4 | Resolved: 2 | Open: 2\n"
            "MTTF (Mean Time to Fix): 3.2 hours\n");
    }
    bool exportCSV(const CustomString& path) override {
        std::ofstream f(path.c_str());
        if (!f.is_open()) return false;
        f << "IncidentID,Vehicle,Severity,Status,Description\n"
          << "INC-01,BUS-003,HIGH,Resolved,Engine breakdown\n"
          << "INC-02,TAXI-011,LOW,Resolved,Minor collision\n"
          << "INC-03,BUS-007,MEDIUM,Open,GPS signal lost\n"
          << "INC-04,FRT-002,CRITICAL,Open,Cargo temp alert\n";
        return true;
    }
    CustomString getTitle() const override { return CustomString("Incidents"); }
    void getDateRange(CustomDate& from, CustomDate& to) const override {
        from = CustomDate::today(); to = CustomDate::today();
    }
};

class DriverPerformanceReport : public IReportGenerator {
public:
    CustomString generateReport() override {
        return CustomString(
            "=== DRIVER PERFORMANCE REPORT ===\n"
            "Generated: Novaris City Transit Authority\n\n"
            "Driver ID | Name          | Trips | Rating | Incidents | Hrs/Week\n"
            "----------+---------------+-------+--------+-----------+---------\n"
            "DRV-001   | Ahmed Khan    |    42 |    4.9 |         0 |     38.5\n"
            "DRV-002   | Bilal Raza    |    38 |    4.7 |         1 |     36.0\n"
            "DRV-003   | Omar Sheikh   |    45 |    4.8 |         0 |     40.0\n"
            "DRV-004   | Zain Malik    |    31 |    4.5 |         2 |     32.5\n\n"
            "Top Performer: Ahmed Khan (DRV-001)\n"
            "Avg Rating: 4.73 / 5.00\n");
    }
    bool exportCSV(const CustomString& path) override {
        std::ofstream f(path.c_str());
        if (!f.is_open()) return false;
        f << "DriverID,Name,Trips,Rating,Incidents,HrsPerWeek\n"
          << "DRV-001,Ahmed Khan,42,4.9,0,38.5\n"
          << "DRV-002,Bilal Raza,38,4.7,1,36.0\n"
          << "DRV-003,Omar Sheikh,45,4.8,0,40.0\n"
          << "DRV-004,Zain Malik,31,4.5,2,32.5\n";
        return true;
    }
    CustomString getTitle() const override { return CustomString("Driver Performance"); }
    void getDateRange(CustomDate& from, CustomDate& to) const override {
        from = CustomDate::today(); to = CustomDate::today();
    }
};

class RouteEfficiencyReport : public IReportGenerator {
public:
    CustomString generateReport() override {
        return CustomString(
            "=== ROUTE EFFICIENCY REPORT ===\n"
            "Generated: Novaris City Transit Authority\n\n"
            "Route        | Stops | Dist(km) | Avg Delay | Load %\n"
            "-------------+-------+----------+-----------+--------\n"
            "Route A      |     8 |     14.2 |    2.1min |   81.0\n"
            "Route B      |     6 |     10.8 |    4.3min |   67.5\n"
            "Route C      |    10 |     18.5 |    1.8min |   74.2\n"
            "Metro Line 1 |    12 |     22.0 |    0.5min |   92.3\n"
            "Metro Line 2 |     9 |     17.3 |    0.7min |   88.1\n\n"
            "Most Efficient: Metro Line 1\n"
            "Network Avg Delay: 1.88 minutes\n");
    }
    bool exportCSV(const CustomString& path) override {
        std::ofstream f(path.c_str());
        if (!f.is_open()) return false;
        f << "Route,Stops,DistanceKm,AvgDelayMin,LoadPercent\n"
          << "Route A,8,14.2,2.1,81.0\n"
          << "Route B,6,10.8,4.3,67.5\n"
          << "Route C,10,18.5,1.8,74.2\n"
          << "Metro Line 1,12,22.0,0.5,92.3\n"
          << "Metro Line 2,9,17.3,0.7,88.1\n";
        return true;
    }
    CustomString getTitle() const override { return CustomString("Route Efficiency"); }
    void getDateRange(CustomDate& from, CustomDate& to) const override {
        from = CustomDate::today(); to = CustomDate::today();
    }
};
