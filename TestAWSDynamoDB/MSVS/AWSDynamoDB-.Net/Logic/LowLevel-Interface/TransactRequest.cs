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
	public class TransactRequest
	{
		static async Task transactGet_get()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				var context = new DynamoDBContext(client);

				var transact_get_items_request = new TransactGetItemsRequest()
				{
					ReturnConsumedCapacity = "TOTAL",

					TransactItems = new List<TransactGetItem>() {
						new TransactGetItem(){
							Get = new Get() {
								TableName = HighLevel.ObjectPersistenceModel.TBL_FORUM,
								Key = new Dictionary<string, AttributeValue>{
									{ "Name", new AttributeValue() { S = "S4-forum" } }
								},
							}
						},
						new TransactGetItem(){
							Get = new Get() {
								TableName = HighLevel.ObjectPersistenceModel.TBL_PRODUCT_CATALOG,
								Key = new Dictionary<string, AttributeValue>()
								{
									{   "Id",
										new AttributeValue {
											N = HighLevel.ObjectPersistenceModel.Book.PARTITION_KEY_BEGIN.ToString()
										}
									},
								},

								ProjectionExpression = "Id, Title, Price"
							}
						},
					}
				};

				await Common.execute_transaction_get(client, transact_get_items_request);
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to Get in TransactionGet !!! : (System.Exception) errMsg:{e.Message}");
			}

			Console.ReadLine();
		}

		static async Task transactWrite_check_and_update_and_put_and_delete()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				var context = new DynamoDBContext(client);

				var transact_write_items_request = new TransactWriteItemsRequest()
				{
					ReturnConsumedCapacity = "TOTAL",

					TransactItems = new List<TransactWriteItem>() {
						new TransactWriteItem(){
							ConditionCheck = new ConditionCheck(){
								TableName = HighLevel.ObjectPersistenceModel.TBL_FORUM,
								Key = new Dictionary<string, AttributeValue>{
									{ "Name", new AttributeValue() { S = "S3-forum" } },
								},
								ConditionExpression = "attribute_exists(Name)",
							}
						},
						new TransactWriteItem(){
							Update = new Update(){
								TableName = HighLevel.ObjectPersistenceModel.TBL_PRODUCT_CATALOG,
								Key = new Dictionary<string, AttributeValue>()
								{
									{ "Id", new AttributeValue { N = HighLevel.ObjectPersistenceModel.Book.PARTITION_KEY_BEGIN.ToString() } },
								},
								ExpressionAttributeValues = new Dictionary<string, AttributeValue>()
								{
									{ ":expected_price",new AttributeValue { N = "0" } },
									{ ":new_price",new AttributeValue { N = "10000" } },
								},

								ConditionExpression = "Price > :expected_price",
								UpdateExpression = "SET Price = :new_price",
								ReturnValuesOnConditionCheckFailure = ReturnValuesOnConditionCheckFailure.ALL_OLD,
							}
						},
						new TransactWriteItem(){
							Put = new Put() {
								TableName = HighLevel.ObjectPersistenceModel.TBL_FORUM,
								Item = new Dictionary<string, AttributeValue>()
								{
									{ "Name", new AttributeValue { S = "S5-forum" } },
									{ "Threads", new AttributeValue { N = "0" } },
								},
								ReturnValuesOnConditionCheckFailure = ReturnValuesOnConditionCheckFailure.ALL_OLD,
								ConditionExpression = "attribute_not_exists(Name)",
							}
						},
						new TransactWriteItem(){
							Delete = new Delete(){
								TableName = HighLevel.ObjectPersistenceModel.TBL_FORUM,
								Key = new Dictionary<string, AttributeValue>()
								{
									{ "Name", new AttributeValue { S = "S4-forum" } },
								},
								ReturnValuesOnConditionCheckFailure = ReturnValuesOnConditionCheckFailure.ALL_OLD,
							}
						}
					}
				};

				await Common.execute_transaction_write(client, transact_write_items_request);
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to Check and Update and Put in TransactionWrite !!! : (System.Exception) errMsg:{e.Message}");
			}

			Console.ReadLine();
		}

		static async Task transactWrite_put_and_update()
		{
			/*
				트랜젝션 Write 처리시 유의 사항 !!! 
			
				- 동일한 Key 를 대상으로 여러개의 TransactWriteItem 을 요청할 수 없다 !!!
			      여러개의 TransactWriteItem 요청시 그 대상이 모두 달라야 한다 !!!
			*/

			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				var context = new DynamoDBContext(client);

				var transact_write_items_request = new TransactWriteItemsRequest()
				{
					ReturnConsumedCapacity = "TOTAL",

					TransactItems = new List<TransactWriteItem>() {
						new TransactWriteItem(){
							Put = new Put(){
								TableName = HighLevel.ObjectPersistenceModel.TBL_FORUM,
								Item = new Dictionary<string, AttributeValue>{
									{ "Name", new AttributeValue { S = "S1-forum" } },
									{ "Threads", new AttributeValue { N = "0" } }
								}
							}
						},
						new TransactWriteItem(){
							Update = new Update(){
								TableName = HighLevel.ObjectPersistenceModel.TBL_FORUM,
								Key = new Dictionary<string, AttributeValue>{
									{ "Name", new AttributeValue() { S = "S3-forum" } }
								},
								UpdateExpression = "SET Threads = :v_threads",
								ExpressionAttributeValues = new Dictionary<string, AttributeValue>
								{
									{":v_threads", new AttributeValue { N =  "1000" }},
								},
							}
						}
					}
				};

				await Common.execute_transaction_write(client, transact_write_items_request);
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to Put and Update in TransactionWrite !!! : (System.Exception) errMsg:{e.Message}");
			}

			Console.ReadLine();
		}

		public static void Test()
		{
			//Common.create_table_all(BillingMode.PROVISIONED).Wait();

			//transactWrite_put_and_update().Wait();

			//transactWrite_check_and_update_and_put_and_delete().Wait();

			//transactGet_get().Wait();
		}
	}
}
