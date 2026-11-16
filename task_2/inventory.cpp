#include "inventory.h"

#include <ostream>

#include "errors.h"

double InventoryItem::energy_per_minute() const { return 0; }

bool InventoryItem::suitable_for_novice(int min_novice_score) const {
  return false;
}

bool InventoryItem::is_available() const { return available; }

void InventoryItem::offer_item(int age, int minutes) {
  if (age <= 0) {
    throw OfferItemError("age must be > 0");
  }

  if (minutes <= 0) {
    throw OfferItemError("minutes must be > 0");
  }
}

void InventoryItem::take() { available = false; }

void InventoryItem::release() { available = true; }

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

Item::Item(const std::string& id, const std::string& name)
    : id(id), name(name) {
  if (id.empty()) {
    throw CommandError("id is empty");
  }

  if (name.empty()) {
    throw CommandError("name is empty");
  }
}

const std::string& Item::inventory_id() const { return id; }

const std::string& Item::get_name() const { return name; }

void Item::describe(std::ostream& out) const { out << id << ' ' << name; }

Transport::Transport(const std::string& id, const std::string& name,
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

double Bike::offer_ride(int age, int minutes) {
  if (age < age_required) {
    throw OfferRideError("you can rent a bike from " +
                         std::to_string(age_required) + " years old");
  }

  if (minutes <= 0) {
    throw OfferRideError("minutes must be > 0");
  }

  return cost_per_minute * minutes;
}

SurreyBike::SurreyBike(const std::string& id, const std::string& name,
                       int novice_score)
    : Transport(id, name, novice_score) {}

double SurreyBike::offer_ride(int age, int minutes) {
  if (age < age_required) {
    throw OfferRideError("you can rent a surrey bike from " +
                         std::to_string(age_required) + " years old");
  }

  if (minutes <= 0) {
    throw OfferRideError("minutes must be > 0");
  }

  return cost_per_minute * minutes;
}

ElectricScooter::ElectricScooter(const std::string& id, const std::string& name,
                                 double consumption_per_minute,
                                 int novice_score, double accumulator_capacity)
    : Transport(id, name, novice_score),
      consumption_per_minute(consumption_per_minute),
      accumulator_capacity(accumulator_capacity) {
  if (consumption_per_minute <= 0) {
    throw CommandError("consumption per minute must be > 0");
  }

  if (accumulator_capacity <= 0) {
    throw CommandError("accumulator capacity must be > 0");
  }
}

double ElectricScooter::get_charge_level() const { return charge_level; }

double ElectricScooter::energy_per_minute() const {
  return consumption_per_minute;
}

void ElectricScooter::charge() { charge_level = accumulator_capacity; }

double ElectricScooter::offer_ride(int age, int minutes) {
  if (age < age_required) {
    throw OfferRideError("you can rent an electric scooter from " +
                         std::to_string(age_required) + " years old");
  }

  if (minutes <= 0) {
    throw OfferRideError("minutes must be > 0");
  }

  double energy_needed = energy_per_minute() * minutes;

  if (charge_level < energy_needed) {
    throw OfferRideError("not enough charge");
  }

  charge_level -= energy_needed;

  return cost_per_minute * minutes;
}

ElectricBike::ElectricBike(const std::string& id, const std::string& name,
                           double consumption_per_minute, int novice_score,
                           double accumulator_capacity)
    : Transport(id, name, novice_score),
      consumption_per_minute(consumption_per_minute),
      accumulator_capacity(accumulator_capacity) {
  if (consumption_per_minute <= 0) {
    throw CommandError("consumption per minute must be > 0");
  }

  if (accumulator_capacity <= 0) {
    throw CommandError("accumulator capacity must be > 0");
  }
}

double ElectricBike::get_charge_level() const { return charge_level; }

double ElectricBike::energy_per_minute() const {
  return consumption_per_minute;
}

void ElectricBike::charge() { charge_level = accumulator_capacity; }

double ElectricBike::offer_ride(int age, int minutes) {
  if (age < age_required) {
    throw OfferRideError("you can rent an electric bike from " +
                         std::to_string(age_required) + " years old");
  }

  if (minutes <= 0) {
    throw OfferRideError("minutes must be > 0");
  }

  double energy_needed = energy_per_minute() * minutes;

  if (charge_level < energy_needed) {
    throw OfferRideError("not enough charge");
  }

  charge_level -= energy_needed;

  return cost_per_minute * minutes;
}

Helmet::Helmet(const std::string& id, const std::string& name)
    : Item(id, name) {}

void Helmet::offer_item(int age, int minutes) {
  if (age <= 0) {
    throw OfferItemError("age must be > 0");
  }

  if (minutes <= 0) {
    throw OfferItemError("minutes must be > 0");
  }
}

Dock::Dock(const std::string& id, const std::string& name,
           double consumption_per_minute, double accumulator_capacity)
    : Item(id, name),
      consumption_per_minute(consumption_per_minute),
      accumulator_capacity(accumulator_capacity) {
  if (consumption_per_minute <= 0) {
    throw CommandError("consumption per minute must be > 0");
  }

  if (accumulator_capacity <= 0) {
    throw CommandError("accumulator capacity must be > 0");
  }
}

double Dock::energy_per_minute() const { return consumption_per_minute; }

double Dock::get_charge_level() const { return charge_level; }

void Dock::charge() { charge_level = accumulator_capacity; }

void Dock::offer_item(int age, int minutes) {
  if (age <= 0) {
    throw OfferItemError("age must be > 0");
  }

  if (minutes <= 0) {
    throw OfferItemError("minutes must be > 0");
  }
}
