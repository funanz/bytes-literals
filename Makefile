TARGET=bytes-literals-test
SRCS=bytes_literals_test.cpp

OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)

CXXFLAGS=-std=c++20 -Wall -O2 -MD
LIBS=

$(TARGET): $(OBJS)
	$(LINK.cpp) -o $@ $(OBJS) $(LIBS)

clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

check: $(TARGET)
	./$(TARGET)
test: check
run: check

sinclude $(DEPS)
