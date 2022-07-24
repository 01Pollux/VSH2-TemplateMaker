#pragma once

#include "extra_callbacks.hpp"

namespace VSH2
{
	class IncludeFile : public IExtraParserCallback
	{
	public:
		IncludeFile(const std::string& name, const std::string& lowercase_name) :
			IExtraParserCallback(name, lowercase_name) { }

		void Parse(std::ofstream& file, const std::string& str, bool is_void) override;
	};
}