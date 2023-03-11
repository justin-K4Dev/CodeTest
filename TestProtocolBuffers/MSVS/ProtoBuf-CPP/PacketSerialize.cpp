// SimpleSerialize.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <iostream>

#include <google/protobuf/text_format.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

#include "Message/protocol.CommandType.pb.h"
#include "Message/protocol.Packet.pb.h"

#include "Function.h"


using namespace std;


void parseMessage(google::protobuf::io::CodedInputStream& cis);


// Message header
struct Header {
	google::protobuf::uint32 size;
	Protocol::CommandType type;
};


/*
	# Packet Format

	Header Block + Message Block + Header Block + Message Block ~

	Header : Network Engine definition
	Message : User Custom definition
*/

const int HeaderSize = sizeof(Header);

void TestPacketSerialize() {
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	try {

		std::cout << "Enter nickname of Player ";
		char inputString[32];
		std::cin.getline(inputString, 32);
		size_t length = strlen(inputString);

		std::string nickname;
		nickname = inputString;

		// make Player message
		Protocol::Player player;
		player.set_uuid(1);
		player.set_nickname(nickname);

		// Character message in Player
		Protocol::Character *pCharacter = player.add_character();
		pCharacter->set_uuid(1001);
		pCharacter->set_tid(1);

		Protocol::Item *pItem;
		pItem = pCharacter->add_item();
		pItem->set_uuid(1000001);
		pItem->set_tid(100);

		pItem = pCharacter->add_item();
		pItem->set_uuid(1000000001);
		pItem->set_tid(1000);

		int bufSize = player.ByteSize();

		char* pBuf = new char[HeaderSize + bufSize];

		// create output stream buffer
		google::protobuf::io::ArrayOutputStream aos(pBuf, HeaderSize + bufSize);
		google::protobuf::io::CodedOutputStream cos(&aos);

		// Header write to stream buffer 
		Header header;
		header.size = HeaderSize + bufSize;
		header.type = Protocol::CommandType::PLAYER_INFO_UPDATE;
		cos.WriteRaw(&header, sizeof(header));

		// Player write to stream buffer
		player.SerializeToCodedStream(&cos);

		// create input stream buffer
		google::protobuf::io::ArrayInputStream ais(pBuf, HeaderSize + bufSize);
		google::protobuf::io::CodedInputStream cis(&ais);

		// parse header & message !!!
		parseMessage(cis);

		delete[] pBuf;
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	// Optional:  Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();

	std::cout << std::endl << "--- End of Simple Client ---" << std::endl;
}

// print to screen message
void PrintMessage(google::protobuf::Message& message)
{
	string textFormatStr;
	google::protobuf::TextFormat::PrintToString(message, &textFormatStr);
	printf("%s\n", textFormatStr.c_str());
}

// parse message
void parseMessage(google::protobuf::io::CodedInputStream& cis)
{
	Header header;

	// read Header
	while (cis.ReadRaw(&header, HeaderSize))
	{
		// 
		const void* pMessage = NULL;
		int remainSize = 0;

		cis.GetDirectBufferPointer(&pMessage, &remainSize);
		if (remainSize < (signed)header.size)
			break;

		int bodyLength = header.size - HeaderSize;

		// create input stream buffer for reading Player message
		google::protobuf::io::ArrayInputStream _ais(pMessage, bodyLength);
		google::protobuf::io::CodedInputStream _cis(&_ais);

		// move to Player message position
		cis.Skip(header.size - bodyLength);

		// case to CommandType
		switch (header.type)
		{
			case Protocol::PLAYER_INFO_UPDATE:
			{
				// set player message from input stream buffer
				Protocol::Player player;
				if (false == player.ParseFromCodedStream(&_cis)) {

					std::cout << "Failed to parse input Stream !!!" << std::endl;
					break;
				}

				// print Player message
				google::protobuf::Message* pMsg = (google::protobuf::Message*)&player;
				PrintMessage((*pMsg));
			} break;
		}
	}
}
