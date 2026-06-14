#ifndef CONVERTER_VOLUME_H
#define CONVERTER_VOLUME_H

#include "../factor_converter.h"

class VolumeConverter : public FactorConverter {
public:
    VolumeConverter() : FactorConverter("\xe4\xbd\x93\xe7\xa7\xaf (Volume)") {
        addUnit("L",            1.0);
        addUnit("mL",           0.001);
        addUnit("m^3",          1000.0);
        addUnit("gallon(US)",   3.785411784);
        addUnit("qt",           0.946352946);
        addUnit("pt",           0.473176473);
        addUnit("cup",          0.24);
    }
};

#endif
