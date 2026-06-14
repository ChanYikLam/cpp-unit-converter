#ifndef CONVERTER_POWER_H
#define CONVERTER_POWER_H

#include "../factor_converter.h"

class PowerConverter : public FactorConverter {
public:
    PowerConverter() : FactorConverter("功率") {
        addUnit("瓦(W)",            1.0);
        addUnit("千瓦(kW)",           1000.0);
        addUnit("兆瓦(MW)",           1000000.0);
        addUnit("公制马力",   735.49875);
        addUnit("英制马力", 745.699871582);
    }
};

#endif
