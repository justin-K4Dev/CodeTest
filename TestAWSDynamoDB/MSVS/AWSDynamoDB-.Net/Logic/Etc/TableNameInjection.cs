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
	public class TableNameInjection
	{
		// No table name attribute needed !!!
		public class Player
		{
			public const string TableName = "TBL_PLAYER";
			public const string PKBegin = "10000";

			[DynamoDBHashKey]
			public string Id { get; set; }

			[DynamoDBProperty]
			public string Name { get; set; }

			[DynamoDBProperty]
			public int HitPoints { get; set; }

			[DynamoDBProperty]
			public int Gold { get; set; }

			[DynamoDBProperty]
			public int Level { get; set; }

			[DynamoDBProperty]
			public List<string> Items { get; set; }
		}

		// No table name attribute needed !!!
		public class Location
		{
			public const string TableName = "TBL_LOCATION";
			public const string PKBegin = "1000000";

			[DynamoDBHashKey]
			public string Id { get; set; }

			[DynamoDBProperty]
			public string Name { get; set; }

			[DynamoDBProperty]
			public string Description { get; set; }
		}

		public interface IDynamoDbContext<T> : IDisposable 
			where T : class
		{
			Task<T> GetByIdAsync(string id);
			Task SaveAsync(T item);
			Task DeleteByIdAsync(T item);
		}

		public class DynamoDbContext<T> : DynamoDBContext, IDynamoDbContext<T>
			where T : class
		{
			private DynamoDBOperationConfig _config;

			public DynamoDbContext(IAmazonDynamoDB client, string tableName)
				: base(client)
			{
				_config = new DynamoDBOperationConfig()
				{
					OverrideTableName = tableName
				};
			}

			public async Task<T> GetByIdAsync(string id)
			{
				return await base.LoadAsync<T>(id, _config);
			}

			public async Task SaveAsync(T item)
			{
				await base.SaveAsync(item, _config);
			}

			public async Task DeleteByIdAsync(T item)
			{
				await base.DeleteAsync(item, _config);
			}
		}

		public class AwesomeDynamoDbService
		{
			private IDynamoDbContext<Player> _playerContext;
			private IDynamoDbContext<Location> _locationContext;

			public AwesomeDynamoDbService(IDynamoDbContext<Player> playerContext, IDynamoDbContext<Location> locationContext)
			{
				_playerContext = playerContext;
				_locationContext = locationContext;
			}

			public async Task<Player> GetPlyaerAsync(string id)
			{
				try
				{
					return await _playerContext.GetByIdAsync(id);
				}
				catch (System.Exception e)
				{
					throw new System.Exception($"DynamoDB error in GetPlyaerAsync table operation !!! : errMsg:{e.Message}");
				}
			}

			public async Task<Location> GetLocationAsync(string id)
			{
				try
				{
					return await _locationContext.GetByIdAsync(id);
				}
				catch (System.Exception e)
				{
					throw new System.Exception($"DynamoDB error in GetLocation table operation !!! : errMsg:{e.Message}");
				}
			}
		}

		static async Task inject_table_name()
		{
			AmazonDynamoDBClient client = ConnectToDB.create_client();

			try
			{
				var db_context_player = new DynamoDbContext<Player>(client, Player.TableName);
				if(null != db_context_player)
				{
					var player = new Player();
					player.Id = Player.PKBegin;
					player.Name = "justin";

					await db_context_player.SaveAsync(player);
				}

				var db_context_location = new DynamoDbContext<Location>(client, Player.TableName);
				if(null != db_context_location)
				{
					var location = new Location();
					location.Id = Location.PKBegin;
					location.Name = "korea";

					await db_context_location.SaveAsync(location);
				}

				var service = new AwesomeDynamoDbService( db_context_player, db_context_location );

				var table_player = await service.GetPlyaerAsync(Player.PKBegin);
				if(null == table_player)
				{
					Console.WriteLine($"Not found Player in {Player.TableName} !!!");
				}

				var table_location = await service.GetLocationAsync(Location.PKBegin);
				if (null == table_location)
				{
					Console.WriteLine($"Not found Location in {Location.TableName} !!!");
				}
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"DynamoDB error, inject table name !!! : errMsg:{e.Message}");
			}

			Console.ReadLine();
		}

		public static async Task create_table_all(BillingMode billingMode)
		{
			await Common.create_table(	Player.TableName
									,	new List<KeySchemaElement>() {
											new KeySchemaElement {
												AttributeName = "Id",
												KeyType = KeyType.HASH
											}
										},
										new List<AttributeDefinition>() {
											new AttributeDefinition {
												AttributeName = "Id",
												AttributeType = ScalarAttributeType.S
											}
										}
									,	billingMode
								);

			await Common.create_table(	Location.TableName
									,	new List<KeySchemaElement>() {
											new KeySchemaElement {
												AttributeName = "Id",
												KeyType = KeyType.HASH
											}
										},
										new List<AttributeDefinition>() {
											new AttributeDefinition {
												AttributeName = "Id",
												AttributeType = ScalarAttributeType.S
											}
										}
									,	billingMode
								);
		}

		public static void Test()
		{
			//create_table_all(BillingMode.PROVISIONED).Wait();

			//inject_table_name().Wait();
		}
	}
}
