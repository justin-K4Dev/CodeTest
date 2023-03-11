using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.Concurrent;


using Amazon.Runtime;
using Amazon.DynamoDBv2;
using Amazon.DynamoDBv2.Model;
using Amazon.DynamoDBv2.DataModel;
using Amazon.DynamoDBv2.DocumentModel;
using Amazon.DynamoDBv2.Model.Internal.MarshallTransformations;
using Amazon.Runtime.Internal;


namespace AWSDynamoDB
{
    /*
		DynamoDB High-Level API
	*/
    public class Document
    {
        private const string TBL_PRODUCT_CATALOG = "TBL_PRODUCT_CATALOG";
        private const int PARTITION_KEY = 1000;
        private const int SORT_KEY = 10;

        static async Task delete_document_by_DeleteItemOperationConfig_with_ReturnValues()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();

            try
            {
                var table = Table.LoadTable(client, TBL_PRODUCT_CATALOG);
                var to_find_key = PARTITION_KEY;

                var found_document = await table.GetItemAsync(to_find_key);
                if (null == found_document)
                {
                    Console.WriteLine($"Not found Item in Table : tableName:{TBL_PRODUCT_CATALOG}");
                    return;
                }

                // Optional configuration.
                DeleteItemOperationConfig config = new DeleteItemOperationConfig
                {
                    // Return the deleted item.
                    ReturnValues = ReturnValues.AllOldAttributes
                };

                var deleted_doc = await table.DeleteItemAsync(found_document, config);

                Console.WriteLine($"Not found Item in Table : tableName:{TBL_PRODUCT_CATALOG}");

                Common.print_document(deleted_doc);
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to Table.DeleteItemAsync !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        static async Task delete_document_by_Table()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();

            try
            {
                var table = Table.LoadTable(client, TBL_PRODUCT_CATALOG);
                var to_find_key = PARTITION_KEY;

                var found_document = await table.GetItemAsync(to_find_key);
                if (null == found_document)
                {
                    Console.WriteLine($"Not found Item in Table : tableName:{TBL_PRODUCT_CATALOG}");
                    return;
                }

                await table.DeleteItemAsync(found_document);

                Console.WriteLine($"Success Table.DeleteItemAsync : toPartitionKey:{to_find_key}, tableName:{TBL_PRODUCT_CATALOG}");
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to Table.DeleteItemAsync !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        static async Task print_document_by_GetItemAsyncOfTable()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();

            try
            {
                var table = Table.LoadTable(client, TBL_PRODUCT_CATALOG);
                var to_find_key = PARTITION_KEY;

                var document = await table.GetItemAsync(to_find_key);
                if (null == document)
                {
                    Console.WriteLine($"Not found Item in Table : tableName:{TBL_PRODUCT_CATALOG}");
                    return;
                }

                Console.WriteLine($"Success Table.GetItemAsync : toPartitionKey:{to_find_key}, tableName:{TBL_PRODUCT_CATALOG}");

                Common.print_document(document);
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to Table.GetItemAsync !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        static async Task print_document_by_GetItemOperationConfig_with_AttributesToGet()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();

            try
            {
                var table = Table.LoadTable(client, TBL_PRODUCT_CATALOG);
                var to_find_key = PARTITION_KEY;

                // Configuration object that specifies optional parameters.
                GetItemOperationConfig config = new GetItemOperationConfig()
                {
                    // 설정한 속성의 값들만 출력 !!!
                    AttributesToGet = new List<string>() { "Id", "Title" },
                };

                var document = await table.GetItemAsync(to_find_key, config);
                if (null == document)
                {
                    Console.WriteLine($"Not found Item in Table : tableName:{TBL_PRODUCT_CATALOG}");
                    return;
                }

                Console.WriteLine($"Success Table.GetItemAsync GetItemOperationConfig + AttributesToGet : toPartitionKey:{to_find_key}, tableName:{TBL_PRODUCT_CATALOG}");

                Common.print_document(document);
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to Table.GetItemAsync GetItemOperationConfig + AttributesToGet !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        static async Task update_document_by_UpdateItemOperationConfig_with_ConditionalExpression()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();

            try
            {
                var table = Table.LoadTable(client, TBL_PRODUCT_CATALOG);
                var to_find_key = PARTITION_KEY;

                var book = new Amazon.DynamoDBv2.DocumentModel.Document();
                book["Id"] = to_find_key;
                book["Price"] = 29.99;

                // For conditional price update, creating a condition expression.
                Expression expr = new Expression();
                expr.ExpressionStatement = "Price = :val";
                expr.ExpressionAttributeValues[":val"] = 25.00;

                // Optional parameters.
                UpdateItemOperationConfig config = new UpdateItemOperationConfig
                {
                    ConditionalExpression = expr,
                    ReturnValues = ReturnValues.AllNewAttributes
                };

                var updated_book = await table.UpdateItemAsync(book, config);

                Console.WriteLine($"Success Table.UpdateItemAsync UpdateItemOperationConfig + ConditionalExpression : toPartitionKey:{to_find_key}, tableName:{TBL_PRODUCT_CATALOG}");

                Common.print_document(updated_book);
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to Table.PutItemAsync PutItemOperationConfig + ConditionalExpression !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        static async Task change_document_by_PutItemOperationConfig_with_ConditionalExpression()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();

            try
            {
                var table = Table.LoadTable(client, TBL_PRODUCT_CATALOG);
                var to_find_key = PARTITION_KEY;

                var book = new Amazon.DynamoDBv2.DocumentModel.Document();
                book["Id"] = to_find_key;
                book["Title"] = "Book 5555 Title";
                book["Price"] = 25.00;
                book["ISBN"] = "22-22-22-22";
                book["Name"] = "Item 2 updated";
                book["Authors"] = new List<string> { "Author x", "Author y" };
                book["InStock"] = new DynamoDBBool(true);
                book["QuantityOnHand"] = new DynamoDBNull();

                // 상기 설정한 값들중에 선택하여 조건이 맞을 경우
                // 상기 설정된 값들로 모두 추가 되거나 변경 된다 !!!
                Expression expr = new Expression();
                expr.ExpressionStatement = "ISBN = :val";
                expr.ExpressionAttributeValues[":val"] = "11-11-11-11";

                PutItemOperationConfig config = new PutItemOperationConfig()
                {
                    // Optional parameter.
                    ConditionalExpression = expr
                };

                // ConditionalExpression 의 정보와 동일한 것이 없다면 예외를 발생 시키고
                // 동일한 것이 있을 경우 상기 Book 정보로 모두 변경 한다.
                await table.PutItemAsync(book, config);

                Console.WriteLine($"Success Table.PutItemAsync PutItemOperationConfig + ConditionalExpression : toPartitionKey:{to_find_key}, tableName:{TBL_PRODUCT_CATALOG}");
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to Table.PutItemAsync PutItemOperationConfig + ConditionalExpression !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        static async Task update_document_by_UpdateItemOperationConfig_with_ReturnValues()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();

            try
            {
                var table = Table.LoadTable(client, TBL_PRODUCT_CATALOG);
                var to_find_key = PARTITION_KEY;

                var book = new Amazon.DynamoDBv2.DocumentModel.Document();
                book["Id"] = to_find_key;
                // List of attribute updates.
                // The following replaces the existing authors list.
                book["Authors"] = new List<string> { "Author x", "Author y" };
                book["newAttribute"] = "New Value";
                book["InStock"] = null; // Remove it.

                // Optional parameters.
                UpdateItemOperationConfig config = new UpdateItemOperationConfig
                {
                    // Get updated item in response.
                    ReturnValues = ReturnValues.AllNewAttributes
                };

                await table.UpdateItemAsync(book, config);

                Console.WriteLine($"Success Table.UpdateItemAsync UpdateItemOperationConfig + ReturnValues : toPartitionKey:{to_find_key}, tableName:{TBL_PRODUCT_CATALOG}");

                Common.print_document(book);
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to Table.UpdateItemAsync UpdateItemOperationConfig + ReturnValues !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        static async Task scan_document_in_Table_with_ScanOperationConfig()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();

            try
            {
                var table = Table.LoadTable(client, TBL_PRODUCT_CATALOG);

                ScanFilter scanFilter = new ScanFilter();
                scanFilter.AddCondition("Price", ScanOperator.GreaterThan, 0);

                ScanOperationConfig config = new ScanOperationConfig()
                {
                    Filter = scanFilter,
                    Select = SelectValues.SpecificAttributes,
                    AttributesToGet = new List<string>
                    {
                        "Id",
                        "Title",
                        "Price"
                    }
                };

                var search = table.Scan(config);

                do
                {
                    var document_sets = await search.GetNextSetAsync();
                    foreach (var document in document_sets)
                    {
                        Common.print_document(document);
                    }
                } while (!search.IsDone);
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to scan in Table !!! : errMsg:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        static async Task scan_document_in_Table()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();

            try
            {
                var table = Table.LoadTable(client, TBL_PRODUCT_CATALOG);

                ScanFilter scanFilter = new ScanFilter();
                scanFilter.AddCondition("Price", ScanOperator.LessThan, 0);

                var search = table.Scan(scanFilter);

                do
                {
                    var document_sets = await search.GetNextSetAsync();
                    foreach (var document in document_sets)
                    {
                        Common.print_document(document);
                    }
                } while (!search.IsDone);
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to scan in Table !!! : errMsg:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        static async Task query_document_in_Table_with_QueryOperationConfig()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();

            try
            {
                var table = Table.LoadTable(client, TBL_PRODUCT_CATALOG);

                DateTime startDate = DateTime.UtcNow.Subtract(new TimeSpan(31, 0, 0, 0));
                DateTime endDate = DateTime.UtcNow.AddDays(1);

                QueryFilter filter = new QueryFilter("Id", QueryOperator.Equal, PARTITION_KEY);
                filter.AddCondition("WriteDateTime", QueryOperator.Between, startDate, endDate);

                QueryOperationConfig config = new QueryOperationConfig()
                {
                    Limit = 2, // 2 items/page.
                    Select = SelectValues.SpecificAttributes,
                    AttributesToGet = new List<string> // 가져올 속성 지정
					{
                        "Id",
                        "Title",
                        "WriteDateTime"
                    },
                    ConsistentRead = true,
                    Filter = filter
                };

                var search = table.Query(config);

                do
                {
                    var document_sets = await search.GetNextSetAsync();
                    foreach (var document in document_sets)
                    {
                        Common.print_document(document);
                    }
                } while (!search.IsDone);
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to query in Table !!! : errMsg:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        static async Task query_document_in_Table()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();

            try
            {
                var table = Table.LoadTable(client, TBL_PRODUCT_CATALOG);

                DateTime twoWeeksAgoDate = DateTime.UtcNow - TimeSpan.FromDays(15);

                QueryFilter filter = new QueryFilter("Id", QueryOperator.Equal, PARTITION_KEY);
                filter.AddCondition("WriteDateTime", QueryOperator.GreaterThan, twoWeeksAgoDate);

                var search = table.Query(filter);

                do
                {
                    var document_sets = await search.GetNextSetAsync();
                    foreach (var document in document_sets)
                    {
                        Common.print_document(document);
                    }
                } while (!search.IsDone);
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to query in Table !!! : errMsg:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        static async Task insert_document_in_Document()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();

            try
            {
                var table = Table.LoadTable(client, TBL_PRODUCT_CATALOG);
                var to_find_key = PARTITION_KEY;

                var book = new Amazon.DynamoDBv2.DocumentModel.Document();
                book["Id"] = PARTITION_KEY;
                book["Title"] = "Book 101 Title";
                book["ISBN"] = "11-11-11-11";
                book["Authors"] = new List<string> { "Author 1", "Author 2" };
                book["InStock"] = new DynamoDBBool(true);
                book["QuantityOnHand"] = new DynamoDBNull();
                book["Price"] = 60000;

                var pictures = new Amazon.DynamoDBv2.DocumentModel.Document();
                pictures.Add("MyUrl-1", "https://MyUrl-1");
                pictures.Add("MyUrl-2", "https://MyUrl-2");

                book.Add("Pictures", pictures);

                // 추가하는 형태로 처리 하므로 위에서 설정않된 속성은 제거됨을 유의 해서 코드 작성 해야 한다. !!!
                await table.PutItemAsync(book);

                Console.WriteLine($"Success Table.PutItemAsync document in document : toPartitionKey:{to_find_key}, tableName:{TBL_PRODUCT_CATALOG}");
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to Table.PutItemAsync document in document !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        static async Task insert_item_list_in_Document()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();

            try
            {
                var table = Table.LoadTable(client, TBL_PRODUCT_CATALOG);
                var to_find_key = PARTITION_KEY;

                var book = new Amazon.DynamoDBv2.DocumentModel.Document();
                book["Id"] = PARTITION_KEY;
                book["Title"] = "Book 101 Title";
                book["ISBN"] = "11-11-11-11";
                book["Authors"] = new List<string> { "Author 1", "Author 2" };
                book["InStock"] = new DynamoDBBool(true);
                book["QuantityOnHand"] = new DynamoDBNull();
                book["Price"] = 60000;

                var relatedItems = new DynamoDBList();
                relatedItems.Add(341);
                relatedItems.Add(472);
                relatedItems.Add(649);
                book.Add("RelatedItems", relatedItems);

                // 추가하는 형태로 처리 하므로 위에서 설정않된 속성은 제거됨을 유의 해서 코드 작성 해야 한다. !!!
                await table.PutItemAsync(book);

                Console.WriteLine($"Success Table.PutItemAsync item list in Document : toPartitionKey:{to_find_key}, tableName:{TBL_PRODUCT_CATALOG}");
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to Table.PutItemAsync item list in Document !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        public static async Task insert_document_in_Table()
        {
            AmazonDynamoDBClient client = ConnectToDB.create_client();

            try
            {
                var table = Table.LoadTable(client, TBL_PRODUCT_CATALOG);

                var book = new Amazon.DynamoDBv2.DocumentModel.Document();
                book["Id"] = PARTITION_KEY;
                book["WriteDateTime"] = DateTime.UtcNow;
                book["Title"] = "Book 101 Title";
                book["ISBN"] = "11-11-11-11";
                book["Authors"] = new List<string> { "Author 1", "Author 2" };
                book["InStock"] = new DynamoDBBool(true);
                book["QuantityOnHand"] = new DynamoDBNull();
                book["Price"] = 60000;

                await table.PutItemAsync(book);

                Console.WriteLine($"Success Table.PutItemAsync document in Table : toPartitionKey:{PARTITION_KEY}, tableName:{TBL_PRODUCT_CATALOG}");
            }
            catch (System.Exception e)
            {
                Console.WriteLine($"Failed to Table.PutItemAsync document in Table !!! : error:{e.Message}, tableName:{TBL_PRODUCT_CATALOG}");
            }

            Console.ReadLine();
        }

        public static void Test()
        {
            //TableRequest.create_table_by_CreateTableRequest(BillingMode.PROVISIONED).Wait();

            //insert_document_in_Table().Wait();

            //insert_item_list_in_Document().Wait();

            //insert_document_in_Document().Wait();

            //query_document_in_Table().Wait();

            //query_document_in_Table_with_QueryOperationConfig().Wait();

            //scan_document_in_Table().Wait();

            //scan_document_in_Table_with_ScanOperationConfig().Wait();

            //update_document_by_UpdateItemOperationConfig_with_ReturnValues().Wait();

            //change_document_by_PutItemOperationConfig_with_ConditionalExpression().Wait();

            //update_document_by_UpdateItemOperationConfig_with_ConditionalExpression().Wait();

            //print_document_by_GetItemOperationConfig_with_AttributesToGet().Wait();

            //print_document_by_GetItemAsyncOfTable().Wait();

            //delete_document_by_Table().Wait();

            //insert_document_in_Table().Wait();

            //delete_document_by_DeleteItemOperationConfig_with_ReturnValues().Wait();
        }
    }
}
