#ifndef CONVERTER_PRESSURE_H
#define CONVERTER_PRESSURE_H

#include "../factor_converter.h"

class PressureConverter : public FactorConverter {
public:
    PressureConverter() : FactorConverter("\xe5\x8e\x8b\xe5\x8a\x9b (Pressure)") {
        addUnit("Pa",           1.0);
        addUnit("kPa",          1000.0);
        addUnit("bar",          100000.0);
        addUnit("atm",          101325.0);
        addUnit("psi",          6894.757293168);
        addUnit("mmHg",         133.3223684);
    }
};

#endif
