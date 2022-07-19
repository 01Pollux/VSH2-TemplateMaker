
#include "extra_parser.hpp"
#include "extra/is_boss_check.hpp"
#include "extra/include_file.hpp"

namespace VSH2
{
	ExtraParser::ExtraParser(const std::string& name, const std::string& lowercase_name)
	{
		m_Callbacks.emplace("is_boss", make_callback<IsBossCheck>(name, lowercase_name));
		m_Callbacks.emplace("include", make_callback<IncludeFile>(name, lowercase_name));
	}

	bool ExtraParser::TryParse(std::ofstream& file, const nlohmann::json& data, bool is_void)
	{
		auto extra = data.find("extra");
		if (extra == data.end())
			return false;

		for (const auto& info : *extra)
		{
			const std::string& str = info.get_ref<const std::string&>();

			auto [tag_pos, value_pos] = SplitString(str);

			std::string tag = str.substr(0, tag_pos);

			auto callback = m_Callbacks.find(tag);
			if (callback != m_Callbacks.end())
			{
				std::string value = str.substr(value_pos);
				return callback->second->Parse(file, value, is_void);
			}
		}

		return false;
	}

	std::pair<size_t, size_t> ExtraParser::SplitString(const std::string& str)
	{
		std::pair<size_t, size_t> tag_value = {};

		size_t tag_pos = str.find(':');
		if (tag_pos != str.npos)
		{
			tag_value.first = tag_pos;

			size_t value_pos = tag_pos + 1;
			for (; value_pos < str.size(); value_pos++)
			{
				switch (str[value_pos])
				{
				case ' ':
				case '\t':
					continue;
				}

				tag_value.second = value_pos;
				break;
			}
		}
		return tag_value;
	}
}