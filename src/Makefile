CXX = g++
CXXFLAGS = -Wall
TARGET = Interpreter
SRCS = main.cpp chip8.cpp instructions.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.cpp: %.o
	$(CXX) $(CXXFLAGS) -c $<
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
