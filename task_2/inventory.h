#pragma once

#include <iosfwd>
#include <string>

class InventoryItem {
 public:
  virtual ~InventoryItem() = default;

  virtual const std::string& inventory_id() const = 0;
  virtual const std::string& get_name() const = 0;
  virtual void describe(std::ostream& out) const = 0;

  virtual double energy_per_minute() const;
  virtual bool suitable_for_novice(int min_novice_score = 6) const;
  virtual void offer_item(int age, int minutes);

  bool is_available() const;
  void take();
  void release();

 private:
  bool available = true;
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

  virtual double get_charge_level() const = 0;
  virtual double energy_per_minute() const = 0;
  virtual void charge() = 0;

 protected:
  double charge_level = 0.0;
};

class Transport : public Item {
 public:
  Transport(const std::string& id, const std::string& name, int novice_score);

  bool suitable_for_novice(int min_novice_score = 6) const override;

  virtual double offer_ride(int age, int minutes) = 0;

 private:
  int novice_score;
};

class Bike : public Transport {
 public:
  Bike(const std::string& id, const std::string& name, int novice_score);

  double offer_ride(int age, int minutes) override;

 private:
  int age_required = 12;
  double cost_per_minute = 3.0;
};

class SurreyBike : public Transport {
 public:
  SurreyBike(const std::string& id, const std::string& name, int novice_score);

  double offer_ride(int age, int minutes) override;

 private:
  int age_required = 14;
  double cost_per_minute = 8.0;
};

class ElectricScooter : public Transport, public EnergyConsumer {
 public:
  ElectricScooter(const std::string& id, const std::string& name,
                  double consumption_per_minute, int novice_score,
                  double accumulator_capacity);

  double get_charge_level() const override;
  double energy_per_minute() const override;
  void charge() override;

  double offer_ride(int age, int minutes) override;

 private:
  int age_required = 18;
  double cost_per_minute = 5.0;

  double consumption_per_minute = 1.5;
  double accumulator_capacity;
};

class ElectricBike : public Transport, public EnergyConsumer {
 public:
  ElectricBike(const std::string& id, const std::string& name,
               double consumption_per_minute, int novice_score,
               double accumulator_capacity);

  double get_charge_level() const override;
  double energy_per_minute() const override;
  void charge() override;

  double offer_ride(int age, int minutes) override;

 private:
  int age_required = 18;
  double cost_per_minute = 7.0;

  double consumption_per_minute = 3.0;
  double accumulator_capacity;
};

class Helmet : public Item {
 public:
  Helmet(const std::string& id, const std::string& name);

  void offer_item(int age, int minutes) override;
};

class Dock : public Item, public EnergyConsumer {
 public:
  Dock(const std::string& id, const std::string& name,
       double consumption_per_minute, double accumulator_capacity);

  double get_charge_level() const override;
  double energy_per_minute() const override;
  void charge() override;

  void offer_item(int age, int minutes) override;

 private:
  double consumption_per_minute = 5.0;
  double accumulator_capacity;
};
