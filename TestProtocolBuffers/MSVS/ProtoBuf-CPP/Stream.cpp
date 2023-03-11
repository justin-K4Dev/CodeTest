// Stream.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>

#include "Message/tutorial.player.pb.h"

#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

#include "Function.h"

using namespace std;

void TestStream() {

	{
		// Player Message ��ü�� �� ����
		tutorial::Player src_player;

		src_player.set_id(41);
		src_player.set_name("alice");
		src_player.set_email("alice@anydomain.com");

		// Phone number �߰�
		tutorial::Player_PhoneNumber* phone0 = src_player.add_phones();
		phone0->set_number("123-0101");
		phone0->set_type(tutorial::Player_PhoneType_MOBILE);

		// Phone number �߰�
		tutorial::Player_PhoneNumber* phone1 = src_player.add_phones();
		phone1->set_number("456-0202");
		phone1->set_type(tutorial::Player_PhoneType_HOME);

		// Item �߰�
		auto itemList = src_player.items();
		tutorial::Player_Item item;
		item.set_id(1000010001);
		item.set_itemtid(1000);
		itemList.insert(google::protobuf::MapPair<google::protobuf::uint64, tutorial::Player_Item>(item.id(), item));

		// �̸� �����ؾ� �ϴ� ������ ���̸� �˾Ƴ��� �����Ҵ�
		int bufSize = src_player.ByteSize();
		char* outputBuf = new char[bufSize];

		// ���ۿ� ����ȭ
		google::protobuf::io::ArrayOutputStream os(outputBuf, bufSize);
		src_player.SerializeToZeroCopyStream(&os);

		// ���ۿ��� ������ȭ
		google::protobuf::io::ArrayInputStream is(outputBuf, bufSize);
		tutorial::Player dst_player0;
		dst_player0.ParseFromZeroCopyStream(&is);

		// Player Message ��ü���� repeated �� �������� (�������� ��)
		string name = dst_player0.name();
		__int64 id = dst_player0.id();
		for (int i = 0; i < dst_player0.phones_size(); ++i) {
			const tutorial::Player_PhoneNumber& phone = dst_player0.phones(i);
			tutorial::Player_PhoneType phone_type = phone.type();
			string phone_number = phone.number();
		}

		// Player Item ��ü���� map �� �������� (�������� ��)
		for (auto itPos = dst_player0.items().begin();
			itPos != dst_player0.items().end();
			++itPos) {
			auto key = itPos->first;
			auto item = itPos->second;
		}

		// ���Ͽ� ����ȭ
		const char* test_filename = "player.txt";
		fstream ofs(test_filename, ios::out | ios::trunc | ios::binary);
		src_player.SerializeToOstream(&ofs);
		ofs.close();

		// ���Ͽ��� ������ȭ
		fstream ifs(test_filename, ios::in | ios::binary);
		tutorial::Player dst_player1;
		dst_player1.ParseFromIstream(&ifs);
		ifs.close();

		// �޸� ����
		delete [] outputBuf;
		outputBuf = NULL;
		google::protobuf::ShutdownProtobufLibrary();
	}
}
