#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include <vector>
#include "sha.h"

#define BLOCK_SIZE 1024
#define WORD_SIZE 32
#define ROUNDS 16
#define IV 0x6a09e667
#define CHUNK_SIZE 16
#define SIGMA1 0x5c5c5c5c
#define SIGMA2 0x3c3c3c3c
#define SIGMA3 0x0f0f0f0f
#define SIGMA4 0x55555555
#define SIGMA5 0xaaaaaaaa
#define SIGMA6 0xcccccccc
#define SIGMA7 0x80000000
using namespace std;

void padBlock(unsigned char *block, int messageSize);
void expandMessage(unsigned int *message, unsigned char *block);
void processBlock(unsigned int *message, unsigned int *h);
unsigned int rotateRight(unsigned int x, int n);
unsigned int rotateLeft(unsigned int x, int n);
void printHexString(unsigned int *h);
void printHash(unsigned int *h);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Usage: ./sha1024 <message>" << endl;
        return 1;
    }

    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)
    {
        cout << "Version: " << VERSION << endl;
        return 0;
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        cout << "Usage: ./sha1024 <message>" << endl;
        cout << "Options:" << endl;
        cout << " -v, --version\t\tPrint the version number" << endl;
        cout << " -h, --help\t\tPrint this help message" << endl;
        return 0;
    }

    string messageString = argv[1];
    int messageSize = messageString.length();

    unsigned char block[BLOCK_SIZE];
    for (int i = 0; i < messageSize; i++)
    {
        block[i] = messageString[i];
    }
    padBlock(block, messageSize);

    unsigned int message[16];
    expandMessage(message, block);

    unsigned int h[8] = {IV, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

    processBlock(message, h);

    //printHexString(h);
	printHash(h);

    return 0;
}

void padBlock(unsigned char *block, int messageSize)
{
    int padSize = BLOCK_SIZE - messageSize;
    for (int i = 0; i < padSize; i++)
    {
        if (i == 0)
        {
            block[messageSize] = 0x80;
        }
        else
        {
            block[messageSize + i] = 0x00;
        }
    }
}

void expandMessage(unsigned int *message, unsigned char *block)
{
    for (int i = 0; i < 16; i++)
    {
        message[i] = 0;
        for (int j = 0; j < 4; j++)
        {
            message[i] |= (unsigned int)block[(i * 4) + j] << (8 * (3 - j));
        }
    }
}

void processBlock(unsigned int *message, unsigned int *h)
{
    unsigned int k[16] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
                          0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174};

    unsigned int a = h[0];
    unsigned int b = h[1];
    unsigned int c = h[2];
    unsigned int d = h[3];
    unsigned int e = h[4];
    unsigned int f = h[5];
    unsigned int g = h[6];
    unsigned int h1 = h[7];

    for (int i = 0; i < ROUNDS; i++)
    {
        unsigned int t1 = h1 + rotateRight((a + (e ^ (b & (c ^ e))) + message[(i * 4) % 16] + k[i]), 7);
        unsigned int t2 = (d + rotateRight((t1 + (f ^ (a & (b ^ f))) + message[(i * 4 + 1) % 16]), 11));
        unsigned int t3 = (c + rotateRight((t2 + (g ^ (d & (a ^ g))) + message[(i * 4 + 2) % 16]), 19));
        unsigned int t4 = (b + rotateRight((t3 + (h1 ^ (c & (d ^ h1))) + message[(i * 4 + 3) % 16]), 3));

        a = t4;
        b = c;
        c = d;
        d = e;
        e = f;
        f = g;
        g = h1;
        h1 = t1;
    }

    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
    h[4] += e;
    h[5] += f;
    h[6] += g;
    h[7] += h1;
}

unsigned int rotateRight(unsigned int x, int n)
{
    return (x >> n) | (x << (WORD_SIZE - n));
}

unsigned int rotateLeft(unsigned int x, int n)
{
    return (x << n) | (x >> (WORD_SIZE - n));
}

void printHexString(unsigned int *h)
{
    for (int i = 0; i < 8; i++)
    {
        printf("%08x", h[i]);
    }
    printf("\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%08x", h[i] >> 24);
        printf("%08x", (h[i] >> 16) & 0xff);
        printf("%08x", (h[i] >> 8) & 0xff);
        printf("%08x", h[i] & 0xff);
    }
    printf("\n");
}

void printHash(unsigned int *h)
{
    for (int i = 0; i < 8; i++)
    {
        printf("%08x", h[i]);
    }
    printf("\n");
}