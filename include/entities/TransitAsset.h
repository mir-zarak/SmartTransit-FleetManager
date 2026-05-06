#pragma once
#include "entities/Entity.h"
#include "utilities/GeoCoordinate.h"

enum class AssetStatus { ACTIVE, UNDER_MAINTENANCE, DECOMMISSIONED };

class TransitAsset : public Entity {
protected:
    CustomString m_assetCode;
    CustomDate m_purchaseDate;
    double m_purchaseValue{};
    double m_currentValue{};
    AssetStatus m_status{AssetStatus::ACTIVE};
    GeoCoordinate m_location;

public:
    TransitAsset();
    TransitAsset(const CustomString& assetCode, const CustomDate& purchaseDate, double value, const GeoCoordinate& location);
    double depreciate(int years);
    double getCurrentValue() const;
    void scheduleMaintenance();
    void decommission();
    int getDaysInService() const;
    bool operator<(const TransitAsset& o) const;
    int operator-(const TransitAsset& o) const;
    CustomString toString() const override;
    CustomString getEntityType() const override;
    void serialize(std::ofstream& out) const override;
    void deserialize(std::ifstream& in) override;
};
