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
using Amazon.DynamoDBv2.Model.Internal.MarshallTransformations;
using Amazon.Runtime.Internal;


namespace AWSDynamoDB
{
	public class DocumentBatch
	{
		static async Task batch_read_by_multi_table_Document()
		{
			var client = ConnectToDB.create_client();

			try
			{
				var forum_table_name = AWSDynamoDB.HighLevel.ObjectPersistenceModel.TBL_FORUM;

				// 1. Specify item to add in the Forum table.
				Table table_forum = Table.LoadTable(client, forum_table_name);
				var forum_batch_get = table_forum.CreateBatchGet();

				var doc_forum = new Amazon.DynamoDBv2.DocumentModel.Document();
				doc_forum["Name"] = "Test BatchWrite Forum";
				forum_batch_get.AddKey(doc_forum);

				var thread_table_name = AWSDynamoDB.HighLevel.ObjectPersistenceModel.TBL_THREAD;

				// 2. Specify item to add in the Thread table.
				Table thread_table = Table.LoadTable(client, thread_table_name);
				var thread_batch_get = thread_table.CreateBatchGet();

				var doc_thread = new Amazon.DynamoDBv2.DocumentModel.Document();
				doc_thread["ForumName"] = "S3-forum";
				doc_thread["Subject"] = "My sample question";
				thread_batch_get.AddKey(doc_thread);

				var batch_get = new MultiTableDocumentBatchGet();
				batch_get.AddBatch(forum_batch_get);
				batch_get.AddBatch(thread_batch_get);
				Console.WriteLine("Performing batch Get in MultiTableDocumentBatchGet()");

				await batch_get.ExecuteAsync();

				foreach (var doc_get in batch_get.Batches)
				{
					Console.WriteLine($"BatchGet - resultCount:{doc_get.Results.Count}");
					foreach (var result in doc_get.Results)
					{
						foreach (var key in result.Keys)
						{
							Console.WriteLine($"\tResult Key:{key}, Value:{result[key]}");
						}
					}
				}
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to batch Get by multi-table Document !!! : error:{e.Message}");
			}

			Console.ReadLine();
		}

		static async Task batch_write_by_multi_table_Document()
		{
			var client = ConnectToDB.create_client();

			try
			{
				var forum_table_name = AWSDynamoDB.HighLevel.ObjectPersistenceModel.TBL_FORUM;

				// 1. Specify item to add in the Forum table.
				Table table_forum = Table.LoadTable(client, forum_table_name);
				var forum_batch_write = table_forum.CreateBatchWrite();

				var doc_forum = new Amazon.DynamoDBv2.DocumentModel.Document();
				doc_forum["Name"] = "Test BatchWrite Forum";
				doc_forum["Threads"] = 0;
				forum_batch_write.AddDocumentToPut(doc_forum);


				var thread_table_name = AWSDynamoDB.HighLevel.ObjectPersistenceModel.TBL_THREAD;

				// 2. Specify item to add in the Thread table.
				Table thread_table = Table.LoadTable(client, thread_table_name);
				var thread_batch_write = thread_table.CreateBatchWrite();

				var thread_doc = new Amazon.DynamoDBv2.DocumentModel.Document();
				thread_doc["ForumName"] = "S3-forum";
				thread_doc["Subject"] = "My sample question";
				thread_doc["Message"] = "Message text";
				thread_doc["KeywordTags"] = new List<string> { "S3", "Bucket" };
				thread_batch_write.AddDocumentToPut(thread_doc);


				// 2.2. Specify item to delete from the Thread table.
				thread_batch_write.AddKeyToDelete("someForumName", "someSubject");


				// 3. Create multi-table batch.
				var super_batch = new MultiTableDocumentBatchWrite();
				super_batch.AddBatch(forum_batch_write);
				super_batch.AddBatch(thread_batch_write);
				Console.WriteLine("Performing batch write in MultiTableBatchWrite()");

				await super_batch.ExecuteAsync();
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to batch Write by multi-table Document !!! : error:{e.Message}");
			}

			Console.ReadLine();
		}

		static async Task batch_read_by_single_table_Document()
		{
			var client = ConnectToDB.create_client();

			var table_name = AWSDynamoDB.HighLevel.ObjectPersistenceModel.TBL_PRODUCT_CATALOG;

			try
			{
				Table table_product_catalog = Table.LoadTable(client, table_name);
				var batch_get = table_product_catalog.CreateBatchGet();

				var doc_book = new Amazon.DynamoDBv2.DocumentModel.Document();
				doc_book["Id"] = AWSDynamoDB.HighLevel.ObjectPersistenceModel.Book.PARTITION_KEY_BEGIN;

				batch_get.AddKey(doc_book);

				Console.WriteLine($"Performing batch read in batch_read_by_single_table_Document()");

				await batch_get.ExecuteAsync();

				Console.WriteLine($"{table_name} BatchGet - resultCount:{batch_get.Results.Count}");
				foreach (var result in batch_get.Results)
				{
					foreach (var key in result.Keys)
					{
						Console.WriteLine($"\tResult Key:{key}, Value:{result[key]}");
					}
				}
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to batch Get by single-table Document !!! : error:{e.Message}, tableName:{table_name}");
			}

			Console.ReadLine();
		}

		static async Task batch_write_by_single_table_Document()
		{
			var client = ConnectToDB.create_client();

			var table_name = AWSDynamoDB.HighLevel.ObjectPersistenceModel.TBL_PRODUCT_CATALOG;

			try
			{
				Table table_product_catalog = Table.LoadTable(client, table_name);
				var batch_write = table_product_catalog.CreateBatchWrite();

				var doc_book = new Amazon.DynamoDBv2.DocumentModel.Document();
				doc_book["Id"] = AWSDynamoDB.HighLevel.ObjectPersistenceModel.Book.PARTITION_KEY_BEGIN;
				doc_book["Title"] = "My book in batch write using .NET helper classes";
				doc_book["ISBN"] = "1000-11-11-1111";
				doc_book["Price"] = 10;
				doc_book["ProductCategory"] = "Book";
				doc_book["Authors"] = new List<string> { "Author 1", "Author 2", "Author 3" };
				doc_book["Dimensions"] = "8.5x11x.5";
				doc_book["InStock"] = new DynamoDBBool(true);
				doc_book["QuantityOnHand"] = new DynamoDBNull(); //Quantity is unknown at this time

				batch_write.AddDocumentToPut(doc_book);

				// Specify delete item using overload that takes PK.
				batch_write.AddKeyToDelete(AWSDynamoDB.HighLevel.ObjectPersistenceModel.Book.PARTITION_KEY_BEGIN + 1);
				Console.WriteLine("Performing batch write in batch_write_by_single_table_Document()");

				await batch_write.ExecuteAsync();
			}
			catch (System.Exception e)
			{
				Console.WriteLine($"Failed to batch Write by single-table Document !!! : error:{e.Message}, tableName:{table_name}");
			}

			Console.ReadLine();
		}


		public static void Test()
		{
			//Common.create_table_all().Wait();

			//batch_write_by_single_table_Document().Wait();

			//batch_read_by_single_table_Document().Wait();

			//batch_write_by_multi_table_Document().Wait();

			//batch_read_by_multi_table_Document().Wait();
		}
	}
}
