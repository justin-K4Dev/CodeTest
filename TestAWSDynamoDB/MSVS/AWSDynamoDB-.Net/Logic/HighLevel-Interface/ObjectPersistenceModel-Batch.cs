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


namespace AWSDynamoDB.HighLevel
{
	public class ObjectPersistenceModelBatch
	{
		static async Task batch_read_by_multi_table_OPModel()
		{
			var client = ConnectToDB.create_client();

			try
			{
				DynamoDBContext context = new DynamoDBContext(client);

				var book_batch_get = context.CreateBatchGet<ObjectPersistenceModel.Book>();
				book_batch_get.AddKey(ObjectPersistenceModel.Book.PARTITION_KEY_BEGIN + 0);
				book_batch_get.AddKey(ObjectPersistenceModel.Book.PARTITION_KEY_BEGIN + 1);

				var thread_batch_get = context.CreateBatchGet<ObjectPersistenceModel.Thread>();
				thread_batch_get.AddKey("Amazon-S3-forum", "My sample question");
				thread_batch_get.AddKey("Amazon-S4-forum", "thread-1");

				var combined_batch = book_batch_get.Combine(thread_batch_get);
				await combined_batch.ExecuteAsync();

				Console.WriteLine($"Book BatchGet - resultCount:{book_batch_get.Results.Count}");
				foreach (var result in book_batch_get.Results)
				{
					Console.WriteLine($"\tResult Id:{result.Id}, Title:{result.Title}, Price:{result.Price}");
				}

				Console.WriteLine($"Thread BatchGet - resultCount:{thread_batch_get.Results.Count}");
				foreach (var result in thread_batch_get.Results)
				{
					Console.WriteLine($"\tResult ForumName:{result.ForumName}, Subject:{result.Subject}");
				}
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to batch Get by multi-table OPModel !!! : error:{e.Message}");
			}

			Console.ReadLine();
		}

		static async Task batch_write_by_multi_table_OPModel()
		{
			var client = ConnectToDB.create_client();

			try
			{
				DynamoDBContext context = new DynamoDBContext(client);
				// Create BatchWrite objects for each of the Forum and Thread classes.
				var forum_batch = context.CreateBatchWrite<ObjectPersistenceModel.Forum>();

				DynamoDBOperationConfig config = new DynamoDBOperationConfig();
				config.SkipVersionCheck = true;
				var thread_batch = context.CreateBatchWrite<ObjectPersistenceModel.Thread>(config);

				// 1. New Forum item.
				var new_forum = new ObjectPersistenceModel.Forum
				{
					Name = "Test-BatchWrite-Forum",
					Threads = 0
				};
				forum_batch.AddPutItem(new_forum);

				// 2. Specify a forum to delete by specifying its primary key.
				forum_batch.AddDeleteKey("Some-forum");

				// 3. New Thread item.
				var new_thread = new ObjectPersistenceModel.Thread
				{
					ForumName = "Amazon-S3-forum",
					Subject = "My sample question",
					KeywordTags = new List<string> { "Amazon-S3", "Bucket" },
					Message = "Message text"
				};

				thread_batch.AddPutItem(new_thread);

				// Now run multi-table batch write.
				var superBatch = new MultiTableBatchWrite(forum_batch, thread_batch);
				await superBatch.ExecuteAsync();
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to batch Write by multi-table OPModel !!! : error:{e.Message}");
			}

			Console.ReadLine();
		}

		static async Task batch_read_by_single_table_OPModel()
		{
			var client = ConnectToDB.create_client();

			try
			{
				DynamoDBContext context = new DynamoDBContext(client);
				var book_batch = context.CreateBatchGet<ObjectPersistenceModel.Book>();
				book_batch.AddKey(ObjectPersistenceModel.Book.PARTITION_KEY_BEGIN + 0);
				book_batch.AddKey(ObjectPersistenceModel.Book.PARTITION_KEY_BEGIN + 1);
				book_batch.AddKey(ObjectPersistenceModel.Book.PARTITION_KEY_BEGIN + 2);
				await book_batch.ExecuteAsync();

				// Process result.
				Console.WriteLine($"{ObjectPersistenceModel.TBL_PRODUCT_CATALOG} BatchGet - resultCount:{book_batch.Results.Count}");
				foreach (var result in book_batch.Results)
				{
					Console.WriteLine($"\tResult Id:{result.Id}, Title:{result.Title}, Price:{result.Price}");
				}
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to batch Get by single-table OPModel !!! : error:{e.Message}");
			}

			Console.ReadLine();
		}

		static async Task batch_write_by_single_table_OPModel()
		{
			var client = ConnectToDB.create_client();

			try
			{
				DynamoDBContext context = new DynamoDBContext(client);
				var bookBatch = context.CreateBatchWrite<ObjectPersistenceModel.Book>();

				// 1. Specify two books to add.
				var book1 = new ObjectPersistenceModel.Book
				{
					Id = ObjectPersistenceModel.Book.PARTITION_KEY_BEGIN + 0,
					ISBN = "1000-11-11-1111",
					ProductCategory = "Book",
					Title = "My book-1 in batch write"
				};
				var book2 = new ObjectPersistenceModel.Book
				{
					Id = ObjectPersistenceModel.Book.PARTITION_KEY_BEGIN + 1,
					ISBN = "1001-11-11-1111",
					ProductCategory = "Book",
					Title = "My book-2 in batch write"
				};

				bookBatch.AddPutItems(new List<ObjectPersistenceModel.Book> { book1, book2 });

				// 2. Specify one book to delete.
				bookBatch.AddDeleteKey(ObjectPersistenceModel.Book.PARTITION_KEY_BEGIN + 2);

				await bookBatch.ExecuteAsync();
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to batch Write by single-table OPModel !!! : error:{e.Message}");
			}

			Console.ReadLine();
		}

		public static void Test()
		{
			//Common.create_table_all(BillingMode.PROVISIONED).Wait();

			//batch_write_by_single_table_OPModel().Wait();

			//batch_read_by_single_table_OPModel().Wait();

			//batch_write_by_multi_table_OPModel().Wait();

			//batch_read_by_multi_table_OPModel().Wait();
		}
	}
}
