#pragma once

#include <cstddef>
#include <iosfwd>
#include <memory>
#include <string>

#include "inventory.h"
#include "registry.h"

class InspectionService {
 public:
  void inspect(const Transport& transport) const;
};

class Fleet {
 public:
  void add(std::unique_ptr<InventoryItem> item);
  void remove(const std::string& id);

  std::size_t size() const;
  double total_energy() const;
  void print_list(std::ostream& out) const;
  void print_novice(std::ostream& out, int min_novice_score = 6) const;
  void print_charge(std::ostream& out) const;
  void charge_item(const std::string& id);

  void focus(const std::string& id);
  void show_focus(std::ostream& out) const;

  double rent_item(const std::string& id, int age, int minutes);
  void release_item(const std::string& id);

 private:
  Registry<std::shared_ptr<InventoryItem>> items;
  std::weak_ptr<InventoryItem> focused_item;
  InspectionService inspection;
};
