#include "errors.h"

FleetError::FleetError(const std::string& message) : message(message) {}

const char* FleetError::what() const noexcept {
    return message.c_str();
}


InspectionRejected::InspectionRejected(): FleetError("inspection rejected") {}


CommandError::CommandError(const std::string& message) : FleetError(message) {}
