#include "entities/TransitAsset.h"
TransitAsset::TransitAsset() = default;
TransitAsset::TransitAsset(const CustomString& assetCode, const CustomDate& purchaseDate, double value, const GeoCoordinate& location)
    : m_assetCode(assetCode), m_purchaseDate(purchaseDate), m_purchaseValue(value), m_currentValue(value), m_location(location) {}
double TransitAsset::depreciate(int years) { m_currentValue *= (1.0 - 0.1 * years); if (m_currentValue < 0) m_currentValue = 0; return m_currentValue; }
double TransitAsset::getCurrentValue() const { return m_currentValue; }
void TransitAsset::scheduleMaintenance() { m_status = AssetStatus::UNDER_MAINTENANCE; }
void TransitAsset::decommission() { m_status = AssetStatus::DECOMMISSIONED; }
int TransitAsset::getDaysInService() const { return CustomDate::today() - m_purchaseDate; }
bool TransitAsset::operator<(const TransitAsset& o) const { return m_purchaseValue < o.m_purchaseValue; }
int TransitAsset::operator-(const TransitAsset& o) const { return m_purchaseDate - o.m_purchaseDate; }
CustomString TransitAsset::toString() const { return CustomString("TransitAsset"); }
CustomString TransitAsset::getEntityType() const { return CustomString("TransitAsset"); }
void TransitAsset::serialize(std::ofstream&) const {}
void TransitAsset::deserialize(std::ifstream&) {}
