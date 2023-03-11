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


using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Serialization;



namespace AWSDynamoDB.HighLevel
{
    /*
		DynamoDB High-Level API
	*/

    public class ObjectPersistenceModel
    {
		public class DimensionType
		{
			public decimal Length
			{
				get; set;
			}
			public decimal Height
			{
				get; set;
			}
			public decimal Thickness
			{
				get; set;
			}
		}

		// Converts the complex type DimensionType to string and vice-versa.
		public class DimensionTypeConverter : IPropertyConverter
		{
			public DynamoDBEntry ToEntry(object value)
			{
				DimensionType bookDimensions = value as DimensionType;
				if (bookDimensions == null) throw new ArgumentOutOfRangeException();

				string data = $"DimensionType convert - Length:{bookDimensions.Length}, Height:{bookDimensions.Height}, Thickness:{bookDimensions.Thickness}";

				DynamoDBEntry entry = new Primitive
				{
					Value = data
				};
				return entry;
			}

			public object FromEntry(DynamoDBEntry entry)
			{
				Primitive primitive = entry as Primitive;
				if (primitive == null || !(primitive.Value is String) || string.IsNullOrEmpty((string)primitive.Value))
					throw new ArgumentOutOfRangeException();

				string[] data = ((string)(primitive.Value)).Split(new string[] { " x " }, StringSplitOptions.None);
				if (data.Length != 3) throw new ArgumentOutOfRangeException();

				DimensionType complexData = new DimensionType
				{
					Length = Convert.ToDecimal(data[0]),
					Height = Convert.ToDecimal(data[1]),
					Thickness = Convert.ToDecimal(data[2])
				};
				return complexData;
			}
		}


		public const string TBL_PRODUCT_CATALOG = "TBL_PRODUCT_CATALOG";
        [DynamoDBTable(TBL_PRODUCT_CATALOG)]
        public class Book
        {
            public const int PARTITION_KEY_BEGIN = 1000;

            [DynamoDBHashKey] //Partition key
            public int Id
            {
                get; set;
            }

            [DynamoDBProperty]
            public string Title
            {
                get; set;
            }

            [DynamoDBProperty]
            public string ISBN
            {
                get; set;
            }

            [DynamoDBProperty("Authors")] //String Set datatype
            public List<string> BookAuthors
            {
                get; set;
            }

            [DynamoDBProperty("WriteDateTime")]
            public DateTime WriteDateTime
            {
                get; set;
            }

            [DynamoDBProperty("Price")]
            public int Price
            {
                get; set;
            }

            [DynamoDBProperty("PageCount")]
            public string PageCount
            {
                get; set;
            }

            [DynamoDBProperty("ProductCategory")]
            public string ProductCategory
            {
                get; set;
            }

            [DynamoDBProperty("InPublication")]
            public bool InPublication
            {
                get; set;
            }

			// Arbitrary type, with a converter to map it to DynamoDB type.
			[DynamoDBProperty(typeof(DimensionTypeConverter))]
			public DimensionType Dimensions
			{
				get; set;
			}

			public string toBasicString()
            {
                var str = $"Book Id:{Id}, Title:{Title}, ISBN:{ISBN}, WriteDT:{WriteDateTime}";
                str += " Authors-[";
                foreach (var author in BookAuthors)
                {
                    str += $"{author},";
                }
                str += "]";

                return str;
            }
        }

        public const string TBL_REPLY = "TBL_REPLY";
        [DynamoDBTable(TBL_REPLY)]
        public class Reply
        {
            public const int PARTITION_KEY_BEGIN = 10000;

            [DynamoDBHashKey] //Partition key
            public string Id
            {
                get; set;
            }

            [DynamoDBRangeKey] //Sort key
            public DateTime ReplyDateTime
            {
                get; set;
            }

            // Properties included implicitly.
            public string Message
            {
                get; set;
            }
            // Explicit property mapping with object persistence model attributes.
            [DynamoDBProperty("LastPostedBy")]
            public string PostedBy
            {
                get; set;
            }
            // Property to store version number for optimistic locking.
            [DynamoDBVersion]
            public int? Version
            {
                get; set;
            }
        }

        public const string TBL_THREAD = "TBL_THREAD";
        [DynamoDBTable(TBL_THREAD)]
        public class Thread
        {
            public const int PARTITION_KEY_BEGIN = 20000;

            // PK mapping.
            [DynamoDBHashKey]      //Partition key
            public string ForumName
            {
                get; set;
            }
            [DynamoDBRangeKey]      //Sort key
            public string Subject
            {
                get; set;
            }
            // Implicit mapping.
            public string Message
            {
                get; set;
            }
            public string LastPostedBy
            {
                get; set;
            }
            public int Views
            {
                get; set;
            }
            public int Replies
            {
                get; set;
            }
            public bool Answered
            {
                get; set;
            }
            public DateTime LastPostedDateTime
            {
                get; set;
            }
            // Explicit mapping (property and table attribute names are different.
            [DynamoDBProperty("Tags")]
            public List<string> KeywordTags
            {
                get; set;
            }
            // Property to store version number for optimistic locking.
            [DynamoDBVersion]
            public int? Version
            {
                get; set;
            }
        }

        public const string TBL_FORUM = "TBL_FORUM";
        [DynamoDBTable(TBL_FORUM)]
        public class Forum
        {
            public const int PARTITION_KEY_BEGIN = 30000;

            [DynamoDBHashKey]      //Partition key
            public string Name
            {
                get; set;
            }

            // All the following properties are explicitly mapped,
            // only to show how to provide mapping.
            [DynamoDBProperty]
            public int Threads
            {
                get; set;
            }
            [DynamoDBProperty]
            public int Views
            {
                get; set;
            }
            [DynamoDBProperty]
            public string LastPostBy
            {
                get; set;
            }
            [DynamoDBProperty]
            public DateTime LastPostDateTime
            {
                get; set;
            }
            [DynamoDBProperty]
            public int Messages
            {
                get; set;
            }
        }

        public const string TBL_TEST = "TBL_TEST";
        [DynamoDBTable(TBL_TEST)]
        public class TBLTest
        {
            public const int PARTITION_KEY_BEGIN = 50000;

            [DynamoDBHashKey]      //Partition key
            public string Name
            {
                get; set;
            }

            // All the following properties are explicitly mapped,
            // only to show how to provide mapping.
            [DynamoDBProperty]
            public int Threads
            {
                get; set;
            }
        }




        static async Task delete_item_by_OPModel()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();
            DynamoDBContext context = new DynamoDBContext(client);

            try
            {
                var book = new Book()
                {
                    Id = 1001,
                    //Title = "YourBook",
                    //ISBN = "Test",
                };
                book.BookAuthors = new List<string>();
                book.BookAuthors.Add("kangms");

                await context.DeleteAsync(book);

                Console.WriteLine($"Success update item by Model - tableName:{TBL_PRODUCT_CATALOG}");
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to update Item by Model !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        static async Task update_item_by_OPModel()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();
            DynamoDBContext context = new DynamoDBContext(client);

            try
            {
                var book = new Book()
                {
                    Id = 1001,
                    Title = "YourBook",
                    //ISBN = "Test",
                };
                book.BookAuthors = new List<string>();
                book.BookAuthors.Add("kangms");

				// DimensionTypeConverter 호출 !!!
				book.Dimensions.Height += 100;
				book.Dimensions.Length += 1;
                book.Dimensions.Thickness += 0.2M;

				await context.SaveAsync(book);

                Console.WriteLine($"Success update item by Model - tableName:{TBL_PRODUCT_CATALOG}");
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to update Item by Model !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        static async Task scan_item_by_OPModel()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();
            DynamoDBContext context = new DynamoDBContext(client);

            try
            {
                var conditions = new List<ScanCondition>
                {
                    new ScanCondition("Price", ScanOperator.GreaterThan, 0),
                    new ScanCondition("ProductCategory", ScanOperator.Equal, "Book")
                };

                var found_books = context.ScanAsync<Book>(conditions).GetRemainingAsync();
                foreach (var book in found_books.Result)
                {
                    Console.WriteLine($"Found Book : Id:{book.Id}, Title:{book.Title}, Price:{book.Price}");
                }
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to laod Item by Model !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        static async Task query_item_by_OPModel()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();
            DynamoDBContext context = new DynamoDBContext(client);

            try
            {
                var filter_period = new DateTime[] {
                    new DateTime(2022, 12, 8)
                ,   new DateTime(2022, 12, 10)
                };
                var scan = new ScanCondition("WriteDateTime", ScanOperator.Between, filter_period);
                var db_operation_config = new DynamoDBOperationConfig();
                db_operation_config.QueryFilter.Add(scan);

                var bookItem = await context.LoadAsync<Book>(Book.PARTITION_KEY_BEGIN, db_operation_config);

                Console.WriteLine($"Success laod item by Model - tableName:{bookItem.ToString()}");
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to laod Item by Model !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        static async Task insert_item_by_OPModel()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();
            DynamoDBContext context = new DynamoDBContext(client);

            try
            {
                var book = new Book()
                {
                    Id = Book.PARTITION_KEY_BEGIN,
                    WriteDateTime = DateTime.UtcNow,
                    Title = "MyBook",
                    ISBN = "Test",
                };
                book.BookAuthors = new List<string>();
                book.BookAuthors.Add("justin");

                await context.SaveAsync(book);

                Console.WriteLine($"Success insert item by Model - tableName:{TBL_PRODUCT_CATALOG}");
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to insert Item by Model !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        public static void Test()
        {
            //Common.create_table_all(BillingMode.PROVISIONED).Wait();

            //insert_item_by_OPModel().Wait();

            //query_item_by_OPModel().Wait();

            //scan_item_by_OPModel().Wait();

            //update_item_by_OPModel().Wait();

            //delete_item_by_OPModel().Wait();
        }
    }
}
