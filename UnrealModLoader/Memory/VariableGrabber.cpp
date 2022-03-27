#include "VariableGrabber.h"
#include "../Utilities/Utility.h"

namespace UML
{
	namespace Memory
	{
		void VariableGrabber::addAlternativeAob(const char* aob, int firstOpCodes, int totalByteInstruction)
		{
			VariableInfo info;
			info.aob = aob;
			info.FirstOpCodes = firstOpCodes;
			info.TotalByteInstruction;
			variableLocations.push_back(info);
		}

		DWORD64 VariableGrabber::ripVariable()
		{
			if (variableLocations.size() > 0)
			{
				for (size_t i = 0; i < variableLocations.size(); i++)
				{
					auto varlocation = variableLocations[i];
					auto Pattern = UML::Utility::FindPattern(varlocation.aob);
					if (Pattern)
					{
						auto varOffset = *reinterpret_cast<uint32_t*>(Pattern + varlocation.FirstOpCodes);
						auto var = (DWORD64)(Pattern + varlocation.TotalByteInstruction + varOffset);
						if (var != 0)
						{
							return (DWORD64)var;
						}
					}
				}
			}
			return 0;
		}
	};
};