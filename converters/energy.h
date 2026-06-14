#ifndef CONVERTER_ENERGY_H
#define CONVERTER_ENERGY_H

#include "../factor_converter.h"

class EnergyConverter : public FactorConverter {
public:
    EnergyConverter() : FactorConverter("能量") {
        addUnit("焦耳(J)",            1.0);
        addUnit("千焦(kJ)",           1000.0);
        addUnit("卡路里(cal)",          4.184);
        addUnit("千卡(kcal)",         4184.0);
        addUnit("瓦时(Wh)",           3600.0);
        addUnit("千瓦时(kWh)",          3600000.0);
    }
};

#endif
