using System;
using System.IO;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;


using Google.Protobuf;
using Protocol;


namespace ProtocolBuffers
{
    public struct Header
    {
        public UInt32 size;
        public UInt32 type;
    }

	public class PacketSerialize
    {
        public static void parseMessage(ref CodedInputStream input )
        {
            Header header = new Header();
            header.size = input.ReadFixed32();
            header.type = input.ReadFixed32();

            switch ((Protocol.CommandType)header.type) {

                case Protocol.CommandType.PlayerInfoUpdate:
                {
                    // player message
                    Player readPlayer = new Player();
                    readPlayer.MergeFrom(input);

                    // print player message
                    Console.WriteLine("Player.UUID: " + readPlayer.UUID);
                    Console.WriteLine("Player.Nickname: " + readPlayer.Nickname.ToStringUtf8());

                    // print character message
                    foreach (Character ch in readPlayer.Character)
                    {
                        Console.WriteLine("Character.UUID:" + ch.UUID);
                        Console.WriteLine("Character.TID:" + ch.TID);

                        // print item message
                        foreach (Item it in ch.Item)
                        {
                            Console.WriteLine("Item.UUID:" + it.UUID);
                            Console.WriteLine("Item.TID:" + it.TID);
                        }
                    }

                } break;
            }
        }

        private static void packet_serialize()
        {
			Console.WriteLine("Enter nickname of Player ");
			string strNickname = Console.ReadLine();

			Player player = new Player();
			player.UUID = 1;
			player.Nickname = ByteString.CopyFromUtf8(strNickname);

			Character character = new Character();
			character.UUID = 1001;
			character.TID = 1;
			player.Character.Add(character);

			Item item = new Item();
			item.UUID = 1000001;
			item.TID = 100;
			character.Item.Add(item);

			// make header & set
			Header header = new Header();
			UInt32 headerLength = (UInt32)Marshal.SizeOf(header);
			header.size = headerLength + (UInt32)player.CalculateSize();
			header.type = (UInt32)Protocol.CommandType.PlayerInfoUpdate;

			byte[] bytes = new byte[header.size];

			// write to bytes array (Output)            
			CodedOutputStream output = new CodedOutputStream(bytes);
			output.WriteFixed32(header.size);
			output.WriteFixed32(header.type);
			player.WriteTo(output);

			// parse message (Input)
			MemoryStream ms = new MemoryStream(bytes);
			while (true)
			{

				// check header length
				UInt32 remainLength = (UInt32)(ms.Length - ms.Position);
				if (remainLength < headerLength)
					break;

				// check body length
				UInt32 packetLength = BitConverter.ToUInt32(bytes, (int)ms.Position);
				if (remainLength < packetLength)
					break;

				// process packet
				CodedInputStream input = new CodedInputStream(ms);
				PacketSerialize.parseMessage(ref input);

				// update position of stream
				ms.Seek(packetLength, SeekOrigin.Begin);
			}

			Console.ReadLine();
		}

        public static void Test()
        {
			//packet_serialize();
		}
    }
}
