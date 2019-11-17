COMPILER = g++
OUTPUT = -o
SRC = fib_heap
TEST = test_fib_heap
TARGET = test

run: test
	./$(TARGET)

test: $(TEST).cpp $(SRC).h
	$(COMPILER) $(TEST).cpp $(OUTPUT) $(TARGET)

.PHONY:
clean:
	rm $(TEST).o $(TARGET)
