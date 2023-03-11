<?php
//Revision : 9
//Update Date : 2014-10-21 19:26:25

class TemplateType
{
	 const CONSTANT = "Constant";		//Constant 템플리트
	 const PC = "PC";		//PC 템플리트
	 const PC_LEVEL = "PCLevel";		//PC Level 템플리트
	 const ERROR_MESSAGE = "ErrorMessage";		//Error Message 템플리트
	 const MESSAGE_STRING = "MessageString";		//MessageString 템플리트
	 const STRING = "String";		//String 템플리트
	 const STAGE = "Stage";		//Stage 템플리트
	 const ITEM = "Item";		//Item 템플리트
	 const REWARD = "Reward";		//Reward 템플리트
	 const BOSS_KILL_DROP = "BossKillDrop";		//Boss Kill Drop 템플리트
	 const SKILL = "Skill";		//Skill 템플리트
	 const MONSTER = "Monster";		//Monster 템플리트
}

class GameConstant
{
	 const GAME_CODE = 14001;		//게임 코드
	 const GAME_NAME = "Project-A";		//게임명
}

class PlatformCode
{
	 const 509_AUTH = 1;		//Platform 종류
	 const KAKAO_AUTH = 2;		//Platform 종류
	 const FACE_BOOK_AUTH = 3;		//Platform 종류
	 const T_STORE_AUTH = 4;		//Platform 종류
	 const LINE_AUTH = 5;		//Platform 종류
	 const TWEETER_AUTH = 6;		//Platform 종류
}

class LanguageType
{
	 const KOREA = 1;		//언어 종류
	 const ENGLISH = 2;		//언어 종류
	 const CHINA = 3;		//언어 종류
}

class OSType
{
	 const IOS = 10;		//OS 종류
	 const ANDROID = 20;		//OS 종류
	 const WINDOWS = 30;		//OS 종류
}

class StoreType
{
	 const ITUNE_STORE = 1;		//Store 종류
	 const T_STORE = 2;		//Store 종류
	 const OLE_MARKET = 3;		//Store 종류
	 const LG_U_PLUS = 4;		//Store 종류
	 const GOOGLE_PLAY_STORE = 5;		//Store 종류
}

class GamePlayType
{
	 const SENARIO = "Senario";		//시나리오 게임 플레이
}

class ObjectType
{
	 const GM = "GM";		//GM 종류
	 const PC = "PC";		//PC 종류
	 const ITEM = "Item";		//Equipment 종류
	 const SKILL = "Skill";		//Skill 종류
	 const INVENTORY = "Inventory";		//Inventory 종류
	 const NPC = "NPC";		//NPC 종류
	 const TICKET = "Ticket";		//Ticket 종류
	 const MONEY = "Money";		//화폐 종류
	 const POINT = "Point";		//Point 종류
	 const GACHA = "Gacha";		//Gacha 종류
}

class ItemType
{
	 const WEAPON = 1;		//무기
	 const CLOTH = 2;		//의상
	 const SHOULDER = 3;		//어깨
	 const SHOES = 4;		//신발
	 const GLOVES = 5;		//장갑
	 const DECO = 6;		//장식
	 const NECKLACE = 7;		//목걸이
	 const RING = 8;		//반지
	 const JEM = 9;		//보석
}

class InventoryType
{
	 const EQUIP = 1;		//장착 인벤토리
	 const WEAPON = 2;		//장비 인벤토리
	 const ACCESSORY = 3;		//장신구 인벤토리
}

class InventoryConstant
{
	 const MAX_ITEM = 40;		//아이템 최대 보관 개수
}

class TicketType
{
	 const GAME_KEY = 1;		//게임 열쇠
	 const PVP = 2;		//PvP 티켓
	 const FREE_FIGHT = 3;		//난투장 티켓
	 const GUILD = 4;		//길드 티켓
}

class MoneyType
{
	 const GOLD = 1;		//컨텐츠 이용하는 골드
	 const CRYSTAL = 2;		//컨텐츠 이용하는 수정
}

class PointType
{
	 const FRIEND_POINT = 1;		//우정 포인트
}

class NPCType
{
	 const MONSTER = 1;		//일반 몬스터
	 const BREAK_OBJECT = 2;		//장식물(파괴가능)
	 const BOSS = 3;		//보스
	 const TRAP = 4;		//트랩(파괴불가능)
}

class PCType
{
	 const WARRIOR = 1;		//플레이어 캐릭터(전사)
	 const MAGICIAN = 2;		//플레이어 캐릭터(술사)
}
?>