var FS = require('fs');
var mysql = require('mysql');


var CONFIG = require('./config');
var ECUTIL = require(CONFIG.LIB_DIR + '/ECUTIL');
var SENTINEL = require(CONFIG.LIB_DIR + '/SENTINEL');
var PROCESS = require(CONFIG.LIB_DIR + '/PROTOCOL').PROCESS;
var DBPOOL = mysql.createPool(CONFIG.SERVER.mysql.game.master);

const JSON_DIR = CONFIG.HOME + '/JSON'; 

function consoleWrite() {
    var args = [];
    for (var i = 0; i < arguments.length; ++i) args.push(arguments[i]);
    var text = ECUTIL.format.apply(null, args);
    var text = util.format.apply(null, args);
    
    console.log(text);
    if (process.send) process.send(text);
}


/*
// justin 테스트용
var config = {
    //    debug : true,
    host : '192.168.1.131',
    user : 'root',
    password : 'kang14',
    connectionLimit : 10,
    supportBigNumbers : true,
    bigNumberStrings : false,
    multipleStatements : true
};

var DBPOOL = mysql.createPool(config);
const JSON_DIR = './GameTemplate';

function consoleWrite(values) {
    console.log(values);
}
*/

function isDBGameTemplate(templateName) {
    
    switch (templateName) {
        case 'mission':
        case 'quest':
        case 'achievement':
        case 'collection':
        case 'item':
        case 'shop':
        case 'gacha':
        case 'gacha_correction':

        case 'guild':
        case 'buff':
        case 'tank':
        case 'skill':
        case 'numen':
        case 'beginner_adventure':
        case 'global':
        case 'stage':
        case 'package':
        case 'reward_item':// Global DB 에 추가 - justin
        case 'character':
            return true;
    }
    
    return false;
}

function execQuery(querys, callback) {
    
    consoleWrite('Query - TotalQueryCount:' + querys.length);
    
    var startTime, endTime;
    
    var query_length = querys.length;
    if (query_length > 5000) {
        
        var qs = [];
        while (querys.length > 0) qs.push(querys.splice(0, 5000));
        var total_length = 0;
        for (var i = 0; i < qs.length; ++i) total_length += qs[i].length;
        if (query_length == total_length) {
            function qq(q) {
                var query = q.join(';');
                
                consoleWrite('Split Query - Count:' + q.length);
                
                consoleWrite('Split Query Start ---------------------------------------------');
                startTime = +new Date();
                
                DBPOOL.query(query, function (err) {
                    if (err) throw err;
                    
                    endTime = +new Date();
                    consoleWrite('Completed Split Query - Count:' + q.length + ' ElapsedTime:' + (endTime - startTime) + 'ms');
                    
                    if (qs.length > 0) {
                        qq(qs.shift());
                    }
                    else {
                        consoleWrite('Completed Split Query All - QueryCount:' + query_length);
                        callback();
                    }
                });
            }
            qq(qs.shift());
        }
        else {
            consoleWrite('Incorrected Query Count !!! - InQueryCount:' + query_length + 'CalQueryCount:' + total_length);
        }
    }
    else {
        var query = querys.join(';');
        
        consoleWrite('Query - Count:' + query_length);
        consoleWrite('Query Start 1 ---------------------------------------------');
        startTime = +new Date();
        
        DBPOOL.query(query, function (err) {
            if (err) throw err;
            
            endTime = +new Date();
            consoleWrite('Completed Query - Count:' + query_length + ' ElapsedTime:' + (endTime - startTime) + 'ms');
            
            callback();
        });
    }
}

var pool_count = 0;

function updateProtocolTemplate(callback) {
    
    if (--pool_count > 0) return;
    
    var GLOBAL_DBs = [];
    
    ///////////////////////////////////////////////////////////////////////////////////////
    GLOBAL_DBs.push('DROP TABLE IF EXISTS EC_GlobalDB.x_protocol');
    GLOBAL_DBs.push('DROP TABLE IF EXISTS EC_GlobalDB.o_protocol');
    GLOBAL_DBs.push('CREATE TABLE EC_GlobalDB.x_protocol LIKE EC_GlobalDB.protocol');
    for (var key in PROCESS) {
        GLOBAL_DBs.push(mysql.format('INSERT INTO EC_GlobalDB.x_protocol SET ?', { 'protocol': key, 'name': PROCESS[key] }));
    }
    GLOBAL_DBs.push('RENAME TABLE EC_GlobalDB.protocol TO EC_GlobalDB.o_protocol');
    GLOBAL_DBs.push('RENAME TABLE EC_GlobalDB.x_protocol TO EC_GlobalDB.protocol');
    GLOBAL_DBs.push('DROP TABLE IF EXISTS EC_GlobalDB.o_protocol');
    
    ///////////////////////////////////////////////////////////////////////////////////////
    GLOBAL_DBs.push('DROP TABLE IF EXISTS EC_GlobalDB.x_cm_code');
    GLOBAL_DBs.push('DROP TABLE IF EXISTS EC_GlobalDB.o_cm_code');
    GLOBAL_DBs.push('CREATE TABLE EC_GlobalDB.x_cm_code LIKE EC_GlobalDB.cm_code');
    
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (1000100, "마켓", "G", "GoogleStore", now()), (1000100, "마켓", "A", "AppleStore", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (1000200, "플랫폼", "GS", "GueSt", now()), (1000200, "플랫폼", "GP", "GooglePlay", now()), (1000200, "플랫폼", "GC", "appleGameCenter", now()), (1000200, "플랫폼", "FB", "FaceBook", now()), (1000200, "플랫폼", "NV", "Naver", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (1000300, "OS", "I", "iOS", now()), (1000300, "OS", "A", "Android", now()), (1000300, "OS", "W", "Windows", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (1000400, "계정구분", "1", "BOT", now()), (1000400, "계정구분", "3", "일반유저", now()), (1000400, "계정구분", "5", "게임메니저", now()), (1000400, "계정구분", "7", "내부계정", now())');
    // GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (1000500, "로그인구분", "F", "설치후 최초", now()), (1000500, "로그인구분",  "T", "튜토리얼 진행", now()), (1000500, "로그인구분", "N", "일반", now())'); // 제거됨, 
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (1000600, "국가구분", "KR", "한국", now()), (1000600, "국가구분",  "US", "미국", now()), (1000600, "국가구분", "CN", "중국", now()), (1000600, "국가구분", "JP", "일본", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (1000700, "언어구분", "ko", "한국어", now()), (1000700, "언어구분",  "en", "영어", now()), (1000700, "언어구분", "zh", "중국어", now()), (1000700, "언어구분", "ja", "일본어", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (1000800, "자원구분", "1", "골드", now()), (1000800, "자원구분", "2", "다이아몬드", now()), (1000800, "자원구분", "4", "식량(하트)", now()), (1000800, "자원구분", "5", "트로피", now()), (1000800, "자원구분", "6", "열쇠", now()), (1000800, "자원구분", "7", "전투력", now()), (1000800, "자원구분", "8", "우정석", now()), (1000800, "자원구분", "9", "명예점수", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (1000900, "증가/감소", "1", "증가", now()), (1000900, "증가/감소", "2", "감소", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (1001000, "성공/실패", "Y", "성공", now()), (1001000, "성공/실패", "N", "실패", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (1001100, "승리/패배", "W", "승리", now()), (1001100, "승리/패배", "L", "패배", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (1001200, "생성/해체", "1", "생성", now()), (1001200, "생성/해체", "2", "해체", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (1001300, "1회성/반복", "0", "1회성", now()), (1001300, "1회성/반복", "1", "반복", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (1001400, "캐시로그타입", "B", "구매(Buy)", now()), (1001400, "캐시로그타입", "R", "환불(Refund)", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (1001500, "결제수단", "C", "신용카드", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (1001600, "통화타입", "1", "미국달러(USD)", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) SELECT DISTINCT 2000100, "프로토콜", name, name, now() FROM EC_GlobalDB.`protocol`');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, ext_int1, ext_int2, ext_int3, ext_str1, ext_str2, ext_str3, reg_date) SELECT DISTINCT 2000200, "캐릭터", character_id, description, `class`, kind, tier, "구분", "종류", "등급", now() FROM EC_GlobalDB.character WHERE `class` > 0 AND tier > 0 AND kind > 0');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) SELECT DISTINCT 2000210, "캐릭터:구분", `class`, description, now() FROM EC_GlobalDB.character WHERE `class` > 0 AND tier > 0 AND kind > 0 GROUP BY `class`');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) SELECT DISTINCT 2000220, "캐릭터:종류", kind, description, now() FROM EC_GlobalDB.character WHERE `class` > 0 AND tier > 0 AND kind > 0');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) SELECT DISTINCT 2000230, "캐릭터:등급", tier, CONCAT(tier,"등급"), now() FROM EC_GlobalDB.character WHERE `class` > 0 AND tier > 0 AND kind > 0');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, ext_int1, ext_int2, ext_int3, ext_str1, ext_str2, ext_str3, reg_date) SELECT DISTINCT 2000300, "아이템", item_id, description, type, `class`, tier, "구분", "종류", "등급", now() FROM EC_GlobalDB.`item`');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) values (2000310, "아이템:구분", 1, "유닛(캐릭터)", now()), (2000310, "아이템:구분", 2, "전차", now()), (2000310, "아이템:구분", 3, "건물", now()), (2000310, "아이템:구분", 4, "장비", now()), (2000310, "아이템:구분", 5, "쉴드", now()), (2000310, "아이템:구분", 6, "자원", now()), (2000310, "아이템:구분", 7, "보물상자", now()), (2000310, "아이템:구분", 8, "재료", now()), (2000310, "아이템:구분", 9, "버프", now()), (2000310, "아이템:구분", 10, "소모품", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) SELECT DISTINCT 2000320, "아이템:장비:등급", tier, CONCAT(tier,"등급 장비"), now() FROM EC_GlobalDB.`item` WHERE tier > 0');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (2000330, "아이템:장비:종류", 1, "무기", now()), (2000330, "아이템:장비:종류", 2, "갑옷", now()), (2000330, "아이템:장비:종류", 3, "투구", now()), (2000330, "아이템:장비:종류", 4, "반지", now()), (2000330, "아이템:장비:종류", 5, "목걸이", now()), (2000330, "아이템:장비:종류", 6, "귀고리", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (2000340, "아이템:건물:종류", 1, "방어탑", now()), (2000340, "아이템:건물:종류", 2, "지상설치물", now()), (2000340, "아이템:건물:종류", 3, "성벽설치물", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (2000350, "아이템:재료:종류", 1, "수호신 소환서", now()), (2000350, "아이템:재료:종류", 5, "제작재료", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (2000360, "아이템:소모품:종류", 1, "확성기", now()), (2000360, "아이템:소모품:종류", 2, "닉네임 변경권", now()), (2000360, "아이템:소모품:종류", 3, "길드명 변경권", now()), (2000360, "아이템:소모품:종류", 4, "경험치 아이템", now()), (2000360, "아이템:소모품:종류", 5, "퀘스트 지급 아이템", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) SELECT DISTINCT 2000400, "상점", shop_id, description, now() FROM EC_GlobalDB.`shop`');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, ext_int1, ext_int2, ext_str1, ext_str2, reg_date) SELECT DISTINCT 2000500, "가챠", gacha_id, description, item_id, count, "아이템ID", "지급수량", now() FROM EC_GlobalDB.`gacha`');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) SELECT DISTINCT 2000600, "전차", tank_id, description, now() FROM EC_GlobalDB.`tank`');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) SELECT DISTINCT 2000610, "전차:구분", `class`, description, now() FROM EC_GlobalDB.`tank`');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) SELECT DISTINCT 2000700, "스킬", skill_id, description, now() FROM EC_GlobalDB.`skill`');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) SELECT DISTINCT 2000800, "버프", buff_id, description, now() FROM EC_GlobalDB.`buff`');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, ext_int1, ext_int2, ext_str1, ext_str2, reg_date) SELECT DISTINCT 3000100, "퀘스트", mission_id, description, 1, count, "일일미션", "목표", now() FROM EC_GlobalDB.`mission`');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, ext_int1, ext_str1, reg_date) SELECT DISTINCT 3000100, "퀘스트", quest_id, description, 2,  "퀘스트", now() FROM EC_GlobalDB.`quest`');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, ext_int1, ext_int2, ext_str1, ext_str2, reg_date) SELECT DISTINCT 3000100, "퀘스트", achievement_id, description, 3, count, "도전과제", "목표", now() FROM EC_GlobalDB.`achievement`');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, ext_int1, ext_str1, reg_date) SELECT DISTINCT 3000100, "퀘스트", collection_id, description, 4,  "도감", now() FROM EC_GlobalDB.`collection`');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) VALUES (3000110, "퀘스트:구분", "1", "일일미션", now()), (3000110, "퀘스트:구분", "2", "퀘스트", now()), (3000110, "퀘스트:구분", "3", "도전과제", now()), (3000110, "퀘스트:구분", "4", "도감", now())');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) SELECT DISTINCT 3000200, "수호신", character_id, description, now() FROM EC_GlobalDB.`numen`');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) SELECT DISTINCT 3000210, "월드맵스테이지", stage, description, now() FROM EC_GlobalDB.`stage`');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) SELECT DISTINCT 3000220, "패키지상품", package_id, description, now() FROM EC_GlobalDB.`package`');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) SELECT DISTINCT 3000230, "애플스토어인앱ID", apple_inapp_id, buy_value, now() FROM EC_GlobalDB.`shop` WHERE apple_inapp_id IS NOT NULL');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) SELECT DISTINCT 3000240, "구글스토어인앱ID", google_inapp_id, buy_value, now() FROM EC_GlobalDB.`shop` WHERE google_inapp_id IS NOT NULL');
    GLOBAL_DBs.push('INSERT INTO EC_GlobalDB.x_cm_code (main_cd, main_name, sub_cd, sub_name, reg_date) SELECT DISTINCT 3000250, "보스", character_id, description, now() FROM EC_GlobalDB.`character` WHERE type = 3');
    
    GLOBAL_DBs.push('RENAME TABLE EC_GlobalDB.cm_code TO EC_GlobalDB.o_cm_code');
    GLOBAL_DBs.push('RENAME TABLE EC_GlobalDB.x_cm_code TO EC_GlobalDB.cm_code');
    GLOBAL_DBs.push('DROP TABLE IF EXISTS EC_GlobalDB.o_cm_code');
    
    ///////////////////////////////////////////////////////////////////////////////////////
    var query = mysql.format(GLOBAL_DBs.join(';'));
    DBPOOL.query(query, function (err) {
        if (err)
            throw err;
        
        if (callback)
            callback(null);
    });
}

var REG_DATE = new Date();

var templates = {};
var swapQueryList = 'RENAME TABLE';
var dropQueryList = 'DROP TABLE IF EXISTS';

// GameTemplate 를 갱신 하기 쿼리를 생성 & 반환해 준다 - justin
function makeGameTemplateUpdateQuery(templateCategoryList) {
    
    var querys = [];
    
    for (var t = 0; t < templateCategoryList.length; ++t) {
        
        var updatedTemplate = false;
        
        var templateId = templateCategoryList[t].id;
        var TEMPLATE_NAME = templateCategoryList[t].name;
        
        if (!isDBGameTemplate(TEMPLATE_NAME)) {
            continue;
        }
        
        consoleWrite('Category:' + templateId + ', Name:' + TEMPLATE_NAME);
        try {
            var templates = JSON.parse(FS.readFileSync(JSON_DIR + '/' + TEMPLATE_NAME + '.json'));
        } 
        catch (err) {
            consoleWrite(TEMPLATE_NAME + ' Failed to pare JSON object !!!');
            throw err;
        }
        
        switch (TEMPLATE_NAME) {
            case 'reward_item':
                (function (templates) {
                    ++pool_count;
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    
                    for (var k = 0; k < templates.length; ++k) {
                        
                        var reward_item = templates[k];
                        
                        var itemList = '';
                        var itemKey = '';
                        
                        for (var j = 1; j <= 5; ++j) {
                            var itemJson = {};
                            itemKey = 'item' + j + '_category';
                            itemJson[itemKey] = reward_item[itemKey];
                            
                            itemKey = 'item' + j + '_count';
                            itemJson[itemKey] = reward_item[itemKey];
                            
                            itemKey = 'item' + j + '_id';
                            itemJson[itemKey] = reward_item[itemKey];
                            
                            itemKey = 'item' + j + '_rate';
                            itemJson[itemKey] = reward_item[itemKey];
                            
                            itemList += JSON.stringify(itemJson);
                        }
                        itemList = itemList.replace(/}{/g, ",");
                        itemList = itemList.replace(/^{+|}+$/g, "");
                        
                        var templateString = '{' + '"reward_item_id":' + reward_item.id +
										     ',' + '"category":' + reward_item.category + 
										     ',' + '"class":' + reward_item.class + 
										     ',' + '"description":' + '"' + reward_item.description + '"' +
										     ',' + itemList +
										     ',' + '"kind":' + reward_item.kind +
										     ',' + '"type":' + reward_item.type +
										     '}';
                        var rewardItemTemplate = JSON.parse(templateString);
                        
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?, reg_date = now()', rewardItemTemplate);
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;
                    
                })(templates);
                break;

            case 'package':
                (function (templates) {
                    ++pool_count;
                    
                    var shop = JSON.parse(FS.readFileSync(JSON_DIR + '/shop.json'));
                    var shop_templates = {};
                    for (var i = 0; i < shop.length; ++i) {
                        var item = shop[i];
                        shop_templates[item.id] = item;
                    }
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        var x_shop = shop_templates[item.shop_id];
                        
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?, reg_date = now()'
                                                 , { 'package_id': item.id, 'description': item.description, 'shop_id': item.shop_id, 'apple_inapp_id': x_shop.apple_inapp_id, 'google_inapp_id': x_shop.google_inapp_id, 'price_USD': x_shop.buy_value, 'price_KRW': x_shop.google_price });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;

                })(templates);
                break;

            case 'stage':
                (function (templates) {
                    ++pool_count;
                    
                    // 챕터정보 빼오기
                    var chapters = [];
                    var gts = JSON.parse(FS.readFileSync(JSON_DIR + '/global.json'));
                    for (var i = 0; i < gts.length; ++i) {
                        var item = gts[i];
                        var re = /^chapter_([0-9]*)_unlock_stage$/;
                        if (re.test(item.description)) {
                            var n = item.description.replace(re, "$1");
                            chapters[Number(n)] = item.value;
                        }
                    }
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        
                        if (item.type != 1) continue; // 싱글이 아니면
                        var stage = item.id - 270000000;
                        var chapter = 1;
                        for (var c = chapters.length; c--;) {
                            var v = chapters[c];
                            if (v == null) continue;
                            if (stage > v && c > chapter) chapter = c;
                        }
                        var chapter_stage = chapter + '-' + (stage - chapters[chapter]);
                        
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?, reg_date = now()', { 'stage': stage, 'chapter': chapter, 'chapter_stage': chapter_stage, 'description': item.description });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;
                    
                })(templates);
                break;

            case 'global':
                (function (templates) {
                    ++pool_count;
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?', { 'name': item.description, 'value': item.value, 'reg_date': REG_DATE });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;
                    
                })(templates);
                break;

            case 'beginner_adventure':
                (function (templates) {
                    ++pool_count;
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?', { 'grade': item.grade, 'comp_count': item.count, 'description': item.description, 'reg_date': REG_DATE });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;
                    
                })(templates);
                break;

            case 'achievement':
                (function (templates) {
                    ++pool_count;
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?', { 'achievement_id': item.id, 'category': item.category, 'type': item.type, 'class': item.class, 'kind': item.kind, 'group_id': item.group_id, 'grade': item.grade, 'description': item.description, 'count': item.count, 'require_user_level': item.require_user_level, 'require_user_stage': item.require_user_stage, 'reward_item_id': item.reward1_item, 'reward_item_count': item.reward1_item_count, 'reg_date': REG_DATE });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;
                    
                })(templates);
                break;

            case 'quest':
                (function (templates) {
                    ++pool_count;
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?', { 'quest_id': item.id, 'category': item.category, 'type': item.type, 'class': item.class, 'kind': item.kind, 'reward_id': item.reward_ID, 'description': item.Desc, 'reg_date': REG_DATE });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;

                })(templates);
                break;

            case 'collection':
                (function (templates) {
                    ++pool_count;
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?', { 'collection_id': item.id, 'category': item.category, 'type': item.type, 'class': item.class, 'kind': item.kind, 'description': item.description, 'reg_date': REG_DATE });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;

                })(templates);
                break;

            case 'mission':
                (function (templates) {
                    ++pool_count;
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?', { 'mission_id': item.id, 'category': item.category, 'type': item.type, 'class': item.class, 'kind': item.kind, 'description': item.description, 'count': item.count, 'reg_date': REG_DATE });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;

                })(templates);
                break;

            case 'character':
                (function (templates) {
                    ++pool_count;
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        var item_id = (item.template_id != 0) ? item.template_id : null;
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?', { 'character_id': item.id, 'category': item.category, 'type': item.type, 'class': item.class, 'kind': item.set_id, 'grade': item.grade, 'tier': item.tier, 'description': item.description, 'sell_type': item.sell_type, 'sell_value': item.sell_value, 'reg_date': REG_DATE });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;
                    
                })(templates);
                break;

            case 'tank':
                (function (templates) {
                    ++pool_count;
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        var item_id = (item.template_id != 0) ? item.template_id : null;
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?', { 'tank_id': item.id, 'category': item.category, 'type': item.type, 'class': item.class, 'kind': item.kind, 'tier': item.tier, 'description': item.description, 'reg_date': REG_DATE });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;
                    
                })(templates);
                break;

            case 'numen':
                (function (templates) {
                    ++pool_count;
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        var item_id = (item.template_id != 0) ? item.template_id : null;
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?', { 'numen_id': item.id, 'category': item.category, 'character_id': item.character_id, 'type': item.type, 'class': item.class, 'kind': item.kind, 'description': item.description, 'reg_date': REG_DATE });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;

                })(templates);
                break;

            case 'skill':
                (function (templates) {
                    ++pool_count;
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        var item_id = (item.template_id != 0) ? item.template_id : null;
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?', { 'skill_id': item.id, 'category': item.category, 'type': item.type, 'class': item.class, 'kind': item.kind, 'description': item.description, 'reg_date': REG_DATE });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;
                    
                })(templates);
                break;
                            
            case 'gacha':
                (function (templates) {
                    ++pool_count;
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?', { 'gacha_id': item.id, 'gacha_type': item.type, 'gacha_kind': item.kind, 'correction_value': item.correction_value, 'rate': item.rate, 'description': item.name, 'item_id': item.template_id, 'count': item.count, 'reg_date': REG_DATE });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;
                    
                })(templates);
                break;
                            
            case 'gacha_correction':
                (function (templates) {
                    ++pool_count;
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?', { 'gacha_type': item.type, 'min_correction': item.correction_value_start, 'max_correction': item.correction_value_end, 'gacha_kind': item.kind, 'reg_date': REG_DATE });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;

                })(templates);
                break;
                            
            case 'item':
                (function (templates) {
                    ++pool_count;
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        var description = item.description + '(' + item.description2 + ')';
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?', { 'item_id': item.id, 'category': item.category, 'type': item.type, 'class': item.class, 'kind': item.kind, 'tier': item.tier, 'description': description, 'sell_type': item.sell_type, 'sell_value': item.sell_value, 'count': item.count, 'reg_date': REG_DATE });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;

                })(templates);
                break;
                            
            case 'shop':
                (function (templates) {
                    ++pool_count;
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        var item_id = (item.template_id != 0) ? item.template_id : null;
                        var gacha_type = (item.gacha_type != 0) ? item.gacha_type : null;
                        if (item.apple_inapp_id == 'empty') item.apple_inapp_id = null;
                        if (item.google_inapp_id == 'empty') item.google_inapp_id = null;
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?, reg_date = now()', { 'shop_id': item.id, 'category': item.category, 'type': item.type, 'class': item.class, 'kind': item.kind, 'description': item.description, 'item_id': item_id, 'gacha_type': gacha_type, 'buy_type': item.buy_type, 'buy_value': item.buy_value, 'count': item.count, 'apple_inapp_id': item.apple_inapp_id, 'google_inapp_id': item.google_inapp_id });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;
                    
                })(templates);
                break;
                            
            case 'guild':
                (function (templates) {
                    ++pool_count;
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        var level = item.type;
                        var min_point = item.min_guildpoint;
                        var max_point = item.max_guildpoint;
                        var max_members = item.max_guilduser;
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?', { 'level': level, 'min_point': min_point, 'max_point': max_point, 'max_members': max_members });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;

                })(templates);
                break;
                            
            case 'buff':
                (function (templates) {
                    ++pool_count;
                    
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.o_' + TEMPLATE_NAME));
                    querys.push(mysql.format('DROP TABLE IF EXISTS EC_GlobalDB.x_' + TEMPLATE_NAME));
                    querys.push(mysql.format('CREATE TABLE EC_GlobalDB.x_' + TEMPLATE_NAME + ' LIKE EC_GlobalDB.' + TEMPLATE_NAME));
                    for (var i = 0; i < templates.length; ++i) {
                        var item = templates[i];
                        var query = mysql.format('INSERT INTO EC_GlobalDB.x_' + TEMPLATE_NAME + ' SET ?', { 'buff_id': item.id, 'type': item.type, 'class': item.class, 'kind': item.kind, 'guild_level': item.guild_level, 'description': item.description });
                        querys.push(query);
                    }
                    
                    updatedTemplate = true;

                })(templates);
                break;

        }
        
        if (true === updatedTemplate) {
            
            if (pool_count >= 2) {
                swapQueryList += ',';
                dropQueryList += ',';
            }
            swapQueryList += ' EC_GlobalDB.' + TEMPLATE_NAME + ' TO EC_GlobalDB.o_' + TEMPLATE_NAME + ',' + 'EC_GlobalDB.x_' + TEMPLATE_NAME + ' TO EC_GlobalDB.' + TEMPLATE_NAME;
            dropQueryList += ' EC_GlobalDB.o_' + TEMPLATE_NAME;
        }
    }
    
    return { 'count' : pool_count, 'queries' : querys, 'swap' : swapQueryList, 'drop' : dropQueryList };
}

// GameTemplate 갱신 쿼리 생성
// targetTemplateList 에 갱신 template category 를 설정 해준다 !!!
function updateGameTemplate(targetTemplateList) {
    
    var result = makeGameTemplateUpdateQuery(targetTemplateList);
    if (result.count > 0) {
        
        // 임시 테이블 생성 & 기존 템플리트 정보 복사 실행
        consoleWrite('Step 1: Temp table creation query start >>>>>>>>>>>>>>>>>>>>>>>>>>>>');
        execQuery(result.queries, function () {
            
            consoleWrite('Pushed Queries = ' + result.queries);
            
            var queryList;
            
            // 스왑 쿼리 실행
            consoleWrite('Step 2: Swap table query start >>>>>>>>>>>>>>>>>>>>>>>>>>>>');
            queryList = [];
            query = mysql.format(swapQueryList);
            queryList.push(query);
            execQuery(queryList, function () {
                
                // 임시 테이블 삭제 쿼리 실행
                consoleWrite('Step 3: Temp table drop query start >>>>>>>>>>>>>>>>>>>>>>>>>>>>');
                queryList = [];
                query = mysql.format(dropQueryList);
                queryList.push(query);
                execQuery(queryList, function () {
                    
                    // Protocol Template 갱신 실행
                    consoleWrite('Protocol table query start >>>>>>>>>>>>>>>>>>>>>>>>>>>>');
                    updateProtocolTemplate();
                });
            });
        });
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
// 사용 예제 - justin
//////////////////////////////////////////////////////////////////////////////////////////

// GameTemplate Category 정보 읽기
var targetTemplateList = JSON.parse(FS.readFileSync(JSON_DIR + '/category.json'));
// GameTemplate 갱신 - targetTemplateList 에 등록된 GameTemplate 을 갱신 !!!
updateGameTemplate(targetTemplateList);



