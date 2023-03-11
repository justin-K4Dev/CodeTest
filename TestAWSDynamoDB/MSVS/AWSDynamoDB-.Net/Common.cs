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
	public class Common
	{
		public static async Task create_table( string tableName
			                                 , List<KeySchemaElement> keySchemas, List<AttributeDefinition> attribDefines
			                                 , BillingMode billingMode )
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			var table_name = tableName;

			try
			{
				// 테이블 생성 및 메타 데이터 설정 하기
				{
					var is_creatable = await AWSDynamoDB.LowLevel.TableRequest.isCreateableTable(client, table_name);
					if (false == is_creatable)
					{
						Console.WriteLine($"Failed to create Table !!! : tableName:{table_name}");
						return;
					}

					CreateTableRequest requestToCreate = null;

					if (true == billingMode.isOnDemand())
					{
						requestToCreate = new CreateTableRequest()
						{
							TableName = table_name,

							KeySchema = keySchemas,

							AttributeDefinitions = attribDefines,

							BillingMode = billingMode
						};
					}
					else
					{
						requestToCreate = new CreateTableRequest()
						{
							TableName = table_name,

							KeySchema = keySchemas,

							AttributeDefinitions = attribDefines,

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
					Console.WriteLine(table_name + " - " + status);

					AWSDynamoDB.LowLevel.ScanRequest.print_item_all_in_table_by_scan(table_name).Wait();
				}
			}
			catch (System.Exception e)
			{
				Console.WriteLine(table_name + " - " + e);
			}

			Console.ReadLine();
		}

		public static async Task create_table_all(BillingMode billingMode)
		{
			await create_table( HighLevel.ObjectPersistenceModel.TBL_PRODUCT_CATALOG
							  , new List<KeySchemaElement>() {
									new KeySchemaElement {
										AttributeName = "Id",
										KeyType = KeyType.HASH
									}
								},
								new List<AttributeDefinition>() {
									new AttributeDefinition {
										AttributeName = "Id",
										AttributeType = ScalarAttributeType.N
									}
								},
								billingMode
							);

			await create_table( HighLevel.ObjectPersistenceModel.TBL_FORUM
							  , new List<KeySchemaElement>() {
									new KeySchemaElement {
										AttributeName = "Name",
										KeyType = KeyType.HASH
									}
								},
								new List<AttributeDefinition>() {
									new AttributeDefinition {
										AttributeName = "Name",
										AttributeType = ScalarAttributeType.S
									}
								},
								billingMode
							);

			await create_table( HighLevel.ObjectPersistenceModel.TBL_THREAD
							  , new List<KeySchemaElement>() {
									new KeySchemaElement {
										AttributeName = "ForumName",
										KeyType = KeyType.HASH
									},
									new KeySchemaElement {
										AttributeName = "Subject",
										KeyType = KeyType.RANGE
									}
								},
								new List<AttributeDefinition>() {
									new AttributeDefinition {
										AttributeName = "ForumName",
										AttributeType = ScalarAttributeType.S
									},
									new AttributeDefinition {
										AttributeName = "Subject",
										AttributeType = ScalarAttributeType.S
									}
								},
								billingMode
							);

			await create_table( HighLevel.ObjectPersistenceModel.TBL_REPLY
							  , new List<KeySchemaElement>() {
									new KeySchemaElement {
										AttributeName = "Id",
										KeyType = KeyType.HASH
									},
									new KeySchemaElement {
										AttributeName = "ReplyDateTime",
										KeyType = KeyType.RANGE
									}
								},
								new List<AttributeDefinition>() {
									new AttributeDefinition {
										AttributeName = "Id",
										AttributeType = ScalarAttributeType.S
									},
									new AttributeDefinition {
										AttributeName = "ReplyDateTime",
										AttributeType = ScalarAttributeType.S
									}
								},
								billingMode
							);
		}

		public static void print_item(Dictionary<string, AttributeValue> attributes)
		{
			foreach (KeyValuePair<string, AttributeValue> kvp in attributes)
			{
				string attributeName = kvp.Key;
				AttributeValue value = kvp.Value;

				Console.WriteLine(
					attributeName + " " +
					(value.S == null ? "" : "S=[" + value.S + "]") +
					(value.N == null ? "" : "N=[" + value.N + "]") +
					(value.SS == null ? "" : "SS=[" + string.Join(",", value.SS.ToArray()) + "]") +
					(value.NS == null ? "" : "NS=[" + string.Join(",", value.NS.ToArray()) + "]")
				);
			}
		}

		public static void print_document(Amazon.DynamoDBv2.DocumentModel.Document document)
		{
			foreach (var attribute in document.GetAttributeNames())
			{
				string stringValue = null;

				var value = document[attribute];
				if (value is Amazon.DynamoDBv2.DocumentModel.Primitive)
				{
					stringValue = (string)value.AsPrimitive().Value;
				}
				else if (value is Amazon.DynamoDBv2.DocumentModel.DynamoDBBool)
				{
					stringValue = value.AsDynamoDBBool().Value.ToString();
				}
				else if (value is Amazon.DynamoDBv2.DocumentModel.PrimitiveList)
				{
					stringValue = string.Join(",", ( from primitive
													 in value.AsPrimitiveList().Entries
													 select primitive.Value).ToArray() );
				}
				else if (value is Amazon.DynamoDBv2.DocumentModel.DynamoDBNull)
				{
					stringValue = value.AsDynamoDBNull().ToString();
				}

				Console.WriteLine("{0} - {1}", attribute, stringValue);
			}
		}

		public static async Task execute_transaction_get(AmazonDynamoDBClient client, TransactGetItemsRequest transactionGetRequest)
		{
			try
			{
				await client.TransactGetItemsAsync(transactionGetRequest);
			}
			catch (TransactionCanceledException e)
			{
				Console.WriteLine($"Transaction Canceled, implies a client issue, fix before retrying !!! : errMsg:{e.Message}");
			}
			catch (AmazonDynamoDBException e)
			{
				Console.WriteLine($"Failed to TransactGetItemsAsync() !!! : (AmazonDynamoDBException) errMsg:{e.Message}");
			}
			catch (AmazonServiceException e)
			{
				Console.WriteLine($"Failed to TransactGetItemsAsync() !!! : (AmazonServiceException) errMsg:{e.Message}");
				Console.WriteLine($"Failed to TransactGetItemsAsync() !!! : (AmazonServiceException) HttpStatus:{e.StatusCode}");
				Console.WriteLine($"Failed to TransactGetItemsAsync() !!! : (AmazonServiceException) AWSErrCode:{e.ErrorCode}");
				Console.WriteLine($"Failed to TransactGetItemsAsync() !!! : (AmazonServiceException) errorType:{e.ErrorType}");
				Console.WriteLine($"Failed to TransactGetItemsAsync() !!! : (AmazonServiceException) requestId:{e.RequestId}");
			}
			catch (System.Exception ex)
			{
				Console.WriteLine($"Failed to TransactGetItemsAsync() !!! : (System.Exception) errMsg:{ex.Message}");
			}
		}

		public static async Task execute_transaction_write(AmazonDynamoDBClient client, TransactWriteItemsRequest transactionWriteRequest)
		{
			try
			{
				await client.TransactWriteItemsAsync(transactionWriteRequest);
			}
			catch (TransactionCanceledException e)
			{
				Console.WriteLine($"Transaction Canceled, implies a client issue, fix before retrying !!! : errMsg:{e.Message}");
			}
			catch (AmazonDynamoDBException e)
			{
				Console.WriteLine($"Failed to TransactWriteItemsAsync() !!! : (AmazonDynamoDBException) errMsg:{e.Message}");
			}
			catch (AmazonServiceException e)
			{
				Console.WriteLine($"Failed to TransactWriteItemsAsync() !!! : (AmazonServiceException) errMsg:{e.Message}");
				Console.WriteLine($"Failed to TransactWriteItemsAsync() !!! : (AmazonServiceException) HttpStatus:{e.StatusCode}");
				Console.WriteLine($"Failed to TransactWriteItemsAsync() !!! : (AmazonServiceException) AWSErrCode:{e.ErrorCode}");
				Console.WriteLine($"Failed to TransactWriteItemsAsync() !!! : (AmazonServiceException) errorType:{e.ErrorType}");
				Console.WriteLine($"Failed to TransactWriteItemsAsync() !!! : (AmazonServiceException) requestId:{e.RequestId}");
			}
			catch (System.Exception ex)
			{
				Console.WriteLine($"Failed to TransactWriteItemsAsync() !!! : (System.Exception) errMsg:{ex.Message}");
			}
		}
	}

	public static class CommonExtend
	{
		public static bool isOnDemand(this BillingMode mode)
		{
			if(BillingMode.FindValue(BillingMode.PAY_PER_REQUEST.Value) == mode)
			{
				return true;
			}

			return false;
		}
	}

}
