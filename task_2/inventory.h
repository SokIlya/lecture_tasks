#pragma once

#include <iosfwd>
#include <string>

class InventoryItem {
 public:
  virtual ~InventoryItem() = default;

  virtual const std::string& inventory_id() const = 0;
  virtual const std::string& get_name() const = 0;
  virtual void describe(std::ostream& out) const = 0;

  virtual double daily_energy() const;
  virtual bool suitable_for_novice(int min_novice_score = 6) const;
};

std::ostream& operator<<(std::ostream& out, const InventoryItem& item);
bool operator<(const InventoryItem& left, const InventoryItem& right);
bool operator==(const InventoryItem& left, const InventoryItem& right);

class Item : public InventoryItem {
 public:
  Item(const std::string& id, const std::string& name);

  const std::string& inventory_id() const override;
  const std::string& get_name() const override;
  void describe(std::ostream& out) const override;

 private:
  std::string id;
  std::string name;
};

class EnergyConsumer {
 public:
  virtual ~EnergyConsumer() = default;
  virtual double daily_energy() const = 0;
};

class Transport : public Item {
 public:
  Transport(const std::string& id, const std::string& name,
            int novice_score);

  bool suitable_for_novice(int min_novice_score = 6) const override;

 private:
  int novice_score;
};

class Bike : public Transport {
 public:
  Bike(const std::string& id, const std::string& name, int novice_score);
};

class ElectricScooter : public Transport, public EnergyConsumer {
 public:
  ElectricScooter(const std::string& id, const std::string& name,
                  double daily_consumption, int novice_score);

  double daily_energy() const override;

 private:
  double daily_consumption;
};

class ElectricBike : public Transport, public EnergyConsumer {
 public:
  ElectricBike(const std::string& id, const std::string& name,
               double daily_consumption, int novice_score);

  double daily_energy() const override;

 private:
  double daily_consumption;
};

class Helmet : public Item {
 public:
  Helmet(const std::string& id, const std::string& name);
};

class Dock : public Item, public EnergyConsumer {
 public:
  Dock(const std::string& id, const std::string& name,
       double daily_consumption);

  double daily_energy() const override;

 private:
  double daily_consumption;
};
