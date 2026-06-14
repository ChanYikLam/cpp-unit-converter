#ifndef CONVERTER_TEMPERATURE_H
#define CONVERTER_TEMPERATURE_H

#include "../converter_base.h"
#include <string>
#include <vector>

class TemperatureConverter : public AbstractConverter {
    std::vector<std::string> units_;

    double toCelsius(double value, const std::string& from) const {
        if (from == "Celsius") return value;
        if (from == "Fahrenheit") return (value - 32.0) * 5.0 / 9.0;
        if (from == "Kelvin") return value - 273.15;
        return 0.0;
    }

    double fromCelsius(double celsius, const std::string& to) const {
        if (to == "Celsius") return celsius;
        if (to == "Fahrenheit") return celsius * 9.0 / 5.0 + 32.0;
        if (to == "Kelvin") return celsius + 273.15;
        return 0.0;
    }

public:
    TemperatureConverter() {
        units_.push_back("Celsius");
        units_.push_back("Fahrenheit");
        units_.push_back("Kelvin");
    }

    const char* getCategoryName() const { return "\xe6\xb8\xa9\xe5\xba\xa6 (Temperature)"; }

    const std::vector<std::string>& getUnits() const { return units_; }

    double convert(double value, const std::string& from,
                   const std::string& to) const {
        if (from == to) return value;
        double celsius = toCelsius(value, from);
        return fromCelsius(celsius, to);
    }
};

#endif
