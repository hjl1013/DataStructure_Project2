CC = g++
CXXFLAGS = -Wall
OBJS = main.o
TARGET = test

%.o: %.cpp %.hpp
	$(CC) $(CXXFLAGS) -c $<

$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $@

.PHONY : clean
clean :
	rm -f $(OBJS)
	rm -f $(TARGET)