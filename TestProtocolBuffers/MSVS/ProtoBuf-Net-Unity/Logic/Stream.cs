using System;
using System.IO;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;


using ProtoBuf;
using Tutorial;


namespace ProtoBuf.Net.Unity
{
    class Stream
    {
        public static void Test()
        {
            // Player Message 객체에 값 설정
            Player player = new Player();
            player.Id = 1000000000;
            player.Name = "하하하";
            player.Email = "alice@anydomain.com";

            // Phone number 추가
            Player.PhoneNumber phoneNumber = new Player.PhoneNumber
            {
                Type = Player.PhoneType.Mobile,
                Number = "010-1111-2222"
            };
            player.Phones.Add(phoneNumber);

            // Item 추가
            Player.Item item = new Player.Item
            {
                Id = 1000011101,
                itemTid = 111111
            };

            player.Items.Add(item.Id, item);

            // make stream
            MemoryStream msWrite = new MemoryStream();
            // write stream
            ProtoBuf.Serializer.SerializeWithLengthPrefix<Player>(msWrite, player, PrefixStyle.Base128);

       
            // make read buffer
            byte[] readBuffer = msWrite.ToArray();
            // make read stream
            MemoryStream msRead = new MemoryStream(readBuffer);
            // deserialize player
            Player outPlayer = Serializer.DeserializeWithLengthPrefix<Player>(msRead, PrefixStyle.Base128);

            // Phone number Message 객체에 값 읽기
            foreach (Player.PhoneNumber pn in outPlayer.Phones)
            {
                Console.WriteLine("PhoneType:" + pn.Type + " PhoneNumber:" + pn.Number);
            }

            // Item 객체에 mapField 값 읽기
            IDictionary<ulong, Player.Item> map = outPlayer.Items;
            var en = map.GetEnumerator();

            // Item 객체에 mapField 값 읽기
            while (en.MoveNext())
            {
                ulong id = en.Current.Key;
                Player.Item objItem = en.Current.Value;
                Console.WriteLine("Key:" + id + " ItemTID:" + objItem.itemTid);
            }
        }
    }
}