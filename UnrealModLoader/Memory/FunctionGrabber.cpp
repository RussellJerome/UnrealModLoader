#include "FunctionGrabber.h"
#include "Memory.h"
#include "../Utilities/Utility.h"
#include <iostream>
namespace UML
{
	namespace Memory
	{
		void FunctionGrabber::addAlternativeAob(const char* Pattern)
		{
			FunctionInfo info;
			info.pattern = Pattern;
			info.offsetToStart = 0;
			functionLocations.push_back(info);
		}

		void FunctionGrabber::addAlternativeAob(const char* Pattern, int OffsetToStart)
		{
			FunctionInfo info;
			info.pattern = Pattern;
			info.offsetToStart = OffsetToStart;
			functionLocations.push_back(info);
		}

		DWORD64 FunctionGrabber::ripFunction()
		{
			if (functionLocations.size() > 0)
			{
				for (size_t i = 0; i < functionLocations.size(); i++)
				{
					auto funcLocation = functionLocations[i];
					if (funcLocation.offsetToStart == 0)
					{
						auto funcpat = (DWORD64)Utility::FindPattern(funcLocation.pattern);
						if (funcpat)
						{
							return funcpat;
						}
					}
					else
					{
						auto Function = Utility::FindPattern(funcLocation.pattern);
						if (Function != nullptr)
						{
							Function += funcLocation.offsetToStart;
							return (DWORD64)GetAddressPTR(Function, 0x1, 0x5);
						}
					}
				}
			}
			return 0;
		}
	};
};