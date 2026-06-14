#ifndef CONVERTER_FACTORY_H
#define CONVERTER_FACTORY_H

#include "converter_base.h"
#include "converters/length.h"
#include "converters/weight.h"
#include "converters/temperature.h"
#include "converters/area.h"
#include "converters/volume.h"
#include "converters/speed.h"
#include "converters/time.h"
#include "converters/data.h"
#include "converters/energy.h"
#include "converters/power.h"
#include "converters/pressure.h"
#include "converters/angle.h"
#include "converters/force.h"

inline AbstractConverter* createConverter(int categoryId) {
    switch (categoryId) {
        case 1:  return new LengthConverter();
        case 2:  return new WeightConverter();
        case 3:  return new TemperatureConverter();
        case 4:  return new AreaConverter();
        case 5:  return new VolumeConverter();
        case 6:  return new SpeedConverter();
        case 7:  return new TimeConverter();
        case 8:  return new DataConverter();
        case 9:  return new EnergyConverter();
        case 10: return new PowerConverter();
        case 11: return new PressureConverter();
        case 12: return new AngleConverter();
        case 13: return new ForceConverter();
        default: return NULL;
    }
}

inline const char* getCategoryNameById(int categoryId) {
    switch (categoryId) {
        case 1:  return "\xe9\x95\xbf\xe5\xba\xa6 (Length)";
        case 2:  return "\xe9\x87\x8d\xe9\x87\x8f (Weight)";
        case 3:  return "\xe6\xb8\xa9\xe5\xba\xa6 (Temperature)";
        case 4:  return "\xe9\x9d\xa2\xe7\xa7\xaf (Area)";
        case 5:  return "\xe4\xbd\x93\xe7\xa7\xaf (Volume)";
        case 6:  return "\xe9\x80\x9f\xe5\xba\xa6 (Speed)";
        case 7:  return "\xe6\x97\xb6\xe9\x97\xb4 (Time)";
        case 8:  return "\xe6\x95\xb0\xe6\x8d\xae\xe5\xad\x98\xe5\x82\xa8 (Data)";
        case 9:  return "\xe8\x83\xbd\xe9\x87\x8f (Energy)";
        case 10: return "\xe5\x8a\x9f\xe7\x8e\x87 (Power)";
        case 11: return "\xe5\x8e\x8b\xe5\x8a\x9b (Pressure)";
        case 12: return "\xe8\xa7\x92\xe5\xba\xa6 (Angle)";
        case 13: return "\xe5\x8a\x9b (Force)";
        default: return NULL;
    }
}

#endif
