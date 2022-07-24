#pragma once

#include "json.hpp"
#include "extra/extra_callbacks.hpp"

namespace VSH2
{
	class ExtraParser
	{
	public:
		ExtraParser(const std::string& name, const std::string& lowercase_name);

		void TryParse(std::ofstream& file, const nlohmann::json& data, bool is_void);

	private:
		std::pair<size_t, size_t> SplitString(const std::string& str);

		template<typename _Ty>
		static std::unique_ptr<IExtraParserCallback> make_callback(
			const std::string& name,
			const std::string& lowercase_name
		)
		{
			return std::unique_ptr<IExtraParserCallback>(
				std::make_unique<_Ty>(name, lowercase_name)
				);
		}

	private:
		std::map<std::string, std::unique_ptr<IExtraParserCallback>> m_Callbacks;
	};
}