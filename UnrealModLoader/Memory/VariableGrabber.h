#pragma once
#include <vector>
#include <Windows.h>

namespace UML
{
	namespace Memory
	{
		/*
		* This class is meant to make the ripping of variables from memory/instruction easier.
		*/
		class VariableGrabber
		{
		public:
			/*
			* Ensures at least one aob is set for the class.
			*/
			VariableGrabber(const char* aob, int firstOpCodes, int totalByteInstruction)
			{
				VariableInfo info;
				info.aob = aob;
				info.FirstOpCodes = firstOpCodes;
				info.TotalByteInstruction;
				variableLocations.push_back(info);
			}

			/*
			* Allows you to add alternative AOBs to help prevent failure.
			*/
			void addAlternativeAob(const char* aob, int firstOpCodes, int totalByteInstruction);

			/*
			* Loops through all the AOBs provided and attempts to rip the address from memory.
			*/
			DWORD64 ripVariable();

		private:
			/*
			* Structure that holds the aob pattern and opcodes needed.
			*/
			struct VariableInfo
			{
				const char* aob;
				int FirstOpCodes;
				int TotalByteInstruction;
			};

			/*
			* Array that holds all the AOB information.
			*/
			std::vector<VariableInfo> variableLocations;
		};
	};
};
