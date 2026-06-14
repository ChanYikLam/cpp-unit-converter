#ifndef FACTOR_CONVERTER_H
#define FACTOR_CONVERTER_H

#include "converter_base.h"
#include <map>
#include <string>
#include <vector>

class FactorConverter : public AbstractConverter {
    std::map<std::string, double> factors_;
    std::vector<std::string> units_;
    const char* name_;

protected:
    explicit FactorConverter(const char* name) : name_(name) {}

    void addUnit(const std::string& name, double factor) {
        factors_[name] = factor;
        units_.push_back(name);
    }

public:
    const char* getCategoryName() const { return name_; }

    const std::vector<std::string>& getUnits() const { return units_; }

    double convert(double value, const std::string& from,
                   const std::string& to) const {
        if (from == to) return value;
        std::map<std::string, double>::const_iterator it_from = factors_.find(from);
        std::map<std::string, double>::const_iterator it_to = factors_.find(to);
        if (it_from == factors_.end() || it_to == factors_.end()) {
            return -1.0;
        }
        return value * it_from->second / it_to->second;
    }
};

#endif // FACTOR_CONVERTER_H
