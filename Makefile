
# Detect OS
ifeq ($(OS), Windows_NT)
    TEST_TARGET = test.exe
else
    TEST_TARGET = ./test.out
endif

ifeq ($(OS), Windows_NT)
	MAIN_TARGET = main.exe
else
	MAIN_TARGET = ./main.out
endif


build:
	g++ src/str.cpp main.cpp -o $(MAIN_TARGET)
run: 
	$(TARGET)
test:
	g++ test.cpp lib/catch_amalgamated.cpp -o $(TEST_TARGET)
	./$(TEST_TARGET) Constructors
