#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include <sstream>
#include <vector>
#include "xMac16.h"

using namespace std;

// Define the block size and word size
#define BLOCK_SIZE 1024
#define WORD_SIZE 64

// Define the number of rounds
#define ROUNDS 16

// Define the initial value (IV)
#define IV 0x6a09e667

// Define the chunk size
#define CHUNK_SIZE 16

// Define the sigma values
#define SIGMA1 0x5c5c5c5c5c5c5c5c
#define SIGMA2 0x3c3c3c3c3c3c3c3c
#define SIGMA3 0x0f0f0f0f0f0f0f0f
#define SIGMA4 0x5555555555555555
#define SIGMA5 0xaaaaaaaaaaaaaaaa
#define SIGMA6 0xcccccccccccccccc
#define SIGMA7 0x8000000000000000

// Define the padding byte
#define PAD_BYTE 0x80

unsigned long long rotateRight(unsigned long long x, int n);

// Define the function to pad the block
void padBlock(unsigned char *block, int messageSize) {
  // Calculate the padding size
  int padSize = BLOCK_SIZE - messageSize;

  // Add the padding byte
  block[messageSize] = PAD_BYTE;

  // Add the length of the message in bits
  for (int i = 1; i < padSize; i++) {
    block[messageSize + i] = 0x00;
  }
}

// Define the function to expand the message
void expandMessage(unsigned long long *message, unsigned char *block) {
  // Copy the block into the message array
  for (int i = 0; i < CHUNK_SIZE; i++) {
    message[i] = 0;
    for (int j = 0; j < 8; j++) {
      message[i] |= (unsigned long long)block[(i * 8) + j] << (8 * (7 - j));
    }
  }
}

// Define the function to process the block
void processBlock(unsigned long long *message, unsigned long long *h) {
  // Define the constants
  unsigned long long k[16] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174
  };

  // Initialize the working variables
  unsigned long long a = h[0];
  unsigned long long b = h[1];
  unsigned long long c = h[2];
  unsigned long long d = h[3];
  unsigned long long e = h[4];
  unsigned long long f = h[5];
  unsigned long long g = h[6];
  unsigned long long h1 = h[7];

  // Perform the rounds
  for (int i = 0; i < ROUNDS; i++) {
    // Calculate the intermediate values
    unsigned long long t1 = h1 + rotateRight(a + (e ^ (b & (c ^ e))) + message[(i * 8) % 16] + k[i], 1);
    unsigned long long t2 = (d + rotateRight(t1 + (f ^ (a & (b ^ f))) + message[(i * 8 + 1) % 16], 8));
    unsigned long long t3 = (c + rotateRight(t2 + (g ^ (d & (a ^ g))) + message[(i * 8 + 2) % 16], 15));
    unsigned long long t4 = (b + rotateRight(t3 + (h1 ^ (c & (d ^ h1))) + message[(i * 8 + 3) % 16], 22));

    // Update the working variables
    a = t4;
    b = c;
    c = d;
    d = e;
    e = f;
    f = g;
    g = h1;
    h1 = t1;
  }

  // Update the hash values
  h[0] += a;
  h[1] += b;
  h[2] += c;
  h[3] += d;
  h[4] += e;
  h[5] += f;
  h[6] += g;
  h[7] += h1;
}

// Define the function to rotate a word to the right
unsigned long long rotateRight(unsigned long long x, int n) {
  return (x >> n) | (x << (WORD_SIZE - n));
}

// Define the function to rotate a word to the left
unsigned long long rotateLeft(unsigned long long x, int n) {
  return (x << n) | (x >> (WORD_SIZE - n));
}

// Define the function to print the hash value in hexadecimal format
void printHex(unsigned long long *h) {
  for (int i = 0; i < 8; i++) {
    printf("%016llx", h[i]);
  }
  printf("\n");
}

// Define the main function
int main(int argc, char **argv) {
  // Check if the user has entered a message
  if (argc != 2) {
    cerr << "Usage: ./xMac16 <message>" << endl;
    return 1;
  }

  if (strcmp(argv[1], "-v") == 0) {
    cout << VERSION << endl;
    return 0;
  }

  if (strcmp(argv[1], "-h") == 0) {
    cout << "Usage: ./xMac16 <message>" << endl;
    return 0;
  }


  // Get the message from the command line
  string message = argv[1];

  // Calculate the message size
  int messageSize = message.length();

  // Pad the block
  unsigned char block[BLOCK_SIZE];
  padBlock(block, messageSize);

  // Expand the message
  unsigned long long messageArray[CHUNK_SIZE];
  expandMessage(messageArray, block);

  // Initialize the hash value
  unsigned long long h[8] = {IV, 0, 0, 0, 0, 0, 0, 0};

  // Process the block
  processBlock(messageArray, h);

  // Print the hash value
  printHex(h);

  return 0;
}