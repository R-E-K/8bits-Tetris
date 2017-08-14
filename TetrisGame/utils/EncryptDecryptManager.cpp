#include "EncryptDecryptManager.h"

namespace REKTetrisGame
{
	EncryptDecryptManager::EncryptDecryptManager()
	{
	}


	EncryptDecryptManager::~EncryptDecryptManager()
	{
	}

	// Taken from : https://kylewbanks.com/blog/Simple-XOR-Encryption-Decryption-in-Cpp
	// https://en.wikipedia.org/wiki/XOR_cipher
	std::string EncryptDecryptManager::EncryptDecryptString(std::string str)
	{
		char key[4] = { 'K', 'C', 'Q', 'X' };
		std::string output = str;

		for (int i = 0; i < str.size(); i++)
			output[i] = str[i] ^ key[i % (sizeof(key) / sizeof(char))];

		return output;
	}
}
