CC = g++
CFLAGS = -Wall 
INCLUDE = -I include
SRC = src
BIN = bin

# List of source files
USH_SRC = $(SRC)/ush.cpp
MD7_SRC = $(SRC)/md7.cpp
SHA1024_SRC = $(SRC)/sha1024.cpp
CRC64_SRC = $(SRC)/crc64.cpp
BLAKE6_SRC = $(SRC)/blake6.cpp
SWIFFTY_SRC = $(SRC)/swiffty.cpp
XMAC16_SRC = $(SRC)/xMac16.cpp

# List of object files
USH_OBJ = $(BIN)/ush.o
MD7_OBJ = $(BIN)/md7.o
SHA1024_OBJ = $(BIN)/sha1024.o
CRC64_OBJ = $(BIN)/crc64.o
BLAKE6_OBJ = $(BIN)/blake6.o
SWIFFTY_OBJ = $(BIN)/swiffty.o
XMAC16_OBJ = $(BIN)/xMac16.o

# Targets
all: init $(BIN)/ush $(BIN)/md7 $(BIN)/sha1024 $(BIN)/crc64 $(BIN)/blake6 $(BIN)/swiffty $(BIN)/xmac16

ush: init $(BIN)/ush

md7: init $(BIN)/md7

sha1024: init $(BIN)/sha1024

crc64: init $(BIN)/crc64

blake6: init $(BIN)/blake6

swiffty: init $(BIN)/swiffty

xmac16: init $(BIN)/xmac16


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

$(BIN)/blake6: $(BLAKE6_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $(BLAKE6_OBJ) $(BLAKE6_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BIN)/blake6 $(BLAKE6_OBJ)

$(BIN)/swiffty: $(SWIFFTY_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $(SWIFFTY_OBJ) $(SWIFFTY_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BIN)/swiffty $(SWIFFTY_OBJ)

$(BIN)/xmac16: $(XMAC16_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $(XMAC16_OBJ) $(XMAC16_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BIN)/xmac16 $(XMAC16_OBJ)


init:
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)