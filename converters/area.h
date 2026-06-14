#ifndef CONVERTER_AREA_H
#define CONVERTER_AREA_H

#include "../factor_converter.h"

class AreaConverter : public FactorConverter {
public:
    AreaConverter() : FactorConverter("\xe9\x9d\xa2\xe7\xa7\xaf (Area)") {
        addUnit("m^2",           1.0);
        addUnit("km^2",          1000000.0);
        addUnit("cm^2",          0.0001);
        addUnit("hectare",       10000.0);
        addUnit("acre",          4046.8564224);
        addUnit("ft^2",          0.09290304);
        addUnit("mu",            666.6666667);
    }
};

#endif
