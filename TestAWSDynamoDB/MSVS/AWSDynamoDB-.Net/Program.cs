using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;



namespace AWSDynamoDB
{
    internal class Program
	{
		static void Main(string[] args)
		{
			PerformanceCheck.Test();

			Monitor.Test();

			TableNameInjection.Test();

			LocalSecondaryIndexes.Test();

			GlobalSecondaryIndexes.Test();

			HighLevel.ObjectPersistenceModel.Test();

			HighLevel.ObjectPersistenceModelBatch.Test();

			HighLevel.ObjectPersistenceModelTransact.Test();

			Document.Test();

			DocumentBatch.Test();

			LowLevel.TransactRequest.Test();

			LowLevel.QueryRequest.Test();

			LowLevel.ScanRequest.Test();

			LowLevel.ItemRequest.Test();

			LowLevel.TableRequest.Test();

			ConnectToDB.Test();

			Exception.Test();
		}
	}
}