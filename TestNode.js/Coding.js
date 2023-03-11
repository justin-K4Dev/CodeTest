var FS = require('fs');
var mysql = require('mysql');

// uncaughtException
process.on('uncaughtException', function (err) {
    console.log('Caught exception: ' + err.stack);
});

// MySQL : justin VM
var config = {
//    debug : true,
    host : '192.168.1.131',
    user : 'root',
    password : 'kang14',
    connectionLimit : 10,
    supportBigNumbers : true,  // BIGINT(17자리 이상 숫자)의 문자열 처리
    bigNumberStrings : false,  // BIGINT라 하더라도 17자리가 넘지 않는 숫자는 숫자로 처리, true 이면 무조건 문자열로 처리
    multipleStatements : true	
};

var DBPOOL = mysql.createPool(config);
const JSON_DIR = './GameTemplateData';


// Redis : justin VM
var assert = require('assert');
var RedisPool = require('pool-redis')({
    'host': '192.168.1.111',
    'password': 'kang14',
    'maxConnections': 5
});



function isServerTemplate(ID) {

    switch (ID) { 
        case 11: // character
        case 12: // tank
        case 13: // tower
        // case 14: // ?? - 제거됨
        case 15: // shield
        case 16: // item
        case 17: // gacha
        case 18: // setting
        case 19: // reward_item
        case 20: // shop
		// case 21: // ani
		// case 22: // character_ani
        case 23: // buff
        case 24: // skill
		// case 25: // missile
		// case 26: // map - ?
        case 27: // stage
        case 28: // boss_stage
        case 30: // numen
		// case 31: // attack_priority
        case 32: // constant
        case 33: // enchant_rate
        case 34: // league_levels
		//case 35: // mix_rate - 합성 자체가 사라짐
        case 36: // unit_guardian - ?
		//case 37: // unit_train
        case 38: // command_center
		// case 39: // tower_wave
        case 40: // reward_mail
        case 41: // reward_rank
		//case 42: // arena_wave_type
        case 43: // friend_present
        case 44: // achievement
		// case 45: // random_wave_type
        case 46: // item_enchant_rate
        case 47: // quest
        case 48: // sanctuary
        case 49: // guild
        case 50: // emblem
        case 51: // collection_group
        case 52: // collection
        case 53: // manufacture
        case 54: // worldmap
        case 56: // mission
        case 57: // promotion
        case 58: // day_boss
		// case 59: // tutorial_setup
		// case 60: // tutorial_sequence
		// case 61: // dialogue
        case 62: // alarm
		// case 63: // guide_type
		// case 64: // guide
        case 65: // guild_boss
        case 67: // warfare
        case 68: // package
        case 69: // shop_personal
        case 71: // vip
        case 83: // attendance
        case 84: // gacha_correction
        // case 85: // button_open
        // case 86: // scene_enter
        case 87: // character_combine
        // case 88: // UNKNOWN
        // case 89: // material_info
        case 90: // series_item
        case 91: // series
        case 92: // beginner_adventure
        // case 93: // UNKNOWN
        // case 94: // UNKNOWN
        // case 95: // UNKNOWN
        case 96: // user_level
		// case 97: // text
		// case 98: // text_error
        case 99:// global
            return true;
            break;
    }

    return false;
}


var category = null;

try {
    category = JSON.parse(FS.readFileSync(JSON_DIR + '/category.json'));
} 
catch (err) {
    console.log('Failed to parse category.json');
}


var multi = RedisPool.multi();


var GameTemplate = 'GT';
multi.del( GameTemplate );
multi.hset( GameTemplate, 'category', JSON.stringify( category ) );


// json file load and cache to Redis
function cacheToRedis() {
    for( var i = 0; i < category.length; ++i) {
        
        var ID = category[i].id;
        if (!isServerTemplate(ID))
            continue;
        
        var gameTemplateName = category[i].name;
        
        try {
            var templateList = JSON.parse(FS.readFileSync(JSON_DIR + '/' + gameTemplateName + '.json'));
        } 
        catch (err) {
            consloe.log('Failed to parse TemplateName:' + gameTemplateName + '.json');
            throw err;
        }
        
        // game template 정보를 id 기준으로 저장
        consloe.log('ID Based Save start !!!' + ' GTName:' + gameTemplateName);
        
        var gameTemplateKey = GameTemplate + '::' + gameTemplateName + '::' + 'ID';
        var gameTemplateByID = {};
        
        for (var j = 0; j < templateList.length; ++j) {
            var templateInfo = templateList[j];
            gameTemplateByID[templateInfo.id] = templateInfo;
            
            multi.hset(gameTemplateKey, templateInfo.id, JSON.stringify(templateInfo));
            
            consloe.log('GTKey:' + gameTemplateKey + ' ID:' + templateInfo.id + ' Count:' + (j + 1));
        }
        consloe.log('ID Based Save End $$' + ' GTName:' + gameTemplateName + ' Count:' + templateList.length);
        
        // game template 정보 종류별 구분 저장
        var gameTemplateBuffer = [];
        var gameTemplateList = {};
        
        // 종류별 그룹화 수준까지만 처리 하며 id 기반 단일 등록은 위에서 처리 했으므로 필요 없음 !!!
        
        switch (gameTemplateName) {

            case 'setting': {
                consloe.log('Kind Save start !!!' + ' GTName:' + gameTemplateName);
                
                var mainKey = GameTemplate + '::' + gameTemplateName + '::' + 'type';
                for (var j = 0; j < templateList.length; ++j) {
                    var templateInfo = templateList[j];
                    
                    var subKey = templateInfo.type;
                    multi.hset(mainKey, subKey, JSON.stringify(templateInfo));
                    
                    consloe.log('GTKey:' + gameTemplateKey + ' ID:' + templateInfo.id);
                }
                consloe.log('Kind Save End $$' + ' GTName:' + gameTemplateName);
            } break;

            case 'tower': {
                consloe.log('Kind Save start !!!' + ' GTName:' + gameTemplateName);
                
                var mainKey = GameTemplate + '::' + 'idun' + '::' + 'type';
                for (var j = 0; j < templateList.length; ++j) {
                    var templateInfo = templateList[j];
                    
                    if (templateInfo.type == 11 && templateInfo.class == 6) {
                        var subKey = templateInfo.type;
                        multi.hset(mainKey, subKey, JSON.stringify(templateInfo));
                    }
                }
                consloe.log('Kind Save End $$' + ' GTName:' + gameTemplateName);
            } break;

            case 'beginner_adventure': {
                consloe.log('Kind Save start !!!' + ' GTName:' + gameTemplateName);
                
                var mainKey = GameTemplate + '::' + gameTemplateName + '::' + 'grade';
                for (var j = 0; j < templateList.length; ++j) {
                    var templateInfo = templateList[j];
                    
                    var subKey = templateInfo.grade;
                    multi.hset(mainKey, subKey, JSON.stringify(templateInfo));
                }
                consloe.log('Kind Save End $$' + ' GTName:' + gameTemplateName);
            } break;

            case 'buff': {
                consloe.log('Kind Save start !!!' + ' GTName:' + gameTemplateName);
                
                var mainKey = GameTemplate + '::' + gameTemplateName + '::' + 'type::guild_level';
                for (var j = 0; j < templateList.length; ++j) {
                    var templateInfo = templateList[j];
                    
                    if (4 == templateInfo.type || 5 == templateInfo.type) {
                        var subKey = templateInfo.type + '::' + templateInfo.guild_level;
                        multi.hset(mainKey, subKey, JSON.stringify(templateInfo));
                    }
                }
                consloe.log('Kind Save End $$' + ' GTName:' + gameTemplateName);
            } break;

            case 'day_boss': {
                consloe.log('Kind Save start !!!' + ' GTName:' + gameTemplateName);
                
                var mainKey = GameTemplate + '::' + gameTemplateName + '::' + 'type::id';
                for (var j = 0; j < templateList.length; ++j) {
                    var templateInfo = templateList[j];
                    
                    var subKey = templateInfo.type + '::' + templateInfo.id;
                    multi.hset(mainKey, subKey, JSON.stringify(templateInfo));
                }
                consloe.log('Kind Save End $$' + ' GTName:' + gameTemplateName);
            } break;

            case 'attendance': {
                consloe.log('Kind Save start !!!' + ' GTName:' + gameTemplateName);
                
                var mainKey = GameTemplate + '::' + gameTemplateName + '::' + 'type::id';
                for (var j = 0; j < templateList.length; ++j) {
                    var templateInfo = templateList[j];
                    
                    var subKey = templateInfo.type + '::' + templateInfo.id;
                    multi.hset(mainKey, subKey, JSON.stringify(templateInfo));
                }
                consloe.log('Kind Save End $$' + ' GTName:' + gameTemplateName);
            } break;

            case 'guild':
            case 'user_level':
            case 'promotion': {
                consloe.log('Kind Save start !!!' + ' GTName:' + gameTemplateName);
                
                var mainKey = GameTemplate + '::' + gameTemplateName + '::' + 'type';
                for (var j = 0; j < templateList.length; ++j) {
                    var templateInfo = templateList[j];
                    
                    var subKey = templateInfo.type;
                    multi.hset(mainKey, subKey, JSON.stringify(templateInfo));
                }
                consloe.log('Kind Save End $$' + ' GTName:' + gameTemplateName);
            } break;

            case 'gacha': {
                consloe.log('Kind Save start !!!' + ' GTName:' + gameTemplateName);
                
                var mainKey = GameTemplate + '::' + gameTemplateName + '::' + 'type';
                gameTemplateList[mainKey] = {};
                for (var j = 0; j < templateList.length; ++j) {
                    var templateInfo = templateList[j];
                    
                    var subKey = templateInfo.type;
                    if (!gameTemplateList[mainKey][subKey]) {
                        gameTemplateList[mainKey][subKey] = { 'list': [], 'totalRate': 0 }
                    };
                    gameTemplateList[mainKey][subKey].list.push(templateInfo);
                    gameTemplateList[mainKey][subKey].totalRate += templateInfo.rate;
                }
                for (var typeKey in gameTemplateList[mainKey]) {
                    multi.hset(mainKey, typeKey, JSON.stringify(gameTemplateList[mainKey][typeKey]));
                }
                consloe.log('Kind Save End $$' + ' GTName:' + gameTemplateName);
            } break;

            case 'quest': {
                consloe.log('Kind Save start !!!' + ' GTName:' + gameTemplateName);
                
                var mainKey = GameTemplate + '::' + gameTemplateName + '::' + 'type';
                gameTemplateList[mainKey] = {};
                for (var j = 0; j < templateList.length; ++j) {
                    var templateInfo = templateList[j];
                    
                    var subKey = templateInfo.group_id;
                    if (!gameTemplateList[mainKey][subKey]) {
                        gameTemplateList[mainKey][subKey] = { 'list': [] };
                    };
                    gameTemplateList[mainKey][subKey].list.push(templateInfo);
                }
                for (var typeKey in gameTemplateList[mainKey]) {
                    multi.hset(mainKey, typeKey, JSON.stringify(gameTemplateList[mainKey][typeKey]));
                }
                consloe.log('Kind Save End $$' + ' GTName:' + gameTemplateName);
            } break;

            case 'stage': {
                consloe.log('Kind Save start !!!' + ' GTName:' + gameTemplateName);
                
                var mainKey = GameTemplate + '::' + gameTemplateName + '::' + 'type::class::kind';
                gameTemplateList[mainKey] = {};
                for (var j = 0; j < templateList.length; ++j) {
                    var templateInfo = templateList[j];
                    
                    var subKey = templateInfo.type + '::' + templateInfo.class + '::' + templateInfo.kind;
                    multi.hset(mainKey, subKey, JSON.stringify(templateInfo));
                }
                consloe.log('Kind Save End $$' + ' GTName:' + gameTemplateName);
            } break;

            case 'worldmap': {
                consloe.log('Kind Save start !!!' + ' GTName:' + gameTemplateName);
                
                var mainKey = GameTemplate + '::' + gameTemplateName + '::' + 'type::class';
                for (var j = 0; j < templateList.length; ++j) {
                    var templateInfo = templateList[j];
                    
                    var subKey = templateInfo.type + '::' + templateInfo.class;
                    multi.hset(mainKey, subKey, JSON.stringify(templateInfo));
                }
                consloe.log('Kind Save End $$' + ' GTName:' + gameTemplateName);
            } break;

            case 'global': {
                consloe.log('Kind Save start !!!' + ' GTName:' + gameTemplateName);
                
                var mainKey1 = GameTemplate + '::' + gameTemplateName + '::' + 'description';
                for (var j = 0; j < templateList.length; ++j) {
                    var templateInfo = templateList[j];
                    
                    var subKey = templateInfo.description;
                    multi.hset(mainKey1, subKey, JSON.stringify(templateInfo.value));
                    
                    if (templateInfo.value_cid) {
                        var mainKey2 = GameTemplate + '::' + gameTemplateName + '::' + 'description_cid';
                        
                        subKey = templateInfo.description + '_cid';
                        multi.hset(mainKey2, subKey, JSON.stringify(templateInfo.value_cid));
                    }
                }
                consloe.log('Kind Save End $$' + ' GTName:' + gameTemplateName);
            } break;

            // case 'numen': 참조형 게임 템플리트
            // templateInfo.id -> templateInfo.character_id -> characterTemplateInfo[templateInfo.character_id] 에서 가져옴
            // 따라서 별도 구분 저장 필요 없음 !!!

            case 'shop_personal': {
                consloe.log('Kind Save start !!!' + ' GTName:' + gameTemplateName);
                
                var mainKey = GameTemplate + '::' + gameTemplateName + '::' + 'class';
                for (var j = 0; j < templateList.length; ++j) {
                    var templateInfo = templateList[j];
                    
                    var subKey = templateInfo.class;
                    multi.hset(mainKey, subKey, JSON.stringify(templateInfo));
                }
                consloe.log('Kind Save End $$' + ' GTName:' + gameTemplateName);
            } break;

            case 'vip': {
                consloe.log('Kind Save start !!!' + ' GTName:' + gameTemplateName);
                
                var mainKey = GameTemplate + '::' + gameTemplateName + '::' + 'type';
                for (var j = 0; j < templateList.length; ++j) {
                    var templateInfo = templateList[j];
                    
                    var subKey = templateInfo.type;
                    multi.hset(mainKey, subKey, JSON.stringify(templateInfo));
                }
                consloe.log('Kind Save End $$' + ' GTName:' + gameTemplateName);
            } break;
        }
    }
} // end of cacheToRedis()

function loadFromRedis() {





}

















