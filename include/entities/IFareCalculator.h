#pragma once
#include <algorithm>
#include <cstdio>
#include "utilities/CustomString.h"
class IFareCalculator {
public:
    virtual ~IFareCalculator() = default;
    virtual double calculateFare(double distanceKm, int passengerCount, bool isPeakHour) const = 0;
    virtual double applyDiscount(double baseFare, int loyaltyPoints) const = 0;
    virtual CustomString getFareType() const = 0;
    virtual double getMinimumFare() const = 0;
    virtual CustomString generateReceipt(double fare, const CustomString& tripId) const = 0;
};

class FlatFareBus : public IFareCalculator {
public:
    double calculateFare(double d,int p,bool peak) const override { return std::max(20.0, d * 3.0 + (peak ? 10.0 : 0.0)); }
    double applyDiscount(double baseFare,int loyaltyPoints) const override { return baseFare * (1.0 - std::min(loyaltyPoints, 20) / 100.0); }
    CustomString getFareType() const override { return CustomString("FlatFareBus"); }
    double getMinimumFare() const override { return 20.0; }
    CustomString generateReceipt(double fare, const CustomString& tripId) const override {
        char buf[32]; std::snprintf(buf, sizeof(buf), "%.2f", fare);
        return CustomString("Receipt:") + tripId + CustomString(" Fare=PKR ") + CustomString(buf);
    }
};
class ZoneBasedMetro : public IFareCalculator {
public:
    double calculateFare(double d,int p,bool peak) const override { return std::max(30.0, d * 4.0 + (peak ? 5.0 : 0.0)); }
    double applyDiscount(double baseFare,int loyaltyPoints) const override { return baseFare * 0.9; }
    CustomString getFareType() const override { return CustomString("ZoneBasedMetro"); }
    double getMinimumFare() const override { return 30.0; }
    CustomString generateReceipt(double fare, const CustomString& tripId) const override {
        char buf[32]; std::snprintf(buf, sizeof(buf), "%.2f", fare);
        return CustomString("MetroReceipt:") + tripId + CustomString(" Fare=PKR ") + CustomString(buf);
    }
};
class SurgeRideHail : public IFareCalculator {
public:
    double calculateFare(double d,int p,bool peak) const override { return d * 8.0 * (peak ? 1.5 : 1.0); }
    double applyDiscount(double baseFare,int loyaltyPoints) const override { return baseFare * (1.0 - loyaltyPoints/200.0); }
    CustomString getFareType() const override { return CustomString("SurgeRideHail"); }
    double getMinimumFare() const override { return 50.0; }
    CustomString generateReceipt(double fare, const CustomString& tripId) const override {
        char buf[32]; std::snprintf(buf, sizeof(buf), "%.2f", fare);
        return CustomString("RideHailReceipt:") + tripId + CustomString(" Fare=PKR ") + CustomString(buf);
    }
};
class WeightFreight : public IFareCalculator {
public:
    double calculateFare(double d,int p,bool peak) const override { return d * 15.0; }
    double applyDiscount(double baseFare,int loyaltyPoints) const override { return baseFare; }
    CustomString getFareType() const override { return CustomString("WeightFreight"); }
    double getMinimumFare() const override { return 100.0; }
    CustomString generateReceipt(double fare, const CustomString& tripId) const override {
        char buf[32]; std::snprintf(buf, sizeof(buf), "%.2f", fare);
        return CustomString("FreightReceipt:") + tripId + CustomString(" Fare=PKR ") + CustomString(buf);
    }
};
class MicroMobility : public IFareCalculator {
public:
    double calculateFare(double d,int p,bool peak) const override { return std::max(10.0, d * 2.0); }
    double applyDiscount(double baseFare,int loyaltyPoints) const override { return baseFare * 0.95; }
    CustomString getFareType() const override { return CustomString("MicroMobility"); }
    double getMinimumFare() const override { return 10.0; }
    CustomString generateReceipt(double fare, const CustomString& tripId) const override {
        char buf[32]; std::snprintf(buf, sizeof(buf), "%.2f", fare);
        return CustomString("MicroReceipt:") + tripId + CustomString(" Fare=PKR ") + CustomString(buf);
    }
};
