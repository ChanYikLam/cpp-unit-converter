#ifndef CONVERTER_BASE_H
#define CONVERTER_BASE_H

#include <string>
#include <vector>

class AbstractConverter {
public:
    virtual ~AbstractConverter() {}

    virtual const char* getCategoryName() const = 0;

    virtual const std::vector<std::string>& getUnits() const = 0;

    virtual double convert(double value,
                           const std::string& from,
                           const std::string& to) const = 0;
};

#endif // CONVERTER_BASE_H
