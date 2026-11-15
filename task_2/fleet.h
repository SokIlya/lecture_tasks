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
  void print_novice(std::ostream& out, int min_score = 6) const;

  void focus(const std::string& id);
  void show_focus(std::ostream& out) const;

 private:
  Registry<std::shared_ptr<InventoryItem>> items;
  std::weak_ptr<InventoryItem> focused_item;
  InspectionService inspection;
};

void run_commands(Fleet& fleet, std::istream& in, std::ostream& out);
