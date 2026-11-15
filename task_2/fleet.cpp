#include "fleet.h"
#include "errors.h"
#include "registry.h"

#include <algorithm>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

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
    int items_size = static_cast<int>(items.size());

    for (int i = 0; i < items_size; ++i) {
        if (items[i]->inventory_id() == id) {
            items.remove(i);
            return;
        }
    }

    throw CommandError("id not found");
}

std::size_t Fleet::size() const {
    return items.size();
}

double Fleet::total_energy() const {
    int items_size = static_cast<int>(items.size());
    double total = 0.0;

    for (int i = 0; i < items_size; ++i) {
        total += items[i]->daily_energy();
    }

    return total;
}

bool compare_items(const std::shared_ptr<InventoryItem>& a,
                  const std::shared_ptr<InventoryItem>& b) {
  return *a < *b;
}

void Fleet::print_list(std::ostream& out) const {
    int items_size = static_cast<int>(items.size());

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
    for (int i = 0; i < static_cast<int>(items.size()); ++i) {
        if (items[i]->suitable_for_novice(min_novice_score)) {
            out << *items[i] << '\n';
        }
    }
}

void Fleet::focus(const std::string& id) {
    int items_size = static_cast<int>(items.size());

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
