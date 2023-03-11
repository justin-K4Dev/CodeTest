using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;



namespace NLogDotNet
{
	class Program
	{
		static void Main(string[] args)
		{
			Advanced.Test();

			Basic.Test();

			NLog.LogManager.Shutdown();
		}
	}
}