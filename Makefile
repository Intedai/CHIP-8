CXX = g++
CXXFLAGS = -Wall
TARGET = Interpreter
SRCDIR = src
SRCS = $(addprefix $(SRCDIR)/, main.cpp chip8.cpp instructions.cpp)
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
