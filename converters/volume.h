#ifndef CONVERTER_VOLUME_H
#define CONVERTER_VOLUME_H

#include "../factor_converter.h"

class VolumeConverter : public FactorConverter {
public:
    VolumeConverter() : FactorConverter("体积") {
        addUnit("升",            1.0);
        addUnit("毫升",           0.001);
        addUnit("立方米",          1000.0);
        addUnit("加仑(美)",   3.785411784);
        addUnit("夸脱",           0.946352946);
        addUnit("品脱",           0.473176473);
        addUnit("杯",          0.24);
    }
};

#endif
