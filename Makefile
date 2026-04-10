
# Detect OS
ifeq ($(OS), Windows_NT)
    TARGET = test.exe
else
    TARGET = test.out
endif

# TODO: Add catch testing library
build:
	g++ test.cpp -o $(TARGET)
run:
	./$(TARGET)
