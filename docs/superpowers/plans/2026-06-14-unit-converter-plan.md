# 单位转换程序 — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build a cross-platform console unit converter with 13 categories using C++98 OOP inheritance hierarchy.

**Architecture:** AbstractConverter pure-virtual base class → FactorConverter intermediate class for 12 factor-based categories → TemperatureConverter (special offset formulas) overriding convert() directly. Factory function maps category ID to concrete converter. Main program runs interactive menu loop, all operations through base class pointer (runtime polymorphism).

**Tech Stack:** C++98, g++, standard library only (iostream, string, vector, map, cstdlib)

**File Structure:**
```
单位转换程序/
├── main.cpp              # Entry point + interactive menu loop + input validation
├── converter_base.h      # AbstractConverter pure-virtual base class
├── factor_converter.h    # FactorConverter intermediate class (factor-based convert())
├── converter_factory.h   # Factory: ID → converter instance
├── converters/
│   ├── length.h          # LengthConverter
│   ├── weight.h          # WeightConverter
│   ├── temperature.h     # TemperatureConverter (special - overrides convert())
│   ├── area.h            # AreaConverter
│   ├── volume.h          # VolumeConverter
│   ├── speed.h           # SpeedConverter
│   ├── time.h            # TimeConverter
│   ├── data.h            # DataConverter
│   ├── energy.h          # EnergyConverter
│   ├── power.h           # PowerConverter
│   ├── pressure.h        # PressureConverter
│   ├── angle.h           # AngleConverter
│   └── force.h           # ForceConverter
└── Makefile
```

**Include dependency chain:**
```
main.cpp → converter_factory.h → all converters/*.h → factor_converter.h → converter_base.h
```

All headers use include guards. Since only main.cpp is compiled, all method definitions live inline in headers — no .cpp files needed for converters.

---

### Task 1: Create directory structure and Makefile

**Files:**
- Create: `converters/` directory
- Create: `Makefile`

- [ ] **Step 1: Create converters subdirectory**

```bash
mkdir -p "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序/converters"
```

- [ ] **Step 2: Write Makefile**

Write `Makefile`:
```makefile
CXX = g++
CXXFLAGS = -std=c++98 -Wall -Wextra
TARGET = unitconverter

HEADERS = converter_base.h factor_converter.h converter_factory.h \
          converters/length.h converters/weight.h converters/temperature.h \
          converters/area.h converters/volume.h converters/speed.h \
          converters/time.h converters/data.h converters/energy.h \
          converters/power.h converters/pressure.h converters/angle.h \
          converters/force.h

SOURCES = main.cpp

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

.PHONY: clean run

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
```

- [ ] **Step 3: Commit**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
git init
git add Makefile
git commit -m "feat: add project structure and Makefile"
```

---

### Task 2: Create AbstractConverter base class

**Files:**
- Create: `converter_base.h`

- [ ] **Step 1: Write converter_base.h**

Write `converter_base.h`:
```cpp
#ifndef CONVERTER_BASE_H
#define CONVERTER_BASE_H

#include <string>
#include <vector>

class AbstractConverter {
public:
    virtual ~AbstractConverter() {}

    // 返回类别名称（中文）
    virtual const char* getCategoryName() const = 0;

    // 返回该类别下所有可用单位名称列表
    virtual const std::vector<std::string>& getUnits() const = 0;

    // 核心转换接口：将 value 从 from 单位转换到 to 单位
    // 参数无效时返回 -1.0
    virtual double convert(double value,
                           const std::string& from,
                           const std::string& to) const = 0;
};

#endif // CONVERTER_BASE_H
```

- [ ] **Step 2: Verify it compiles as a header**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
echo 'int main() { return 0; }' | g++ -std=c++98 -Wall -Wextra -I. -x c++ - -o /dev/null
```

- [ ] **Step 3: Commit**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
git add converter_base.h
git commit -m "feat: add AbstractConverter pure-virtual base class"
```

---

### Task 3: Create FactorConverter intermediate class

**Files:**
- Create: `factor_converter.h`

- [ ] **Step 1: Write factor_converter.h**

Write `factor_converter.h`:
```cpp
#ifndef FACTOR_CONVERTER_H
#define FACTOR_CONVERTER_H

#include "converter_base.h"
#include <map>
#include <string>
#include <vector>

// 因子转换器的中间类：12 个类别（除温度外）均继承此类
// convert() 使用转换因子公式：result = value * factor[from] / factor[to]
class FactorConverter : public AbstractConverter {
    std::map<std::string, double> factors_;
    std::vector<std::string> units_;
    const char* name_;

protected:
    explicit FactorConverter(const char* name) : name_(name) {}

    // 子类构造函数中调用此方法注册单位和对应的转换因子
    void addUnit(const std::string& name, double factor) {
        factors_[name] = factor;
        units_.push_back(name);
    }

public:
    const char* getCategoryName() const { return name_; }

    const std::vector<std::string>& getUnits() const { return units_; }

    double convert(double value, const std::string& from,
                   const std::string& to) const {
        if (from == to) return value;
        std::map<std::string, double>::const_iterator it_from = factors_.find(from);
        std::map<std::string, double>::const_iterator it_to = factors_.find(to);
        if (it_from == factors_.end() || it_to == factors_.end()) {
            return -1.0;
        }
        return value * it_from->second / it_to->second;
    }
};

#endif // FACTOR_CONVERTER_H
```

- [ ] **Step 2: Commit**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
git add factor_converter.h
git commit -m "feat: add FactorConverter intermediate class"
```

---

### Task 4: Create Length and Weight converters

**Files:**
- Create: `converters/length.h`
- Create: `converters/weight.h`

- [ ] **Step 1: Write converters/length.h**

Write `converters/length.h`:
```cpp
#ifndef CONVERTER_LENGTH_H
#define CONVERTER_LENGTH_H

#include "../factor_converter.h"

class LengthConverter : public FactorConverter {
public:
    LengthConverter() : FactorConverter("长度 (Length)") {
        addUnit("m",          1.0);
        addUnit("km",         1000.0);
        addUnit("cm",         0.01);
        addUnit("mm",         0.001);
        addUnit("mile",       1609.344);
        addUnit("yard",       0.9144);
        addUnit("foot",       0.3048);
        addUnit("inch",       0.0254);
        addUnit("\xe9\x87\x8c (li)", 500.0);  // UTF-8: 里
    }
};

#endif // CONVERTER_LENGTH_H
```

- [ ] **Step 2: Write converters/weight.h**

Write `converters/weight.h`:
```cpp
#ifndef CONVERTER_WEIGHT_H
#define CONVERTER_WEIGHT_H

#include "../factor_converter.h"

class WeightConverter : public FactorConverter {
public:
    WeightConverter() : FactorConverter("重量 (Weight)") {
        addUnit("kg",          1.0);
        addUnit("g",           0.001);
        addUnit("mg",          0.000001);
        addUnit("t (metric)",  1000.0);
        addUnit("lb",          0.45359237);
        addUnit("oz",          0.028349523125);
        addUnit("\xe6\x96\xa4 (jin)", 0.5);  // UTF-8: 斤
    }
};

#endif // CONVERTER_WEIGHT_H
```

- [ ] **Step 3: Commit**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
git add converters/length.h converters/weight.h
git commit -m "feat: add Length and Weight converters"
```

---

### Task 5: Create Temperature converter (special case)

**Files:**
- Create: `converters/temperature.h`

- [ ] **Step 1: Write converters/temperature.h**

Write `converters/temperature.h`:
```cpp
#ifndef CONVERTER_TEMPERATURE_H
#define CONVERTER_TEMPERATURE_H

#include "../converter_base.h"
#include <string>
#include <vector>

// 温度转换不能用因子法，因为涉及偏移量
// 直接重写 convert()，先转换为摄氏度为中间基准，再转换到目标单位
class TemperatureConverter : public AbstractConverter {
    std::vector<std::string> units_;

    // 将任意温度单位转为摄氏度
    double toCelsius(double value, const std::string& from) const {
        if (from == "Celsius") return value;
        if (from == "Fahrenheit") return (value - 32.0) * 5.0 / 9.0;
        if (from == "Kelvin") return value - 273.15;
        return 0.0;
    }

    // 将摄氏度转为目标单位
    double fromCelsius(double celsius, const std::string& to) const {
        if (to == "Celsius") return celsius;
        if (to == "Fahrenheit") return celsius * 9.0 / 5.0 + 32.0;
        if (to == "Kelvin") return celsius + 273.15;
        return 0.0;
    }

public:
    TemperatureConverter() {
        units_.push_back("Celsius");
        units_.push_back("Fahrenheit");
        units_.push_back("Kelvin");
    }

    const char* getCategoryName() const { return "温度 (Temperature)"; }

    const std::vector<std::string>& getUnits() const { return units_; }

    double convert(double value, const std::string& from,
                   const std::string& to) const {
        if (from == to) return value;
        double celsius = toCelsius(value, from);
        return fromCelsius(celsius, to);
    }
};

#endif // CONVERTER_TEMPERATURE_H
```

- [ ] **Step 2: Commit**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
git add converters/temperature.h
git commit -m "feat: add Temperature converter with offset formulas"
```

---

### Task 6: Create Area and Volume converters

**Files:**
- Create: `converters/area.h`
- Create: `converters/volume.h`

- [ ] **Step 1: Write converters/area.h**

Write `converters/area.h`:
```cpp
#ifndef CONVERTER_AREA_H
#define CONVERTER_AREA_H

#include "../factor_converter.h"

class AreaConverter : public FactorConverter {
public:
    AreaConverter() : FactorConverter("面积 (Area)") {
        addUnit("m^2",           1.0);
        addUnit("km^2",          1000000.0);
        addUnit("cm^2",          0.0001);
        addUnit("hectare",       10000.0);
        addUnit("acre",          4046.8564224);
        addUnit("ft^2",          0.09290304);
        addUnit("\xe4\xba\xa9 (mu)", 666.6666667);  // UTF-8: 亩
    }
};

#endif // CONVERTER_AREA_H
```

- [ ] **Step 2: Write converters/volume.h**

Write `converters/volume.h`:
```cpp
#ifndef CONVERTER_VOLUME_H
#define CONVERTER_VOLUME_H

#include "../factor_converter.h"

class VolumeConverter : public FactorConverter {
public:
    VolumeConverter() : FactorConverter("体积 (Volume)") {
        addUnit("L",            1.0);
        addUnit("mL",           0.001);
        addUnit("m^3",          1000.0);
        addUnit("gallon(US)",   3.785411784);
        addUnit("qt",           0.946352946);
        addUnit("pt",           0.473176473);
        addUnit("cup",          0.24);
    }
};

#endif // CONVERTER_VOLUME_H
```

- [ ] **Step 3: Commit**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
git add converters/area.h converters/volume.h
git commit -m "feat: add Area and Volume converters"
```

---

### Task 7: Create Speed and Time converters

**Files:**
- Create: `converters/speed.h`
- Create: `converters/time.h`

- [ ] **Step 1: Write converters/speed.h**

Write `converters/speed.h`:
```cpp
#ifndef CONVERTER_SPEED_H
#define CONVERTER_SPEED_H

#include "../factor_converter.h"

class SpeedConverter : public FactorConverter {
public:
    SpeedConverter() : FactorConverter("速度 (Speed)") {
        addUnit("m/s",          1.0);
        addUnit("km/h",         0.2777777778);
        addUnit("mph",          0.44704);
        addUnit("knot",         0.5144444444);
        addUnit("mach",         340.2933);
    }
};

#endif // CONVERTER_SPEED_H
```

- [ ] **Step 2: Write converters/time.h**

Write `converters/time.h`:
```cpp
#ifndef CONVERTER_TIME_H
#define CONVERTER_TIME_H

#include "../factor_converter.h"

class TimeConverter : public FactorConverter {
public:
    TimeConverter() : FactorConverter("时间 (Time)") {
        addUnit("sec",          1.0);
        addUnit("min",          60.0);
        addUnit("hour",         3600.0);
        addUnit("day",          86400.0);
        addUnit("week",         604800.0);
        addUnit("month(30d)",   2592000.0);
        addUnit("year(365d)",   31536000.0);
    }
};

#endif // CONVERTER_TIME_H
```

- [ ] **Step 3: Commit**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
git add converters/speed.h converters/time.h
git commit -m "feat: add Speed and Time converters"
```

---

### Task 8: Create Data and Energy converters

**Files:**
- Create: `converters/data.h`
- Create: `converters/energy.h`

- [ ] **Step 1: Write converters/data.h**

Write `converters/data.h`:
```cpp
#ifndef CONVERTER_DATA_H
#define CONVERTER_DATA_H

#include "../factor_converter.h"

class DataConverter : public FactorConverter {
public:
    DataConverter() : FactorConverter("数据存储 (Data)") {
        addUnit("B",            1.0);
        addUnit("KB",           1024.0);
        addUnit("MB",           1048576.0);
        addUnit("GB",           1073741824.0);
        addUnit("TB",           1099511627776.0);
        addUnit("PB",           1125899906842624.0);
        addUnit("bit",          0.125);
    }
};

#endif // CONVERTER_DATA_H
```

- [ ] **Step 2: Write converters/energy.h**

Write `converters/energy.h`:
```cpp
#ifndef CONVERTER_ENERGY_H
#define CONVERTER_ENERGY_H

#include "../factor_converter.h"

class EnergyConverter : public FactorConverter {
public:
    EnergyConverter() : FactorConverter("能量 (Energy)") {
        addUnit("J",            1.0);
        addUnit("kJ",           1000.0);
        addUnit("cal",          4.184);
        addUnit("kcal",         4184.0);
        addUnit("Wh",           3600.0);
        addUnit("kWh",          3600000.0);
    }
};

#endif // CONVERTER_ENERGY_H
```

- [ ] **Step 3: Commit**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
git add converters/data.h converters/energy.h
git commit -m "feat: add Data and Energy converters"
```

---

### Task 9: Create Power and Pressure converters

**Files:**
- Create: `converters/power.h`
- Create: `converters/pressure.h`

- [ ] **Step 1: Write converters/power.h**

Write `converters/power.h`:
```cpp
#ifndef CONVERTER_POWER_H
#define CONVERTER_POWER_H

#include "../factor_converter.h"

class PowerConverter : public FactorConverter {
public:
    PowerConverter() : FactorConverter("功率 (Power)") {
        addUnit("W",            1.0);
        addUnit("kW",           1000.0);
        addUnit("MW",           1000000.0);
        addUnit("hp(metric)",   735.49875);
        addUnit("hp(imperial)", 745.699871582);
    }
};

#endif // CONVERTER_POWER_H
```

- [ ] **Step 2: Write converters/pressure.h**

Write `converters/pressure.h`:
```cpp
#ifndef CONVERTER_PRESSURE_H
#define CONVERTER_PRESSURE_H

#include "../factor_converter.h"

class PressureConverter : public FactorConverter {
public:
    PressureConverter() : FactorConverter("压力 (Pressure)") {
        addUnit("Pa",           1.0);
        addUnit("kPa",          1000.0);
        addUnit("bar",          100000.0);
        addUnit("atm",          101325.0);
        addUnit("psi",          6894.757293168);
        addUnit("mmHg",         133.3223684);
    }
};

#endif // CONVERTER_PRESSURE_H
```

- [ ] **Step 3: Commit**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
git add converters/power.h converters/pressure.h
git commit -m "feat: add Power and Pressure converters"
```

---

### Task 10: Create Angle and Force converters

**Files:**
- Create: `converters/angle.h`
- Create: `converters/force.h`

- [ ] **Step 1: Write converters/angle.h**

Write `converters/angle.h`:
```cpp
#ifndef CONVERTER_ANGLE_H
#define CONVERTER_ANGLE_H

#include "../factor_converter.h"

class AngleConverter : public FactorConverter {
public:
    AngleConverter() : FactorConverter("角度 (Angle)") {
        addUnit("degree",       1.0);
        addUnit("radian",       57.29577951308232);   // 180/PI
        addUnit("gradian",      0.9);                  // gon, 1 grad = 0.9 degree
    }
};

#endif // CONVERTER_ANGLE_H
```

- [ ] **Step 2: Write converters/force.h**

Write `converters/force.h`:
```cpp
#ifndef CONVERTER_FORCE_H
#define CONVERTER_FORCE_H

#include "../factor_converter.h"

class ForceConverter : public FactorConverter {
public:
    ForceConverter() : FactorConverter("力 (Force)") {
        addUnit("N",            1.0);
        addUnit("kN",           1000.0);
        addUnit("dyne",         0.00001);
        addUnit("lbf",          4.448221615);
        addUnit("kgf",          9.80665);
    }
};

#endif // CONVERTER_FORCE_H
```

- [ ] **Step 3: Commit**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
git add converters/angle.h converters/force.h
git commit -m "feat: add Angle and Force converters"
```

---

### Task 11: Create converter factory

**Files:**
- Create: `converter_factory.h`

- [ ] **Step 1: Write converter_factory.h**

Write `converter_factory.h`:
```cpp
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

// 工厂函数：根据类别 ID (1-13) 创建对应的转换器对象
// 调用方负责 delete 返回的对象
// 非法 ID 返回 NULL
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

// 获取类别名称，不创建对象
inline const char* getCategoryNameById(int categoryId) {
    switch (categoryId) {
        case 1:  return "长度 (Length)";
        case 2:  return "重量 (Weight)";
        case 3:  return "温度 (Temperature)";
        case 4:  return "面积 (Area)";
        case 5:  return "体积 (Volume)";
        case 6:  return "速度 (Speed)";
        case 7:  return "时间 (Time)";
        case 8:  return "数据存储 (Data)";
        case 9:  return "能量 (Energy)";
        case 10: return "功率 (Power)";
        case 11: return "压力 (Pressure)";
        case 12: return "角度 (Angle)";
        case 13: return "力 (Force)";
        default: return NULL;
    }
}

#endif // CONVERTER_FACTORY_H
```

- [ ] **Step 2: Commit**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
git add converter_factory.h
git commit -m "feat: add converter factory with getCategoryNameById"
```

---

### Task 12: Create main.cpp with interactive menu

**Files:**
- Create: `main.cpp`

- [ ] **Step 1: Write main.cpp**

Write `main.cpp`:
```cpp
#include <iostream>
#include <cstdlib>
#include "converter_base.h"
#include "converter_factory.h"

static const int NUM_CATEGORIES = 13;

// 跨平台清屏
static void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

// 清空 cin 错误状态和缓冲区
static void resetInput() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

// 显示主菜单
static void showMainMenu() {
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "         单位转换程序  Unit Converter      \n";
    std::cout << "========================================\n";
    for (int i = 1; i <= NUM_CATEGORIES; ++i) {
        const char* name = getCategoryNameById(i);
        std::cout << "   " << i << ". " << name << std::endl;
    }
    std::cout << "   0. 退出程序 (Exit)\n";
    std::cout << "========================================\n";
    std::cout << "请选择类别 (0-" << NUM_CATEGORIES << "): ";
}

// 执行一次转换流程
static void doConversion(AbstractConverter* conv) {
    const std::vector<std::string>& units = conv->getUnits();
    int fromIdx, toIdx;
    double value;

    std::cout << "\n--- " << conv->getCategoryName() << " 转换 ---\n";
    std::cout << "可选单位:\n";
    for (std::size_t i = 0; i < units.size(); ++i) {
        std::cout << "   " << (i + 1) << ". " << units[i] << std::endl;
    }

    std::cout << "请选择源单位 (1-" << units.size() << "): ";
    if (!(std::cin >> fromIdx) || fromIdx < 1 || fromIdx > static_cast<int>(units.size())) {
        std::cout << "错误: 无效的单位选择!\n";
        resetInput();
        return;
    }

    std::cout << "请选择目标单位 (1-" << units.size() << "): ";
    if (!(std::cin >> toIdx) || toIdx < 1 || toIdx > static_cast<int>(units.size())) {
        std::cout << "错误: 无效的单位选择!\n";
        resetInput();
        return;
    }

    std::cout << "请输入数值: ";
    if (!(std::cin >> value)) {
        std::cout << "错误: 请输入有效的数字!\n";
        resetInput();
        return;
    }

    double result = conv->convert(value, units[fromIdx - 1], units[toIdx - 1]);
    if (result == -1.0 && value != -1.0) {
        std::cout << "错误: 转换失败，单位不匹配!\n";
    } else {
        std::cout << "\n  " << value << " " << units[fromIdx - 1]
                  << " = " << result << " " << units[toIdx - 1] << std::endl;
    }
    resetInput();
}

int main() {
    while (true) {
        clearScreen();
        showMainMenu();

        int choice;
        if (!(std::cin >> choice)) {
            resetInput();
            continue;
        }

        if (choice == 0) {
            std::cout << "\n感谢使用，再见!\n" << std::endl;
            break;
        }

        if (choice < 1 || choice > NUM_CATEGORIES) {
            std::cout << "错误: 无效的选择，请重试!\n";
            resetInput();
            std::cout << "按回车键继续...";
            std::cin.get();
            continue;
        }

        AbstractConverter* conv = createConverter(choice);
        if (conv == NULL) {
            std::cout << "错误: 创建转换器失败!\n";
            resetInput();
            std::cout << "按回车键继续...";
            std::cin.get();
            continue;
        }

        doConversion(conv);
        delete conv;

        std::cout << "\n按回车键返回主菜单...";
        std::cin.get();
    }

    return 0;
}
```

- [ ] **Step 2: Commit**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
git add main.cpp
git commit -m "feat: add main program with interactive menu loop"
```

---

### Task 13: Build and verify

- [ ] **Step 1: Clean build**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
make clean
make
```

Expected: Compiles without errors or warnings under `-std=c++98 -Wall -Wextra`.

- [ ] **Step 2: Verify binary exists**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
ls -la ./unitconverter
```

Expected: Binary file `unitconverter` exists and is executable.

- [ ] **Step 3: Verify C++98 compliance (no C++11 features)**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
g++ -std=c++98 -Wall -Wextra -pedantic-errors -o unitconverter main.cpp 2>&1
```

Expected: No errors or warnings.

- [ ] **Step 4: Quick functional test (non-interactive)**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
# Test via piping input: select category 1 (length), source 1 (m), target 2 (km), value 1000, then exit
echo "1 1 2 1000 0" | ./unitconverter
```

Expected: Output shows `1000 m = 1 km`.

- [ ] **Step 5: Commit**

```bash
cd "/Users/chenyilin/Desktop/GDMU/CPP课程设计/单位转换程序"
git add -A
git commit -m "chore: verified build and functional test"
```

---

## Self-Review

**Spec coverage check:**
- [x] AbstractConverter base class with 3 pure virtuals → Task 2
- [x] 13 category list with units → Tasks 4-10
- [x] Factor-based conversion (12 categories) → Tasks 4,6-10 via FactorConverter
- [x] Temperature special handling → Task 5
- [x] Factory function → Task 11
- [x] Interactive menu loop → Task 12
- [x] Cross-platform (cls/clear) → Task 12
- [x] Input validation / error handling → Task 12
- [x] C++98 standard → all files, verified in Task 13

**Placeholder scan:** None found. All tasks contain complete code and exact commands.

**Type consistency:**
- `AbstractConverter::convert(double, const std::string&, const std::string&)` → `double` — consistent in base, FactorConverter, TemperatureConverter, and main.cpp call site
- `createConverter(int)` → `AbstractConverter*` — consistent
- `getCategoryNameById(int)` → `const char*` — consistent with main.cpp usage
- `getUnits()` → `const std::vector<std::string>&` — consistent across all classes and main.cpp usage
- All header include guards follow `CONVERTER_<NAME>_H` pattern consistently
