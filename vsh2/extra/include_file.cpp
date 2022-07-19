
#include <sstream>
#include "include_file.hpp"

namespace VSH2
{
	bool IncludeFile::Parse(std::ofstream& file, const std::string& str, bool is_void)
	{
		std::ifstream subfile(str);
		if (!subfile)
			throw std::runtime_error("Failed to parse sub-file: " + str);

		std::stringstream stream;
		stream << subfile.rdbuf();
		subfile.close();
		
		std::string file_str = stream.str();
		replace_strings(file_str, "<Name>", m_Name);
		replace_strings(file_str, "<name>", m_LowerCaseName);

		file << '\n' << file_str << '\n';
		return false;
	}
}