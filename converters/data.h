#ifndef CONVERTER_DATA_H
#define CONVERTER_DATA_H

#include "../factor_converter.h"

class DataConverter : public FactorConverter {
public:
    DataConverter() : FactorConverter("\xe6\x95\xb0\xe6\x8d\xae\xe5\xad\x98\xe5\x82\xa8 (Data)") {
        addUnit("B",            1.0);
        addUnit("KB",           1024.0);
        addUnit("MB",           1048576.0);
        addUnit("GB",           1073741824.0);
        addUnit("TB",           1099511627776.0);
        addUnit("PB",           1125899906842624.0);
        addUnit("bit",          0.125);
    }
};

#endif
