using Profiler;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace CSharp
{
	class Program
	{
		static void Main(string[] args)
		{
			AdvancedStep.Record.Test();
			AdvancedStep.AutoPropertyInitializer.Test();
			AdvancedStep.DictionaryInitializer.Test();
			AdvancedStep.ExpressionBodied.Test();
			AdvancedStep.NameOf.Test();
			AdvancedStep.NullConditionalOperator.Test();
			AdvancedStep.StringInterpolation.Test();
			AdvancedStep.UsingStatic.Test();

			MultiThread.Tasking.Test();
			MultiThread.PeriodicTimer.Test();
			MultiThread.Parallel.Test();
			MultiThread.AwaitInCatchBlock.Test();

			Performance.ForProfiler.Test();
			Performance.ConcurrencyAPIComparison.Test();
		}
	}
}
