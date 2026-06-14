#ifndef CONVERTER_TIME_H
#define CONVERTER_TIME_H

#include "../factor_converter.h"

class TimeConverter : public FactorConverter {
public:
    TimeConverter() : FactorConverter("时间") {
        addUnit("秒",          1.0);
        addUnit("分",          60.0);
        addUnit("时",         3600.0);
        addUnit("天",          86400.0);
        addUnit("周",         604800.0);
        addUnit("月(30天)",   2592000.0);
        addUnit("年(365天)",   31536000.0);
    }
};

#endif
