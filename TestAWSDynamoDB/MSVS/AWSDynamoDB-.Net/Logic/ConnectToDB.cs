using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using Amazon.Runtime;
using Amazon.DynamoDBv2;
using Amazon.DynamoDBv2.DataModel;
using Amazon.DynamoDBv2.DocumentModel;


using Newtonsoft.Json.Linq;


namespace AWSDynamoDB
{
	public class ConnectToDB
	{
		public class AwsCredentials : AWSCredentials
		{
			public AwsCredentials()
			{}

			public override ImmutableCredentials GetCredentials()
			{
				var config = Config.getInstance();

				return new ImmutableCredentials( config.AccessKey
								               , config.SecretKey
											   , null );
			}
		}

		public static AmazonDynamoDBClient create_client(bool toWaitInfo = false)
		{
			var config = Config.getInstance();

			return create_client_by_region(config.RegionName, toWaitInfo);
		}

		public static AmazonDynamoDBClient create_client_by_region(string regionName, bool toWaitInfo = false)
		{
			var config = Config.getInstance();

			AmazonDynamoDBClient db_client = null;

			if (true == config.IsUseLocalDB)
			{
				AmazonDynamoDBConfig db_config = new AmazonDynamoDBConfig();
				db_config.ServiceURL = config.ServiceURL;

				try
				{
					db_client = new AmazonDynamoDBClient("fakeAccessKey", "fakeSecretKey", db_config);

					Console.WriteLine($"Success connect to DynamoDB-Local : serviceURL:{config.ServiceURL}");
				}
				catch (System.Exception e)
				{
					Console.WriteLine( $"Failed to connect DynamoDB-Local !!!"
									 + $" : serviceUrl:{db_config.ServiceURL}");
					return null;
				}
			}
			else
			{
				try
				{
					// AWS 리전명, IAM 액세스키와 씨크릿키, 접속할 서버의 URL 까지 설정해서 AWS 다이나모 DB에 연결 한다. !!!
					// 접속할 서버의 URL 은 설정이 않되어 있어도 접속 가능 하다 !!!
					db_client = new AmazonDynamoDBClient(config.AccessKey, config.SecretKey,
															 new AmazonDynamoDBConfig
															 {
																 ServiceURL = config.ServiceURL,
																 UseHttp = true,
																 RegionEndpoint = Amazon.RegionEndpoint.GetBySystemName(regionName)
															 }
														);
					if (null == db_client)
					{
						Console.WriteLine($"Failed to connect AWS DynamoDB !!!"
										 + $" : region:{regionName}, serviceURL:{config.ServiceURL}"
										 + $", accessKey:{config.AccessKey}, secretKey:{config.SecretKey}");
					}
					else
					{
						Console.WriteLine($"Success connect to AWS DynamoDB-Remote : region:{regionName}, serviceURL:{config.ServiceURL}");
					}
				}
				catch (System.Exception e)
				{
					Console.WriteLine ( $"Failed to connect DynamoDB-Remote !!!"
									  + $" : errMsg{e.Message}, serviceUrl:{config.ServiceURL}");
					return null;
				}
			}

			if (true == toWaitInfo)
			{
				Console.ReadLine();
			}

			return db_client;
		}

		static void connect_to_dynamo_db()
		{
			create_client();

			Console.ReadLine();
		}


		public static void Test()
		{
			//connect_to_dynamo_db();

			//create_client(true);
		}

	}
}

