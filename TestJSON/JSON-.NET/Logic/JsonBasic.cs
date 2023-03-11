using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;


using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Utilities;
using System.Security.Cryptography;


namespace json
{
	/*
		JSON 반드시 숙지 사항

		[ ... ] => [] 둘러 싸고 있는 요소가 JArray
		{ ... } => {} 둘러 싸고 있는 요소가 JObject
	    { ... } => {} 안에 있는 각각의 요소를 JProperty

		JArray > JObject > JObject > JProperty 종속 관계를 지닌다.
	
		JArray 는 Key-Value 로 접근이 불가능 하다.
		JObject 는 Key-Value 접근이 가능 하다.
		JProperty 는 Key-Value 접근이 불가능 하다.

		JProperty 는 기본적으로 순회하며 대상 요소를 찾아야 한다.
		JArray 는 기본적으로 배열 인덱스를 통해 대상 요소에 접근이 가능 한다.
		JObject 는 기본적으로 Key 를 통해 대상 요소에 접근이 가능 하다.

		JObject -> JProperty 변환 가능 하다.
		JProperty -> JObject 기본적으로 변환은 불가능 하다.
	 */

	public class JsonBasic
	{

		private static void proc_json_array(JArray jsonArray)
		{
			foreach (JToken element in jsonArray)
			{
				if (JTokenType.Array == element.Type)
				{
					proc_json_array(element as JArray);
				}
				else if (JTokenType.Object == element.Type)
				{
					proc_json_object(element as JObject);
				}
				else
				{
					Console.WriteLine($"Invalid element type in JArray !!! : JTokenType:{element.Type}");
				}
			}
		}

		private static void proc_json_object(JObject jsonObject)
		{
			foreach (var property in jsonObject.Properties())
			{
				var jtoken_value = property.Value;
				if (JTokenType.Array == jtoken_value.Type)
				{
					Console.WriteLine(property.Name + " : [");
					proc_json_array(jtoken_value as JArray);
					Console.WriteLine($"] end of {property.Name}");
				}
				else if (JTokenType.Object == jtoken_value.Type)
				{
					Console.WriteLine($"{property.Name}" + " : {");
					proc_json_object(jtoken_value as JObject);
					Console.WriteLine("}" + $" end of {property.Name}");
				}
				else
				{
					proc_json_propertyt(property);
				}
			}
		}

		private static void proc_json_propertyt(JProperty jsonProperty)
		{
			if(null == jsonProperty)
			{
				Console.WriteLine($"JProperty is null !!!");
				return;
			}

			Console.WriteLine(jsonProperty.ToString());
		}

		private static void convert_json_file_parse_and_print()
		{
			var loaded_json = JObject.Parse(File.ReadAllText(".\\json-define\\sample.json"));
			string json_string = JsonConvert.SerializeObject(loaded_json);
			Console.WriteLine(json_string);

			JToken found_targets = loaded_json["targets"];
			if (null == found_targets)
			{
				return;
			}

			if (JTokenType.Array != found_targets.Type)
			{
				return;
			}

			proc_json_array(found_targets as JArray);

			Console.ReadLine();
		}


		private static void update_json_array(string key, string toUpdateValue, JArray jsonArray)
		{
			foreach (JToken element in jsonArray)
			{
				if (JTokenType.Array == element.Type)
				{
					update_json_array(key, toUpdateValue, element as JArray);
				}
				else if (JTokenType.Object == element.Type)
				{
					update_json_object(key, toUpdateValue, element as JObject);
				}
				else
				{
					Console.WriteLine($"Invalid element type in JArray !!! : JTokenType:{element.Type}");
				}
			}
		}

		private static void update_json_object(string key, string toUpdateValue, JObject jsonObject)
		{
			foreach (var property in jsonObject.Properties())
			{
				var jtoken_value = property.Value;
				if (JTokenType.Array == jtoken_value.Type)
				{
					Console.WriteLine(property.Name + " : [");
					update_json_array(key, toUpdateValue, jtoken_value as JArray);
					Console.WriteLine($"] end of {property.Name}");
				}
				else if (JTokenType.Object == jtoken_value.Type)
				{
					Console.WriteLine($"{property.Name}" + " : {");
					update_json_object(key, toUpdateValue, jtoken_value as JObject);
					Console.WriteLine("}" + $" end of {property.Name}");
				}
				else
				{
					update_json_propertyt(key, toUpdateValue, property);
				}
			}
		}

		private static void update_json_propertyt(string key, string toUpdateValue, JProperty jsonProperty)
		{
			if (null == jsonProperty)
			{
				Console.WriteLine($"JProperty is null !!!");
				return;
			}

			if (jsonProperty.Name == key)
			{
				var before = jsonProperty.Value;
				jsonProperty.Value = toUpdateValue;
				Console.WriteLine($"Found !!! and Updated {jsonProperty.Name}, before:{before} => after:{jsonProperty.Value}");
			}
		}

		private static void convert_json_file_parse_and_iterate_and_update()
		{
			var loaded_json = JObject.Parse(File.ReadAllText(".\\json-define\\sample.json"));
			string json_string = JsonConvert.SerializeObject(loaded_json);
			Console.WriteLine(json_string);

			JToken found_targets = loaded_json["targets"];
			if (null == found_targets)
			{
				return;
			}

			if (JTokenType.Array != found_targets.Type)
			{
				return;
			}

			update_json_array("Id", "kangms", found_targets as JArray);

			proc_json_array(found_targets as JArray);

			Console.ReadLine();
		}

		public static void Test()
		{
			//convert_json_file_parse_and_iterate_and_update();

			//convert_json_file_parse_and_print();
		}
	}
}
