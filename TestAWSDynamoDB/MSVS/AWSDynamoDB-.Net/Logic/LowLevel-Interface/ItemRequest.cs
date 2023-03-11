using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;


using Amazon.Runtime;
using Amazon.DynamoDBv2;
using Amazon.DynamoDBv2.Model;
using Amazon.DynamoDBv2.DataModel;
using Amazon.DynamoDBv2.DocumentModel;



namespace AWSDynamoDB.LowLevel
{
    public class ItemRequest
	{
		private const string TBL_PRODUCT_CATALOG = "TBL_PRODUCT_CATALOG";


		static async Task delete_item_by_DeleteItemRequest_with_ConditionExpression()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				var request = new DeleteItemRequest
				{
					TableName = TBL_PRODUCT_CATALOG,
					Key = new Dictionary<string, AttributeValue>()
					{
						{ "Id", new AttributeValue {
							  N = "1000"
							} 
						}
					},

					// Return the entire item as it appeared before the update.
					ReturnValues = "ALL_OLD",
					ExpressionAttributeNames = new Dictionary<string, string>()
					{
						{"#IP", "InPublication"}
					},
					
					ExpressionAttributeValues = new Dictionary<string, AttributeValue>()
					{
						{":inpub",new AttributeValue {
								BOOL = false
							}
						}
					},

					// DeleteItemRequest 처리가 실행될 조건 정보를 설정 한다.
					// InPublication : false 일 경우 1000 Item 을 삭제 한다.
					ConditionExpression = "#IP = :inpub"
				};

				var response = await client.DeleteItemAsync(request);

				Console.WriteLine($"Success DeleteItemRequest : httpStatusCode:{response.HttpStatusCode}, tableName:{TBL_PRODUCT_CATALOG}");

				// Check the response.
				var attributes = response.Attributes; // Attributes in the response.
				Common.print_item(attributes);
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to DeleteItemRequest !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
			}

			Console.ReadLine();
		}

		static async Task update_item_by_UpdateItemRequest_with_ConditionExpression()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				var request = new UpdateItemRequest
				{
					TableName = TBL_PRODUCT_CATALOG,
					Key = new Dictionary<string, AttributeValue>()
					{
						{ "Id", new AttributeValue {
								N = "1000"
							} 
						}
					},
					ExpressionAttributeNames = new Dictionary<string, string>()
					{
						{"#P", "Price"}
					},
					ExpressionAttributeValues = new Dictionary<string, AttributeValue>()
					{
						{":newprice", new AttributeValue {
								N = "22.00"
							}
						},
						{":currprice", new AttributeValue {
								N = "20.00"
							}
						}
					},

					// This updates price only if current price is 20.00.
					UpdateExpression = "SET #P = :newprice",

					// UpdateExpression 처리가 실행될 조건 정보를 설정 한다.
					// Price : 20 일 경우 UpdateExpression 실행 한다.
					ConditionExpression = "#P = :currprice",

					ReturnValues = "ALL_NEW" // Give me all attributes of the updated item.
				};

				var response = await client.UpdateItemAsync(request);

				Console.WriteLine($"Success UpdateItemRequest with conditions : httpStatusCode:{response.HttpStatusCode}, tableName:{TBL_PRODUCT_CATALOG}");

				// Check the response.
				var attributes = response.Attributes; // attributes in the response.
				Common.print_item(attributes);
			}
			catch(System.Exception e)
			{
				Console.WriteLine($"Failed to UpdateItemRequest with conditions !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
			}

			Console.ReadLine();
		}

		static async Task automic_counter_by_UpdateItemRequest_with_UpdateExpression()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				var request = new UpdateItemRequest
				{
					TableName = TBL_PRODUCT_CATALOG,

					Key = new Dictionary<string, AttributeValue>() { { "Id", new AttributeValue { N = HighLevel.ObjectPersistenceModel.Book.PARTITION_KEY_BEGIN.ToString() } } },
					
					ExpressionAttributeNames = new Dictionary<string, string>()
					{
						{"#Q", "Quantity"}
					},
					ExpressionAttributeValues = new Dictionary<string, AttributeValue>()
					{
						{":incr", new AttributeValue {N = "1"}}
					},

					UpdateExpression = "SET #Q = #Q + :incr",
				};

				var response = await client.UpdateItemAsync(request);

				Console.WriteLine($"Success UpdateItemRequest : httpStatusCode:{response.HttpStatusCode}, tableName:{TBL_PRODUCT_CATALOG}");

				// Check the response.
				var attributes = response.Attributes; // attributes in the response.
				Common.print_item(attributes);
			}
			catch(System.Exception e)
			{
				Console.WriteLine($"Failed to UpdateItemRequest !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
			}

			Console.ReadLine();
		}

		static async Task update_item_by_UpdateItemRequest_with_UpdateExpression()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				var request = new UpdateItemRequest
				{
					Key = new Dictionary<string, AttributeValue>()
					{
						{ "Id", new AttributeValue {
							  N = "1000"
							} 
						}
					},

					// Perform the following updates:
					// 1) Add two new authors to the list
					// 1) Set a new attribute
					// 2) Remove the ISBN attribute
					ExpressionAttributeNames = new Dictionary<string, string>()
					{
						{"#A","Authors"},
						{"#NA","NewAttribute"},
						{"#I","ISBN"}
					},
					
					ExpressionAttributeValues = new Dictionary<string, AttributeValue>()
					{
						{":auth",new AttributeValue {
							 SS = {"Author YY", "Author ZZ"}
							}
						},
						{":new",new AttributeValue {
							 S = "New Value"
							}
						}
					},

					// 상기 설정한 ExpressionAttributeNames, ExpressionAttributeValues 정보들을
					// ADD, SET, REMOVE 처리에 각각 설정 한다.
					UpdateExpression = "ADD #A :auth SET #NA = :new REMOVE #I",

					TableName = TBL_PRODUCT_CATALOG,
					ReturnValues = "ALL_NEW" // Give me all attributes of the updated item.
				};

				var response = await client.UpdateItemAsync(request);

				Console.WriteLine($"Success UpdateItemRequest : httpStatusCode:{response.HttpStatusCode}, tableName:{TBL_PRODUCT_CATALOG}");

				// Check the response.
				var attributes = response.Attributes; // attributes in the response.
				Common.print_item(attributes);
			}
			catch(System.Exception e)
			{
				Console.WriteLine($"Failed to UpdateItemRequest !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
			}

			Console.ReadLine();
		}

		static async Task lookup_item_by_GetItemRequest_with_ProjectionExpression()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				var request = new GetItemRequest
				{
					TableName = TBL_PRODUCT_CATALOG,
					Key = new Dictionary<string, AttributeValue>()
					{
						{ "Id", new AttributeValue {
								N = "1000"
							}
						}
					},
					// 조회할 속성명 목록
					ProjectionExpression = "Id, ISBN, Title, Authors",
					ConsistentRead = true
				};

				var response = await client.GetItemAsync(request);

				Console.WriteLine($"Success GetItemRequest : httpStatusCode:{response.HttpStatusCode}, tableName:{TBL_PRODUCT_CATALOG}");

				// Check the response.
				var attributes = response.Item; // attributes in the response.
				Common.print_item(attributes);
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to GetItemRequest !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
			}

			Console.ReadLine();
		}

		static async Task insert_item_by_PutItemRequest()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				var request = new PutItemRequest
				{
					TableName = TBL_PRODUCT_CATALOG,
					Item = new Dictionary<string, AttributeValue>()
					{
						{	"Id",
							new AttributeValue {
								N = "1000"
							}
						},
						{	"Title",
							new AttributeValue {
								S = "Book 201 Title"
							}
						},
						{	"ISBN", 
							new AttributeValue {
								S = "11-11-11-11"
							}
						},
						{	"Authors", 
							new AttributeValue {
								SS = new List<string>{"Author1", "Author2" }
							}
						},
						{	"Price",
							new AttributeValue {
								N = "20.00"
							}
						},
						{	"Dimensions",
							new AttributeValue {
								S = "8.5x11.0x.75"
							}
						},
						{	"InPublication",
							new AttributeValue {
								BOOL = false
							}
						}
					}
				};

				var response = await client.PutItemAsync(request);

				Console.WriteLine($"Success PutItemRequest : httpStatusCode:{response.HttpStatusCode}, tableName:{TBL_PRODUCT_CATALOG}");

				// Check the response.
				var attributes = response.Attributes; // attributes in the response.
				Common.print_item(attributes);
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to PutItemRequest !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
			}

			Console.ReadLine();
		}

		public static void Test()
		{
			//insert_item_by_PutItemRequest().Wait();

			//lookup_item_by_GetItemRequest_with_ProjectionExpression().Wait();

			//update_item_by_UpdateItemRequest_with_UpdateExpression().Wait();

			//update_item_by_UpdateItemRequest_with_ConditionExpression().Wait();

			//automic_counter_by_UpdateItemRequest_with_UpdateExpression().Wait();

			//delete_item_by_DeleteItemRequest_with_ConditionExpression().Wait();
		}
	}
}
