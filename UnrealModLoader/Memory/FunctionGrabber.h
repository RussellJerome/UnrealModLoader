#pragma once
#include <vector>
#include <Windows.h>

namespace UML
{
	namespace Memory
	{
		class FunctionGrabber
		{
		public:
			FunctionGrabber(const char* Pattern)
			{
				FunctionInfo info;
				info.pattern = Pattern;
				info.offsetToStart = 0;
				functionLocations.push_back(info);
			}
			FunctionGrabber(const char* Pattern, int OffsetToStart)
			{
				FunctionInfo info;
				info.pattern = Pattern;
				info.offsetToStart = OffsetToStart;
				functionLocations.push_back(info);
			}

			void addAlternativeAob(const char* Pattern);
			void addAlternativeAob(const char* Pattern, int OffsetToStart);

			DWORD64 ripFunction();

		private:
			struct FunctionInfo
			{
				const char* pattern;
				int offsetToStart;
			};
			std::vector<FunctionInfo> functionLocations;
		};
	};
};