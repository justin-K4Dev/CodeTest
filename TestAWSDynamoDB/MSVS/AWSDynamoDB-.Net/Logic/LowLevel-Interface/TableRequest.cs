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
	/*
		DynamoDB Low-Level API
	*/

	public class TableRequest
	{
		private const string TABLE_STATUS_UNKOWN = "UNKNOWN";
		private const string TABLE_STATUS_ACTIVE = "ACTIVE";

		private const string TBL_PRODUCT_CATALOG = "TBL_PRODUCT_CATALOG";


		static async Task delete_table_by_DeleteTableRequest()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				var request = new DeleteTableRequest
				{
					TableName = TBL_PRODUCT_CATALOG
				};

				await client.DeleteTableAsync(request);
				Console.WriteLine($"Delete Table - tableName:{TBL_PRODUCT_CATALOG}");

				ScanRequest.print_item_all_in_table_by_scan(TBL_PRODUCT_CATALOG).Wait();
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to delete Table by Exception !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
			}

			Console.ReadLine();
		}

		static async Task wait_until_table_ready(AmazonDynamoDBClient client, string tableName)
		{
			string status = null;

			// Let us wait until table is created. Call DescribeTable.
			do
			{
				System.Threading.Thread.Sleep(5000); // Wait 5 seconds.
				try
				{
					var response = await client.DescribeTableAsync(new DescribeTableRequest
					{
						TableName = TBL_PRODUCT_CATALOG
					});

					Console.WriteLine( $"Table name: {0}, status: {1}",
									   response.Table.TableName,
									   response.Table.TableStatus );

					status = response.Table.TableStatus;
				}
				catch (ResourceNotFoundException)
				{
					// DescribeTable is eventually consistent. So you might
					// get resource not found. So we handle the potential exception.
				}
			} while (status != "ACTIVE");
		}
	
		static async Task update_table_by_UpdateTableRequest()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				var request = new UpdateTableRequest()
				{
					TableName = TBL_PRODUCT_CATALOG,

					ProvisionedThroughput = new ProvisionedThroughput()
					{
						ReadCapacityUnits = 6,
						WriteCapacityUnits = 7
					}
				};

				var response = await client.UpdateTableAsync(request);
				var desc = response.TableDescription;
				Console.WriteLine($"Update table name:{desc.TableName}, status:{desc.TableStatus}");

				await wait_until_table_ready(client, TBL_PRODUCT_CATALOG);

				ScanRequest.print_item_all_in_table_by_scan(TBL_PRODUCT_CATALOG).Wait();
			}
			catch(System.Exception e)
			{
				Console.WriteLine($"Failed to update table !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
			}

			Console.ReadLine();
		}

		static async Task<bool> hasTable(AmazonDynamoDBClient client, string tableName)
		{
			bool is_found = false;

			try
			{
				var response = await client.ListTablesAsync();
				is_found = response.TableNames.Contains(tableName);
			}
			catch (System.Exception e)
			{
				return is_found;
			}

			return is_found;
		}

		static async Task<string> getTableStatus(AmazonDynamoDBClient client, string tableName)
		{
			try
			{
				var response = await client.DescribeTableAsync(new DescribeTableRequest
				{
					TableName = tableName
				});

				return response?.Table.TableStatus;
			}
			catch (System.Exception e)
			{
				return TABLE_STATUS_UNKOWN;
			}
		}

		public static async Task<List<TableDescription>> get_table_desc_all_by_ListTablesRequest(AmazonDynamoDBClient client)
		{
			var has_table_descs = new List<TableDescription>();

			try
			{
				string last_table_name_evaluated = null;
				do
				{
					var request_tables = new ListTablesRequest
					{
						Limit = 2,
						ExclusiveStartTableName = last_table_name_evaluated
					};

					var response = await client.ListTablesAsync(request_tables);
					foreach (string name in response.TableNames)
					{
						var request = new ListTablesRequest
						{
							Limit = 2,
							ExclusiveStartTableName = last_table_name_evaluated
						};

						var response_table = await client.DescribeTableAsync(new DescribeTableRequest
						{
							TableName = name
						});

						var description = response_table.Table;
						has_table_descs.Add(description);
					}

					last_table_name_evaluated = response.LastEvaluatedTableName;
				} while (last_table_name_evaluated != null);

				return has_table_descs;
			}
			catch (System.Exception e)
			{
				return has_table_descs;
			}
		}

		public static async Task<bool> isCreateableTable(AmazonDynamoDBClient client, string tableName)
		{
			bool is_found = await hasTable(client, tableName);
			if (true == is_found)
			{
				return false;
			}

			var curr_status = await getTableStatus(client, tableName);
			if (TABLE_STATUS_UNKOWN != curr_status)
			{
				return false;
			}

			return true;
		}

		static async Task print_table_desc_all()
		{
			var db_client = ConnectToDB.create_client();

			var table_decss = await get_table_desc_all_by_ListTablesRequest(db_client);

			foreach (var desc in table_decss)
			{
				Console.WriteLine("Table Name: {0}", desc.TableName);
				Console.WriteLine("item Count: {0}", desc.ItemCount);
				Console.WriteLine("Provision Throughput (reads/sec): {0}", desc.ProvisionedThroughput.ReadCapacityUnits);
				Console.WriteLine("Provision Throughput (writes/sec): {0}", desc.ProvisionedThroughput.WriteCapacityUnits);
			}

			Console.WriteLine($"Loaded Table All Count:{table_decss.Count}");

			Console.ReadLine();
		}

		public static async Task create_table_by_CreateTableRequest(BillingMode billingMode)
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				// 테이블 생성 및 메타 데이터 설정 하기
				{
					var is_creatable = await isCreateableTable(client, TBL_PRODUCT_CATALOG);
					if (false == is_creatable)
					{
						Console.WriteLine($"Failed to create Table !!! : tableName:{TBL_PRODUCT_CATALOG}");
						return;
					}

					CreateTableRequest requestToCreate = null;

					if (true == billingMode.isOnDemand())
					{
						requestToCreate = new CreateTableRequest()
						{
							TableName = TBL_PRODUCT_CATALOG,

							KeySchema = new List<KeySchemaElement>() {
								new KeySchemaElement
								{
									AttributeName = "Id",
									KeyType = KeyType.HASH
								}
							},

							AttributeDefinitions = new List<AttributeDefinition>() {
								new AttributeDefinition
								{
									AttributeName = "Id",
									AttributeType = ScalarAttributeType.N
								}
							},

							BillingMode = billingMode
						};
					}
					else
					{
						requestToCreate = new CreateTableRequest()
						{
							TableName = TBL_PRODUCT_CATALOG,

							KeySchema = new List<KeySchemaElement>() {
								new KeySchemaElement
								{
									AttributeName = "Id",
									KeyType = KeyType.HASH
								},
							},

							AttributeDefinitions = new List<AttributeDefinition>() {
								new AttributeDefinition
								{
									AttributeName = "Id",
									AttributeType = ScalarAttributeType.N
								},
							},

							ProvisionedThroughput = new ProvisionedThroughput()
							{
								ReadCapacityUnits = 10,
								WriteCapacityUnits = 5
							}
						};
					}

					var response = await client.CreateTableAsync(requestToCreate);

					var tableDescription = response.TableDescription;
					Console.WriteLine( $"TableName:{0}, Status:{1}, ReadCapacityUnits:{2}, WriteCapacityUnits:{3}"
									 , tableDescription.TableName
									 , tableDescription.TableStatus
									 , tableDescription.ProvisionedThroughput.ReadCapacityUnits
									 , tableDescription.ProvisionedThroughput.WriteCapacityUnits);

					string status = tableDescription.TableStatus;
					Console.WriteLine(TBL_PRODUCT_CATALOG + " - " + status);

					ScanRequest.print_item_all_in_table_by_scan(TBL_PRODUCT_CATALOG	).Wait();
				}
			}
			catch(System.Exception e)
			{
				Console.WriteLine(TBL_PRODUCT_CATALOG + " - " + e);
			}

			Console.ReadLine();
		}

		public static async Task create_global_table_by_UpdateTableRequest()
		{
			var other_region_name = "us-east-1";

			AmazonDynamoDBClient client = ConnectToDB.create_client_by_region(other_region_name);

			try
			{
				// 테이블 생성 및 메타 데이터 설정 하기
				{
					var is_creatable = await isCreateableTable(client, TBL_PRODUCT_CATALOG);
					if (false == is_creatable)
					{
						Console.WriteLine($"Failed to create Global Table !!! : tableName:{TBL_PRODUCT_CATALOG}, regionName:{other_region_name}");
						return;
					}

					var request = new UpdateTableRequest()
					{
						TableName = TBL_PRODUCT_CATALOG,

						ReplicaUpdates = new List<ReplicationGroupUpdate>()
						{
							new ReplicationGroupUpdate()
							{
								Create = new CreateReplicationGroupMemberAction()
								{
									RegionName = other_region_name
								}
							}
						}
					};

					var response = await client.UpdateTableAsync(request);
					var desc = response.TableDescription;
					Console.WriteLine($"Create Global table name:{desc.TableName}, status:{desc.TableStatus}, regionName:{other_region_name}");

					await wait_until_table_ready(client, TBL_PRODUCT_CATALOG);

					ScanRequest.print_item_all_in_table_by_scan(TBL_PRODUCT_CATALOG).Wait();
				}
			}
			catch (System.Exception e)
			{
				Console.WriteLine(TBL_PRODUCT_CATALOG + " - " + e);
			}

			Console.ReadLine();
		}

		public static void Test()
		{
			//create_global_table_by_UpdateTableRequest().Wait();

			//create_table_by_CreateTableRequest(BillingMode.PROVISIONED).Wait();

			//update_table_by_UpdateTableRequest().Wait();

			//delete_table_by_DeleteTableRequest().Wait();

			//print_table_desc_all().Wait();
		}
	}
}
