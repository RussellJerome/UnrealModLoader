using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UnrealModLauncher.Utilities
{
    public static class TaskHelpers
    {
#pragma warning disable CS8632 // The annotation for nullable reference types should only be used in code within a '#nullable' annotations context.
        public static async void SafeFireAndForget(this Task task, Action<Exception>? onException = null, bool continueOnCapturedContext = false)
#pragma warning restore CS8632 // The annotation for nullable reference types should only be used in code within a '#nullable' annotations context.
        {
			try
			{
				await task.ConfigureAwait(continueOnCapturedContext);
			}
			catch (Exception ex) when (onException != null)
			{
				onException.Invoke(ex);
			}
		}

		public async static Task<T> WithTimeout<T>(this Task<T> task, int timeoutInMilliseconds)
		{
			var retTask = await Task.WhenAny(task, Task.Delay(timeoutInMilliseconds))
				.ConfigureAwait(false);

			return retTask is Task<T> ? task.Result : default;
		}

		public static Task<T> WithTimeout<T>(this Task<T> task, TimeSpan timeout) =>
			WithTimeout(task, (int)timeout.TotalMilliseconds);
	}
}
