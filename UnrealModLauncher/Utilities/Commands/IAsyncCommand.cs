using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace UnrealModLauncher.Utilities.Commands
{
	public interface IAsyncCommand : ICommand
	{
		Task ExecuteAsync();

		void RaiseCanExecuteChanged();
	}

	public interface IAsyncCommand<T> : ICommand
	{
		Task ExecuteAsync(T parameter);

		void RaiseCanExecuteChanged();
	}
}
