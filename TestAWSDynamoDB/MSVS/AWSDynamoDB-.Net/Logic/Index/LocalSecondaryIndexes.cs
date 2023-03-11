using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using Amazon.Runtime;
using Amazon.DynamoDBv2;
using Amazon.DynamoDBv2.Model;
using Amazon.DynamoDBv2.DataModel;



namespace AWSDynamoDB
{
	public class LocalSecondaryIndexes
	{
		private const string TBL_PRODUCT_CATALOG = "Music";

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

		static async Task query_local_secondary_indexes()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
                Amazon.DynamoDBv2.Model.QueryRequest queryRequest = new Amazon.DynamoDBv2.Model.QueryRequest
				{
					TableName = TBL_PRODUCT_CATALOG,
					IndexName = "AlbumTitleIndex",
					Select = "ALL_ATTRIBUTES",
					ScanIndexForward = true,
					KeyConditionExpression = "Artist = :v_artist and AlbumTitle = :v_title",
					ExpressionAttributeValues = new Dictionary<string, AttributeValue>()
					{
						{":v_artist",new AttributeValue { S = "Acme Band"}},
						{":v_title",new AttributeValue { S = "Songs About Life"}}
					},
				};

				QueryResponse response = await client.QueryAsync(queryRequest);

				foreach (var attribs in response.Items)
				{
					foreach (var attrib in attribs)
					{
						Console.WriteLine(attrib.Key + " ---> " + attrib.Value.S);
					}
					Console.WriteLine();
				}
			}
			catch (AmazonDynamoDBException ex)
			{
				Console.WriteLine($"Failed to QueryAsync !!! : (AmazonDynamoDBException) errorMsg:{ex.Message}");
			}
			catch (AmazonServiceException ex)
			{
				Console.WriteLine($"Failed to QueryAsync !!! : (AmazonServiceException) errorMsg:{ex.Message}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to QueryAsync !!! : (AmazonServiceException) HttpStatus:{ex.StatusCode}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to QueryAsync !!! : (AmazonServiceException) AWSErrCode:{ex.ErrorCode}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to QueryAsync !!! : (AmazonServiceException) errorType:{ex.ErrorType}, tableName:{TBL_PRODUCT_CATALOG}");
				Console.WriteLine($"Failed to QueryAsync !!! : (AmazonServiceException) requestId:{ex.RequestId}, tableName:{TBL_PRODUCT_CATALOG}");
			}
			catch (System.Exception ex)
			{
				Console.WriteLine($"Failed to CreateTableAsync !!! : (System.Exception) errorMsg:{ex.Message}");
			}

			Console.ReadLine();
		}

		static async Task print_local_secondary_indexes_all()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				var response = await client.DescribeTableAsync(new DescribeTableRequest() { TableName = TBL_PRODUCT_CATALOG });
				var localSecondaryIndexes = response.Table.LocalSecondaryIndexes;

				// This code snippet will work for multiple indexes, even though
				// there is only one index in this example.
				foreach (LocalSecondaryIndexDescription lsiDescription in localSecondaryIndexes)
				{
					Console.WriteLine("Info for index " + lsiDescription.IndexName + ":");

					foreach (KeySchemaElement kse in lsiDescription.KeySchema)
					{
						Console.WriteLine("\t" + kse.AttributeName + ": key type is " + kse.KeyType);
					}

					Projection projection = lsiDescription.Projection;

					Console.WriteLine("\tThe projection type is: " + projection.ProjectionType);

					if (projection.ProjectionType.ToString().Equals("INCLUDE"))
					{
						Console.WriteLine("\t\tThe non-key projected attributes are:");

						foreach (String s in projection.NonKeyAttributes)
						{
							Console.WriteLine("\t\t" + s);
						}

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

		static async Task create_local_secondary_indexes()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				CreateTableRequest createTableRequest = new CreateTableRequest()
				{
					TableName = TBL_PRODUCT_CATALOG
				};

				//ProvisionedThroughput
				createTableRequest.ProvisionedThroughput = new ProvisionedThroughput()
				{
					ReadCapacityUnits = (long)5,
					WriteCapacityUnits = (long)5
				};

				//AttributeDefinitions
				List<AttributeDefinition> attributeDefinitions = new List<AttributeDefinition>();

				attributeDefinitions.Add(new AttributeDefinition()
				{
					AttributeName = "Artist",
					AttributeType = "S"
				});

				attributeDefinitions.Add(new AttributeDefinition()
				{
					AttributeName = "SongTitle",
					AttributeType = "S"
				});

				attributeDefinitions.Add(new AttributeDefinition()
				{
					AttributeName = "AlbumTitle",
					AttributeType = "S"
				});

				createTableRequest.AttributeDefinitions = attributeDefinitions;

				//KeySchema
				List<KeySchemaElement> tableKeySchema = new List<KeySchemaElement>();

				tableKeySchema.Add(new KeySchemaElement() { AttributeName = "Artist", KeyType = "HASH" });  //Partition key
				tableKeySchema.Add(new KeySchemaElement() { AttributeName = "SongTitle", KeyType = "RANGE" });  //Sort key

				createTableRequest.KeySchema = tableKeySchema;

				List<KeySchemaElement> indexKeySchema = new List<KeySchemaElement>();
				indexKeySchema.Add(new KeySchemaElement() { AttributeName = "Artist", KeyType = "HASH" });  //Partition key
				indexKeySchema.Add(new KeySchemaElement() { AttributeName = "AlbumTitle", KeyType = "RANGE" });  //Sort key

				Projection projection = new Projection() { ProjectionType = "INCLUDE" };

				List<string> nonKeyAttributes = new List<string>();
				nonKeyAttributes.Add("Genre");
				nonKeyAttributes.Add("Year");
				projection.NonKeyAttributes = nonKeyAttributes;

				LocalSecondaryIndex localSecondaryIndex = new LocalSecondaryIndex()
				{
					IndexName = "AlbumTitleIndex",
					KeySchema = indexKeySchema,
					Projection = projection
				};

				List<LocalSecondaryIndex> localSecondaryIndexes = new List<LocalSecondaryIndex>();
				localSecondaryIndexes.Add(localSecondaryIndex);
				createTableRequest.LocalSecondaryIndexes = localSecondaryIndexes;

				CreateTableResponse result = await client.CreateTableAsync(createTableRequest);
				Console.WriteLine(result.TableDescription.TableName);
				Console.WriteLine(result.TableDescription.TableStatus);
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
			//create_local_secondary_indexes().Wait();

			//print_local_secondary_indexes_all().Wait();

			//query_local_secondary_indexes().Wait();

			//delete_table().Wait();
		}
	}
}
