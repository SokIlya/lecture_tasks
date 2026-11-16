#include "fleet.h"

#include <algorithm>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "errors.h"
#include "registry.h"

void InspectionService::inspect(const Transport& transport) const {
  std::string name = transport.get_name();

  std::string broken_word = "broken";
  int idx = 0;

  for (char c : name) {
    if (c == broken_word[idx] || 'a' + c - 'A' == broken_word[idx]) {
      ++idx;
    } else {
      if (c == 'b' || c == 'B') {
        idx = 1;
      } else {
        idx = 0;
      }
    }

    if (idx == static_cast<int>(broken_word.size())) {
      throw InspectionRejected();
    }
  }
}

void Fleet::add(std::unique_ptr<InventoryItem> item) {
  Transport* transport = dynamic_cast<Transport*>(item.get());

  if (transport != nullptr) {
    inspection.inspect(*transport);
  }

  std::shared_ptr<InventoryItem> accepted_item(std::move(item));
  items.add(std::move(accepted_item));
}

void Fleet::remove(const std::string& id) {
  int items_size = static_cast<int>(size());

  for (int i = 0; i < items_size; ++i) {
    if (items[i]->inventory_id() == id) {
      items.remove(i);
      return;
    }
  }

  throw CommandError("id not found");
}

std::size_t Fleet::size() const { return items.size(); }

double Fleet::total_energy() const {
  int items_size = static_cast<int>(size());
  double total = 0.0;

  for (int i = 0; i < items_size; ++i) {
    total += items[i]->energy_per_minute();
  }

  return total;
}

bool compare_items(const std::shared_ptr<InventoryItem>& a,
                   const std::shared_ptr<InventoryItem>& b) {
  return *a < *b;
}

void Fleet::print_list(std::ostream& out) const {
  int items_size = static_cast<int>(size());

  std::vector<std::shared_ptr<InventoryItem>> sorted_items(items_size);

  for (int i = 0; i < items_size; ++i) {
    sorted_items[i] = items[i];
  }

  std::sort(sorted_items.begin(), sorted_items.end(), compare_items);

  for (int i = 0; i < items_size; ++i) {
    out << *sorted_items[i] << '\n';
  }
}

void Fleet::print_novice(std::ostream& out, int min_novice_score) const {
  for (int i = 0; i < static_cast<int>(size()); ++i) {
    if (items[i]->suitable_for_novice(min_novice_score)) {
      out << *items[i] << '\n';
    }
  }
}

void Fleet::print_charge(std::ostream& out) const {
  for (int i = 0; i < static_cast<int>(size()); ++i) {
    auto consumer = std::dynamic_pointer_cast<EnergyConsumer>(items[i]);

    if (consumer) {
      out << *items[i] << ' ' << consumer->get_charge_level() << '\n';
    }
  }
}

void Fleet::charge_item(const std::string& id) {
  for (int i = 0; i < static_cast<int>(size()); ++i) {
    if (items[i]->inventory_id() != id) {
      continue;
    }

    auto consumer = std::dynamic_pointer_cast<EnergyConsumer>(items[i]);

    if (!consumer) {
      throw CommandError("this item have no accumulator");
    }

    consumer->charge();

    return;
  }

  throw GetItemError("id not found");
}

void Fleet::focus(const std::string& id) {
  int items_size = static_cast<int>(size());

  for (int i = 0; i < items_size; ++i) {
    if (items[i]->inventory_id() == id) {
      focused_item = items[i];
      return;
    }
  }

  throw CommandError("id not found");
}

void Fleet::show_focus(std::ostream& out) const {
  if (focused_item.expired()) {
    out << "expired\n";
  } else {
    std::shared_ptr<InventoryItem> item = focused_item.lock();
    out << *item << '\n';
  }
}

double Fleet::rent_item(const std::string& id, int age, int minutes) {
  for (int i = 0; i < static_cast<int>(size()); ++i) {
    if (items[i]->inventory_id() != id) {
      continue;
    }

    auto item = items[i];

    if (!item->is_available()) {
      throw GetItemError("item is not available");
    }

    auto transport = std::dynamic_pointer_cast<Transport>(item);
    double cost = 0;

    if (transport) {
      cost = transport->offer_ride(age, minutes);
    } else {
      item->offer_item(age, minutes);
    }

    item->take();

    return cost;
  }

  throw GetItemError("id not found");
}

void Fleet::release_item(const std::string& id) {
  for (int i = 0; i < static_cast<int>(size()); ++i) {
    if (items[i]->inventory_id() == id) {
      items[i]->release();
      return;
    }
  }

  throw GetItemError("id not found");
}
