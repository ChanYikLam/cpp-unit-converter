#ifndef CONVERTER_TEMPERATURE_H
#define CONVERTER_TEMPERATURE_H

#include "../converter_base.h"
#include <string>
#include <vector>

class TemperatureConverter : public AbstractConverter {
    std::vector<std::string> units_;

    double toCelsius(double value, const std::string& from) const {
        if (from == "摄氏度(℃)") return value;
        if (from == "华氏度(℉)") return (value - 32.0) * 5.0 / 9.0;
        if (from == "开尔文(K)") return value - 273.15;
        return 0.0;
    }

    double fromCelsius(double celsius, const std::string& to) const {
        if (to == "摄氏度(℃)") return celsius;
        if (to == "华氏度(℉)") return celsius * 9.0 / 5.0 + 32.0;
        if (to == "开尔文(K)") return celsius + 273.15;
        return 0.0;
    }

public:
    TemperatureConverter() {
        units_.push_back("摄氏度(℃)");
        units_.push_back("华氏度(℉)");
        units_.push_back("开尔文(K)");
    }

    const char* getCategoryName() const { return "温度"; }

    const std::vector<std::string>& getUnits() const { return units_; }

    double convert(double value, const std::string& from,
                   const std::string& to) const {
        if (from == to) return value;
        double celsius = toCelsius(value, from);
        return fromCelsius(celsius, to);
    }
};

#endif
