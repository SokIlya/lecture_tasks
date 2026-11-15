#include "errors.h"
#include "fleet.h"

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

int main() {
  Fleet fleet;

  std::string cmd;

  while (std::cin >> cmd) {
    try {
      if (cmd == "add") {
        std::string item_type;
        std::cin >> item_type;

        if (item_type == "scooter") {
          std::string id;
          std::string name;
          double energy;
          int score;
          std::cin >> id >> name >> energy >> score;

          auto scooter = std::make_unique<ElectricScooter>(id, name, energy, score);

          fleet.add(std::move(scooter));

        } else if (item_type == "bike") {
          std::string id;
          std::string name;
          int score;
          std::cin >> id >> name >> score;

          auto bike = std::make_unique<Bike>(id, name, score);

          fleet.add(std::move(bike));

        } else if (item_type == "ebike") {
          std::string id;
          std::string name;
          double energy;
          int score;
          std::cin >> id >> name >> energy >> score;

          auto ebike = std::make_unique<ElectricBike>(id, name, energy, score);

          fleet.add(std::move(ebike));

        } else if (item_type == "helmet") {
          std::string id;
          std::string name;
          std::cin >> id >> name;

          auto helmet = std::make_unique<Helmet>(id, name);

          fleet.add(std::move(helmet));

        } else if (item_type == "dock") {
          std::string id;
          std::string name;
          double energy;
          std::cin >> id >> name >> energy;

          auto dock = std::make_unique<Dock>(id, name, energy);

          fleet.add(std::move(dock));

        } else {
          throw CommandError("unknown type");
        }

      } else if (cmd == "energy") {
        std::cout << std::fixed << std::setprecision(1) << fleet.total_energy() << '\n';

      } else if (cmd == "novice") {
      fleet.print_novice(std::cout);
        
      } else if (cmd == "list") {
        fleet.print_list(std::cout);

      } else if (cmd == "focus") {
        std::string id;
        std::cin >> id;

        fleet.focus(id);

      } else if (cmd == "show_focus") {
        fleet.show_focus(std::cout);

      } else if (cmd == "remove") {
        std::string id;
        std::cin >> id;

        fleet.remove(id);

      } else if (cmd == "quit") {
        break;

      } else {
        throw CommandError("unknown command");
      }
  }
  
  catch (const FleetError& error) {
    std::cout << "error: " << error.what() << '\n';
  }

  }
  
  return 0;
}
