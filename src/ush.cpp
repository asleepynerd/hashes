#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <random>
#include <fstream>
#include <cstring>
#include <math.h>

#include "ush.h"

using namespace std;

// Function to generate a secure hash
string USH(string input)
{
	// Initialize the random number generator
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 255);
	
	// Generate a random 256 bit key
	vector<uint8_t> key;
	for (int i = 0; i < 32; i++)
		key.push_back(dis(gen));
	
	// Initialize the hash
	string hash = "";
	
	// Iterate over the input string
	for (int i = 0; i < input.length(); i++)
	{
		// Convert the current character to its unicode value
		int unicode_val = (int)input[i];
		
		// XOR the unicode value with the corresponding byte in the key
		int xor_val = unicode_val ^ key[i % 32];
		
		// Convert the xor value to a hexadecimal string
		string hex_val = to_string(xor_val);
		string hex_str = "";
		for (int j = 0; j < hex_val.length(); j++)
			hex_str += hex_val[j];
		
		// Append the hexadecimal string to the hash
		hash += hex_str;
	}
	
	return hash;
}

int main(int argc, char* argv[])
{
	// Check for the -v flag
	if (argc == 2 && string(argv[1]) == "-v")
	{
		cout << "Unicode-Secure-Hash (USH)" << VERSION << endl;
		return 0;
	}

	if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)
	// Check for the correct number of arguments
	if (argc != 2)
	{
		cout << "Usage: ush <input-file-name> [-v] \nMade By imjoshie(Joshie#5868)" << endl;
		return -1;
	}
	
	// Read the input file
	string input = "";
	ifstream fin(argv[1]);
	string line;
	while (getline(fin, line))
		input += line;
	
	// Generate and print the hash
	string hash = USH(input);
	cout << hash << endl;
	
	return 0;
}