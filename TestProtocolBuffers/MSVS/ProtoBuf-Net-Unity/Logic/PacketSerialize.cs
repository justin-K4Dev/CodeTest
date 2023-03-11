using System;
using System.IO;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

using ProtoBuf;
using Protocol;


namespace ProtoBuf.Net.Unity
{
    public struct Header
    {
        public UInt32 size;
        public UInt32 type;
    }

    class PacketSerialize
    {
        public static void Test()
        {
            Console.WriteLine("Load player info !!!");
            string strNickname = "하하하";

            // make body
            Player player = new Player();
            player.Uuid = 1;
            player.Nickname = System.Text.Encoding.UTF8.GetBytes(strNickname.ToCharArray());

            Character character = new Character();
            character.Uuid = 1001;
            character.Tid = 1;
            player.Characters.Add(character);

            Item item = new Item();
            item.Uuid = 1000001;
            item.Tid = 100;

            character.Items.Add(item);

            // make header
            Header header = new Header();
            UInt32 headerLength = (UInt32)Marshal.SizeOf(header);

            // make stream
            MemoryStream msWrite = new MemoryStream();

            // body write to stream
            msWrite.Position = headerLength;
            ProtoBuf.Serializer.SerializeWithLengthPrefix<Player>(msWrite, player, PrefixStyle.Base128);

            // header set
            header.size = (UInt32)msWrite.Length;
            header.type = (UInt32)Protocol.CommandType.PlayerInfoUpdate;

            object tempObj = header;
            byte[] buffer = new byte[headerLength];
            Utility.copyObjectToPtr(ref tempObj, ref buffer, 0);

            // hreader write to stream 
            msWrite.Position = 0;
            msWrite.Write(buffer, 0, (int)headerLength);

            // make read buffer
            byte[] readBuffer = msWrite.ToArray();

            // parse message (Input)
            MemoryStream msRead = new MemoryStream(readBuffer);
            PacketSerialize.parseMessage(ref msRead);

            Console.ReadLine();
        }

        public static void parseMessage(ref MemoryStream input)
        {
            Header header = new Header();
            UInt32 headerLength = (UInt32)Marshal.SizeOf(header);

            byte[] readBuffer = input.ToArray();

            while (true)
            {
                // check header length
                UInt32 remainLength = (UInt32)(input.Length - input.Position);
                if (remainLength < headerLength)
                    break;

                // check body length
                UInt32 packetLength = BitConverter.ToUInt32(readBuffer, (int)input.Position);
                if (remainLength < packetLength)
                    break;

                // read command type
                input.Position = (UInt32)Marshal.SizeOf(header.size);
                Protocol.CommandType commandType = (Protocol.CommandType)BitConverter.ToUInt32(readBuffer, (int)input.Position);

                // update header position of stream
                input.Position = headerLength;

                switch (commandType)
                {

                    case Protocol.CommandType.PlayerInfoUpdate:
                    {
                        Player readPlayer = Serializer.DeserializeWithLengthPrefix<Player>(input, PrefixStyle.Base128);

                        // print player message
                        Console.WriteLine("Player.UUID: " + readPlayer.Uuid);
                        Console.WriteLine("Player.Nickname: " + System.Text.Encoding.UTF8.GetString(readPlayer.Nickname));

                        // print character message
                        foreach (Character ch in readPlayer.Characters)
                        {
                            Console.WriteLine("Character.UUID:" + ch.Uuid);
                            Console.WriteLine("Character.TID:" + ch.Tid);

                            // print item message
                            foreach (Item it in ch.Items)
                            {
                                Console.WriteLine("Item.UUID:" + it.Uuid);
                                Console.WriteLine("Item.TID:" + it.Tid);
                            }
                        }
                    } break;
                }

                // update body position of stream
                input.Seek(packetLength, SeekOrigin.Begin);
            }
        }
    }
}
