#pragma once

#include <exception>
#include <string>

class FleetError : public std::exception {
 public:
  explicit FleetError(const std::string& message);
  const char* what() const noexcept override;

 private:
  std::string message;
};

class InspectionRejected : public FleetError {
 public:
  InspectionRejected();
};

class CommandError : public FleetError {
 public:
  explicit CommandError(const std::string& message);
};
