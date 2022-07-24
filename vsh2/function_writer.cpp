#include <fstream>
#include "function_writer.hpp"

namespace VSH2
{
	TemplateWriter::TemplateWriter(const nlohmann::json& data) noexcept :
		m_Name(data["name"]),
		m_LowerCaseName(GetLowerCase(m_Name)),
		m_Data(data),
		m_ExtraParser(m_Name, m_LowerCaseName)
	{}

	void TemplateWriter::Write()
	{
		std::map<std::string, std::ofstream> loaded_files;

		std::set<std::string> inserted_callbacks;
		std::set<std::string> inserted_files;

		for (auto& data : m_Data["callbacks"])
		{
			const std::string& return_name = JsonToString(data["return"]);
			bool is_void = return_name == "void";

			const std::string& file_name = JsonToString(data["file"]);
			inserted_files.emplace(file_name);


			const auto& args = data["args"];
			size_t args_size = args.size();


			auto iter = loaded_files.find(file_name);
			if (iter == loaded_files.end())
				iter = loaded_files.emplace(file_name, OpenFileFromPath(file_name)).first;

			std::ofstream& file = iter->second;

			for (auto& func_name : data["forwards"])
			{
				const std::string& func_str = JsonToString(func_name);
				inserted_callbacks.emplace(func_str);
				
				file << return_name << " " << m_Name << "_" << func_str << "(";

				ParseFunctionArgs(file, args, args_size);
				ParseFunctionBody(file, data, is_void);
			}
		}

		CreateHookFunction(inserted_callbacks, inserted_files);
		CreateUtilsFunctions();
	}


	void TemplateWriter::CreateHookFunction(
		const std::set<std::string>& inserted_callbacks,
		const std::set<std::string>& inserted_files
	)
	{
		if (inserted_files.empty())
			return;

		std::ofstream file("vsh2_" + m_LowerCaseName + "_callbacks.sp");
		for (const std::string& cur_file : inserted_files)
			file << "#include \"" << cur_file << "\"\n";
		file << '\n';

		for (auto type : {
			"Hook", "Unhook",
			})
		{
			file << "void VSH2_" << type << m_Name <<"()\n{";
			if (inserted_callbacks.empty())
				file << " }\n";
			else
			{
				file << '\n';
				for (const std::string& callback_type : inserted_callbacks)
					file << "\tVSH2_" << type << "(" << callback_type << ", " << m_Name << "_" << callback_type << ");\n";
			}
			file << "}\n\n";
		}
	}


	void TemplateWriter::ParseFunctionArgs(
		std::ofstream& file, 
		const nlohmann::json& args,
		size_t args_size
	)
	{
		switch (args_size)
		{
		case 0:
			file << ")";
			break;

		case 1:
		case 2:
			file << JsonToString(args[0]);
			if (args_size != 1)
				file << ", " << JsonToString(args[1]);

			file << ")";
			break;

		default:
			file << '\n';
			for (size_t args_idx = 0; args_idx < args_size - 1; args_idx++)
				file << '\t' << JsonToString(args[args_idx]) << ", \n";

			file << '\t' << JsonToString(args[args_size - 1]) << '\n';

			file << ")";
			break;
		}

	}


	void TemplateWriter::ParseFunctionBody(
		std::ofstream& file,
		const nlohmann::json& data,
		bool is_void
	)
	{
		file << "\n{";

		m_ExtraParser.TryParse(file, data, is_void);
		
		if (!is_void)
			file << "\n\treturn Plugin_Continue;\n";

		file << "}\n\n";
	}


	std::ofstream TemplateWriter::OpenFileFromPath(const std::string& path_name)
	{
		std::filesystem::path path(path_name);
		path.remove_filename();

		if (!std::filesystem::exists(path))
			std::filesystem::create_directory(path);

		return std::ofstream(path_name);
	}
}
