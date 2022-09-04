using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UnrealModLauncher.Utilities.Commands.Exceptions
{
	public class InvalidCommandParameterException : Exception
	{
		public InvalidCommandParameterException(Type expectedType, Type actualType, Exception innerException) : base(CreateErrorMessage(expectedType, actualType), innerException)
		{

		}

		public InvalidCommandParameterException(Type expectedType, Exception innerException) : base(CreateErrorMessage(expectedType), innerException)
		{

		}

		public InvalidCommandParameterException(Type expectedType, Type actualType) : base(CreateErrorMessage(expectedType, actualType))
		{

		}

		public InvalidCommandParameterException(Type expectedType) : base(CreateErrorMessage(expectedType))
		{

		}

		static string CreateErrorMessage(Type expectedType, Type actualType) =>
			$"Invalid type for parameter. Expected Type: {expectedType}, but received Type: {actualType}";

		static string CreateErrorMessage(Type expectedType) =>
			$"Invalid type for parameter. Expected Type {expectedType}";
	}
}
