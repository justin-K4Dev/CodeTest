using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using Newtonsoft.Json.Linq;
using Amazon.Runtime;
using Amazon.DynamoDBv2;
using Amazon.DynamoDBv2.Model;
using Amazon.DynamoDBv2.DataModel;
using Amazon.DynamoDBv2.DocumentModel;


namespace AWSDynamoDB.HighLevel
{
	public class ObjectPersistenceModelTransact
	{
		static async Task transactWrite_put_and_update_with_OPModel()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				var context = new DynamoDBContext(client);


				var table_name = context.GetTargetTable<ObjectPersistenceModel.Forum>().TableName;

				var forum_put = new ObjectPersistenceModel.Forum();
				forum_put.Name = "S1-forum";
				forum_put.Threads = 0;

				var forum_update = new ObjectPersistenceModel.Forum();
				forum_update.Name = "S3-forum";
				forum_update.Threads = 0;

				var transact_write_items_request = new TransactWriteItemsRequest()
				{
					ReturnConsumedCapacity = "TOTAL",

					TransactItems = new List<TransactWriteItem>() {
						new TransactWriteItem() {
							Put = new Put(){
								TableName = table_name,
								Item = context.ToDocument(forum_put).ToAttributeMap(),
							}
						},
						new TransactWriteItem() {
							Update = new Update() {
								TableName = table_name,
								Key = new Dictionary<string, AttributeValue> {
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

			//transactWrite_put_and_update_with_OPModel().Wait();
		}
	}
}
