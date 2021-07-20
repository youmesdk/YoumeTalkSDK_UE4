// Copyright © 2014-2021 YouMe. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "YouMeConstDefine.h"
#include "vector"
#include "string"
using namespace std;

UENUM(BlueprintType)
enum class EYouMeEvent : uint8
{
	YOUME_EVENT_INIT_OK = 0,  ///< SDK初始化成功
	YOUME_EVENT_INIT_FAILED = 1,  ///< SDK初始化失败
	YOUME_EVENT_JOIN_OK = 2,  ///< 进入语音频道成功
	YOUME_EVENT_JOIN_FAILED = 3,  ///< 进入语音频道失败
	YOUME_EVENT_LEAVED_ONE = 4,  ///< 退出单个语音频道完成
	YOUME_EVENT_LEAVED_ALL = 5,  ///< 退出所有语音频道完成
	YOUME_EVENT_PAUSED = 6,  ///< 暂停语音频道完成
	YOUME_EVENT_RESUMED = 7,  ///< 恢复语音频道完成
	YOUME_EVENT_SPEAK_SUCCESS = 8,  ///< 切换对指定频道讲话成功（适用于多频道模式）
	YOUME_EVENT_SPEAK_FAILED = 9,  ///< 切换对指定频道讲话失败（适用于多频道模式）
	YOUME_EVENT_RECONNECTING = 10, ///< 断网了，正在重连
	YOUME_EVENT_RECONNECTED = 11, ///< 断网重连成功
	YOUME_EVENT_REC_PERMISSION_STATUS = 12, ///< 通知录音权限状态，成功获取权限时错误码为YOUME_SUCCESS，获取失败为YOUME_ERROR_REC_NO_PERMISSION（此时不管麦克风mute状态如何，都没有声音输出）
	YOUME_EVENT_BGM_STOPPED = 13, ///< 通知背景音乐播放结束
	YOUME_EVENT_BGM_FAILED = 14, ///< 通知背景音乐播放失败
	//YOUME_EVENT_MEMBER_CHANGE        = 15, ///< 频道成员变化
	YOUME_EVENT_OTHERS_MIC_ON = 16, ///< 其他用户麦克风打开
	YOUME_EVENT_OTHERS_MIC_OFF = 17, ///< 其他用户麦克风关闭
	YOUME_EVENT_OTHERS_SPEAKER_ON = 18, ///< 其他用户扬声器打开
	YOUME_EVENT_OTHERS_SPEAKER_OFF = 19, ///< 其他用户扬声器关闭
	YOUME_EVENT_OTHERS_VOICE_ON = 20, ///< 其他用户进入讲话状态
	YOUME_EVENT_OTHERS_VOICE_OFF = 21, ///< 其他用户进入静默状态
	YOUME_EVENT_MY_MIC_LEVEL = 22, ///< 麦克风的语音级别

	YOUME_EVENT_MIC_CTR_ON = 23, ///< 麦克风被其他用户打开
	YOUME_EVENT_MIC_CTR_OFF = 24, ///< 麦克风被其他用户关闭    
	YOUME_EVENT_SPEAKER_CTR_ON = 25, ///< 扬声器被其他用户打开
	YOUME_EVENT_SPEAKER_CTR_OFF = 26, ///< 扬声器被其他用户关闭
	YOUME_EVENT_LISTEN_OTHER_ON = 27, ///< 取消屏蔽某人语音
	YOUME_EVENT_LISTEN_OTHER_OFF = 28, ///< 屏蔽某人语音

	YOUME_EVENT_LOCAL_MIC_ON = 29, ///< 自己的麦克风打开	
	YOUME_EVENT_LOCAL_MIC_OFF = 30, ///< 自己的麦克风关闭	
	YOUME_EVENT_LOCAL_SPEAKER_ON = 31, ///< 自己的扬声器打开
	YOUME_EVENT_LOCAL_SPEAKER_OFF = 32, ///< 自己的扬声器关闭

	YOUME_EVENT_GRABMIC_START_OK = 33, ///< 发起抢麦活动成功
	YOUME_EVENT_GRABMIC_START_FAILED = 34, ///< 发起抢麦活动失败
	YOUME_EVENT_GRABMIC_STOP_OK = 35, ///< 停止抢麦活动成功
	YOUME_EVENT_GRABMIC_STOP_FAILED = 36, ///< 停止抢麦活动失败
	YOUME_EVENT_GRABMIC_REQUEST_OK = 37, ///< 抢麦成功（可以说话）
	YOUME_EVENT_GRABMIC_REQUEST_FAILED = 38, ///< 抢麦失败
	YOUME_EVENT_GRABMIC_REQUEST_WAIT = 39, ///< 进入抢麦等待队列（仅权重模式下会回调此事件）
	YOUME_EVENT_GRABMIC_RELEASE_OK = 40, ///< 释放麦成功
	YOUME_EVENT_GRABMIC_RELEASE_FAILED = 41, ///< 释放麦失败
	YOUME_EVENT_GRABMIC_ENDMIC = 42, ///< 不再占用麦（到麦使用时间或者其他原因）

	YOUME_EVENT_GRABMIC_NOTIFY_START = 43, ///< [通知]抢麦活动开始
	YOUME_EVENT_GRABMIC_NOTIFY_STOP = 44, ///< [通知]抢麦活动结束
	YOUME_EVENT_GRABMIC_NOTIFY_HASMIC = 45, ///< [通知]有麦可以抢
	YOUME_EVENT_GRABMIC_NOTIFY_NOMIC = 46, ///< [通知]没有麦可以抢

	YOUME_EVENT_INVITEMIC_SETOPT_OK = 47, ///< 连麦设置成功
	YOUME_EVENT_INVITEMIC_SETOPT_FAILED = 48, ///< 连麦设置失败
	YOUME_EVENT_INVITEMIC_REQUEST_OK = 49, ///< 请求连麦成功（连上了，需等待对方回应）
	YOUME_EVENT_INVITEMIC_REQUEST_FAILED = 50, ///< 请求连麦失败
	YOUME_EVENT_INVITEMIC_RESPONSE_OK = 51, ///< 响应连麦成功（被叫方无论同意/拒绝都会收到此事件，错误码是YOUME_ERROR_INVITEMIC_REJECT表示拒绝）
	YOUME_EVENT_INVITEMIC_RESPONSE_FAILED = 52, ///< 响应连麦失败
	YOUME_EVENT_INVITEMIC_STOP_OK = 53, ///< 停止连麦成功
	YOUME_EVENT_INVITEMIC_STOP_FAILED = 54, ///< 停止连麦失败

	YOUME_EVENT_INVITEMIC_CAN_TALK = 55, ///< 双方可以通话了（响应方已经同意）
	YOUME_EVENT_INVITEMIC_CANNOT_TALK = 56, ///< 双方不可以再通话了（有一方结束了连麦或者连麦时间到）

	YOUME_EVENT_INVITEMIC_NOTIFY_CALL = 57, ///< [通知]有人请求与你连麦
	YOUME_EVENT_INVITEMIC_NOTIFY_ANSWER = 58, ///< [通知]对方对你的连麦请求作出了响应（同意/拒绝/超时，同意的话双方就可以通话了）
	YOUME_EVENT_INVITEMIC_NOTIFY_CANCEL = 59, ///< [通知]连麦过程中，对方结束了连麦或者连麦时间到

	YOUME_EVENT_SEND_MESSAGE_RESULT = 60, ///< sendMessage成功与否的通知，param为回传的requestID
	YOUME_EVENT_MESSAGE_NOTIFY = 61, ///< 收到Message, param为message内容


	YOUME_EVENT_SET_WHITE_USER_LIST_OK = 62, ///< 对指定频道设置白名单成功，但可能有异常用户
	YOUME_EVENT_SET_WHITE_USER_LIST_FAILED = 63, ///< 对指定频道设置白名单失败

	YOUME_EVENT_KICK_RESULT = 64,   ///< 踢人的应答
	YOUME_EVENT_KICK_NOTIFY = 65,   ///< 被踢通知   ,param: （踢人者ID，被踢原因，被禁时间）

	YOUME_EVENT_FAREND_VOICE_LEVEL = 66,  ///< 远端说话人音量大小
	YOUME_EVENT_OTHERS_BE_KICKED = 67,   ///< 房间里其他人被踢出房间

	YOUME_EVENT_SPEAK_RECORD_ON = 68,	///< 扬声器内录开启通知（成功、失败）
	YOUME_EVENT_SPEAK_RECORD_OFF = 69,	///< 扬声器内录关闭通知（成功、失败）
	YOUME_EVENT_SPEAK_RECORD_RESET = 70,	///< 扬声器内录重启通知（成功、失败）

	YOUME_EVENT_EFFECT_PLAY_COMPLETE = 71,   ///< 音效播放完成
	//72-74 video已占用
	YOUME_EVENT_SWITCH_OUTPUT = 75,   ///< 切换扬声器/听筒

	YOUME_EVENT_CHECK_DEVICE_MUTE_RESULT = 76,   ///获取设备是否禁音的回调，errcode为1表示静音了，为0表示没禁音

	YOUME_EVENT_EOF = 76
};

UENUM(BlueprintType)
enum class EYouMeErrorCode : uint8
{
	YOUME_SUCCESS,    ///< 成功

	// 参数和状态检查
	YOUME_ERROR_API_NOT_SUPPORTED,   ///< 正在使用的SDK不支持特定的API
	YOUME_ERROR_INVALID_PARAM,   ///< 传入参数错误
	YOUME_ERROR_ALREADY_INIT,   ///< 已经初始化
	YOUME_ERROR_NOT_INIT,   ///< 还没有初始化，在调用某函数之前要先调用初始化并且要根据返回值确保初始化成功
	YOUME_ERROR_CHANNEL_EXIST,   ///< 要加入的频道已经存在
	YOUME_ERROR_CHANNEL_NOT_EXIST,   ///< 对频道进入（检查参数为true时）、退出、讲话、设置白名单、抢麦等接口时频道不存在
	YOUME_ERROR_WRONG_STATE,   ///< 状态错误
	YOUME_ERROR_NOT_ALLOWED_MOBILE_NETWROK,   ///< 不允许使用移动网络
	YOUME_ERROR_WRONG_CHANNEL_MODE,   ///< 在单频道模式下调用了多频道接口，或者反之
	YOUME_ERROR_TOO_MANY_CHANNELS,  ///< 同时加入了太多频道
	YOUME_ERROR_TOKEN_ERROR,  ///< 传入的token认证错误
	YOUME_ERROR_NOT_IN_CHANNEL,  ///< 用户不在该频道
	YOUME_ERROR_BE_KICK,  ///< 被踢了，还在禁止时间内，不允许进入房间

	// 内部操作错误
	YOUME_ERROR_MEMORY_OUT, ///< 内存错误
	YOUME_ERROR_START_FAILED, ///< 启动引擎失败
	YOUME_ERROR_STOP_FAILED, ///<  停止引擎失败
	YOUME_ERROR_ILLEGAL_SDK, ///< 非法使用SDK
	YOUME_ERROR_SERVER_INVALID, ///< 语音服务不可用
	YOUME_ERROR_NETWORK_ERROR, ///< 网络错误
	YOUME_ERROR_SERVER_INTER_ERROR, ///< 服务器内部错误
	YOUME_ERROR_QUERY_RESTAPI_FAIL, ///< 请求RestApi信息失败了
	YOUME_ERROR_USER_ABORT, ///< 用户请求中断当前操作
	YOUME_ERROR_SEND_MESSAGE_FAIL, ///< 发送消息失败


	// 麦克风错误
	YOUME_ERROR_REC_INIT_FAILED, ///< 录音模块初始化失败
	YOUME_ERROR_REC_NO_PERMISSION, ///< 没有录音权限
	YOUME_ERROR_REC_NO_DATA, ///< 虽然初始化成功，但没有音频数据输出，比如oppo系列手机在录音权限被禁止的时候
	YOUME_ERROR_REC_OTHERS, ///< 其他录音模块的错误
	YOUME_ERROR_REC_PERMISSION_UNDEFINED, ///< 录音权限未确定，iOS显示是否允许录音权限对话框时，返回的是这个错误码

	// 抢麦错误
	YOUME_ERROR_GRABMIC_FULL, ///< 抢麦失败，人数满
	YOUME_ERROR_GRABMIC_HASEND, ///< 抢麦失败，活动已经结束
	// 连麦错误
	YOUME_ERROR_INVITEMIC_NOUSER, ///< 连麦失败，用户不存在
	YOUME_ERROR_INVITEMIC_OFFLINE, ///< 连麦失败，用户已离线
	YOUME_ERROR_INVITEMIC_REJECT, ///< 连麦失败，用户拒绝
	YOUME_ERROR_INVITEMIC_TIMEOUT, ///< 连麦失败，两种情况：1.连麦时，对方超时无应答 2.通话中，双方通话时间到

	// 频道白名单错误
	YOUME_ERROR_WHITE_SOMEUSER_ABNORMAL, ///< 设置白名单部分用户异常：已不在房间

	// 变声相关错误
	YOUME_ERROR_MAGICVOICE_EXPIRED, ///< 变声音效已过期

	YOUME_ERROR_UNKNOWN,         ///< 未知错误

};

UENUM(BlueprintType)
enum class EYouMeRTCServerRegion : uint8
{
	RTC_CN_SERVER = 0,  // 中国
	RTC_HK_SERVER = 1,  // 香港
	RTC_US_SERVER = 2,  // 美国东部
	RTC_SG_SERVER = 3,  // 新加坡
	RTC_KR_SERVER = 4,  // 韩国
	RTC_AU_SERVER = 5,  // 澳洲
	RTC_DE_SERVER = 6,  // 德国
	RTC_BR_SERVER = 7,  // 巴西
	RTC_IN_SERVER = 8,  // 印度
	RTC_JP_SERVER = 9,  // 日本
	RTC_IE_SERVER = 10, // 爱尔兰
	RTC_USW_SERVER = 11, // 美国西部
	RTC_USM_SERVER = 12, // 美国中部
	RTC_CA_SERVER = 13, // 加拿大
	RTC_LON_SERVER = 14, // 伦敦
	RTC_FRA_SERVER = 15, // 法兰克福
	RTC_DXB_SERVER = 16, // 迪拜

	RTC_EXT_SERVER, // 使用扩展服务器
	RTC_DEFAULT_SERVER, // 缺省服务器

};

UENUM(BlueprintType)
enum class EYouMeLogLevel : uint8
{
	LOG_DISABLED = 0,	//禁用日志
	LOG_FATAL = 1,	//严重错误
	LOG_ERROR =	10,	//错误
	LOG_WARNING	= 20,	//警告
	LOG_INFO = 40,	//信息
	LOG_DEBUG =	50,	//调试
	LOG_VERBOSE = 60	//所有日志
};

UENUM(BlueprintType)
enum class EYouMeUserRole : uint8
{
	YOUME_USER_NONE = 0,         ///< 非法用户，调用API时不能传此参数
	YOUME_USER_TALKER_FREE,      ///< 自由讲话者，适用于小组通话（建议小组成员数最多10个），每个人都可以随时讲话, 同一个时刻只能在一个语音频道里面
	YOUME_USER_TALKER_ON_DEMAND, ///< 需要通过抢麦等请求麦克风权限之后才可以讲话，适用于较大的组或工会等（比如几十个人），同一个时刻只能有一个或几个人能讲话, 同一个时刻只能在一个语音频道里面
	YOUME_USER_LISTENER,         ///< 听众，主播/指挥/嘉宾的听众，同一个时刻只能在一个语音频道里面，只听不讲
	YOUME_USER_COMMANDER,        ///< 指挥，国家/帮派等的指挥官，同一个时刻只能在一个语音频道里面，可以随时讲话，可以播放背景音乐，戴耳机情况下可以监听自己语音
	YOUME_USER_HOST,             ///< 主播，广播型语音频道的主持人，同一个时刻只能在一个语音频道里面，可以随时讲话，可以播放背景音乐，戴耳机情况下可以监听自己语音
	YOUME_USER_GUSET,            ///< 嘉宾，主播或指挥邀请的连麦嘉宾，同一个时刻只能在一个语音频道里面， 可以随时讲话
};

UENUM(BlueprintType)
enum class EChannelAudioMode : uint8
{
	CHANNEL_AUDIO_MODE_CALL = 0, ///< 通话模式
	CHANNEL_AUDIO_MODE_HQ_MUSIC  ///< 高音质音乐模式
};

namespace YouMeTalkDefineConvert
{
	static EYouMeErrorCode YouMeErrorCodeConvert(YouMeErrorCode code) {
		switch (code)
		{
		case YOUME_SUCCESS:
			return EYouMeErrorCode::YOUME_SUCCESS;
			break;
		case YOUME_ERROR_API_NOT_SUPPORTED:
			return EYouMeErrorCode::YOUME_ERROR_API_NOT_SUPPORTED;
			break;
		case YOUME_ERROR_INVALID_PARAM:
			return EYouMeErrorCode::YOUME_ERROR_INVALID_PARAM;
			break;
		case YOUME_ERROR_ALREADY_INIT:
			return EYouMeErrorCode::YOUME_ERROR_ALREADY_INIT;
			break;
		case YOUME_ERROR_NOT_INIT:
			return EYouMeErrorCode::YOUME_ERROR_NOT_INIT;
			break;
		case YOUME_ERROR_CHANNEL_EXIST:
			return EYouMeErrorCode::YOUME_ERROR_CHANNEL_EXIST;
			break;
		case YOUME_ERROR_CHANNEL_NOT_EXIST:
			return EYouMeErrorCode::YOUME_ERROR_CHANNEL_NOT_EXIST;
			break;
		case YOUME_ERROR_WRONG_STATE:
			return EYouMeErrorCode::YOUME_ERROR_WRONG_STATE;
			break;
		case YOUME_ERROR_NOT_ALLOWED_MOBILE_NETWROK:
			return EYouMeErrorCode::YOUME_ERROR_NOT_ALLOWED_MOBILE_NETWROK;
			break;
		case YOUME_ERROR_WRONG_CHANNEL_MODE:
			return EYouMeErrorCode::YOUME_ERROR_WRONG_CHANNEL_MODE;
			break;
		case YOUME_ERROR_TOO_MANY_CHANNELS:
			return EYouMeErrorCode::YOUME_ERROR_TOO_MANY_CHANNELS;
			break;
		case YOUME_ERROR_TOKEN_ERROR:
			return EYouMeErrorCode::YOUME_ERROR_TOKEN_ERROR;
			break;
		case YOUME_ERROR_NOT_IN_CHANNEL:
			return EYouMeErrorCode::YOUME_ERROR_NOT_IN_CHANNEL;
			break;
		case YOUME_ERROR_BE_KICK:
			return EYouMeErrorCode::YOUME_ERROR_BE_KICK;
			break;
		case YOUME_ERROR_MEMORY_OUT:
			return EYouMeErrorCode::YOUME_ERROR_MEMORY_OUT;
			break;
		case YOUME_ERROR_START_FAILED:
			return EYouMeErrorCode::YOUME_ERROR_START_FAILED;
			break;
		case YOUME_ERROR_STOP_FAILED:
			return EYouMeErrorCode::YOUME_ERROR_STOP_FAILED;
			break;
		case YOUME_ERROR_ILLEGAL_SDK:
			return EYouMeErrorCode::YOUME_ERROR_ILLEGAL_SDK;
			break;
		case YOUME_ERROR_SERVER_INVALID:
			return EYouMeErrorCode::YOUME_ERROR_SERVER_INVALID;
			break;
		case YOUME_ERROR_NETWORK_ERROR:
			return EYouMeErrorCode::YOUME_ERROR_NETWORK_ERROR;
			break;
		case YOUME_ERROR_SERVER_INTER_ERROR:
			return EYouMeErrorCode::YOUME_ERROR_SERVER_INTER_ERROR;
			break;
		case YOUME_ERROR_QUERY_RESTAPI_FAIL:
			return EYouMeErrorCode::YOUME_ERROR_QUERY_RESTAPI_FAIL;
			break;
		case YOUME_ERROR_USER_ABORT:
			return EYouMeErrorCode::YOUME_ERROR_USER_ABORT;
			break;
		case YOUME_ERROR_SEND_MESSAGE_FAIL:
			return EYouMeErrorCode::YOUME_ERROR_SEND_MESSAGE_FAIL;
			break;
		case YOUME_ERROR_REC_INIT_FAILED:
			return EYouMeErrorCode::YOUME_ERROR_REC_INIT_FAILED;
			break;
		case YOUME_ERROR_REC_NO_PERMISSION:
			return EYouMeErrorCode::YOUME_ERROR_REC_NO_PERMISSION;
			break;
		case YOUME_ERROR_REC_NO_DATA:
			return EYouMeErrorCode::YOUME_ERROR_REC_NO_DATA;
			break;
		case YOUME_ERROR_REC_OTHERS:
			return EYouMeErrorCode::YOUME_ERROR_REC_OTHERS;
			break;
		case YOUME_ERROR_REC_PERMISSION_UNDEFINED:
			return EYouMeErrorCode::YOUME_ERROR_REC_PERMISSION_UNDEFINED;
			break;
		case YOUME_ERROR_GRABMIC_FULL:
			return EYouMeErrorCode::YOUME_ERROR_GRABMIC_FULL;
			break;
		case YOUME_ERROR_GRABMIC_HASEND:
			return EYouMeErrorCode::YOUME_ERROR_GRABMIC_HASEND;
			break;
		case YOUME_ERROR_INVITEMIC_NOUSER:
			return EYouMeErrorCode::YOUME_ERROR_INVITEMIC_NOUSER;
			break;
		case YOUME_ERROR_INVITEMIC_OFFLINE:
			return EYouMeErrorCode::YOUME_ERROR_INVITEMIC_OFFLINE;
			break;
		case YOUME_ERROR_INVITEMIC_REJECT:
			return EYouMeErrorCode::YOUME_ERROR_INVITEMIC_REJECT;
			break;
		case YOUME_ERROR_INVITEMIC_TIMEOUT:
			return EYouMeErrorCode::YOUME_ERROR_INVITEMIC_TIMEOUT;
			break;
		case YOUME_ERROR_WHITE_SOMEUSER_ABNORMAL:
			return EYouMeErrorCode::YOUME_ERROR_WHITE_SOMEUSER_ABNORMAL;
			break;
		case YOUME_ERROR_MAGICVOICE_EXPIRED:
			return EYouMeErrorCode::YOUME_ERROR_MAGICVOICE_EXPIRED;
			break;
		case YOUME_ERROR_UNKNOWN:
			return EYouMeErrorCode::YOUME_ERROR_UNKNOWN;
			break;
		}
		return EYouMeErrorCode::YOUME_ERROR_UNKNOWN;
	}

	static EYouMeRTCServerRegion YouMeRTCServerRegionConvert(YOUME_RTC_SERVER_REGION serverRegion)
	{
		switch (serverRegion)
		{
		case RTC_CN_SERVER:
			return EYouMeRTCServerRegion::RTC_CN_SERVER;
			break;
		case RTC_HK_SERVER:
			return EYouMeRTCServerRegion::RTC_HK_SERVER;
			break;
		case RTC_US_SERVER:
			return EYouMeRTCServerRegion::RTC_US_SERVER;
			break;
		case RTC_SG_SERVER:
			return EYouMeRTCServerRegion::RTC_SG_SERVER;
			break;
		case RTC_KR_SERVER:
			return EYouMeRTCServerRegion::RTC_KR_SERVER;
			break;
		case RTC_AU_SERVER:
			return EYouMeRTCServerRegion::RTC_AU_SERVER;
			break;
		case RTC_DE_SERVER:
			return EYouMeRTCServerRegion::RTC_DE_SERVER;
			break;
		case RTC_BR_SERVER:
			return EYouMeRTCServerRegion::RTC_BR_SERVER;
			break;
		case RTC_IN_SERVER:
			return EYouMeRTCServerRegion::RTC_IN_SERVER;
			break;
		case RTC_JP_SERVER:
			return EYouMeRTCServerRegion::RTC_JP_SERVER;
			break;
		case RTC_IE_SERVER:
			return EYouMeRTCServerRegion::RTC_IE_SERVER;
			break;
		case RTC_USW_SERVER:
			return EYouMeRTCServerRegion::RTC_USW_SERVER;
			break;
		case RTC_USM_SERVER:
			return EYouMeRTCServerRegion::RTC_USM_SERVER;
			break;
		case RTC_CA_SERVER:
			return EYouMeRTCServerRegion::RTC_CA_SERVER;
			break;
		case RTC_LON_SERVER:
			return EYouMeRTCServerRegion::RTC_LON_SERVER;
			break;
		case RTC_FRA_SERVER:
			return EYouMeRTCServerRegion::RTC_FRA_SERVER;
			break;
		case RTC_DXB_SERVER:
			return EYouMeRTCServerRegion::RTC_DXB_SERVER;
			break;
		case RTC_EXT_SERVER:
			return EYouMeRTCServerRegion::RTC_EXT_SERVER;
			break;
		case RTC_DEFAULT_SERVER:
			return EYouMeRTCServerRegion::RTC_DEFAULT_SERVER;
			break;
		}
		return EYouMeRTCServerRegion::RTC_DEFAULT_SERVER;
	}

	static YOUME_RTC_SERVER_REGION YouMeRTCServerRegionConvert(EYouMeRTCServerRegion serverRegion)
	{
		switch (serverRegion)
		{
		case EYouMeRTCServerRegion::RTC_CN_SERVER:
			return RTC_CN_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_HK_SERVER:
			return RTC_HK_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_US_SERVER:
			return RTC_US_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_SG_SERVER:
			return RTC_SG_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_KR_SERVER:
			return RTC_KR_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_AU_SERVER:
			return RTC_AU_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_DE_SERVER:
			return RTC_DE_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_BR_SERVER:
			return RTC_BR_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_IN_SERVER:
			return RTC_IN_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_JP_SERVER:
			return RTC_JP_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_IE_SERVER:
			return RTC_IE_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_USW_SERVER:
			return RTC_USW_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_USM_SERVER:
			return RTC_USM_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_CA_SERVER:
			return RTC_CA_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_LON_SERVER:
			return RTC_LON_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_FRA_SERVER:
			return RTC_FRA_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_DXB_SERVER:
			return RTC_DXB_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_EXT_SERVER:
			return RTC_EXT_SERVER;
			break;
		case EYouMeRTCServerRegion::RTC_DEFAULT_SERVER:
			return RTC_DEFAULT_SERVER;
			break;
		default:
			break;
		}
		return RTC_DEFAULT_SERVER;
	}

	static YouMeUserRole YouMeUserRoleConvert(EYouMeUserRole youMeUserRole)
	{
		switch (youMeUserRole)
		{
		case EYouMeUserRole::YOUME_USER_NONE:
			return YOUME_USER_NONE;
			break;
		case EYouMeUserRole::YOUME_USER_TALKER_FREE:
			return YOUME_USER_TALKER_FREE;
			break;
		case EYouMeUserRole::YOUME_USER_TALKER_ON_DEMAND:
			return YOUME_USER_TALKER_ON_DEMAND;
			break;
		case EYouMeUserRole::YOUME_USER_LISTENER:
			return YOUME_USER_LISTENER;
			break;
		case EYouMeUserRole::YOUME_USER_COMMANDER:
			return YOUME_USER_COMMANDER;
			break;
		case EYouMeUserRole::YOUME_USER_HOST:
			return YOUME_USER_HOST;
			break;
		case EYouMeUserRole::YOUME_USER_GUSET:
			return YOUME_USER_GUSET;
			break;
		default:
			break;
		}
		return YOUME_USER_NONE;
	}

	static EYouMeEvent YouMeEventConvert(YouMeEvent youMeEvent)
	{
		switch (youMeEvent)
		{
		case YOUME_EVENT_INIT_OK:
			return EYouMeEvent::YOUME_EVENT_INIT_OK;
			break;
		case YOUME_EVENT_INIT_FAILED:
			return EYouMeEvent::YOUME_EVENT_INIT_FAILED;
			break;
		case YOUME_EVENT_JOIN_OK:
			return EYouMeEvent::YOUME_EVENT_JOIN_OK;
			break;
		case YOUME_EVENT_JOIN_FAILED:
			return EYouMeEvent::YOUME_EVENT_JOIN_FAILED;
			break;
		case YOUME_EVENT_LEAVED_ONE:
			return EYouMeEvent::YOUME_EVENT_LEAVED_ONE;
			break;
		case YOUME_EVENT_LEAVED_ALL:
			return EYouMeEvent::YOUME_EVENT_LEAVED_ALL;
			break;
		case YOUME_EVENT_PAUSED:
			return EYouMeEvent::YOUME_EVENT_PAUSED;
			break;
		case YOUME_EVENT_RESUMED:
			return EYouMeEvent::YOUME_EVENT_RESUMED;
			break;
		case YOUME_EVENT_SPEAK_SUCCESS:
			return EYouMeEvent::YOUME_EVENT_SPEAK_SUCCESS;
			break;
		case YOUME_EVENT_SPEAK_FAILED:
			return EYouMeEvent::YOUME_EVENT_SPEAK_FAILED;
			break;
		case YOUME_EVENT_RECONNECTING:
			return EYouMeEvent::YOUME_EVENT_RECONNECTING;
			break;
		case YOUME_EVENT_RECONNECTED:
			return EYouMeEvent::YOUME_EVENT_RECONNECTED;
			break;
		case YOUME_EVENT_REC_PERMISSION_STATUS:
			return EYouMeEvent::YOUME_EVENT_REC_PERMISSION_STATUS;
			break;
		case YOUME_EVENT_BGM_STOPPED:
			return EYouMeEvent::YOUME_EVENT_BGM_STOPPED;
			break;
		case YOUME_EVENT_BGM_FAILED:
			return EYouMeEvent::YOUME_EVENT_BGM_FAILED;
			break;
		case YOUME_EVENT_OTHERS_MIC_ON:
			return EYouMeEvent::YOUME_EVENT_OTHERS_MIC_ON;
			break;
		case YOUME_EVENT_OTHERS_MIC_OFF:
			return EYouMeEvent::YOUME_EVENT_OTHERS_MIC_OFF;
			break;
		case YOUME_EVENT_OTHERS_SPEAKER_ON:
			return EYouMeEvent::YOUME_EVENT_OTHERS_SPEAKER_ON;
			break;
		case YOUME_EVENT_OTHERS_SPEAKER_OFF:
			return EYouMeEvent::YOUME_EVENT_OTHERS_SPEAKER_OFF;
			break;
		case YOUME_EVENT_OTHERS_VOICE_ON:
			return EYouMeEvent::YOUME_EVENT_OTHERS_VOICE_ON;
			break;
		case YOUME_EVENT_OTHERS_VOICE_OFF:
			return EYouMeEvent::YOUME_EVENT_OTHERS_VOICE_OFF;
			break;
		case YOUME_EVENT_MY_MIC_LEVEL:
			return EYouMeEvent::YOUME_EVENT_MY_MIC_LEVEL;
			break;
		case YOUME_EVENT_MIC_CTR_ON:
			return EYouMeEvent::YOUME_EVENT_MIC_CTR_ON;
			break;
		case YOUME_EVENT_MIC_CTR_OFF:
			return EYouMeEvent::YOUME_EVENT_MIC_CTR_OFF;
			break;
		case YOUME_EVENT_SPEAKER_CTR_ON:
			return EYouMeEvent::YOUME_EVENT_SPEAKER_CTR_ON;
			break;
		case YOUME_EVENT_SPEAKER_CTR_OFF:
			return EYouMeEvent::YOUME_EVENT_SPEAKER_CTR_OFF;
			break;
		case YOUME_EVENT_LISTEN_OTHER_ON:
			return EYouMeEvent::YOUME_EVENT_LISTEN_OTHER_ON;
			break;
		case YOUME_EVENT_LISTEN_OTHER_OFF:
			return EYouMeEvent::YOUME_EVENT_LISTEN_OTHER_OFF;
			break;
		case YOUME_EVENT_LOCAL_MIC_ON:
			return EYouMeEvent::YOUME_EVENT_LOCAL_MIC_ON;
			break;
		case YOUME_EVENT_LOCAL_MIC_OFF:
			return EYouMeEvent::YOUME_EVENT_LOCAL_MIC_OFF;
			break;
		case YOUME_EVENT_LOCAL_SPEAKER_ON:
			return EYouMeEvent::YOUME_EVENT_LOCAL_SPEAKER_ON;
			break;
		case YOUME_EVENT_LOCAL_SPEAKER_OFF:
			return EYouMeEvent::YOUME_EVENT_LOCAL_SPEAKER_OFF;
			break;
		case YOUME_EVENT_GRABMIC_START_OK:
			return EYouMeEvent::YOUME_EVENT_GRABMIC_START_OK;
			break;
		case YOUME_EVENT_GRABMIC_START_FAILED:
			return EYouMeEvent::YOUME_EVENT_GRABMIC_START_FAILED;
			break;
		case YOUME_EVENT_GRABMIC_STOP_OK:
			return EYouMeEvent::YOUME_EVENT_GRABMIC_STOP_OK;
			break;
		case YOUME_EVENT_GRABMIC_STOP_FAILED:
			return EYouMeEvent::YOUME_EVENT_GRABMIC_STOP_FAILED;
			break;
		case YOUME_EVENT_GRABMIC_REQUEST_OK:
			return EYouMeEvent::YOUME_EVENT_GRABMIC_REQUEST_OK;
			break;
		case YOUME_EVENT_GRABMIC_REQUEST_FAILED:
			return EYouMeEvent::YOUME_EVENT_GRABMIC_REQUEST_FAILED;
			break;
		case YOUME_EVENT_GRABMIC_REQUEST_WAIT:
			return EYouMeEvent::YOUME_EVENT_GRABMIC_REQUEST_WAIT;
			break;
		case YOUME_EVENT_GRABMIC_RELEASE_OK:
			return EYouMeEvent::YOUME_EVENT_GRABMIC_RELEASE_OK;
			break;
		case YOUME_EVENT_GRABMIC_RELEASE_FAILED:
			return EYouMeEvent::YOUME_EVENT_GRABMIC_RELEASE_FAILED;
			break;
		case YOUME_EVENT_GRABMIC_ENDMIC:
			return EYouMeEvent::YOUME_EVENT_GRABMIC_ENDMIC;
			break;
		case YOUME_EVENT_GRABMIC_NOTIFY_START:
			return EYouMeEvent::YOUME_EVENT_GRABMIC_NOTIFY_START;
			break;
		case YOUME_EVENT_GRABMIC_NOTIFY_STOP:
			return EYouMeEvent::YOUME_EVENT_GRABMIC_NOTIFY_STOP;
			break;
		case YOUME_EVENT_GRABMIC_NOTIFY_HASMIC:
			return EYouMeEvent::YOUME_EVENT_GRABMIC_NOTIFY_HASMIC;
			break;
		case YOUME_EVENT_GRABMIC_NOTIFY_NOMIC:
			return EYouMeEvent::YOUME_EVENT_GRABMIC_NOTIFY_NOMIC;
			break;
		case YOUME_EVENT_INVITEMIC_SETOPT_OK:
			return EYouMeEvent::YOUME_EVENT_INVITEMIC_SETOPT_OK;
			break;
		case YOUME_EVENT_INVITEMIC_SETOPT_FAILED:
			return EYouMeEvent::YOUME_EVENT_INVITEMIC_SETOPT_FAILED;
			break;
		case YOUME_EVENT_INVITEMIC_REQUEST_OK:
			return EYouMeEvent::YOUME_EVENT_INVITEMIC_REQUEST_OK;
			break;
		case YOUME_EVENT_INVITEMIC_REQUEST_FAILED:
			return EYouMeEvent::YOUME_EVENT_INVITEMIC_REQUEST_FAILED;
			break;
		case YOUME_EVENT_INVITEMIC_RESPONSE_OK:
			return EYouMeEvent::YOUME_EVENT_INVITEMIC_RESPONSE_OK;
			break;
		case YOUME_EVENT_INVITEMIC_RESPONSE_FAILED:
			return EYouMeEvent::YOUME_EVENT_INVITEMIC_RESPONSE_FAILED;
			break;
		case YOUME_EVENT_INVITEMIC_STOP_OK:
			return EYouMeEvent::YOUME_EVENT_INVITEMIC_STOP_OK;
			break;
		case YOUME_EVENT_INVITEMIC_STOP_FAILED:
			return EYouMeEvent::YOUME_EVENT_INVITEMIC_STOP_FAILED;
			break;
		case YOUME_EVENT_INVITEMIC_CAN_TALK:
			return EYouMeEvent::YOUME_EVENT_INVITEMIC_CAN_TALK;
			break;
		case YOUME_EVENT_INVITEMIC_CANNOT_TALK:
			return EYouMeEvent::YOUME_EVENT_INVITEMIC_CANNOT_TALK;
			break;
		case YOUME_EVENT_INVITEMIC_NOTIFY_CALL:
			return EYouMeEvent::YOUME_EVENT_INVITEMIC_NOTIFY_CALL;
			break;
		case YOUME_EVENT_INVITEMIC_NOTIFY_ANSWER:
			return EYouMeEvent::YOUME_EVENT_INVITEMIC_NOTIFY_ANSWER;
			break;
		case YOUME_EVENT_INVITEMIC_NOTIFY_CANCEL:
			return EYouMeEvent::YOUME_EVENT_INVITEMIC_NOTIFY_CANCEL;
			break;
		case YOUME_EVENT_SEND_MESSAGE_RESULT:
			return EYouMeEvent::YOUME_EVENT_SEND_MESSAGE_RESULT;
			break;
		case YOUME_EVENT_MESSAGE_NOTIFY:
			return EYouMeEvent::YOUME_EVENT_MESSAGE_NOTIFY;
			break;
		case YOUME_EVENT_SET_WHITE_USER_LIST_OK:
			return EYouMeEvent::YOUME_EVENT_SET_WHITE_USER_LIST_OK;
			break;
		case YOUME_EVENT_SET_WHITE_USER_LIST_FAILED:
			return EYouMeEvent::YOUME_EVENT_SET_WHITE_USER_LIST_FAILED;
			break;
		case YOUME_EVENT_KICK_RESULT:
			return EYouMeEvent::YOUME_EVENT_KICK_RESULT;
			break;
		case YOUME_EVENT_KICK_NOTIFY:
			return EYouMeEvent::YOUME_EVENT_KICK_NOTIFY;
			break;
		case YOUME_EVENT_FAREND_VOICE_LEVEL:
			return EYouMeEvent::YOUME_EVENT_FAREND_VOICE_LEVEL;
			break;
		case YOUME_EVENT_OTHERS_BE_KICKED:
			return EYouMeEvent::YOUME_EVENT_OTHERS_BE_KICKED;
			break;
		case YOUME_EVENT_SPEAK_RECORD_ON:
			return EYouMeEvent::YOUME_EVENT_SPEAK_RECORD_ON;
			break;
		case YOUME_EVENT_SPEAK_RECORD_OFF:
			return EYouMeEvent::YOUME_EVENT_SPEAK_RECORD_OFF;
			break;
		case YOUME_EVENT_SPEAK_RECORD_RESET:
			return EYouMeEvent::YOUME_EVENT_SPEAK_RECORD_RESET;
			break;
		case YOUME_EVENT_EFFECT_PLAY_COMPLETE:
			return EYouMeEvent::YOUME_EVENT_EFFECT_PLAY_COMPLETE;
			break;
		case YOUME_EVENT_SWITCH_OUTPUT:
			return EYouMeEvent::YOUME_EVENT_SWITCH_OUTPUT;
			break;
		case YOUME_EVENT_CHECK_DEVICE_MUTE_RESULT:
			return EYouMeEvent::YOUME_EVENT_CHECK_DEVICE_MUTE_RESULT;
			break;
		case YOUME_EVENT_EOF:
			return EYouMeEvent::YOUME_EVENT_EOF;
			break;
		default:
			break;
		}
		return EYouMeEvent::YOUME_EVENT_EOF;
	}

	static EYouMeUserRole YouMeUserRoleConvert(YouMeUserRole youMeUserRole)
	{
		switch (youMeUserRole)
		{
		case YOUME_USER_NONE:
			return EYouMeUserRole::YOUME_USER_NONE;
			break;
		case YOUME_USER_TALKER_FREE:
			return EYouMeUserRole::YOUME_USER_TALKER_FREE;
			break;
		case YOUME_USER_TALKER_ON_DEMAND:
			return EYouMeUserRole::YOUME_USER_TALKER_ON_DEMAND;
			break;
		case YOUME_USER_LISTENER:
			return EYouMeUserRole::YOUME_USER_LISTENER;
			break;
		case YOUME_USER_COMMANDER:
			return EYouMeUserRole::YOUME_USER_COMMANDER;
			break;
		case YOUME_USER_HOST:
			return EYouMeUserRole::YOUME_USER_HOST;
			break;
		case YOUME_USER_GUSET:
			return EYouMeUserRole::YOUME_USER_GUSET;
			break;
		default:
			break;
		}
		return EYouMeUserRole::YOUME_USER_NONE;
	}

	static ChannelAudioMode ChannelAudioModeConvert(EChannelAudioMode channelAudioMode)
	{
		switch (channelAudioMode)
		{
		case EChannelAudioMode::CHANNEL_AUDIO_MODE_CALL:
			return CHANNEL_AUDIO_MODE_CALL;
			break;
		case EChannelAudioMode::CHANNEL_AUDIO_MODE_HQ_MUSIC:
			return CHANNEL_AUDIO_MODE_HQ_MUSIC;
			break;
		default:
			break;
		}
		return CHANNEL_AUDIO_MODE_CALL;
	}

	static std::vector<std::string> TArrayFStringConvertToVectorString(const TArray<FString>& vecWhiteUserList)
	{
		std::vector<std::string> stdStrArr;
		for (auto& str : vecWhiteUserList)
		{
			std::string stdStr = std::string(TCHAR_TO_UTF8(*str));
			stdStrArr.push_back(stdStr);
		}
		return stdStrArr;
	}
}

