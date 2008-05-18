CXX = g++
SLICE = slice2cpp

CXXFLAGS = -c -Wall -ansi -pedantic -g -I.
LDFLAGS = -lIce -lm -lccgnu2 -lboost_regex

OBJS = iface.o fsm.o tools.o
TARGET = app
ICE_SRCS = iface.cpp
ICE_HEADS = iface.h

.PHONY: all interface clean

all: interface $(TARGET)
	cp $(TARGET) ../bin

clean:
	rm -rf $(OBJS) $(TARGET) $(ICE_SRCS) $(ICE_HEADS)

interface: iface.o

%.cpp: %.ice
	$(SLICE) $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<


$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

