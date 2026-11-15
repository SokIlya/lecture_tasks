#include "inventory.h"
#include "errors.h"

#include <ostream>

Item::Item(const std::string& id, const std::string& name)
    : id(id), name(name) {
  if (id.empty()) {
    throw CommandError("id is empty");
  }

  if (name.empty()) {
    throw CommandError("name is empty");
  }
}

const std::string& Item::inventory_id() const {
  return id;
}

const std::string& Item::get_name() const {
  return name;
}

void Item::describe(std::ostream& out) const {
  out << id << ' ' << name;
}


double InventoryItem::daily_energy() const {
  return 0;
}

bool InventoryItem::suitable_for_novice(int min_novice_score) const {
  return false;
}

std::ostream& operator<<(std::ostream& out, const InventoryItem& item) {
  item.describe(out);
  return out;
}

bool operator<(const InventoryItem& left, const InventoryItem& right) {
  return left.inventory_id() < right.inventory_id();
}

bool operator==(const InventoryItem& left, const InventoryItem& right) {
  return left.inventory_id() == right.inventory_id();
}


Transport::Transport(const std::string& id,
                     const std::string& name,
                     int novice_score)
    : Item(id, name), novice_score(novice_score) {
  if (novice_score < 1 || novice_score > 10) {
    throw CommandError("novice score must be from 1 to 10");
  }
}

bool Transport::suitable_for_novice(int min_novice_score) const {
  return novice_score >= min_novice_score;
}


Bike::Bike(const std::string& id, const std::string& name, int novice_score)
    : Transport(id, name, novice_score) {}


ElectricScooter::ElectricScooter(const std::string& id,
                                 const std::string& name,
                                 double daily_consumption,
                                 int novice_score)
  : Transport(id, name, novice_score), daily_consumption(daily_consumption) {
  if (daily_consumption < 0) {
    throw CommandError("daily consumption must be >= 0");
  }
}

double ElectricScooter::daily_energy() const {
  return daily_consumption;
}


ElectricBike::ElectricBike(const std::string& id,
                           const std::string& name,
                           double daily_consumption,
                           int novice_score)
    : Transport(id, name, novice_score), daily_consumption(daily_consumption) {
  if (daily_consumption < 0) {
    throw CommandError("daily consumption must be >= 0");
  }
}

double ElectricBike::daily_energy() const {
  return daily_consumption;
}


Helmet::Helmet(const std::string& id, const std::string& name)
    : Item(id, name) {}


Dock::Dock(const std::string& id, const std::string& name, double daily_consumption)
    : Item(id, name), daily_consumption(daily_consumption) {
  if (daily_consumption < 0) {
    throw CommandError("daily consumption must be >= 0");
  }
}

double Dock::daily_energy() const {
  return daily_consumption;
}
