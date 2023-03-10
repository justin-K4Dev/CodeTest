// This file was generated by a tool; you should avoid making direct changes.
// Consider using 'partial classes' to extend these types
// Input: tutorial.player.proto

#pragma warning disable CS1591, CS0612, CS3021

namespace Tutorial
{

    [global::ProtoBuf.ProtoContract()]
    public partial class Player
    {
        [global::ProtoBuf.ProtoMember(1, Name = @"id")]
        public ulong Id { get; set; }

        [global::ProtoBuf.ProtoMember(2, Name = @"name")]
        [global::System.ComponentModel.DefaultValue("")]
        public string Name { get; set; } = "";

        [global::ProtoBuf.ProtoMember(3, Name = @"email")]
        [global::System.ComponentModel.DefaultValue("")]
        public string Email { get; set; } = "";

        [global::ProtoBuf.ProtoMember(4, Name = @"phones")]
        public global::System.Collections.Generic.List<PhoneNumber> Phones { get; } = new global::System.Collections.Generic.List<PhoneNumber>();

        [global::ProtoBuf.ProtoMember(5, Name = @"items")]
        [global::ProtoBuf.ProtoMap]
        public global::System.Collections.Generic.Dictionary<ulong, Player.Item> Items { get; } = new global::System.Collections.Generic.Dictionary<ulong, Player.Item>();

        [global::ProtoBuf.ProtoMember(6)]
        public MobilePhone mobilePhone
        {
            get { return __pbn__msg.Is(6) ? ((MobilePhone)__pbn__msg.Object) : default(MobilePhone); }
            set { __pbn__msg = new global::ProtoBuf.DiscriminatedUnionObject(6, value); }
        }
        public bool ShouldSerializemobilePhone() => __pbn__msg.Is(6);
        public void ResetmobilePhone() => global::ProtoBuf.DiscriminatedUnionObject.Reset(ref __pbn__msg, 6);

        private global::ProtoBuf.DiscriminatedUnionObject __pbn__msg;

        [global::ProtoBuf.ProtoMember(7)]
        public Watch watch
        {
            get { return __pbn__msg.Is(7) ? ((Watch)__pbn__msg.Object) : default(Watch); }
            set { __pbn__msg = new global::ProtoBuf.DiscriminatedUnionObject(7, value); }
        }
        public bool ShouldSerializewatch() => __pbn__msg.Is(7);
        public void Resetwatch() => global::ProtoBuf.DiscriminatedUnionObject.Reset(ref __pbn__msg, 7);

        [global::ProtoBuf.ProtoMember(8, Name = @"bags")]
        public global::System.Collections.Generic.List<Bag> Bags { get; } = new global::System.Collections.Generic.List<Bag>();

        [global::ProtoBuf.ProtoMember(9)]
        [global::ProtoBuf.ProtoMap]
        public global::System.Collections.Generic.Dictionary<ulong, Player.MyTrunk> myTrunks { get; } = new global::System.Collections.Generic.Dictionary<ulong, Player.MyTrunk>();

        [global::ProtoBuf.ProtoContract()]
        public partial class PhoneNumber
        {
            [global::ProtoBuf.ProtoMember(1, Name = @"number")]
            [global::System.ComponentModel.DefaultValue("")]
            public string Number { get; set; } = "";

            [global::ProtoBuf.ProtoMember(2, Name = @"type")]
            public Player.PhoneType Type { get; set; }

        }

        [global::ProtoBuf.ProtoContract()]
        public partial class Item
        {
            [global::ProtoBuf.ProtoMember(1, Name = @"id")]
            public ulong Id { get; set; }

            [global::ProtoBuf.ProtoMember(2)]
            public int itemTid { get; set; }

        }

        [global::ProtoBuf.ProtoContract()]
        public partial class MobilePhone
        {
            [global::ProtoBuf.ProtoMember(1, Name = @"device")]
            [global::System.ComponentModel.DefaultValue("")]
            public string Device { get; set; } = "";

        }

        [global::ProtoBuf.ProtoContract()]
        public partial class Watch
        {
            [global::ProtoBuf.ProtoMember(1, Name = @"device")]
            [global::System.ComponentModel.DefaultValue("")]
            public string Device { get; set; } = "";

        }

        [global::ProtoBuf.ProtoContract()]
        public partial class Wallet
        {
            [global::ProtoBuf.ProtoMember(1, Name = @"items")]
            public global::System.Collections.Generic.List<Player.Item> Items { get; } = new global::System.Collections.Generic.List<Player.Item>();

        }

        [global::ProtoBuf.ProtoContract()]
        public partial class Bag
        {
            [global::ProtoBuf.ProtoMember(1, Name = @"wallets")]
            public global::System.Collections.Generic.List<Player.Wallet> Wallets { get; } = new global::System.Collections.Generic.List<Player.Wallet>();

        }

        [global::ProtoBuf.ProtoContract()]
        public partial class Box
        {
            [global::ProtoBuf.ProtoMember(1, Name = @"items")]
            [global::ProtoBuf.ProtoMap]
            public global::System.Collections.Generic.Dictionary<ulong, Player.Item> Items { get; } = new global::System.Collections.Generic.Dictionary<ulong, Player.Item>();

        }

        [global::ProtoBuf.ProtoContract()]
        public partial class MyTrunk
        {
            [global::ProtoBuf.ProtoMember(1, Name = @"boxs")]
            [global::ProtoBuf.ProtoMap]
            public global::System.Collections.Generic.Dictionary<ulong, Player.Box> Boxs { get; } = new global::System.Collections.Generic.Dictionary<ulong, Player.Box>();

        }

        [global::ProtoBuf.ProtoContract()]
        public enum PhoneType
        {
            [global::ProtoBuf.ProtoEnum(Name = @"MOBILE")]
            Mobile = 0,
            [global::ProtoBuf.ProtoEnum(Name = @"HOME")]
            Home = 1,
            [global::ProtoBuf.ProtoEnum(Name = @"WORK")]
            Work = 2,
        }

    }

}

#pragma warning restore CS1591, CS0612, CS3021
