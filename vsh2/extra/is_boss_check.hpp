#pragma once

#include "base_class.hpp"

namespace VSH2
{
	class IsBossCheck : public IExtraParserCallback
	{
	public:
		IsBossCheck(const std::string& name, const std::string& lowercase_name) : 
			IExtraParserCallback(name, lowercase_name) { }

		bool Parse(std::ofstream& file, const std::string& str, bool is_void) override;
	};
}