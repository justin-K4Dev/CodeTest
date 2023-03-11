using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using Amazon.DynamoDBv2;
using Amazon.DynamoDBv2.Model;
using Amazon.DynamoDBv2.DocumentModel;


namespace AWSDynamoDB.LowLevel
{
	public class ScanRequest
	{
		private const string TBL_PRODUCT_CATALOG = "TBL_PRODUCT_CATALOG";

		static async Task scan_item_with_ScanRequest_with_Segment(Int32 totalSegments, Int32 currSegment)
		{
			Int32 scanItemLimit = 10;

			var db_client = ConnectToDB.create_client();

			try
			{
				Console.WriteLine($"Starting to Scan by Segment... : currSegment:{currSegment}, totalSegments:{totalSegments}, tableName:{TBL_PRODUCT_CATALOG}");
				Dictionary<string, AttributeValue> lastEvaluatedKey = null;
				int totalScannedItemCount = 0;
				int totalScanRequestCount = 0;

				do
				{
					var request = new Amazon.DynamoDBv2.Model.ScanRequest
					{
						TableName = TBL_PRODUCT_CATALOG,
						Limit = scanItemLimit,
						ExclusiveStartKey = lastEvaluatedKey,
						Segment = currSegment,
						TotalSegments = totalSegments
					};

					var response = await db_client.ScanAsync(request);

					lastEvaluatedKey = response.LastEvaluatedKey;
					totalScanRequestCount++;
					totalScannedItemCount += response.ScannedCount;

					foreach (var each in response.Items)
					{
						Console.WriteLine($"Scanned Item with Title:{each["Title"].S} : currSegment:{currSegment}");
					}
				} while (lastEvaluatedKey.Count != 0);

				Console.WriteLine( $"Completed Scan Segment : currSegment:{currSegment}"
					             + $", totalScanReqCount:{totalScanRequestCount}, totalScannedItemCount:{totalScannedItemCount}, tableName:{TBL_PRODUCT_CATALOG}");
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to scan in Table !!! : errMsg:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
			}

			Console.ReadLine();
		}

		static async Task scan_parallel_with_Segment()
		{
			Int32 totalSegments = 5;

			var db_client = ConnectToDB.create_client();

			try
			{
				Console.WriteLine("\n*** Creating {0} Parallel Scan Tasks to scan {1}", totalSegments, TBL_PRODUCT_CATALOG);
				Task[] tasks = new Task[totalSegments];
				for (int segment = 0; segment < totalSegments; segment++)
				{
					int curr_segment = segment;
					Task task = Task.Factory.StartNew( async delegate
					{
						await scan_item_with_ScanRequest_with_Segment(totalSegments, curr_segment);
					});

					tasks[segment] = task;
				}

				Console.WriteLine("All scan tasks are created, waiting for them to complete.");
				Task.WaitAll(tasks);

				Console.WriteLine("All scan tasks are completed.");
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to scan in Table !!! : errMsg:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
			}

			Console.ReadLine();
		}

		static async Task scan_item_with_ScanRequest_with_ExpressionAttributeValues()
		{
			var db_client = ConnectToDB.create_client();

			try
			{
				Dictionary<string, AttributeValue> lastKeyEvaluated = null;
				do
				{
					var request = new Amazon.DynamoDBv2.Model.ScanRequest
					{
						TableName = TBL_PRODUCT_CATALOG,

						Limit = 2,
						ExclusiveStartKey = lastKeyEvaluated,

						ExpressionAttributeValues = new Dictionary<string, AttributeValue> {
							{ ":val", new AttributeValue { N = "70000" } }
						},

						FilterExpression = "Price < :val",
						ProjectionExpression = "Id, Title, Price"
					};

					var response = await db_client.ScanAsync(request);

					foreach (var each in response.Items)
					{
						Console.WriteLine("\nScanThreadTableUsePaging - printing.....");
						Common.print_item(each);
					}
					lastKeyEvaluated = response.LastEvaluatedKey;
				} while (lastKeyEvaluated != null && lastKeyEvaluated.Count != 0);
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to scan in Table !!! : errMsg:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
			}

			Console.ReadLine();
		}

		public static async Task print_item_all_in_table_by_scan(string tableName)
		{
			var db_client = ConnectToDB.create_client();

			try
			{
				var request = new Amazon.DynamoDBv2.Model.ScanRequest
				{
					TableName = tableName
				};

				var response = await db_client.ScanAsync(request);

				foreach (Dictionary<string, AttributeValue> each in response.Items)
				{
					Common.print_item(each);
				}

				Console.WriteLine($"Scaned in Table - tableName:{tableName}");
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to scan in Table !!! : errMsg:{e.Message}, tableName:{tableName}");
			}

			Console.ReadLine();
		}

		public static void Test()
		{
			//print_item_all_in_table_by_scan(TBL_PRODUCT_CATALOG).Wait();

			//scan_item_with_ScanRequest_with_ExpressionAttributeValues().Wait();

			//scan_parallel_with_Segment().Wait();
		}
	}
}
