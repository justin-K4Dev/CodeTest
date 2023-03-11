<?php
///////////////////////////////////////////////////////////////////////////////
/// @file Protocol.inc
/// @title 프로토콜용 COMMAND, KEY 상수 클래스 
/// @brief 클라이언트와 통신시 필요한 값들이므로 값 수정시 클라이언트파트와 협의 요함.
/// 
/// @author giman
/// @date 2013. 8. 9. 오전 11:35:46
///////////////////////////////////////////////////////////////////////////////


// Eternal Crash 
// Protocol Command Key List
class COMMAND
{	
	// NO_AUTH_LOGIN 인증용 테스트 계정 관리
	const ID_UNIQUE_CHECK = "ID_UNIQUE_CHECK";
	const MEMBER_SIGN_UP = "MEMBER_SIGN_UP";
	const MEMBER_WITHDRAWAL = "MEMBER_WITHDRAWAL";
	
	// Patch URL
	const CLIENT_VERSION_PATCH_URL = 'CLIENT_VERSION_PATCH_URL';
	
	// 인증
	const NO_AUTH_LOGIN = "NO_AUTH_LOGIN";
	const LOGIN = "LOGIN";
	const LOGOUT = "LOGOUT";
	
	// 초기화
	const INIT = "INIT";
	
	// 캐릭터, 헤어, 의상 구매
	const ITEM_BUY = "ITEM_BUY";
	
	// 헤어, 의상 장착/해제
	const ITEM_EQUIP = "ITEM_EQUIP";
	const ITEM_UNEQUIP = "ITEM_UNEQUIP";
	
	//친구초대
	const FRIEND_INVITE = "FRIEND_INVITE";
	
	//친구리스트
	const FRIEND_LIST = "FRIEND_LIST";
	
	//자랑하기
	const BOAST_SCORE = "BOAST_SCORE";
	
	//티켓선물
	const TICKET_SEND = "TICKET_SEND";
	
	//티켓갱신
	const TICKET_TICK = "TICKET_TICK";

	//선물리스트
	const GIFT_LIST = "GIFT_LIST";
	
	//선물받기
	const GIFT_ACCEPT = "GIFT_ACCEPT";
	
	//선물 뽑기
	const PRIZE_PICKUP = "PRIZE_PICKUP";
	
	//서포터 고용
	const SUPPORTER_EMPLOY = "SUPPORTER_EMPLOY";
	
	// 게임 시작
	const GAME_START = "GAME_START";

	// 게임 완료
	const GAME_FINISH = "GAME_FINISH";
	
	// 쿠폰 암호화 요청
	const COUPON_ENCRYPT = "COUPON_ENCRYPT";

	// 캐릭터 뽑기
	const CHARACTER_DRAW = "CHARACTER_DRAW";

	// 장비 뽑기
	const STUFF_DRAW = "STUFF_DRAW";
	
	// 메달로 코인 종류 구매
	const COIN_BUY_BY_MEDAL = "COIN_BUY_BY_MEDAL";
	
	// 캐쉬로 매달 구매
	const MEDAL_BUY_BY_CASH = "MEDAL_BUY_BY_CASH";
}


?>