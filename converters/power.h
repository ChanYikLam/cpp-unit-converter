#ifndef CONVERTER_POWER_H
#define CONVERTER_POWER_H

#include "../factor_converter.h"

class PowerConverter : public FactorConverter {
public:
    PowerConverter() : FactorConverter("\xe5\x8a\x9f\xe7\x8e\x87 (Power)") {
        addUnit("W",            1.0);
        addUnit("kW",           1000.0);
        addUnit("MW",           1000000.0);
        addUnit("hp(metric)",   735.49875);
        addUnit("hp(imperial)", 745.699871582);
    }
};

#endif
