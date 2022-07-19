#pragma once

#include <set>
#include "extra_parser.hpp"

namespace VSH2
{
	class TemplateWriter
	{
	public:
		TemplateWriter(const nlohmann::json& data) noexcept;

		void Write();

	private:
		static std::string GetLowerCase(const std::string& str)
		{
			std::string lstr(str.size(), '\0');
			std::transform(str.begin(), str.end(), lstr.begin(), [](auto c)
				{
					return std::tolower(c);
				});
			return lstr;
		}

		static const std::string& JsonToString(const nlohmann::json& info)
		{
			return info.get_ref<const std::string&>();
		}

		std::ofstream OpenFileFromPath(const std::string& path_name);

		void CreateHookFunction(
			const std::set<std::string>& inserted_callbacks,
			const std::set<std::string>& inserted_files
		);

		void ParseFunctionArgs(
			std::ofstream& file,
			const nlohmann::json& args,
			size_t args_size
		);
		
		void ParseFunctionBody(
			std::ofstream& file,
			const nlohmann::json& data,
			bool is_void
		);

		void CreateUtilsFunctions();

	private:
		std::string m_Name, m_LowerCaseName;
		const nlohmann::json& m_Data;

		ExtraParser m_ExtraParser;
	};
}