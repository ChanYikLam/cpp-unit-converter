#ifndef CONVERTER_ANGLE_H
#define CONVERTER_ANGLE_H

#include "../factor_converter.h"

class AngleConverter : public FactorConverter {
public:
    AngleConverter() : FactorConverter("角度") {
        addUnit("度(°)",       1.0);
        addUnit("弧度(rad)",       57.29577951308232);
        addUnit("百分度(gon)",      0.9);
    }
};

#endif
