#ifndef CONVERTER_LENGTH_H
#define CONVERTER_LENGTH_H

#include "../factor_converter.h"

class LengthConverter : public FactorConverter {
public:
    LengthConverter() : FactorConverter("\xe9\x95\xbf\xe5\xba\xa6 (Length)") {
        addUnit("m",          1.0);
        addUnit("km",         1000.0);
        addUnit("cm",         0.01);
        addUnit("mm",         0.001);
        addUnit("mile",       1609.344);
        addUnit("yard",       0.9144);
        addUnit("foot",       0.3048);
        addUnit("inch",       0.0254);
        addUnit("li",         500.0);
    }
};

#endif
