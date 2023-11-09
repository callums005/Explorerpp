#pragma once

#include <stdio.h>
#include <string>


namespace Utils
{
	class Debug
	{
	public:
		static void Assert(bool condition, std::string msg)
		{
			if (condition)
				printf("[DEBUG]: %s", msg.c_str());
		}
	};
}