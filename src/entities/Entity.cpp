#include "entities/Entity.h"
int Entity::s_nextId = 1;
Entity::Entity() : m_id(s_nextId++), m_createdOn(CustomDate::today()), m_updatedOn(CustomDate::today()) {}
Entity::Entity(int id) : m_id(id), m_createdOn(CustomDate::today()), m_updatedOn(CustomDate::today()) {}
Entity::Entity(const Entity& o) : m_id(o.m_id), m_createdOn(o.m_createdOn), m_updatedOn(o.m_updatedOn) {}
int Entity::getId() const { return m_id; }
CustomDate Entity::getCreatedOn() const { return m_createdOn; }
bool Entity::operator==(const Entity& o) const { return m_id == o.m_id; }
bool Entity::operator<(const Entity& o) const { return m_id < o.m_id; }
std::ostream& operator<<(std::ostream& os, const Entity& e){ return os << e.toString(); }
