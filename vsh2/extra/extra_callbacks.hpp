#pragma once

#include <fstream>
#include <string>

namespace VSH2
{
	class IExtraParserCallback
	{
	public:
		IExtraParserCallback(const std::string& name, const std::string& lowercase_name) :
			m_Name(name), m_LowerCaseName(lowercase_name) {}

		virtual void Parse(std::ofstream& file, const std::string& str, bool is_void) = 0;

	protected:
		void replace_strings(std::string& str, const std::string& from, const std::string& to)
		{
			if (from.empty())
				return;
			size_t start_pos = 0;
			while ((start_pos = str.find(from, start_pos)) != std::string::npos)
			{
				str.replace(start_pos, from.length(), to);
				start_pos += to.length();
			}
		}

	protected:
		const std::string m_Name;
		const std::string m_LowerCaseName;
	};
}