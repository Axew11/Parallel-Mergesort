CC = g++

CFLAGS = -pthread -O1

TARGET = mergesort_benchmark

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)
