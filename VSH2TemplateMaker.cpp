#include <iostream>
#include <fstream>
#include "vsh2/function_writer.hpp"

static void PrintUsage(const char* executable_name)
{
	std::cout << "Usage: " << executable_name << " [template.json, ...]\n";
}

int main(int argc, const char** argv)
{
	if (argc <= 1)
	{
		PrintUsage(argv[0]);
		return 0;
	}

	try
	{
		for (int i = 1; i < argc; i++)
		{
			std::string file_name(argv[i]);
			{
				size_t pos = file_name.rfind(".json");
				if (pos == -1 || pos != (file_name.size() - sizeof(".json") + 1))
					file_name += ".json";
			}
			std::ifstream file(file_name);
			nlohmann::json data = nlohmann::json::parse(file, nullptr, true, true);
			file.close();

			VSH2::TemplateWriter fn(data);
			fn.Write();
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Exception reported while creating template:\n" <<
			ex.what();
	}
	return 0;
}
