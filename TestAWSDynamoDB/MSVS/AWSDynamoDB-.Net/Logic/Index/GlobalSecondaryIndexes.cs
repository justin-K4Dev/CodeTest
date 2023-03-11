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
	public class GlobalSecondaryIndexes
	{
		private const string TBL_PRODUCT_CATALOG = "WeatherData";

		static async Task delete_table()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();
			DynamoDBContext context = new DynamoDBContext(client);

			try
			{
				var request = new DeleteTableRequest
				{
					TableName = TBL_PRODUCT_CATALOG
				};

				await client.DeleteTableAsync(request);
				Console.WriteLine($"Delete Table - tableName:{TBL_PRODUCT_CATALOG}");

				LowLevel.ScanRequest.print_item_all_in_table_by_scan(TBL_PRODUCT_CATALOG).Wait();
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to delete Table by Exception !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
			}

			Console.ReadLine();
		}

		static async Task query_global_secondary_indexes()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
                Amazon.DynamoDBv2.Model.QueryRequest queryRequest = new Amazon.DynamoDBv2.Model.QueryRequest
				{
					TableName = "WeatherData",
					IndexName = "PrecipIndex",
					KeyConditionExpression = "#dt = :v_date and Precipitation > :v_precip",
					ExpressionAttributeNames = new Dictionary<string, string>
                    {
						{"#dt", "Date"}
					},
					ExpressionAttributeValues = new Dictionary<string, AttributeValue>
                    {
						{":v_date", new AttributeValue { S =  "2013-08-01" }},
						{":v_precip", new AttributeValue { N =  "0" }}
					},
					ScanIndexForward = true
				};

				var result = await client.QueryAsync(queryRequest);

				var items = result.Items;
				foreach (var currentItem in items)
				{
					foreach (string attr in currentItem.Keys)
					{
						Console.Write(attr + "---> ");
						if (attr == "Precipitation")
						{
							Console.WriteLine(currentItem[attr].N);
						}
						else
						{
							Console.WriteLine(currentItem[attr].S);
						}

					}
					Console.WriteLine();
				}
			}
			catch (AmazonDynamoDBException ex)
			{
				Console.WriteLine($"Failed to CreateTableAsync !!! : (AmazonDynamoDBException) errMsg:{ex.Message}");
			}
			catch (AmazonServiceException ex)
			{
				Console.WriteLine($"Failed to CreateTableAsync !!! : (AmazonServiceException) errorMsg:{ex.Message}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to CreateTableAsync !!! : (AmazonServiceException) HttpStatus:{ex.StatusCode}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to CreateTableAsync !!! : (AmazonServiceException) AWSErrCode:{ex.ErrorCode}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to CreateTableAsync !!! : (AmazonServiceException) errorType:{ex.ErrorType}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to CreateTableAsync !!! : (AmazonServiceException) requestId:{ex.RequestId}, tableName:{TBL_PRODUCT_CATALOG}");
			}
			catch (System.Exception ex)
			{
				Console.WriteLine($"Failed to CreateTableAsync !!! : (System.Exception) errMsg:{ex.Message}");
			}

			Console.ReadLine();
		}

		static async Task print_global_secondary_indexes_all()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				var response = await client.DescribeTableAsync(new DescribeTableRequest { TableName = TBL_PRODUCT_CATALOG });

				var globalSecondaryIndexes = response.Table.GlobalSecondaryIndexes;

				// This code snippet will work for multiple indexes, even though
				// there is only one index in this example.
				foreach (var gsiDescription in globalSecondaryIndexes)
				{
					Console.WriteLine("Info for index " + gsiDescription.IndexName + ":");

					foreach (KeySchemaElement kse in gsiDescription.KeySchema)
					{
						Console.WriteLine("\t" + kse.AttributeName + ": key type is " + kse.KeyType);
					}

					Projection projection = gsiDescription.Projection;
					Console.WriteLine("\tThe projection type is: " + projection.ProjectionType);

					if (projection.ProjectionType.ToString().Equals("INCLUDE"))
					{
						Console.WriteLine("\t\tThe non-key projected attributes are: "
							             + projection.NonKeyAttributes );
					}
				}
			}
			catch (AmazonDynamoDBException ex)
			{
				Console.WriteLine($"Failed to DescribeTableAsync !!! : (AmazonDynamoDBException) errorMsg:{ex.Message}");
			}
			catch (AmazonServiceException ex)
			{
				Console.WriteLine($"Failed to DescribeTableAsync !!! : (AmazonServiceException) errorMsg:{ex.Message}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to DescribeTableAsync !!! : (AmazonServiceException) HttpStatus:{ex.StatusCode}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to DescribeTableAsync !!! : (AmazonServiceException) AWSErrCode:{ex.ErrorCode}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to DescribeTableAsync !!! : (AmazonServiceException) errorType:{ex.ErrorType}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to DescribeTableAsync !!! : (AmazonServiceException) requestId:{ex.RequestId}, tableName:{TBL_PRODUCT_CATALOG}");
			}
			catch (System.Exception ex)
			{
				Console.WriteLine($"Failed to DescribeTableAsync !!! : (System.Exception) errorMsg:{ex.Message}");
			}

			Console.ReadLine();
		}

		static async Task create_global_secondary_indexes()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				// Attribute definitions
				var attributeDefinitions = new List<AttributeDefinition>()
				{
					new AttributeDefinition {
						AttributeName = "Location",
						AttributeType = "S"
					},
					new AttributeDefinition {
						AttributeName = "Date",
						AttributeType = "S"
					},
					new AttributeDefinition {
						AttributeName = "Precipitation",
						AttributeType = "N"
					},
				};

				// Table key schema
				var tableKeySchema = new List<KeySchemaElement>()
				{
					new KeySchemaElement {
						AttributeName = "Location",
						KeyType = "HASH"
					},  //Partition key
					new KeySchemaElement {
						AttributeName = "Date",
						KeyType = "RANGE"
					},	//Sort key
				};

				// GSI 정보 구성 : PrecipIndex
				var precipIndex = new GlobalSecondaryIndex
				{
					IndexName = "PrecipIndex",
					ProvisionedThroughput = new ProvisionedThroughput
					{
						ReadCapacityUnits = (long)10,
						WriteCapacityUnits = (long)1
					},
					Projection = new Projection { ProjectionType = "ALL" }
				};

				var indexKeySchema = new List<KeySchemaElement>
				{
					new KeySchemaElement {
						AttributeName = "Date",
						KeyType = "HASH"
					},  //Partition key
					new KeySchemaElement
					{
						AttributeName = "Precipitation",
						KeyType = "RANGE"
					},	//Sort key
				};

				precipIndex.KeySchema = indexKeySchema;

				var createTableRequest = new CreateTableRequest
				{
					TableName = TBL_PRODUCT_CATALOG,
					ProvisionedThroughput = new ProvisionedThroughput
					{
						ReadCapacityUnits = (long)5,
						WriteCapacityUnits = (long)1
					},
					AttributeDefinitions = attributeDefinitions,
					KeySchema = tableKeySchema,
					// GSI 설정
					GlobalSecondaryIndexes = { precipIndex }
				};

				CreateTableResponse response = await client.CreateTableAsync(createTableRequest);
				Console.WriteLine(response.TableDescription.TableName);
				Console.WriteLine(response.TableDescription.TableStatus);
			}
			catch (AmazonDynamoDBException ex)
			{
				Console.WriteLine($"Failed to CreateTableAsync !!! : (AmazonDynamoDBException) errMsg:{ex.Message}");
			}
			catch (AmazonServiceException ex)
			{
				Console.WriteLine($"Failed to CreateTableAsync !!! : (AmazonServiceException) errorMsg:{ex.Message}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to CreateTableAsync !!! : (AmazonServiceException) HttpStatus:{ex.StatusCode}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to CreateTableAsync !!! : (AmazonServiceException) AWSErrCode:{ex.ErrorCode}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to CreateTableAsync !!! : (AmazonServiceException) errorType:{ex.ErrorType}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to CreateTableAsync !!! : (AmazonServiceException) requestId:{ex.RequestId}, tableName:{TBL_PRODUCT_CATALOG}");
			}
			catch (System.Exception ex)
			{
				Console.WriteLine($"Failed to CreateTableAsync !!! : (System.Exception) errorMsg:{ex.Message}");
			}

			Console.ReadLine();
		}

		public static void Test()
		{
			//create_global_secondary_indexes().Wait();

			//print_global_secondary_indexes_all().Wait();

			//query_global_secondary_indexes().Wait();

			//delete_table().Wait();
		}
	}
}
