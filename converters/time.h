#ifndef CONVERTER_TIME_H
#define CONVERTER_TIME_H

#include "../factor_converter.h"

class TimeConverter : public FactorConverter {
public:
    TimeConverter() : FactorConverter("\xe6\x97\xb6\xe9\x97\xb4 (Time)") {
        addUnit("sec",          1.0);
        addUnit("min",          60.0);
        addUnit("hour",         3600.0);
        addUnit("day",          86400.0);
        addUnit("week",         604800.0);
        addUnit("month(30d)",   2592000.0);
        addUnit("year(365d)",   31536000.0);
    }
};

#endif
