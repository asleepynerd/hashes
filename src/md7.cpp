#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdint>
#include "md7.h"

using namespace std;

//Function prototypes
void printHelp();
string Method7(string message);

int main(int argc, char* argv[])
{
	//Command Line Input
	if (argc == 1)
	{
		printHelp();
		return 0;
	}
	else if (argc > 1)
	{
		string param = argv[1];
		if (param == "-h" || param == "--help")
		{
			printHelp();
			return 0;
		}
        else if (param == "-v" || param == "--version")
        {
            cout << "Version: " << VERSION << endl;
            return 0;
        }
		else if (param == "-f")
		{
			if (argc < 3)
			{
				cout << "Error! Please provide a filename.";
				return 1;
			}
			else
			{
				string filename = argv[2];
				ifstream file;
				file.open(filename);
				if (!file.good())
				{
					cout << "Error! File not found." << endl;
					return 1;
				}
				string message;
				while (!file.eof())
				{
					string line;
					getline(file, line);
					message += line;
				}
				cout << "Message Digest: " << Method7(message) << endl;
				file.close();
				return 0;
			}
		}
		else
		{
			string message = argv[1];
			for (int i = 2; i < argc; i++)
			{
				message += argv[i];
			}
			cout << "Message Digest: " << Method7(message) << endl;
			return 0;
		}
	}
	return 0;
}

//Function Definitions
void printHelp()
{
	cout << "Usage: md7 -f <filename> or md7 <message>" << endl;
}

string Method7(string message)
{
	//Message padding
	int paddingSize = 64 - (message.length() % 64);
	if (paddingSize < 9)
	{
		paddingSize += 64;
	}
	message += (char)0x80;
	for (int i = 1; i < paddingSize; i++)
	{
		message += (char) 0;
	}
	// Append the length of the message in bits
	uint64_t messageLength = message.length() * 8;
	for (int i = 0; i < 8; i++)
	{
		message += (char)((messageLength >> (56 - (i * 8))) & 0xff);
	}
	
	//Variable Declarations
	const int M = 64; //Message block size
	const int N = 16; //Number of 32-bit words in a message block
	uint32_t A = 0x67452301;
	uint32_t B = 0xefcdab89;
	uint32_t C = 0x98badcfe;
	uint32_t D = 0x10325476;
	
	//Precomputed values
	const uint32_t S[4][4] =
	{
		{7, 12, 17, 22},
		{5, 9, 14, 20},
		{4, 11, 16, 23},
		{6, 10, 15, 21}
	};
	const uint32_t K[4] =
	{
		0xd76aa478,
		0xe8c7b756,
		0x242070db,
		0xc1bdceee
	};
	
	//Process message
	uint32_t X[16];
	for (unsigned int i = 0; i < message.length(); i += M)
	{
		for (int j = 0; j < N; j++)
		{
			X[j] = 0;
			for (int k = 0; k < 4; k++)
			{
				X[j] += (unsigned char)message[i + (j * 4) + k] << (24 - (k * 8));
			}
		}
		
		uint32_t AA = A;
		uint32_t BB = B;
		uint32_t CC = C;
		uint32_t DD = D;
		
		for (int j = 0; j < 64; j++)
		{
			uint32_t F;
			int g;
			if (j < 16)
			{
				F = (B & C) | (~B & D);
				g = j;
			}
			else if (j < 32)
			{
				F = (D & B) | (~D & C);
				g = (5 * j + 1) % 16;
			}
			else if (j < 48)
			{
				F = B ^ C ^ D;
				g = (3 * j + 5) % 16;
			}
			else
			{
				F = C ^ (B | ~D);
				g = (7 * j) % 16;
			}
			
			uint32_t temp = D;
			D = C;
			C = B;
			B += ((A + F + K[j / 16] + X[g]) << S[j / 16][j % 4]) | ((A + F + K[j / 16] + X[g]) >> (32 - S[j / 16][j % 4]));
			A = temp;
		}
		
		A += AA;
		B += BB;
		C += CC;
		D += DD;
	}
	
	string digest;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			digest += (char)((A >> (24 - (j * 8))) & 0xff);
			digest += (char)((B >> (24 - (j * 8))) & 0xff);
			digest += (char)((C >> (24 - (j * 8))) & 0xff);
			digest += (char)((D >> (24 - (j * 8))) & 0xff);
		}
	}
	
	return digest;
}