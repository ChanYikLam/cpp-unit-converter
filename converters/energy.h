#ifndef CONVERTER_ENERGY_H
#define CONVERTER_ENERGY_H

#include "../factor_converter.h"

class EnergyConverter : public FactorConverter {
public:
    EnergyConverter() : FactorConverter("\xe8\x83\xbd\xe9\x87\x8f (Energy)") {
        addUnit("J",            1.0);
        addUnit("kJ",           1000.0);
        addUnit("cal",          4.184);
        addUnit("kcal",         4184.0);
        addUnit("Wh",           3600.0);
        addUnit("kWh",          3600000.0);
    }
};

#endif
