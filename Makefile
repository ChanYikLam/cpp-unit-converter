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
