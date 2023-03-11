using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using Amazon.Runtime;
using Amazon.DynamoDBv2;
using Amazon.DynamoDBv2.Model;
using Amazon.DynamoDBv2.DataModel;
using Amazon.DynamoDBv2.DocumentModel;


namespace AWSDynamoDB
{
	public class Exception
	{
		private const string TBL_PRODUCT_CATALOG = "TBL_PRODUCT_CATALOG";
		private const Int32 PARTITION_KEY = 1000;

		static async void basic_exception()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				var table = Amazon.DynamoDBv2.DocumentModel.Table.LoadTable(client, TBL_PRODUCT_CATALOG);
				var to_find_key = PARTITION_KEY;

				var document = await table.GetItemAsync(to_find_key);
				if (null == document)
				{
					Console.WriteLine($"Not found Item in Table : tableName:{TBL_PRODUCT_CATALOG}");
					return;
				}

				Console.WriteLine($"Success Table.GetItemAsync : toPartitionKey:{to_find_key}, tableName:{TBL_PRODUCT_CATALOG}");

				Common.print_document(document);
			}
			catch (AmazonDynamoDBException ex)
			{ 
				Console.WriteLine($"Failed to Table.GetItemAsync !!! : (AmazonDynamoDBException) errMsg:{ex.Message}"); 
			}
			catch (AmazonServiceException ex)
			{ 
				Console.WriteLine($"Failed to Table.GetItemAsync !!! : (AmazonServiceException) errMsg:{ex.Message}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to Table.GetItemAsync !!! : (AmazonServiceException) HttpStatus:{ex.StatusCode}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to Table.GetItemAsync !!! : (AmazonServiceException) AWSErrCode:{ex.ErrorCode}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to Table.GetItemAsync !!! : (AmazonServiceException) errorType:{ex.ErrorType}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to Table.GetItemAsync !!! : (AmazonServiceException) requestId:{ex.RequestId}, tableName:{TBL_PRODUCT_CATALOG}");
			}
			catch (System.Exception ex)
			{ 
				Console.WriteLine($"Failed to Table.GetItemAsync !!! : (System.Exception) errMsg:{ex.Message}"); 
			}

			Console.ReadLine();
		}

		public static void Test()
		{
			//basic_exception().Wait();
		}
	}
}
