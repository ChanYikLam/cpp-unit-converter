#ifndef CONVERTER_AREA_H
#define CONVERTER_AREA_H

#include "../factor_converter.h"

class AreaConverter : public FactorConverter {
public:
    AreaConverter() : FactorConverter("面积") {
        addUnit("平方米",           1.0);
        addUnit("平方千米",          1000000.0);
        addUnit("平方厘米",          0.0001);
        addUnit("公顷",       10000.0);
        addUnit("英亩",          4046.8564224);
        addUnit("平方英尺",          0.09290304);
        addUnit("亩",            666.6666667);
    }
};

#endif
