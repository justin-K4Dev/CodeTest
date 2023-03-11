using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.Concurrent;
using System.Collections;


using Amazon.Runtime;
using Amazon.DynamoDBv2;
using Amazon.DynamoDBv2.Model;
using Amazon.DynamoDBv2.DataModel;
using Amazon.DynamoDBv2.DocumentModel;
using Amazon.DynamoDBv2.Model.Internal.MarshallTransformations;


namespace AWSDynamoDB.LowLevel
{
	public class QueryRequest
	{
		private const string TBL_PRODUCT_CATALOG = "TBL_PRODUCT_CATALOG";
		private const Int32 PARTITION_KEY = 1000;
		private const Int32 SORT_KEY = 10;

		static async Task lookup_item_by_QueryRequest_with_KeyConditionExpression()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				var request = new Amazon.DynamoDBv2.Model.QueryRequest
				{
					TableName = TBL_PRODUCT_CATALOG,
					KeyConditionExpression = "Id = :v_Id", // 키로 설정된 속성에 대한 검색 조건 지정
					ExpressionAttributeValues = new Dictionary<string, AttributeValue> {
						{":v_Id", new AttributeValue { N = PARTITION_KEY.ToString() }}
					},
					ProjectionExpression = "Title, WriteDateTime", // 출력 속성명 지정
					ConsistentRead = true
				};

				var response = await client.QueryAsync(request);

				foreach (Dictionary<string, AttributeValue> each in response.Items)
				{
					// Process the result.
					Common.print_item(each);
				}
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to query in Table !!! : errMsg:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
			}

			Console.ReadLine();
		}


		static async Task lookup_item_by_QueryRequest_with_KeyConditionExpression_Between()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				DateTime startDate = DateTime.UtcNow - TimeSpan.FromDays(31);
				string start = startDate.ToString(Amazon.Util.AWSSDKUtils.ISO8601DateFormat);

				DateTime endDate = DateTime.UtcNow.AddDays(1);
				string end = endDate.ToString(Amazon.Util.AWSSDKUtils.ISO8601DateFormat);

				var request = new Amazon.DynamoDBv2.Model.QueryRequest
				{
					TableName = TBL_PRODUCT_CATALOG,

					// WriteDateTime 속성을 Key 로 설정했을 경우 !!!, DynamoDBHashKey 나 DynamoDBRangeKey 로 설정 않했을 경우
					// Amazon.DynamoDBv2.AmazonDynamoDBException: 'Query key condition not supported' 예외 발생 !!!
					KeyConditionExpression = "Id = :v_Id and WriteDateTime between :v_start and :v_end",
					ExpressionAttributeValues = new Dictionary<string, AttributeValue> {
					
						{ ":v_Id", new AttributeValue { N = PARTITION_KEY.ToString() } },
						{ ":v_start", new AttributeValue { S = start } },
						{ ":v_end", new AttributeValue { S = end } },
					},
				};

				var response = await client.QueryAsync(request);

				foreach (Dictionary<string, AttributeValue> each in response.Items)
				{
					// Process the result.
					Common.print_item(each);
				}
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to query in Table !!! : errMsg:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
			}

			Console.ReadLine();
		}

		public static void Test()
		{
			//TableRequest.create_table_by_CreateTableRequest(BillingMode.PAY_PER_REQUEST).Wait();
			//Document.insert_document_in_Table().Wait();

			//lookup_item_by_QueryRequest_with_KeyConditionExpression().Wait();
			//lookup_item_by_QueryRequest_with_KeyConditionExpression_Between().Wait();
		}
	}
}
