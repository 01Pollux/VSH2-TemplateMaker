#include "is_boss_check.hpp"

namespace VSH2
{
	void IsBossCheck::Parse(std::ofstream& file, const std::string& str, bool is_void)
	{
		file << "\n\tif (!VSH2_Is" << m_Name << "(" << str << ")) ";
		if (is_void)
			file << "return;\n";
		else
			file << "return Plugin_Continue;\n";
	}
}
