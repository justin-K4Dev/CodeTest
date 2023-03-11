using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using Google.Protobuf;
using Google.Protobuf.Collections;
using Google.Protobuf.Reflection;
using Tutorial;


namespace ProtocolBuffers
{
	public class Reflection
	{
		public static void printProtobufMessage(Google.Protobuf.IMessage protobufMsg)
		{
			if (protobufMsg == null)
			{
				return;
			}

			foreach (var field in protobufMsg.Descriptor.Fields.InFieldNumberOrder())
			{
				if (field.IsMap)
				{
					var key_field = field.MessageType.Fields.InFieldNumberOrder()[0];
					var value_field = field.MessageType.Fields.InFieldNumberOrder()[1];
					IDictionary mapFields = field.Accessor.GetValue(protobufMsg) as IDictionary;
					if (null != mapFields)
					{
						foreach (DictionaryEntry mapField in mapFields)
						{
							Console.WriteLine($"Map Iterating - Field: No:{field.FieldNumber}, FullName:{field.FullName} - Key:{mapField.Key}");
							if (value_field.FieldType == Google.Protobuf.Reflection.FieldType.Message)
							{
								printProtobufMessage(mapField.Value as IMessage);
							}
							else
							{
								printProtobufField(value_field, mapField.Value);
							}
						}
					}
				}
				else if (field.IsRepeated)
				{
					IList repeatedFieldValues = field.Accessor.GetValue(protobufMsg) as IList;
					if (repeatedFieldValues != null)
					{
						foreach (var repeatedFieldValue in repeatedFieldValues)
						{
							Console.WriteLine($"Repeated Iterating - Field: No:{field.FieldNumber}, FullName:{field.FullName}");
							if (field.FieldType == Google.Protobuf.Reflection.FieldType.Message)
							{
								printProtobufMessage(repeatedFieldValue as IMessage);
							}
							else
							{
								printProtobufField(field, repeatedFieldValue);
							}
						}
					}
				}
				else
				{
					if (field.FieldType == Google.Protobuf.Reflection.FieldType.Message)
					{
						var fieldValue = field.Accessor.GetValue(protobufMsg);
						printProtobufMessage(fieldValue as IMessage);
					}
					else
					{
						printProtobufField(field, protobufMsg);
					}
				}
			}
		}

		public static void printProtobufField(FieldDescriptor field, IMessage protobufMsg)
		{
			var fieldValue = field.Accessor.GetValue(protobufMsg);
			printProtobufField(field, fieldValue);
		}

		public static void printProtobufField(FieldDescriptor field, object fieldValue)
		{
			if (fieldValue != null)
			{
				Console.WriteLine($"Field: No:{field.FieldNumber}, Name:{field.Name}, FullName:{field.FullName}, Value:{fieldValue}");
			}
		}

		public static void traversal_of_protobuf_messages()
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

			printProtobufMessage(player);

			Console.ReadLine();
		}

		public static bool setValueInProtobufMessage( Google.Protobuf.IMessage protobufMsg
			                                        , string targetHierarchyFullName, object key, object value
			                                        , ref string currHierarchyString )
		{
			if (protobufMsg == null)
			{
				return false;
			}

			string leaf_hierarchy_string = string.Empty;

			bool is_success = false;

			foreach (var field in protobufMsg.Descriptor.Fields.InFieldNumberOrder())
			{
				leaf_hierarchy_string = currHierarchyString + "." + field.JsonName.ToLower();

				Console.WriteLine($"Field Iterating - LeafHS:{leaf_hierarchy_string}, Field: No:{field.FieldNumber}, FullName:{field.FullName}");

				if (field.IsMap)
				{
					var key_field = field.MessageType.Fields.InFieldNumberOrder()[0];
					var value_field = field.MessageType.Fields.InFieldNumberOrder()[1];
					IDictionary mapFields = field.Accessor.GetValue(protobufMsg) as IDictionary;
					if (null != mapFields)
					{
						foreach (DictionaryEntry mapField in mapFields)
						{
							Console.WriteLine($"Map Iterating - Field: No:{field.FieldNumber}, FullName:{field.FullName} - Key:{mapField.Key}");

							if (    leaf_hierarchy_string == targetHierarchyFullName
								 && mapField.Key == key )
							{
								setValueOfMapField(value_field, mapField, value);
								return true;
							}

							if (value_field.FieldType == Google.Protobuf.Reflection.FieldType.Message)
							{
								is_success = setValueInProtobufMessage(mapField.Value as IMessage, targetHierarchyFullName, key, value, ref leaf_hierarchy_string);
							}
						}

						if (   false == is_success
							&& leaf_hierarchy_string == targetHierarchyFullName)
						{
							mapFields.Add(key, value);

							Console.WriteLine($"Map Add Field: No:{field.FieldNumber}, Name:{field.Name}, FullName:{field.FullName}, Key:{key}, Value:{value}");
							return true;
						}
						else
						{
							var sub_string = targetHierarchyFullName.Substring(0, leaf_hierarchy_string.Length);
							if (leaf_hierarchy_string == sub_string)
							{
								if (value_field.FieldType == Google.Protobuf.Reflection.FieldType.Message)
								{
									var child_msg = value_field.MessageType.Parser.ParseFrom(ByteString.Empty) as IMessage;

									is_success = setValueInProtobufMessage(child_msg as IMessage, targetHierarchyFullName, key, value, ref leaf_hierarchy_string);
								}
							}
						}
					}
				}
				else if (field.IsRepeated)
				{
					IList repeatedFieldValues = field.Accessor.GetValue(protobufMsg) as IList;
					if (repeatedFieldValues != null)
					{
						if (   false == is_success
							&& leaf_hierarchy_string == targetHierarchyFullName)
						{
							repeatedFieldValues.Add(value);

							Console.WriteLine($"Repeated Add Field: No:{field.FieldNumber}, Name:{field.Name}, FullName:{field.FullName}, Value:{value}");
							return true;
						}
						else
						{
							var sub_string = targetHierarchyFullName.Substring(0, leaf_hierarchy_string.Length);
							if(leaf_hierarchy_string == sub_string)
							{
								var child_msg = field.MessageType.Parser.ParseFrom(ByteString.Empty) as IMessage;
								if(null != child_msg)
								{
									var fieldValue = field.Accessor.GetValue(protobufMsg);
									is_success = setValueInProtobufMessage(child_msg, targetHierarchyFullName, key, value, ref leaf_hierarchy_string);
								}
							}
						}
					}
				}
				else
				{
					if (field.FieldType == Google.Protobuf.Reflection.FieldType.Message)
					{
						var fieldValue = field.Accessor.GetValue(protobufMsg);
						is_success = setValueInProtobufMessage(fieldValue as IMessage, targetHierarchyFullName, key, value, ref leaf_hierarchy_string);
					}
					else
					{
						if (   false == is_success
							&& leaf_hierarchy_string == targetHierarchyFullName)
						{
							setValueOfField(field, protobufMsg, value);
							return true;
						}
					}
				}
			}

			return is_success;
		}

		private static void setValueOfMapField(FieldDescriptor field, DictionaryEntry mapField, object value)
		{
			mapField.Value = value;

			Console.WriteLine($"Map Update Field: No:{field.FieldNumber}, Name:{field.Name}, FullName:{field.FullName}, Key:{mapField.Key}, Value:{value}");
		}

		private static void setValueOfField(FieldDescriptor field, IMessage protobufMsg, object value)
		{
			field.Accessor.SetValue(protobufMsg, value);

			var fieldValue = field.Accessor.GetValue(protobufMsg);
			Console.WriteLine($"Updated Field: No:{field.FieldNumber}, Name:{field.Name}, FullName:{field.FullName}, Value:{fieldValue}");
		}

		private static void update_value_of_protobuf_message_1()
		{
			var player = new Player();
			var item = new Player.Types.Item();
			item.Id = 1000011101;
			item.ItemTid = 111111;


			var root_string = "tutorial.player";
			var target_field_full_name = "tutorial.player.items";

			var is_success = setValueInProtobufMessage( player, target_field_full_name.ToLower(), item.Id, item,
													    ref root_string);
			if (false == is_success)
			{
				Console.WriteLine($"Failed to set value in ProtobufMessage !!! : value:{item.ToString()}");
			}
		}

		private static void update_value_of_protobuf_message_2()
		{
			var player = new Player();

			var item = new Player.Types.Item();
			item.Id = 1000011101;
			item.ItemTid = 111111;

			var root_string = "tutorial.player";
			var target_field_full_name = "tutorial.player.bags.wallets.items";

			var is_success = setValueInProtobufMessage( player, target_field_full_name.ToLower(), item.Id, item
				                                      , ref root_string );
			if (false == is_success)
			{
				Console.WriteLine($"Failed to set value in ProtobufMessage !!! : value:{item.ToString()}");
			}
		}

		private static void update_value_of_protobuf_message_3()
		{
			var player = new Player();

			var item = new Player.Types.Item();
			item.Id = 1000011101;
			item.ItemTid = 111111;

			var root_string = "tutorial.player";
			var target_field_full_name = "tutorial.player.mytrunks.boxs.items";

			var is_success = setValueInProtobufMessage( player, target_field_full_name.ToLower(), item.Id, item
													  , ref root_string );
			if (false == is_success)
			{
				Console.WriteLine($"Failed to set value in ProtobufMessage !!! : value:{item.ToString()}");
			}
		}

		public static void Test()
		{
			update_value_of_protobuf_message_3();

			//update_value_of_protobuf_message_2();

			//update_value_of_protobuf_message_1();

			//traversal_of_protobuf_messages();
		}
	}
}
