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


namespace AWSDynamoDB.LowLevel
{
	public class BatchRequest
	{
		static async Task batch_read_with_BatchGetItemRequest(AmazonDynamoDBClient client, BatchGetItemRequest request)
		{
			BatchGetItemResponse response;

			try
			{
				Int32 callCount = 0;
				do
				{
					Console.WriteLine("request BatchGetItemRequest by async");
					response = await client.BatchGetItemAsync(request);
					callCount++;

					// Check the response.
					var responses = response.Responses; // Attribute list in the response.

					foreach (var tableResponse in responses)
					{
						var tableResults = tableResponse.Value;
						Console.WriteLine($"Items get from table {tableResponse.Key}");
						foreach (var each in tableResults)
						{
							Common.print_item(each);
						}
					}

					// Any unprocessed keys? could happen if you exceed ProvisionedThroughput or some other error.
					Dictionary<string, KeysAndAttributes> unprocessedKeys = response.UnprocessedKeys;
					foreach (var unprocessedTableKeys in unprocessedKeys)
					{
						// Print table name.
						Console.WriteLine(unprocessedTableKeys.Key);
						// Print unprocessed primary keys.
						foreach (var key in unprocessedTableKeys.Value.Keys)
						{
							Common.print_item(key);
						}
					}

					request.RequestItems = unprocessedKeys;
				} while (response.UnprocessedKeys.Count > 0);

				Console.WriteLine($"Total Batch BatchGetItemAsync() calls count:{callCount}");
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to batch Get by BatchGetItemAsync !!! : error:{e.Message}");
			}
		}

		static async Task batch_write_with_BatchWriteItemRequest(AmazonDynamoDBClient client, BatchWriteItemRequest request)
		{
			BatchWriteItemResponse response;

			try
			{
				Int32 callCount = 0;
				do
				{
					Console.WriteLine("request BatchWriteItemRequest by async");
					response = await client.BatchWriteItemAsync(request);
					callCount++;

					// Check the response.
					var tableConsumedCapacities = response.ConsumedCapacity;
					var unprocessed = response.UnprocessedItems;

					Console.WriteLine("response BatchWriteItemResponse");
					foreach (var tableConsumedCapacity in tableConsumedCapacities)
					{
						Console.WriteLine($"TableConsumedCapacity:{tableConsumedCapacity.TableName} - CapacityUnits:{tableConsumedCapacity.CapacityUnits}");
					}

					Console.WriteLine("Unprocessed");
					foreach (var unp in unprocessed)
					{
						Console.WriteLine($"Key:{unp.Key}, Count:{unp.Value.Count}");
					}
					Console.WriteLine();

					// For the next iteration, the request will have unprocessed items.
					request.RequestItems = unprocessed;
				} while (response.UnprocessedItems.Count > 0);

				Console.WriteLine($"Total Batch BatchWriteItemAsync() calls count:{callCount}");
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to batch Write by BatchWriteItemAsync !!! : error:{e.Message}");
			}
		}

		static async Task batch_read_by_BatchRequest()
		{
			var client = ConnectToDB.create_client();

			try
			{
				var request = new BatchGetItemRequest
				{
					RequestItems = new Dictionary<string, KeysAndAttributes>()
					{
						{
							HighLevel.ObjectPersistenceModel.TBL_FORUM, new KeysAndAttributes
							{
								Keys = new List<Dictionary<string, AttributeValue>>()
								{
									new Dictionary<string, AttributeValue>()
									{
										{ "Name", new AttributeValue { S = "S3-forum" } }
									},
									new Dictionary<string, AttributeValue>()
									{
										{ "Name", new AttributeValue { S = "Test BatchWrite Forum" } }
									}
								}
							}
						},
						{
							HighLevel.ObjectPersistenceModel.TBL_THREAD, new KeysAndAttributes
							{
								Keys = new List<Dictionary<string, AttributeValue> >()
								{
									new Dictionary<string, AttributeValue>()
									{
										{ "ForumName", new AttributeValue { S = "Amazon-S3-forum" } },
										{ "Subject", new AttributeValue { S = "My sample question" } }
									},
									new Dictionary<string, AttributeValue>()
									{
										{ "ForumName", new AttributeValue { S = "S3-forum" } },
										{ "Subject", new AttributeValue { S = "My sample question" } }
									},
								}
							}
						}
					}
				};

				await batch_read_with_BatchGetItemRequest(client, request);
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to batch Get by BatchGetItemRequest !!! : error:{e.Message}");
			}

			Console.ReadLine();
		}

		static async Task batch_write_by_BatchRequest()
		{
			var client = ConnectToDB.create_client();

			try
			{
				var request = new BatchWriteItemRequest
				{
					ReturnConsumedCapacity = "TOTAL",
					RequestItems = new Dictionary<string, List<WriteRequest>>
					{
						{
							HighLevel.ObjectPersistenceModel.TBL_FORUM, new List<WriteRequest>
							{
								new WriteRequest
								{
									PutRequest = new PutRequest
									{
										Item = new Dictionary<string, AttributeValue>
										{
											{ "Name", new AttributeValue { S = "S3-forum" } },
											{ "Threads", new AttributeValue { N = "0" } }
										}
									}
								}
							}
						},
						{
							HighLevel.ObjectPersistenceModel.TBL_THREAD, new List<WriteRequest>
							{
								new WriteRequest
								{
									PutRequest = new PutRequest
									{
										Item = new Dictionary<string, AttributeValue>
										{
											{ "ForumName", new AttributeValue { S = "S3-forum" } },
											{ "Subject", new AttributeValue { S = "My sample question" } },
											{ "Message", new AttributeValue { S = "Message Text !!!" } },
											{ "KeywordTags", new AttributeValue { SS = new List<string> { "S3", "Bucket" } } }
										}
									}
								},
								new WriteRequest
								{
									// For the operation to delete an item, if you provide a primary key value
									// that does not exist in the table, there is no error, it is just a no-op.
									DeleteRequest = new DeleteRequest
									{
										Key = new Dictionary<string, AttributeValue>()
										{
											{ "ForumName",  new AttributeValue { S = "S3-forum" } },
											{ "Subject", new AttributeValue { S = "My sample question" } }
										}
									}
								}
							}
						}
					}
				};

				await batch_write_with_BatchWriteItemRequest(client, request);
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to batch Write by BatchWriteItemRequest !!! : error:{e.Message}");
			}

			Console.ReadLine();
		}

		public static void Test()
		{
			//Common.create_table_all(BillingMode.PROVISIONED).Wait();

			//batch_write_by_BatchRequest().Wait();

			//batch_read_by_BatchRequest().Wait();
		}
	}
}
