<?php 

///////////////////////////////////////////////////////////////////////////////
/// @file Key.inc
/// @class KEY
/// @brief 프로토콜 키 정의 목록
/// (Value는 나중에 셋팅할겁니다! 일단은 디버깅 쉽게 키네임과 같게...)
/// 분류도 나중에 다시 해야함
///
/// @author giman
/// @date 2013. 8. 7. 오후 6:27:10
///////////////////////////////////////////////////////////////////////////////

class KEY
{
	// Common
	const COMMAND = "COMMAND";
	const BODY = "BODY";
	const ERROR_CODE = "ERROR_CODE";
	const ERROR_MESSAGE = "ERROR_MESSAGE";
	const STATUS_CODE = "STATUS_CODE";

	// System
	const URL = "URL";
	const DEVICE_NAME = "DEVICE_NAME";
	const OS_INFO = "OS_INFO";
	const MAC_ADDRESS = "MAC_ADDRESS";
	const CLIENT_VERSION = "CLIENT_VERSION";
	const SERVER_VERSION = "SERVER_VERSION";
	const SERVER_TIME = "SERVER_TIME";
	const APP_ID = "APP_ID";
	const LANGUAGE_TYPE = "LANGUAGE_TYPE";
	const STORE_TYPE = "STORE_TYPE";
	const MESSAGE = "MESSAGE";
	const CODE = "CODE";

	// Auth
	const USER_NO = "USER_NO"; // Kakao 인증 이용시 - Kakao User ID 적재
	const USER_ID = "USER_ID";
	const USER_PW = "USER_PW";
	const ACCESS_TOKEN = "ACCESS_TOKEN";
	const KAKAO_ACCESS_TOKEN = "KAKAO_ACCESS_TOKEN";
	const KAKAO_CLIENT_ID = "KAKAO_CLIENT_ID";
	const KAKAO_SDK_VERSION = "KAKAO_SDK_VERSION";

	// Template
	const TEMPLATE_LIST = "TEMPLATE_LIST";
	const TEMPLATE_ID = "TEMPLATE_ID";
	const OBJECT_TYPE = "OBJECT_TYPE";

	// Coins
	const COIN_TYPE = "COIN_TYPE";
	const TICKET = "TICKET";
	const GOLD = "GOLD";
	const MEDAL = "MEDAL";
	const ADD_TICKET = "ADD_TICKET";
	const ADD_GOLD = "ADD_GOLD";
	const ADD_MEDAL = "ADD_MEDAL";
	const NEXT_TICKET_TIME = "NEXT_TICKET_TIME";
	const TICKET_USE_DATE = 'TICKET_USE_DATE';
	const TICKET_RECHARGE_REMAIN_TIME = 'TICKET_RECHARGE_REMAIN_TIME';

	// Point
	const GIFT_POINT = "GIFT_POINT";

	// Stage
	const CURRENT_STAGE_TID = "CURRENT_STAGE_TID";
	const STAGE_LIST = "STAGE_LIST";
	const STAGE_TID = "STAGE_TID";
	const TOTAL_SCORE = "TOTAL_SCORE";

	// Game Score
	const INGAME_LIST = "INGAME_LIST";
	const INGAME_TID = "INGAME_TID";
	const GAME_TID = "GAME_TID";
	const RECORD = "RECORD";
	const SCORE = "SCORE";
	const ADD_SCORE = "ADD_SCORE";
	const PLAY_GOLD = "PLAY_GOLD";
	const NEW_WEEK_YN = "NEW_WEEK_YN";
	const RESET_WEEK_SCORE_LEFT_TIME = "RESET_WEEK_SCORE_LEFT_TIME";

	// Quest - 등급 달성
	const PERFECT_COUNT = "PERFECT_COUNT";
	const GOOD_COUNT = "GOOD_COUNT";
	const EXCELLENT_COUNT = "EXCELLENT_COUNT";

	// Quest - Fever 횟수
	const FEVER_COUNT = "FEVER_COUNT";

	// Quest - 추가시간 획득
	const GET_ITEM_TIME = "GET_ITEM_TIME";

	// Quest - 골인 시간
	const LAP_TIME = "LAP_TIME";

	// Quest - 추월 횟수
	const PASS_COUNT = "PASS_COUNT";

	// Quest - 거리
	const DISTACNE = "DISTACNE";

	// Quest - 맞춘 횟수
	const ATTACK_COUNT = "ATTACK_COUNT";

	// Quest - 최대힘으로 던진 횟수
	const THROW_COUNT = "THROW_COUNT";

	// Quest - Combo 달성 횟수
	const COMBO_COUNT = "COMBO_COUNT";

	// Quest
	const CLEAR_QUEST_TID_LIST = "CLEAR_QUEST_TID_LIST";
	const QUEST_LIST = "QUEST_LIST";

	// Character
	const CURRENT_CHARACTER_UUID = "CURRENT_CHARACTER_UUID";
	const CHARACTER_LIST = "CHARACTER_LIST";
	const CHARACTER_UUID = "CHARACTER_UUID";
	const CHARACTER_TID = "CHARACTER_TID";
	const RANK = 'RANK';
	const STAR = 'STAR';

	// Item
	const ITEM_TYPE = "ITEM_TYPE";

	// Stuff
	const STUFF_LIST = "STUFF_LIST";
	const STUFF_TID = "STUFF_TID";

	// Skill
	const USE_SKILL_LIST = "USE_SKILL_LIST";
	const SKILL_LIST = "SKILL_LIST";
	const SKILL_TID = "SKILL_TID";

	// Supporter
	const SUPPORTER_TID = "SUPPORTER_TID";
	const SUPPORTER_USER_NO = "SUPPORTER_USER_NO";

	// Friend
	const PLAYER_FRIEND_LIST = "PLAYER_FRIEND_LIST";
	const NON_PLAYER_FRIEND_LIST = "NON_PLAYER_FRIEND_LIST";
	const TARGET_USER_NO = "TARGET_USER_NO";
	const NEXT_SEND_TICKET_TIME = "NEXT_SEND_TICKET_TIME";
	const TICKET_SEND_REMAIN_TIME = "SEND_TICKET_REMAIN_TIME";
	const INVITE_REMAIN_TIME = "INVITE_REMAIN_TIME";
	const INVITE_COUNT = "INVITE_COUNT";
	const SUPPORT_EMPLOY_REMAIN_TIME = "SUPPORT_EMPLOY_REMAIN_TIME";

	//Gift
	const GIFT_ID_LIST = "GIFT_ID_LIST";
	const GIFT_LIST = "GIFT_LIST";
	const GIFT_ID = "GIFT_ID";
	const COUNT = "COUNT";
	const RECV_DATE = "RECV_DATE";
	const SENDER_OBJECT_TYPE = "SENDER_OBJECT_TYPE";
	const REASON_COMMENT = "REASON_COMMENT";

	//Event & Prize
	const EVENT_TID = "EVENT_TID";
	const PRIZE_TID = "PRIZE_TID";

	//Reward
	const REWARD_LIST = "REWARD_LIST";
	const REWARD = "REWARD";
	const REWARD_OBJECT_TYPE = "REWARD_OBJECT_TYPE";
	const REWARD_OBJECT_VALUE = "REWARD_OBJECT_VALUE";

	//Game Management
	const EVENT_NOTICE_LIST = "EVENT_NOTICE_LIST";
	const GAME_NOTICE_LIST = "GAME_NOTICE_LIST";
	const TITLE = "TITLE";
	const CONTENT = "CONTENT";

	/// @brief Shop - justin 2013. 8. 26. 오후 12:03:27
	const GOOGLE_PLAY_PUBLIC_KEY = 'GOOGLE_PLAY_PUBLIC_KEY';
	const PAYMENT_INFO = "PAYMENT_INFO";
	const PAYMENT_SIGNATURE = "PAYMENT_SIGNATURE";
	const SANDBOX_YN = "SANDBOX_YN";
}


?>