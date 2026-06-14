#ifndef CONVERTER_DATA_H
#define CONVERTER_DATA_H

#include "../factor_converter.h"

class DataConverter : public FactorConverter {
public:
    DataConverter() : FactorConverter("数据存储") {
        addUnit("字节(B)",            1.0);
        addUnit("千字节(KB)",           1024.0);
        addUnit("兆字节(MB)",           1048576.0);
        addUnit("吉字节(GB)",           1073741824.0);
        addUnit("太字节(TB)",           1099511627776.0);
        addUnit("拍字节(PB)",           1125899906842624.0);
        addUnit("比特(bit)",          0.125);
    }
};

#endif
