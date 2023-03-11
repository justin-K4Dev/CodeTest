using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Dynamic;
using System.CodeDom;
using System.Reflection;



using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Utilities;
using Newtonsoft.Json.Serialization;
using Google.Protobuf;
using Google.Protobuf.Collections;
using Google.Protobuf.Reflection;
using Tutorial;
using Google.Protobuf.WellKnownTypes;
using System.Diagnostics.Metrics;
using System.Xml.Linq;
using System.Security.Cryptography.X509Certificates;



namespace ProtocolBuffers
{
	public class JsonToProto
	{
		private static void convert_protobuf_2_json_2_protobuf_by_ParseJson()
		{
			// Player Message 객체에 값 설정
			Player player = new Player();
			player.Id = 1000000000;
			player.Name = "하하하";
			player.Email = "alice@anydomain.com";

			// Phone number 추가
			Player.Types.PhoneNumber phoneNumber = new Player.Types.PhoneNumber
			{
				Type = Player.Types.PhoneType.Mobile,
				Number = "010-1111-2222"
			};
			player.Phones.Add(phoneNumber);

			// Item 추가
			Player.Types.Item item = new Player.Types.Item
			{
				Id = 1000011101,
				ItemTid = 111111
			};
			player.Items.Add(item.Id, item);

			player.MobilePhone = new Player.Types.MobilePhone();
			player.MobilePhone.Device = "iPhone 14 ProMax";

			// player.MobilePhone 정보는 Watch 정보 설정시 oneof 구조에 의해 삭제 된다 !!!
			player.Watch = new Player.Types.Watch();
			player.Watch.Device = "iWatch";


			// ProtoBuf => JSON 변환
			var json_formatter = JsonFormatter.Default;
			string player_json = json_formatter.Format(player);
			Console.WriteLine(player_json);


			// JSON => ProtoBuf 변환
			Player converted_player = Player.Parser.ParseJson(player_json);
			string palyer_protobuf = converted_player.ToString();
			Console.WriteLine(palyer_protobuf);

			
			Console.ReadLine();
		}

		private static void convert_protobuf_2_json_2_protobuf_by_JsonConvert()
		{
			// Player Message 객체에 값 설정
			Player player = new Player();
			player.Id = 1000000000;
			player.Name = "하하하";
			player.Email = "alice@anydomain.com";

			// Phone number 추가
			Player.Types.PhoneNumber phoneNumber = new Player.Types.PhoneNumber
			{
				Type = Player.Types.PhoneType.Mobile,
				Number = "010-1111-2222"
			};
			player.Phones.Add(phoneNumber);

			// Item 추가
			Player.Types.Item item = new Player.Types.Item
			{
				Id = 1000011101,
				ItemTid = 111111
			};
			player.Items.Add(item.Id, item);

			player.MobilePhone = new Player.Types.MobilePhone();
			player.MobilePhone.Device = "iPhone 14 ProMax";

			// player.MobilePhone 정보는 Watch 정보 설정시 oneof 구조에 의해 삭제 된다 !!!
			player.Watch = new Player.Types.Watch();
			player.Watch.Device = "iWatch";


			// ProtoBuf => JSON 변환
			string json_string = JsonConvert.SerializeObject(player);
			Console.WriteLine(json_string);


			// JSON => ProtoBuf 변환
			var json_obj = Newtonsoft.Json.JsonConvert.DeserializeObject(json_string);
			var player_string = JsonConvert.SerializeObject(json_obj);
			var cloned_player = JsonConvert.DeserializeObject<Player>(player_string);
			Console.WriteLine(cloned_player.ToString());

			Console.ReadLine();
		}


		private static void proc_json_array<T>( T parentMsg, FieldDescriptor fieldDesc
			                                  , JArray jsonArray)
			where T : class, IMessage
		{
			IList repeated_fields = fieldDesc.Accessor.GetValue(parentMsg) as IList;
			if(null == repeated_fields)
			{
				return;
			}

			var child_msg = fieldDesc.MessageType.Parser.ParseFrom(ByteString.Empty) as IMessage;
			if (null == child_msg)
			{
				return;
			}

			repeated_fields.Add(child_msg);

			foreach (JObject members in jsonArray)
			{
				proc_json_object( child_msg, fieldDesc
								, members );
			}
		}

		private static void proc_json_object<T>( T parentMsg, FieldDescriptor fieldDesc
			                                   , JObject jObject )
			where T : class, IMessage
		{
			IMessage child_msg = null;

			if (true == fieldDesc.IsMap)
			{
				proc_json_map( parentMsg, fieldDesc
					         , jObject );
			}
			else if(null != fieldDesc.RealContainingOneof)
			{
				proc_json_oneof( parentMsg, fieldDesc
							   , jObject );
			}
			else
			{
				foreach (var member in jObject)
				{
					proc_json_key_value( parentMsg, member );
				}
			}
		}

		private static void proc_json_map<T>( T parentMsg, FieldDescriptor fieldDesc
											, JObject jObject )
			where T : class, IMessage
		{
			var key_field = fieldDesc.MessageType.Fields.InFieldNumberOrder()[0];
			var value_field = fieldDesc.MessageType.Fields.InFieldNumberOrder()[1];
			IDictionary mapFields = fieldDesc.Accessor.GetValue(parentMsg) as IDictionary;
			if (null == mapFields)
			{
				return;
			}

			IMessage curr_msg = null;
			if (value_field.FieldType == Google.Protobuf.Reflection.FieldType.Message)
			{
				curr_msg = value_field.MessageType.Parser.ParseFrom(ByteString.Empty) as IMessage;
			}
			else
			{
				curr_msg = parentMsg;
			}

			foreach (var member in jObject)
			{
				var key_value = getKey(key_field.FieldType, member.Key);
				mapFields[key_value] = curr_msg;

				var jtoken_value = member.Value;

				if(JTokenType.Array == jtoken_value.Type)
				{
					proc_json_array( curr_msg, value_field
						           , jtoken_value as JArray );
				}
				else if(JTokenType.Object == jtoken_value.Type)
				{
					proc_json_object( curr_msg, value_field
						            , jtoken_value as JObject );
				}
				else
				{
					proc_json_primitive( curr_msg, member );
				}
			}
		}

		private static object getKey(FieldType keyType, object keyObject)
		{
			switch (keyType)
			{
				case FieldType.String:
					return (string)keyObject;

				case FieldType.Enum:
					return (Int32)Convert.ToInt32(keyObject);

				case FieldType.Double:
					return (double)Convert.ToDouble(keyObject);

				case FieldType.Float:
					return (float)Convert.ToDouble(keyObject);

				case FieldType.Int64:
					return (Int64)Convert.ToInt64(keyObject);

				case FieldType.UInt64:
					return (UInt64)Convert.ToUInt64(keyObject);

				case FieldType.Int32:
					return (Int32)Convert.ToInt32(keyObject);

				case FieldType.UInt32:
					return (UInt32)Convert.ToUInt32(keyObject);

				case FieldType.Bool:
					return (bool)Convert.ToBoolean(keyObject);
			}

			return null;
		}

		private static void proc_json_oneof<T>( T parentMsg, FieldDescriptor fieldDesc
											  , JObject jObject )
			where T : class, IMessage
		{
			var found_one_of_desc = parentMsg.Descriptor.FindDescriptor<OneofDescriptor>(fieldDesc.RealContainingOneof.Name);
			if (null == found_one_of_desc)
			{
				return;
			}
			if (null == jObject.Parent)
			{
				return;
			}

			var key = jObject.Parent.ToObject<JProperty>();
			var found_to_check_one_of_field = found_one_of_desc.ContainingType.FindFieldByName(key.Name);
			if (null == found_to_check_one_of_field)
			{
				return;
			}

			var found_one_of_field_message = found_to_check_one_of_field.MessageType.Parser.ParseFrom(ByteString.Empty) as IMessage;
			found_to_check_one_of_field.Accessor.SetValue(parentMsg, found_one_of_field_message);

			var found_field = found_one_of_desc.Accessor.GetCaseFieldDescriptor(parentMsg);
			if(null == found_field)
			{
				return;
			}

			foreach (var member in jObject)
			{
				proc_json_key_value( found_one_of_field_message
								   , member );
			}
		}

		private static void proc_json_key_value<T>(T parentMsg, KeyValuePair<string, JToken> pair)
			where T : class, IMessage
		{
			var found_field = parentMsg.Descriptor.FindFieldByName(pair.Key);
			if (null == found_field)
			{
				return;
			}

			var jtoken = pair.Value;

			if (JTokenType.Array == jtoken.Type)
			{
				proc_json_array( parentMsg, found_field, jtoken as JArray);
			}
			else if (JTokenType.Object == jtoken.Type)
			{
				proc_json_object( parentMsg, found_field, jtoken as JObject );
			}
			else
			{
				proc_json_primitive(parentMsg, pair);
			}
		}


		public static void proc_json_primitive<T>( T currMsg, KeyValuePair<string, JToken> pair)
			where T : class, IMessage
		{
			var descriptor = currMsg.Descriptor.FindFieldByName(pair.Key);
			var jtoken = pair.Value;

			switch (descriptor.FieldType)
			{
				case FieldType.String:
					descriptor.Accessor.SetValue(currMsg, jtoken.Value<string>());
					break;

				case FieldType.Enum:
					descriptor.Accessor.SetValue(currMsg, jtoken.Value<Int32>());
					break;

				case FieldType.Double:
					descriptor.Accessor.SetValue(currMsg, jtoken.Value<double>());
					break;

				case FieldType.Float:
					descriptor.Accessor.SetValue(currMsg, jtoken.Value<float>());
					break;

				case FieldType.Int64:
					descriptor.Accessor.SetValue(currMsg, jtoken.Value<long>());
					break;

				case FieldType.UInt64:
					descriptor.Accessor.SetValue(currMsg, jtoken.Value<ulong>());
					break;

				case FieldType.Int32:
					descriptor.Accessor.SetValue(currMsg, jtoken.Value<Int32>());
					break;

				case FieldType.UInt32:
					descriptor.Accessor.SetValue(currMsg, jtoken.Value<UInt32>());
					break;

				case FieldType.Bool:
					descriptor.Accessor.SetValue(currMsg, jtoken.Value<bool>());
					break;

				default:
					Console.WriteLine( $"Faild to setValue for Primitive Type !!!"
						             + $" : FieldNo:{descriptor.FieldNumber}, MsgType:{descriptor.FullName}, Value:{descriptor.Accessor.GetValue(currMsg)}");
					return;
			}
		}

		public static void fillupProtobufMessage<T>(T parentMsg, JObject members)
			where T : class, IMessage
		{
			var root_string = parentMsg.Descriptor.FullName.ToLower();

			foreach (var member in members)
			{
				proc_json_key_value( parentMsg, member );
			}
		}

		public static void convert_json_file_2_protobuf_by_reflection()
		{
			var loaded_json = JObject.Parse(File.ReadAllText(".\\Message\\Json-define\\monster.json"));

			JToken found_targets = loaded_json["targets"];
			if (null == found_targets)
			{
				return;
			}

			if (JTokenType.Array != found_targets.Type)
			{
				return;
			}

			foreach (JToken member in found_targets)
			{
				var found_type = member["type"];
				var type_string = found_type.Value<string>();

				var to_create_type = System.Type.GetType(type_string);

				var protobuf_message = Activator.CreateInstance(to_create_type) as IMessage;
				if(null != protobuf_message)
				{
					var found_member = member["members"];

					fillupProtobufMessage(protobuf_message, found_member.ToObject<JObject>());
				}
			}

			Console.ReadLine();
		}


		public static List<System.Type> getTypeByName(string className, string fullName, bool ignoreCase = true)
		{
			var found_types = new List<System.Type>();
			if (true == ignoreCase)
			{
				className = className.ToLower();
				fullName = fullName.ToLower();
			}

			foreach (System.Reflection.Assembly a in AppDomain.CurrentDomain.GetAssemblies())
			{
				System.Type[] assemblyTypes = a.GetTypes();
				for (int i = 0; i < assemblyTypes.Length; i++)
				{
					if (ignoreCase)
					{
						if (assemblyTypes[i].Name.Equals(className, StringComparison.OrdinalIgnoreCase)
							 && assemblyTypes[i].FullName.Equals(fullName, StringComparison.OrdinalIgnoreCase))
						{
							found_types.Add(assemblyTypes[i]);
						}
					}
					else
					{
						if (true == assemblyTypes[i].Name.Equals(className)
							&& true == assemblyTypes[i].FullName.Equals(fullName))
						{
							found_types.Add(assemblyTypes[i]);
						}
					}
				}
			}

			return found_types;
		}

		public static IMessage makeChildProtobufMessage(IMessage parentMsg, string currFieldName)
		{
			var found_oneof = parentMsg.Descriptor.Oneofs.First<OneofDescriptor>();
			if (null == found_oneof)
			{
				return null;
			}

			FieldDescriptor found_to_check_oneof_field = null;
			foreach (var field in found_oneof.ContainingType.Fields.InFieldNumberOrder())
			{
				if (true == currFieldName.ToLower().Equals(field.Name.ToLower(), StringComparison.OrdinalIgnoreCase))
				{
					found_to_check_oneof_field = field;
					break;
				}
			}
			if (null == found_to_check_oneof_field)
			{
				return null;
			}

			var found_oneof_field_msg = found_to_check_oneof_field.MessageType.Parser.ParseFrom(ByteString.Empty) as IMessage;
			found_to_check_oneof_field.Accessor.SetValue(parentMsg, found_oneof_field_msg);

			var curr_oneof_field = found_oneof.Accessor.GetCaseFieldDescriptor(parentMsg);
			if (null == curr_oneof_field)
			{
				return null;
			}

			var field_msg = (IMessage)curr_oneof_field.Accessor.GetValue(parentMsg);
			if (null == field_msg)
			{
				return null;
			}

			return field_msg;
		}

		public static IMessage makeProtobufMessage(JToken command)
		{
			var command_value = command.Value<string>();
			var splitted_cmd = command_value.Split(".");

			if(3 != splitted_cmd.Length)
			{
				return null;
			}

			string root_msg_name = splitted_cmd[0];
			string child_field_name = splitted_cmd[1];
			string body_field_name = splitted_cmd[2];

			var to_root_msg_types = getTypeByName(root_msg_name, root_msg_name);
			if(0 == to_root_msg_types.Count)
			{
				return null;
			}

			var to_root_msg_type = to_root_msg_types[0];

			var root_protobuf_msg = Activator.CreateInstance(to_root_msg_type) as IMessage;
			if(null == root_protobuf_msg)
			{
				return null;
			}

			var child_field_msg = makeChildProtobufMessage(root_protobuf_msg, child_field_name);
			if(null == child_field_msg)
			{
				return null;
			}

			var body_field_msg = makeChildProtobufMessage(child_field_msg, body_field_name);
			if (null == body_field_msg)
			{
				return null;
			}

			return body_field_msg;
		}

		public static void convert_json_file_2_protobuf_by_hierarchy_reflection()
		{
			var loaded_json = JObject.Parse(File.ReadAllText(".\\Message\\Json-define\\hierarchy.json"));

			var found_protocol = loaded_json[(object)"protocol"];
			if (null == found_protocol)
			{
				return;
			}

			var found_command = found_protocol[(object)"command"];
			if(null == found_command)
			{
				return;
			}

			var made_protobuf_msg = makeProtobufMessage(found_command);
			if(null == made_protobuf_msg)
			{
				return;
			}

			Reflection.printProtobufMessage(made_protobuf_msg);

			Console.ReadLine();
		}

		public static void Test()
		{
			//convert_json_file_2_protobuf_by_hierarchy_reflection();

			//convert_json_file_2_protobuf_by_reflection();

			//convert_protobuf_2_json_2_protobuf_by_JsonConvert();

			//convert_protobuf_2_json_2_protobuf_by_ParseJson();
		}
	}



}
