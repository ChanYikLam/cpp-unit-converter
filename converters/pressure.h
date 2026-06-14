#ifndef CONVERTER_PRESSURE_H
#define CONVERTER_PRESSURE_H

#include "../factor_converter.h"

class PressureConverter : public FactorConverter {
public:
    PressureConverter() : FactorConverter("压力") {
        addUnit("帕(Pa)",           1.0);
        addUnit("千帕(kPa)",          1000.0);
        addUnit("巴(bar)",          100000.0);
        addUnit("标准大气压(atm)",          101325.0);
        addUnit("磅力/平方英寸(psi)",          6894.757293168);
        addUnit("毫米汞柱(mmHg)",         133.3223684);
    }
};

#endif
