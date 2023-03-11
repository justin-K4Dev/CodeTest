using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;


using Google.Protobuf;
using Tutorial;


namespace ProtocolBuffers
{
	public class Stream
    {
        private static void stream_by_code_inout_stream()
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

            byte[] bytes = new byte[player.CalculateSize()];

            // write to bytes array (Output)
            CodedOutputStream output = new CodedOutputStream(bytes);
            player.WriteTo(output);


            CodedInputStream input = new CodedInputStream(bytes);

            // read from bytes array (Input)
            Player outPlayer = new Player();
            outPlayer.MergeFrom(input);

            // Phone number Message 객체에 값 읽기
            foreach (Player.Types.PhoneNumber pn in outPlayer.Phones)
            {
                Console.WriteLine("PhoneType:" + pn.Type + " PhoneNumber:" + pn.Number);
            }

            // Item 객체에 mapField 값 읽기
            IDictionary<ulong, Player.Types.Item> map = outPlayer.Items;
            var en = map.GetEnumerator();

            while (en.MoveNext())
            {
                ulong id = en.Current.Key;
                Player.Types.Item objItem = en.Current.Value;
                Console.WriteLine("Key:" + id + " ItemTID:" + objItem.ItemTid);
            }

            Console.ReadLine();
        }


        public static void Test()
        {
            //stream_by_code_inout_stream();
		}

    }
}
