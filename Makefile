CC = g++
CFLAGS = -Wall 
INCLUDE = -I include
SRC = src
BIN = bin

VERSION = 1.1.0

# List of source files
USH_SRC = $(SRC)/ush.cpp
MD7_SRC = $(SRC)/md7.cpp
SHA1024_SRC = $(SRC)/sha1024.cpp
CRC64_SRC = $(SRC)/crc64.cpp

# List of object files
USH_OBJ = $(BIN)/ush.o
MD7_OBJ = $(BIN)/md7.o
SHA1024_OBJ = $(BIN)/sha1024.o
CRC64_OBJ = $(BIN)/crc64.o

# Targets
all: init $(BIN)/ush $(BIN)/md7 $(BIN)/sha1024 $(BIN)/crc64

ush: init $(BIN)/ush

md7: init $(BIN)/md7

sha1024: init $(BIN)/sha1024

crc64: init $(BIN)/crc64


$(BIN)/ush: $(USH_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $(USH_OBJ) $(USH_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BIN)/ush $(USH_OBJ)

$(BIN)/md7: $(MD7_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $(MD7_OBJ) $(MD7_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BIN)/md7 $(MD7_OBJ)

$(BIN)/sha1024: $(SHA1024_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $(SHA1024_OBJ) $(SHA1024_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BIN)/sha1024 $(SHA1024_OBJ)

$(BIN)/crc64: $(CRC64_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $(CRC64_OBJ) $(CRC64_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BIN)/crc64 $(CRC64_OBJ)

init:
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)