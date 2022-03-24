CC = g++

CFLAGS = -pthread -O3

TARGET = mergesort_benchmark

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)
