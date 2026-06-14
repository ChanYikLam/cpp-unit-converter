#ifndef CONVERTER_ANGLE_H
#define CONVERTER_ANGLE_H

#include "../factor_converter.h"

class AngleConverter : public FactorConverter {
public:
    AngleConverter() : FactorConverter("\xe8\xa7\x92\xe5\xba\xa6 (Angle)") {
        addUnit("degree",       1.0);
        addUnit("radian",       57.29577951308232);
        addUnit("gradian",      0.9);
    }
};

#endif
