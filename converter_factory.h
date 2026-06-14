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
        case 1:  return "长度";
        case 2:  return "重量";
        case 3:  return "温度";
        case 4:  return "面积";
        case 5:  return "体积";
        case 6:  return "速度";
        case 7:  return "时间";
        case 8:  return "数据存储";
        case 9:  return "能量";
        case 10: return "功率";
        case 11: return "压力";
        case 12: return "角度";
        case 13: return "力";
        default: return NULL;
    }
}

#endif
