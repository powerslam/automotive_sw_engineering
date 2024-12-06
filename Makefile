# Makefile
CXX = g++
CXXFLAGS = -std=c++14 -isystem /usr/local/include -pthread
LDFLAGS = -lgtest -lgtest_main
TARGET = test_stack_calculator
MAIN_TARGET = stack_calculator
DEFINES = -DTEST

all: $(MAIN_TARGET) $(TARGET)

$(MAIN_TARGET): stack_calculator.cpp
	$(CXX) -o $@ $<

$(TARGET): test_stack_calculator.cpp
	$(CXX) $(CXXFLAGS) $(DEFINES) $< $(LDFLAGS) -o $@

clean:
	rm -f $(MAIN_TARGET) $(TARGET)

.PHONY: all