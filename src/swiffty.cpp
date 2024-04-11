#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include <sstream>
#include <vector>
#include "swiffty.h"

#define BLOCK_SIZE 4096
#define WORD_SIZE 128
#define ROUNDS 16
#define IV 0x6a09e667
#define CHUNK_SIZE 32
#define SIGMA1 0x5c5c5c5c5c5c5c5c
#define SIGMA2 0x3c3c3c3c3c3c3c3c
#define SIGMA3 0x0f0f0f0f0f0f0f0f
#define SIGMA4 0x5555555555555555
#define SIGMA5 0xaaaaaaaaaaaaaaaa
#define SIGMA6 0xcccccccccccccccc
#define SIGMA7 0x8000000000000000
using namespace std;

void padBlock(unsigned char *block, int messageSize);
void expandMessage(unsigned long long *message, unsigned char *block);
void processBlock(unsigned long long *message, unsigned long long *h);
unsigned long long rotateRight(unsigned long long x, int n);
unsigned long long rotateLeft(unsigned long long x, int n);
void printHexString(unsigned long long *h);
void printBinaryString(unsigned long long *h);
void printHash(unsigned long long *h);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Usage: ./swiffty <message>" << endl;
        return 1;
    }

    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)
    {
        cout << "Version: " << VERSION << endl;
        return 0;
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        cout << "Usage: ./swiffty <message>" << endl;
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

    unsigned long long message[32];
    expandMessage(message, block);

    unsigned long long h[8] = {IV, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

    processBlock(message, h);

    /*printHexString(h);

    printf("\n--------------------------------------------------------------------------------\n");

    printBinaryString(h);

    printf("\n--------------------------------------------------------------------------------\n");*/

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

void expandMessage(unsigned long long *message, unsigned char *block)
{
    for (int i = 0; i < 32; i++)
    {
        message[i] = 0;
        for (int j = 0; j < 16; j++)
        {
            message[i] |= (unsigned long long)block[(i * 16) + j] << (8 * (15 - j));
        }
    }
}

void processBlock(unsigned long long *message, unsigned long long *h)
{
    unsigned long long k[16] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
                                 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174};

    unsigned long long a = h[0];
    unsigned long long b = h[1];
    unsigned long long c = h[2];
    unsigned long long d = h[3];
    unsigned long long e = h[4];
    unsigned long long f = h[5];
    unsigned long long g = h[6];
    unsigned long long h1 = h[7];

    for (int i = 0; i < ROUNDS; i++)
    {
        unsigned long long t1 = h1 + rotateRight((a + (e ^ (b & (c ^ e))) + message[(i * 8) % 32] + k[i]), 1);
        unsigned long long t2 = (d + rotateRight((t1 + (f ^ (a & (b ^ f))) + message[(i * 8 + 1) % 32]), 8));
        unsigned long long t3 = (c + rotateRight((t2 + (g ^ (d & (a ^ g))) + message[(i * 8 + 2) % 32]), 15));
        unsigned long long t4 = (b + rotateRight((t3 + (h1 ^ (c & (d ^ h1))) + message[(i * 8 + 3) % 32]), 22));

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

unsigned long long rotateRight(unsigned long long x, int n)
{
    return (x >> n) | (x << (WORD_SIZE - n));
}

unsigned long long rotateLeft(unsigned long long x, int n)
{
    return (x << n) | (x >> (WORD_SIZE - n));
}

void printHexString(unsigned long long *h)
{
    for (int i = 0; i < 8; i++)
    {
        printf("%032llx", h[i]);
    }
    printf("\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%032llx", h[i] >> 120);
        printf("%032llx", (h[i] >> 112) & 0xff);
        printf("%032llx", (h[i] >> 104) & 0xff);
        printf("%032llx", (h[i] >> 96) & 0xff);
        printf("%032llx", (h[i] >> 88) & 0xff);
        printf("%032llx", (h[i] >> 80) & 0xff);
        printf("%032llx", (h[i] >> 72) & 0xff);
        printf("%032llx", (h[i] >> 64) & 0xff);
        printf("%032llx", (h[i] >> 56) & 0xff);
        printf("%032llx", (h[i] >> 48) & 0xff);
        printf("%032llx", (h[i] >> 40) & 0xff);
        printf("%032llx", (h[i] >> 32) & 0xff);
        printf("%032llx", (h[i] >> 24) & 0xff);
        printf("%032llx", (h[i] >> 16) & 0xff);
        printf("%032llx", (h[i] >> 8) & 0xff);
        printf("%032llx", h[i] & 0xff);
    }
    printf("\n");
}

void printBinaryString(unsigned long long *h)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = WORD_SIZE - 1; j >= 0; j--)
        {
            printf("%llu", (h[i] >> j) & 1ULL);
        }
    }
    printf("\n");
}

void printHash(unsigned long long *h)
{
    for (int i = 0; i < 8; i++)
    {
        printf("%016llx", h[i]);
    }
    printf("\n");
}