#pragma once
#include "utilities/CustomString.h"
#include "utilities/CustomDate.h"
#include <fstream>

class Entity {
protected:
    static int s_nextId;
    int m_id;
    CustomDate m_createdOn;
    CustomDate m_updatedOn;

public:
    Entity();
    explicit Entity(int id);
    Entity(const Entity& o);
    virtual ~Entity() = default;

    int getId() const;
    CustomDate getCreatedOn() const;

    virtual CustomString toString() const = 0;
    virtual CustomString getEntityType() const = 0;
    virtual void serialize(std::ofstream& out) const = 0;
    virtual void deserialize(std::ifstream& in) = 0;

    bool operator==(const Entity& o) const;
    bool operator<(const Entity& o) const;
    friend std::ostream& operator<<(std::ostream& os, const Entity& e);
};
