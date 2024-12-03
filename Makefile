# Original command to compile
# gcc -I src/include -L src/lib -o main main.c -lmingw32 -lSDL2main -lSDL2 -mconsole

#Compiler and flags
CC = gcc
CFLAGS = -I src/include -L src/lib -mconsole
LIBS = -lmingw32 -lSDL2main -lSDL2

# Target and source files
TARGET = main
SRC = main.c

# Build target
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

# Clean build artifacts
clean:
	rm -f $(TARGET)
