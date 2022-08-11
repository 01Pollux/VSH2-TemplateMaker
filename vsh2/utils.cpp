
#include "function_writer.hpp"

namespace VSH2
{
	void TemplateWriter::CreateUtilsFunctions()
	{
		std::ofstream file("vsh2_" + m_LowerCaseName + ".sp");

		// create enum struct
		file << 
			"#include vsh2_" << m_LowerCaseName << "_callbacks.sp\n\n"

			"enum struct " << m_Name << "Config\n{\n"
			"\tint boss_id;\n"
			"\tVSH2GameMode gm;\n"
			"\tConfigMap cfg;\n\n";

		file << 
			"\tvoid Register()\n\t{\n"
				"\t\tthis.cfg = new ConfigMap(\"configs/saxton_hale/boss_cfgs/" << m_LowerCaseName << "_boss.cfg\");\n"

				"\t\tif (template_boss.cfg == null)\n\t\t{\n"
					"\t\t\tLogError(\"[VSH2] ERROR :: **** couldn't find 'configs/saxton_hale/boss_cfgs/" <<
						m_LowerCaseName << "_boss.cfg'. Failed to register Boss module. ****\");\n"
					"\t\t\treturn;\n\t\t}\n"
				
				"\t\tchar plugin_name_str[MAX_BOSS_NAME_SIZE];\n"
				"\t\tthis.cfg.Get(\"boss.plugin name\", plugin_name_str, sizeof(plugin_name_str));\n"
				"\t\tthis.boss_id = VSH2_RegisterPlugin(plugin_name_str);\n"
				"\t\tVSH2_Hook" << m_Name << "();\n\t}\n";
			;

			file << "\n\tvoid Unregister()\n\t{\n"
				"\t\tVSH2_Unhook" << m_Name << "();\n"
				"\t\tDeleteCfg(this.cfg);\n"
				"\t}\n";

		file << "}\n";
		file << m_Name << "Config g" << m_Name << ";\n\n";


		// create bool IsTemplate(player)
		file << "bool VSH2_Is" << m_Name << "(const VSH2Player player)\n{\n";
		file << "\treturn g" << m_Name << ".boss_id == player.GetPropInt(\"iBossType\");\n}\n";
	}
}
