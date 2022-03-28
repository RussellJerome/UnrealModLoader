#pragma once
#include <vector>
#include <Windows.h>

namespace UML
{
	namespace Memory
	{
		/*
		* This class is meant to make the ripping of functions from memory/instruction easier.
		*/
		class FunctionGrabber
		{
		public:
			/*
			* Ensures at least one aob is set for the class.
			*/
			FunctionGrabber(const char* Pattern)
			{
				FunctionInfo info;
				info.pattern = Pattern;
				info.offsetToStart = 0;
				functionLocations.push_back(info);
			}

			/*
			* Ensures at least one aob is set for the class.
			*/
			FunctionGrabber(const char* Pattern, int OffsetToStart)
			{
				FunctionInfo info;
				info.pattern = Pattern;
				info.offsetToStart = OffsetToStart;
				functionLocations.push_back(info);
			}

			/*
			* Allows you to add alternative AOBs to help prevent failure.
			*/
			void addAlternativeAob(const char* Pattern);

			/*
			* Allows you to add alternative AOBs to help prevent failure.
			*/
			void addAlternativeAob(const char* Pattern, int OffsetToStart);

			/*
			* Loops through all the AOBs provided and attempts to rip the function address from memory.
			*/
			DWORD64 ripFunction();

		private:
			/*
			* Structure that holds the aob pattern and offset needed.
			*/
			struct FunctionInfo
			{
				const char* pattern;
				int offsetToStart;
			};

			/*
			* Array that holds all the AOB information.
			*/
			std::vector<FunctionInfo> functionLocations;
		};
	};
};