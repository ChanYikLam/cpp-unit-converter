# 跨平台单位转换程序 — 设计规范

## 概述

基于 C++98 标准的跨平台控制台单位转换程序。采用交互式菜单驱动，覆盖 13 个单位类别，通过 OOP 继承体系实现，重点展示多态和虚函数等核心面向对象特性。

## 技术约束

- **语言标准**: C++98
- **平台**: Windows / macOS / Linux 跨平台
- **界面**: 控制台文本菜单
- **依赖**: 仅 C++ 标准库（iostream, string, vector, map 等）

## 交互流程

```
启动
  → 显示主菜单（13 个类别 + 退出）
  → 用户选择类别编号
  → 进入子菜单：列出该类别所有单位
  → 选择源单位
  → 选择目标单位
  → 输入数值
  → 显示转换结果
  → 返回主菜单
```

## 架构设计

### 类继承体系

```
AbstractConverter (抽象基类)
  ├── LengthConverter      # 长度
  ├── WeightConverter      # 重量
  ├── TemperatureConverter # 温度（特殊：偏移量公式）
  ├── AreaConverter        # 面积
  ├── VolumeConverter      # 体积
  ├── SpeedConverter       # 速度
  ├── TimeConverter        # 时间
  ├── DataConverter        # 数据存储
  ├── EnergyConverter      # 能量
  ├── PowerConverter       # 功率
  ├── PressureConverter    # 压力
  ├── AngleConverter       # 角度
  └── ForceConverter       # 力
```

### 抽象基类接口 (AbstractConverter)

```cpp
class AbstractConverter {
public:
    virtual ~AbstractConverter() {}
    virtual const char* getCategoryName() const = 0;
    virtual const std::vector<std::string>& getUnits() const = 0;
    virtual double convert(double value,
                           const std::string& from,
                           const std::string& to) const = 0;
};
```

### 工厂函数

```cpp
AbstractConverter* createConverter(int categoryId);  // 1-13, 非法返回NULL
```

主程序通过工厂获取转换器对象，所有操作通过基类指针完成——展示运行时多态。

## 转换策略

### 因子转换器（12个类别）

每个类别定义一个基准单位（因子=1.0），其他单位通过转换因子表示。转换公式：

```
result = value * factor[from] / factor[to]
```

### 温度转换器（特殊）

温度转换涉及偏移量，不能用因子法。6 种转换组合直接实现：

- C→F: `(C × 9/5) + 32`
- F→C: `(F − 32) × 5/9`
- C→K: `C + 273.15`
- K→C: `K − 273.15`
- F→K: `(F − 32) × 5/9 + 273.15`
- K→F: `(K − 273.15) × 9/5 + 32`

这恰好展示多态：调用方只调用 `convert()`，不关心内部是因子公式还是温度公式。

## 类别与单位明细

### 1. 长度 Length (基准: m)
km=1000, m=1, cm=0.01, mm=0.001, mile=1609.344, yard=0.9144, foot=0.3048, inch=0.0254, 里=500

### 2. 重量 Weight (基准: kg)
kg=1, g=0.001, mg=1e-6, t(公吨)=1000, lb(磅)=0.45359237, oz(盎司)=0.028349523125, 斤=0.5

### 3. 温度 Temperature (特殊处理)
℃, ℉, K

### 4. 面积 Area (基准: m²)
m²=1, km²=1e6, cm²=0.0001, hectare=10000, acre=4046.8564224, ft²=0.09290304, 亩=666.6666667

### 5. 体积 Volume (基准: L)
L=1, mL=0.001, m³=1000, gallon(US)=3.785411784, qt=0.946352946, pt=0.473176473, cup=0.24

### 6. 速度 Speed (基准: m/s)
m/s=1, km/h=0.2777777778, mph=0.44704, knot=0.5144444444, mach=340.2933

### 7. 时间 Time (基准: sec)
sec=1, min=60, hour=3600, day=86400, week=604800, month(30d)=2592000, year(365d)=31536000

### 8. 数据存储 Data (基准: B)
B=1, KB=1024, MB=1048576, GB=1073741824, TB=1099511627776, PB=1125899906842624, bit=0.125

### 9. 能量 Energy (基准: J)
J=1, kJ=1000, cal=4.184, kcal=4184, Wh=3600, kWh=3.6e6

### 10. 功率 Power (基准: W)
W=1, kW=1000, MW=1e6, hp(metric)=735.49875, hp(imperial)=745.699871582

### 11. 压力 Pressure (基准: Pa)
Pa=1, kPa=1000, bar=100000, atm=101325, psi=6894.757293168, mmHg=133.3223684

### 12. 角度 Angle (基准: degree)
degree(°)=1, radian=180/PI, gradian=0.9

### 13. 力 Force (基准: N)
N=1, kN=1000, dyne=1e-5, lbf=4.448221615, kgf=9.80665

## 文件结构

```
单位转换程序/
├── main.cpp              # 入口 + 主菜单循环 + 交互逻辑
├── converter_base.h      # AbstractConverter 抽象基类
├── converter_factory.h   # 工厂函数
├── converters/
│   ├── length.h
│   ├── weight.h
│   ├── temperature.h
│   ├── area.h
│   ├── volume.h
│   ├── speed.h
│   ├── time.h
│   ├── data.h
│   ├── energy.h
│   ├── power.h
│   ├── pressure.h
│   ├── angle.h
│   └── force.h
├── utils.h               # 工具函数
└── Makefile
```

## 错误处理

- 非法菜单选择：提示重新输入
- 非法单位名：返回 -1.0 或 NaN 标记
- 输入非数字：清空输入流并提示重新输入
- 特殊值处理：除数不为 0，支持正负数和 0

## C++98 特性覆盖

| 特性 | 使用位置 |
|------|----------|
| 类与对象 | 所有 Converter 类 |
| 继承 | 所有子类继承 AbstractConverter |
| 多态（虚函数） | convert()/getUnits() 运行时绑定 |
| 纯虚函数 | AbstractConverter 中的三个纯虚函数 |
| 虚析构函数 | AbstractConverter::~virtual dtor() |
| STL 容器 | std::map 存储转换因子, std::vector 存储单位列表 |
| 字符串 | std::string 处理单位名和输入 |
| 流 I/O | std::cin/cout 交互, std::stringstream 解析 |
| new/delete | 工厂中动态分配，主程序负责释放 |

## 构建与运行

```bash
# Linux / macOS
make
./unitconverter

# Windows (MinGW)
mingw32-make
unitconverter.exe
```
