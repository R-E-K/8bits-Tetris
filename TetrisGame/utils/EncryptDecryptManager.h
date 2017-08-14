#pragma once
#include <string>

namespace REKTetrisGame
{
	class EncryptDecryptManager
	{
	public:
		EncryptDecryptManager();
		~EncryptDecryptManager();

		static std::string EncryptDecryptString(std::string str);
	};
}
