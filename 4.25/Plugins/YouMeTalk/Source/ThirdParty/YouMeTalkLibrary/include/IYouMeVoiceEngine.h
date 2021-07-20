/**
 @file IYouMeVoiceEngine.h
 @brief 游密音频通话引擎接口
 
 该文件主要用于定义游密音频通话引擎的接口
 
 @version 1.0 Copyright(c) 2015-2020 YOUME All rights reserved.
 @author YOUME

 */
 
#ifndef cocos2d_x_sdk_IYouMeVoiceEngine_h
#define cocos2d_x_sdk_IYouMeVoiceEngine_h
#include <string>
#include <vector>

#include "IYouMeEventCallback.h"
#include "YouMeConstDefine.h"

#ifdef WIN32
#ifdef YOUMEDLL_EXPORTS
#define YOUMEDLL_API __declspec(dllexport)
#else
#define YOUMEDLL_API __declspec(dllimport)
#endif
#else
#define YOUMEDLL_API __attribute ((visibility("default")))
#endif
class YOUMEDLL_API IYouMeVoiceEngine
{
public:
    /**
     *  功能描述:获取引擎实例指针
     *
     *  @return 引擎实例指针
     */
    static IYouMeVoiceEngine *getInstance ()
#ifdef YOUME_MAC
	{
		return nullptr;
	}
#else
    ;
#endif
    
    /**
     *  功能描述:销毁引擎实例，释放内存
     *
     *  @return 无
     */
    static void destroy ()
#ifdef YOUME_MAC
	{
	}
#else
    ;
#endif

public:
    /**
     *  功能描述:初始化引擎
     *
     *  @param pCommonCallback:通用回调类地址，需要继承IYouMeCommonCallback并实现其中的回调函数
     *  @param pConferenceCallback:会议回调类地址，需要继承IYouMeConferenceCallback并实现其中的回调函数
     *  @param strAPPKey:在申请SDK注册时得到的App Key，也可凭账号密码到http://gmx.dev.net/createApp.html查询
     *  @param strAPPSecret:在申请SDK注册时得到的App Secret，也可凭账号密码到http://gmx.dev.net/createApp.html查询
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode init (IYouMeEventCallback * pEventCallback, const char* pAPPKey, const char* pAPPSecret,
                         YOUME_RTC_SERVER_REGION serverRegionId, const char* pExtServerRegionName)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
	;
#endif
	
	/**
     *  功能描述:设置身份验证的token和用户加入房间的时间
     *  @param pToken: 身份验证用token，设置为NULL或者空字符串，清空token值。
     *  @param uTimeStamp: 用户加入房间的时间
     *  @return 无
     */
    void setToken( const char* pToken, unsigned int uTimeStamp = 0 )
#ifdef YOUME_MAC
	{
	}
#else
    ;
#endif
    
    /**
     *  功能描述:反初始化引擎
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */

    YouMeErrorCode unInit ()
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

	/**
	*  功能描述:判断是否初始化完成
	*
	*  @return true——完成，false——还未完成
	*/
	// 是否初始化成功
	bool isInited()
#ifdef YOUME_MAC
	{
		return false;
    }
#else
    ;
#endif

    /**
     *  功能描述:设置服务器区域
     *  @param region: YOUME_RTC_SERVER_REGION枚举可选的服务器区域
     *  @return 无
     */
    void setServerRegion(YOUME_RTC_SERVER_REGION regionId, const char* extRegionName, bool bAppend)
#ifdef YOUME_MAC
	{

	}
#else
    ;
#endif
    
    /**
     *  功能描述:切换语音输出设备
     *  默认输出到扬声器，在加入房间成功后设置（iOS受系统限制，如果已释放麦克风则无法切换到听筒）
     *
     *  @param bOutputToSpeaker:true——使用扬声器，false——使用听筒
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode setOutputToSpeaker (bool bOutputToSpeaker)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

    /**
     *  功能描述:设置扬声器静音
     *
     *  @param bOn:true——静音，false——取消静音
     *  @return 无
     */
    void setSpeakerMute (bool bOn)
#ifdef YOUME_MAC
	{

	}
#else
    ;
#endif

    /**
     *  功能描述:获取扬声器静音状态
     *
     *  @return true——静音，false——没有静音
     */
    bool getSpeakerMute ()
#ifdef YOUME_MAC
	{
		return false;
	}
#else
    ;
#endif

    /**
     *  功能描述:获取麦克风静音状态
     *
     *  @return true——静音，false——没有静音
     */
    bool getMicrophoneMute ()
#ifdef YOUME_MAC
	{
		return false;
	}
#else
    ;
#endif

    /**
     *  功能描述:设置麦克风静音
     *
     *  @param bOn:true——静音，false——取消静音
     *  @return 无
     */
    void setMicrophoneMute (bool mute)
#ifdef YOUME_MAC
	{

	}
#else
    ;
#endif
    
    /**
     *  功能描述:设置是否通知其他人自己的开关麦克风和扬声器的状态
     *
     *  @param bAutoSend:true——通知，false——不通知
     *  @return 无
     */
    void setAutoSendStatus( bool bAutoSend )
#ifdef YOUME_MAC
	{

	}
#else
    ;
#endif

    /**
     *  功能描述:获取音量大小,此音量值为程序内部的音量，与系统音量相乘得到程序使用的实际音量
     *
     *  @return 音量值[0,100]
     */
    unsigned int getVolume ()
#ifdef YOUME_MAC
	{
		return 0;
	}
#else
    ;
#endif

    /**
     *  功能描述:增加音量，音量数值加1
     *
     *  @return 无
     */
    void setVolume (const unsigned int &uiVolume)
#ifdef YOUME_MAC
	{

	}
#else
    ;
#endif
    
    /**
      *  功能描述:获取背景音乐时长
      *
      *  @return 音频时长，单位ms
      */
     long long getBgmDuration ()
#ifdef YOUME_MAC
	 {
		 return 1;
	 }
#else
    ;
#endif
    
    /**
     *  功能描述:获取背景音乐播放进度
     *
     *  @return 进度范围(0,音频时长]，单位ms
     */
    long long getBgmProgress ()
#ifdef YOUME_MAC
	{
		return 1;
	}
#else
    ;
#endif

    /**
     *  功能描述:控制背景音乐播放进度
     *
     *  @return 无
     */
    void setBgmProgress (const long long uiProgress)
#ifdef YOUME_MAC
	{
		
	}
#else
    ;
#endif

	/**
	*  功能描述:获取麦克风音量增益大小,此音量值为程序内部的麦克风音量增益值，与系统音量相乘得到程序使用的实际音量
	*
	*  @return 音量值[0,1000]
	*/
	unsigned int getMicVolume()
#ifdef YOUME_MAC
	{
		return 1;
	}
#else
    ;
#endif

	/**
	*  功能描述:设置麦克风音量增益(0-1000)，100为正常值
	*
	*  @return 无
	*/
	void setMicVolume(const unsigned int &uiVolume)
#ifdef YOUME_MAC
	{

	}
#else
    ;
#endif

    /**
     *  功能描述:是否可使用移动网络
     *
     *  @return true-可以使用，false-禁用
     */
    bool getUseMobileNetworkEnabled ()
#ifdef YOUME_MAC
	{
		return false;
	}
#else
    ;
#endif

    /**
     *  功能描述:启用/禁用移动网络
     *
     *  @param bEnabled:true-可以启用，false-禁用，默认禁用
     *
     *  @return 无
     */
    void setUseMobileNetworkEnabled (bool bEnabled)
#ifdef YOUME_MAC
	{
	}
#else
    ;
#endif


    //---------------------多人语音接口---------------------//

    /**
     *  功能描述:加入语音频道
     *
     * @param strUserID:用户ID，要保证全局唯一
     *  @param strRoomID:频道ID，要保证全局唯一
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */

    /**
     *  功能描述:加入语音频道（单频道模式，每个时刻只能在一个语音频道里面）
     *
     *  @param pUserID: 用户ID，要保证全局唯一
     *  @param pChannelID: 频道ID，要保证全局唯一
     *  @param eUserRole: 用户角色，用于决定讲话/播放背景音乐等权限
     *  @param bCheckRoomExist:是否检查频道存在时才加入，默认为false: true 当频道存在时加入、不存在时返回错误（多用于观众角色），false 无论频道是否存在都加入频道
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode joinChannelSingleMode(const char* pUserID, const char* pChannelID, YouMeUserRole_t eUserRole, bool bCheckRoomExist = false)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述：加入语音频道（多频道模式，可以同时在多个语音频道里面）
     *
     *  @param pUserID: 用户ID，要保证全局唯一
     *  @param pChannelID: 频道ID，要保证全局唯一
     *  @param eUserRole: 用户角色，用于决定讲话/播放背景音乐等权限
     *  @param bCheckRoomExist:是否检查频道存在时才加入，默认为false: true 当频道存在时加入、不存在时返回错误（多用于观众角色），false 无论频道是否存在都加入频道
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode joinChannelMultiMode(const char* pUserID, const char* pChannelID, YouMeUserRole_t eUserRole, bool bCheckRoomExist = false)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

    /**
     *  功能描述：对指定频道说话
     *
     *  @param pChannelID: 频道ID，要保证全局唯一
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode speakToChannel(const char* pChannelID)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述:退出多频道模式下的某个语音频道
     *
     *  @param pChannelID:频道ID，要保证全局唯一
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode leaveChannelMultiMode (const char* pChannelID)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述:退出所有语音频道
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode leaveChannelAll ()
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
	/**
	*  功能描述:切换身份(仅支持单频道模式，进入房间以后设置)
	*
	*  @param eUserRole: 用户身份
	*
	*  @return 错误码，详见YouMeConstDefine.h定义
	*/
	YouMeErrorCode setUserRole(YouMeUserRole_t eUserRole)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

	/**
	*  功能描述:获取身份(仅支持单频道模式)
	*
	*  @return 身份定义，详见YouMeConstDefine.h定义
	*/
	YouMeUserRole_t getUserRole()
#ifdef YOUME_MAC
	{
		YouMeUserRole_t userRole;
		userRole = (YouMeUserRole_t)1;
		return userRole;
	}
#else
    ;
#endif


	/**
	*  功能描述:查询是否在某个语音频道内
	*
	*  @param pChannelID:要查询的频道ID
	*
	*  @return true——在频道内，false——没有在频道内
	*/
	// 
	bool isInChannel(const char* pChannelID)
#ifdef YOUME_MAC
	{
		return false;
	}
#else
    ;
#endif
    
    /**
     *  功能描述:查询是否在语音频道内
     *
     *  @return true——在频道内，false——没有在频道内
     */
    //
    bool isInChannel()
#ifdef YOUME_MAC
	{
		return false;
	}
#else
    ;
#endif

    /**
     *  功能描述:查询频道的用户列表
     *  @param channelID:要查询的频道ID
     *  @param maxCount:想要获取的最大数量，-1表示获取全部
     *  @param notifyMemChagne: 其他用户进出房间时，是否要收到通知
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode getChannelUserList( const char*  channelID, int maxCount, bool notifyMemChange )
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述:控制其他人的麦克风开关
     *
     *  @param pUserID:用户ID，要保证全局唯一
     *  @param mute: true 静音对方的麦克风，false 取消静音对方麦克风
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode setOtherMicMute (const char* pUserID,bool mute)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述:控制其他人的扬声器开关
     *
     *  @param pUserID:用户ID，要保证全局唯一
     *  @param mute: true 静音对方的扬声器，false 取消静音对方扬声器
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode setOtherSpeakerMute (const char* pUserID,bool mute)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

    /**
     *  功能描述:选择消除其他人的语音
     *
     *  @param pUserID:用户ID，要保证全局唯一
     *  @param on: false屏蔽对方语音，true取消屏蔽
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode setListenOtherVoice (const char* pUserID, bool on )
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
//    
//    /**
//     *  功能描述: 将提供的音频数据混合到麦克风或者扬声器的音轨里面。
//     *  @param pBuf 指向PCM数据的缓冲区
//     *  @param nSizeInByte 缓冲区中数据的大小，以Byte为单位
//     *  @param nChannelNum 声道数量
//     *  @param nSampleRateHz 采样率, 已Hz为单位
//     *  @param nBytesPerSample 一个声道里面每个采样的字节数，典型情况下，如果数据是整型，该值为2，如果是浮点数，该值为4
//     *  @param bFloat, true - 数据是浮点数， false - 数据是整型
//     *  @param bLittleEndian, true - 数据是小端存储，false - 数据是大端存储
//     *  @param bInterleaved, 用于多声道数据时，true - 不同声道采样交错存储，false - 先存储一个声音数据，再存储另一个声道数据
//     *  @param bForSpeaker, true - 该数据要混到扬声器输出， false - 该数据要混到麦克风输入
//     *  @return YOUME_SUCCESS - 成功
//     *          其他 - 具体错误码
//     */
//    YouMeErrorCode mixAudioTrack(const void* pBuf, int nSizeInByte, int nChannelNUm,
//                                 int nSampleRate, int nBytesPerSample, bool bFloat,
//                                 bool bLittleEndian, bool bInterleaved, bool bForSpeaker);

    /**
     *  功能描述: 播放背景音乐，并允许选择混合到扬声器输出麦克风输入
     *  @param pFilePath 音乐文件的路径
     *  @param bRepeat 是否重复播放
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode playBackgroundMusic(const char* pFilePath, bool bRepeat)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

    /**
     *  功能描述: 如果当前正在播放背景音乐的话，暂停播放
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode pauseBackgroundMusic()
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 如果当前背景音乐处于暂停状态的话，恢复播放
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode resumeBackgroundMusic()
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 如果当前正在播放背景音乐的话，停止播放
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode stopBackgroundMusic()
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

	/**
	*  功能描述:背景音乐是否在播放
	*
	*  @return true——正在播放，false——没有播放
	*/
	bool isBackgroundMusicPlaying()
#ifdef YOUME_MAC
	{
		return false;
	}
#else
    ;
#endif

    /**
     *  功能描述: 设置背景音乐播放的音量
     *  @param vol 背景音乐的音量，范围 0-100
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setBackgroundMusicVolume(int vol)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

    /**
     *  功能描述: 获取背景音乐播放的音量
     *  @return vol 背景音乐的音量，范围 0-100
     */
    int getBackgroundMusicVolume()
#ifdef YOUME_MAC
	{
		return 0;
	}
#else
    ;
#endif
    
     /**
     *  功能描述: 设置监听时mic的音量
     *  @param vol 监听时mic的音量，范围 0-100
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setMicbypassVolume (int vol)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

    /**
     *  功能描述: 获取监听时mic的音量
     *  @return vol 监听时mic的音量，范围 0-100
     */
    int getMicbypassVolume ()
#ifdef YOUME_MAC
	{
		return 1;
	}
#else
    ;
#endif

    /**
     *  功能描述:播放音效
     *  @param pFilePath 音乐文件的路径
     *  @param repeatCount 重复播放次数，-1表示无限循环，0 播放1次， 1 播放两次
     *  @param pEffectId 返回音效的标识
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode playEffect(const char* pFilePath, int repeatCount, int* pEffectId )
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述:停止音效
     *  @param effectId 要停止的effect的Id
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode stopEffect( int effectId )
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述:停止所有音效
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode stopAllEffects()
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述:暂停音效
     *  @param effectId 要暂停的音效Id
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode pauseEffect( int effectId )
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述:恢复音效
     *  @param effectId 要暂停的音效Id
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode resumeEffect( int effectId )
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述:暂停所有音效
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode pauseAllEffects()
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述:恢复所有音效
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode resumeAllEffects()
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 设置音效播放的音量
     *  @param vol 音效的音量，范围 0-100
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setEffectVolume(int vol)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 获取音效播放的音量
     *  @return vol 音效的音量，范围 0-100
     */
    int getEffectVolume()
#ifdef YOUME_MAC
	{
		return 1;
	}
#else
    ;
#endif

    /**
     *  功能描述: 设置是否监听自己的声音或背景音乐
     *  @param micEnabled 是否监听麦克风 true 监听，false 不监听
     *  @param bgmEnabled 是否监听背景音乐 true 监听，false 不监听
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setHeadsetMonitorOn(bool micEnabled, bool bgmEnabled = true)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 设置是否开启主播混响模式
     *  @param enabled, true 开启，false 关闭
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setReverbEnabled(bool enabled)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

    /**
     *  功能描述: 设置主播音频效果类型
     *  @param effectType, 1~6 音频特效
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setAudioEffectType(unsigned int effectType)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

    /**
     *  功能描述: 设置是否开启语音检测回调
     *  @param enabled, true 开启，false 关闭
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setVadCallbackEnabled(bool enabled)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

	/**
	*  功能描述: 设置是否开启扬声器内录功能，主要用来给主播电脑放歌并演唱后，发给听众
	*  @param enabled, true 开启内录，false 关闭内录
	*  @return YOUME_SUCCESS - 成功
	*          其他 - 具体错误码
	*/
	YouMeErrorCode setSpeakerRecordOn(bool enabled)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

	/**
	*  功能描述: 获取当前是否已开启扬声器内录功能
	*  @return YOUME_SUCCESS - 成功
	*          其他 - 具体错误码
	*/
	bool isSpeakerRecording()
#ifdef YOUME_MAC
	{
		return true;
	}
#else
    ;
#endif

	/**
	*  功能描述: 清除内录缓存数据，主要用来给主播电脑放歌一段时间感觉有延迟后，手动清除缓存数据
	*  @return YOUME_SUCCESS - 成功
	*          其他 - 具体错误码
	*/
	YouMeErrorCode cleanSpeakerRecordCache()
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

    /**
     *  功能描述: 设置是否开启讲话音量回调, 并设置相应的参数
     *  @param maxLevel, 音量最大时对应的级别，最大可设100。根据实际需要设置小于100的值可以减少回调的次数。
     *                   比如你只在UI上呈现10级的音量变化，那就设10就可以了。
     *                   设 0 表示关闭回调。
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setMicLevelCallback(int maxLevel)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 设置是否开启远端语音音量回调, 并设置相应的参数
     *  @param maxLevel, 音量最大时对应的级别，最大可设100。
     *                   比如你只在UI上呈现10级的音量变化，那就设10就可以了。
     *                   设 0 表示关闭回调。
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setFarendVoiceLevelCallback(int maxLevel)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 设置当麦克风静音时，是否释放麦克风设备，在初始化之后、加入房间之前调用
     *  @param enabled,
     *      true 当麦克风静音时，释放麦克风设备，此时允许第三方模块使用麦克风设备录音。在Android上，语音通过媒体音轨，而不是通话音轨输出。
     *      false 不管麦克风是否静音，麦克风设备都会被占用。
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setReleaseMicWhenMute(bool enabled)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 设置频道音频模式
     *
     *  @param audioMode,
     *      CHANNEL_AUDIO_MODE_CALL 通话模式，激活系统的通话模式，优化对人声的通话体验
     *      CHANNEL_AUDIO_MODE_HQ_MUSIC 高音质音乐模式，着重优化音乐播放的效果，可能会产生额外费用
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setChannelAudioMode (ChannelAudioMode audioMode)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 设置插入耳机时，是否自动退出系统通话模式(禁用手机系统硬件信号前处理)
     *          系统提供的前处理效果包括回声消除、自动增益等，有助于抑制背景音乐等回声噪音，减少系统资源消耗，对Windows系统无效
     *          由于插入耳机可从物理上阻断回声产生，故可设置禁用该效果以保留背景音乐的原生音质效果
     *          默认为false，在初始化之后、加入房间之前调用
     *  @param enabled,
     *      true 当插入耳机时，自动禁用系统硬件信号前处理，拔出时还原
     *      false 插拔耳机不做处理
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setExitCommModeWhenHeadsetPlugin(bool enabled)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 设置是否为外置声卡模式，外置声卡模式强制关闭软件音频信号前处理（包含噪声消除/滤波器等），声卡内录模式播放音乐的场景中，戴耳机的情况下可以强制关闭，提高音乐质量
     *
     *  @param isExternalSoundCard,
     *      true  申明外置声卡，强制禁用部分软件音频信号前处理
     *      false 取消强制禁用软件音频信号前处理
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setExternalSoundCardMode(bool isExternalSoundCard)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 设置是否强制关闭软件AEC 处理,声卡内录模式播放音乐的话，戴耳机的情况下可以强制关闭，提高音乐质量
     *
     *  @param disable,
     *      true 强制禁用软件AEC
     *      false 取消强制禁用软件AEC
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setForceDisableAEC(bool disable)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 设置是否强制关闭软件AGC 处理,声卡内录模式播放音乐的话，戴耳机的情况下可以强制关闭，提高音乐质量
     *
     *  @param disable,
     *      true 强制禁用软件AGC
     *      false 取消强制禁用软件AGC
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setForceDisableAGC(bool disable)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 暂停通话，释放麦克风等设备资源
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode pauseChannel()
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

    /**
     *  功能描述: 恢复通话
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode resumeChannel()
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 获取变声音调（增值服务，需要后台配置开启）
     *  @return 变声音调，范围为-12~12，0为原声，值越高音调越高
     */
    float getSoundtouchPitchSemiTones()
#ifdef YOUME_MAC
	{
		return 1.0;
	}
#else
    ;
#endif

    /**
     *  功能描述: 设置变声音调（增值服务，需要后台配置开启），退出房间时重置为0
     *  @param fPitchSemiTones: 变声音调，范围为-12~12，0为原声，值越高音调越高
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode setSoundtouchPitchSemiTones(float fPitchSemiTones)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 设置当前录音的时间戳
     *  @return  None
     */
    void setRecordingTimeMs(unsigned int timeMs)
#ifdef YOUME_MAC
	{
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 设置当前播放的时间戳
     *  @return  None
     */
    void setPlayingTimeMs(unsigned int timeMs)
#ifdef YOUME_MAC
	{
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 设置PCM数据回调对象
     *  @param  pcmCallback 回调方法
     *  @param  flag:有3种pcm回调，分别为远端pcm,本地录音pcm及远端和录音的混合pcm。flag用于标记打开哪几种回调，形如PcmCallbackFlag_Remote| PcmCallbackFlag_Record|PcmCallbackFlag_Mix。
     *  @param  outputToSpeaker 是否扬声器静音:true 不静音;false 静音
     *  @param  nOutputSampleRate pcm callback重采样的采样率
     *  @param  nOutputChannel pcm callback重采样的通道数
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setPcmCallbackEnable(IYouMePcmCallback* pcmCallback, int flag,  bool bOutputToSpeaker = true, int nOutputSampleRate=16000, int nOutputChannel=1)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

    /**
     *  功能描述:获取SDK 版本号
     *
     *
     *  @return 整形数字版本号
     */
    int getSDKVersion ()
#ifdef YOUME_MAC
	{
		return 1;
	}
#else
    ;
#endif
    
    /**
     *  功能描述:Rest API , 向服务器请求额外数据
     *  @param requestID: 回传id,回调的时候传回，标识消息
     *  @param strCommand: 请求的命令字符串
     *  @param strQueryBody: 请求需要的数据,json格式，内容参考restAPI
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode  requestRestApi( const char* strCommand , const char* strQueryBody , int* requestID = NULL  )
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述:requestRestApi的回调消息
     *  @param cb: requestRestApi的回调， 需要继承IRestApiCallback并实现其中的回调函数
     *
     *  @return None
     */
    void setRestApiCallback(IRestApiCallback* cb )
#ifdef YOUME_MAC
	{
	}
#else
    ;
#endif
    
    /**
     *  功能描述:getChannelUserList的回调消息
     *  @param cb: getChannelUserList的回调， 需要继承IYouMeMemberChangeCallback并实现其中的回调函数
     *
     *  @return None
     */
    void setMemberChangeCallback( IYouMeMemberChangeCallback* cb )
#ifdef YOUME_MAC
	{
	}
#else
    ;
#endif

	/**
	 * 功能描述:    设置频道内的广播消息回调(抢麦、连麦等）
	 * @param cb: 抢麦、连麦等的广播回调，需要继承IYouMeNotifyCallback并实现其中的回调函数
	 * @return   void: 
	 */
	 void setNotifyCallback(IYouMeChannelMsgCallback* cb)
#ifdef YOUME_MAC
	 {
	 }
#else
    ;
#endif

	//---------------------抢麦接口---------------------//
	 /**
	 * 功能描述:    抢麦相关设置（抢麦活动发起前调用此接口进行设置）
	 * @param const char * pChannelID: 抢麦活动的频道id
	 * @param int mode: 抢麦模式（1:先到先得模式；2:按权重分配模式）
	 * @param int maxAllowCount: 允许能抢到麦的最大人数
	 * @param int maxTalkTime: 允许抢到麦后使用麦的最大时间（秒）
	 * @param unsigned int voteTime: 抢麦仲裁时间（秒），过了X秒后服务器将进行仲裁谁最终获得麦（仅在按权重分配模式下有效）
	 * @return   YOUME_SUCCESS - 成功
	 *          其他 - 具体错误码
	 */
	 YouMeErrorCode setGrabMicOption(const char* pChannelID, int mode, int maxAllowCount, int maxTalkTime, unsigned int voteTime)
#ifdef YOUME_MAC
	 {
		 YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		 return errorcode;
	 }
#else
    ;
#endif

	/**
	 * 功能描述:    发起抢麦活动
	 * @param const char * pChannelID: 抢麦活动的频道id
	 * @param const char * pContent: 游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）
	 * @return   YOUME_SUCCESS - 成功
	 *          其他 - 具体错误码
	 */
	YouMeErrorCode startGrabMicAction(const char* pChannelID, const char* pContent)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

	/**
	 * 功能描述:    停止抢麦活动
	 * @param const char * pChannelID: 抢麦活动的频道id
	 * @param const char * pContent: 游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）
	 * @return   YOUME_SUCCESS - 成功
	 *          其他 - 具体错误码
	 */
	YouMeErrorCode stopGrabMicAction(const char* pChannelID, const char* pContent)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

	 /**
	  * 功能描述:    发起抢麦请求
	  * @param const char * pChannelID: 抢麦的频道id
	  * @param int score: 积分（权重分配模式下有效，游戏根据自己实际情况设置）
	  * @param bool isAutoOpenMic: 抢麦成功后是否自动开启麦克风权限
	  * @param const char * pContent: 游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）
	  * @return   YOUME_SUCCESS - 成功
	  *          其他 - 具体错误码
	  */
	 YouMeErrorCode requestGrabMic(const char* pChannelID, int score, bool isAutoOpenMic, const char* pContent)
#ifdef YOUME_MAC
	 {
		 YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		 return errorcode;
	 }
#else
    ;
#endif

	 /**
	  * 功能描述:    释放抢到的麦
	  * @param const char * pChannelID: 抢麦活动的频道id
	  * @return   YOUME_SUCCESS - 成功
	  *          其他 - 具体错误码
	  */
	 YouMeErrorCode releaseGrabMic(const char* pChannelID)
#ifdef YOUME_MAC
	 {
		 YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		 return errorcode;
	 }
#else
	;
#endif

	//---------------------连麦接口---------------------//
	 /**
	 * 功能描述:    连麦相关设置（角色是频道的管理者或者主播时调用此接口进行频道内的连麦设置）
	 * @param const char * pChannelID: 连麦的频道id
	 * @param int waitTimeout: 等待对方响应超时时间（秒）
	 * @param int maxTalkTime: 最大通话时间（秒）
	 * @return   YOUME_SUCCESS - 成功
	 *          其他 - 具体错误码
	 */
	 YouMeErrorCode setInviteMicOption(const char* pChannelID, int waitTimeout, int maxTalkTime)
#ifdef YOUME_MAC
	 {
		 YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		 return errorcode;
	 }
#else
	;
#endif

	 /**
	  * 功能描述:    发起与某人的连麦请求（主动呼叫）
	  * @param const char * pUserID: 被叫方的用户id
	  * @param const char * pContent: 游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）
	  * @return   YOUME_SUCCESS - 成功
	  *          其他 - 具体错误码
	  */
	 YouMeErrorCode requestInviteMic(const char* pChannelID, const char* pUserID, const char* pContent)
#ifdef YOUME_MAC
	 {
		 YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		 return errorcode;
	 }
#else
	;
#endif

	 /**
	  * 功能描述:    对连麦请求做出回应（被动应答）
	  * @param const char * pUserID: 主叫方的用户id
	  * @param bool isAccept: 是否同意连麦
	  * @param const char * pContent: 游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）
	  * @return   YOUME_SUCCESS - 成功
	  *          其他 - 具体错误码
	  */
    YouMeErrorCode responseInviteMic(const char* pUserID, bool isAccept, const char* pContent)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

	 /**
	  * 功能描述:    停止连麦
	  * @return   YOUME_SUCCESS - 成功
	  *          其他 - 具体错误码
	  */
    YouMeErrorCode stopInviteMic()
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

    /**
     * 功能描述:   向房间广播消息
     * @param pChannelID: 广播房间
     * @param pContent: 广播内容-文本串
     * @param requestID:返回消息标识，回调的时候会回传该值
     * @return   YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode  sendMessage( const char* pChannelID,  const char* pContent, int* requestID )
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

    /**
     * 功能描述:   对频道设置白名单用户
     * @param pChannelID: 要设置的频道
     * @param vecWhiteUserList: 白名单用户列表
     * @return   YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setWhiteUserList( const char* pChannelID,  const char* whiteUserList )
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

 	/**
     *  功能描述: 把某人踢出房间
     *  @param  pUserID: 被踢的用户ID
     *  @param  pChannelID: 从哪个房间踢出
     *  @param  lastTime: 踢出后，多长时间内不允许再次进入
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode kickOtherFromChannel( const char* pUserID, const char* pChannelID , int lastTime )
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述: 调用后同步完成麦克风释放，只是为了方便使用 IM 的录音接口时切换麦克风使用权。
     *  @return bool - true 成功
     */
    bool releaseMicSync()
#ifdef YOUME_MAC
	{
		return false;
	}
#else
    ;
#endif

    /**
     *  功能描述: 调用后恢复麦克风到释放前的状态，只是为了方便使用 IM 的录音接口时切换麦克风使用权。
     *  @return bool - true 成功
     */
    bool resumeMicSync()
#ifdef YOUME_MAC
	{
		return false;
	}
#else
    ;
#endif

    /**
     *  功能描述:设置变声是否可用
     *
     *  @param enabled: 设置变声是否可用，开启时会略微增大声音延迟
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setMagicVoiceEnable(bool enabled)
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     *  功能描述:检查设备是否设置了静音，异步回调（），仅IOS有效
     *          这个功能有限制，Ios不支持静音键的情况（比如进入录音模式）下无效。可在进房间前检测。
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode checkIsDeviceMute()
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif

     /**
      *  功能描述:设置变声功能参数
      *
      *  @param effectInfo: 由变声管理模块获取到的YMMagicVoiceEffectInfo（变声音效信息），其中的m_param参数，设置时将变声器置为可用
      *  @return YOUME_SUCCESS - 成功
      *          其他 - 具体错误码
      */
     YouMeErrorCode setMagicVoiceInfo(const char *effectInfo)
#ifdef YOUME_MAC
	 {
		 YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		 return errorcode;
	 }
#else
    ;
#endif
    
     /**
      *  功能描述:清除变声功能参数
      *
      *  @return YOUME_SUCCESS - 成功
      *          其他 - 具体错误码
      */
     YouMeErrorCode clearMagicVoiceInfo()
#ifdef YOUME_MAC
	 {
		 YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		 return errorcode;
	 }
#else
    ;
#endif
    
     /**
      *  功能描述:设置变声参数微调接口
      *
      *  @param dFS: 音色的微调值，范围-1.0f~1.0f，在后台下发的基准值的基础上按百分比调节，值减小音色会变厚重，值增大音色会变尖锐
      *         dSemitones: 音调的微调值，范围-1.0f~1.0f，在后台下发的基准值的基础上按百分比调节，值减小音调会低，值增大音调会变高
      *  @return YOUME_SUCCESS - 成功
      *          其他 - 具体错误码
      */
     YouMeErrorCode setMagicVoiceAdjust(double dFS, double dSemitones)
#ifdef YOUME_MAC
	 {
		 YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		 return errorcode;
	 }
#else
    ;
#endif

     /**
      *  功能描述:变声器效果是否启用
      *
      *  @return 变声器是否可用，为false时表示当前没有变声效果生效，可以不创建变声器
      */
     bool getMagicVoiceEffectEnabled()
#ifdef YOUME_MAC
	 {
		 return false;
	 }
#else
    ;
#endif
    
    /**
     * 功能描述：设置缓存自己最近的一段语音
     *
     *  @param  nTimeSec: 保存多长的语音
     *  @return YOUME_SUCCESS - 成功
     *      其他 - 具体错误码
     */
    YouMeErrorCode setReportBufferTime( int nTimeSec )
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     * 功能描述：把缓存的语音保存成文件
     * 回调函数： onEvent
     *
     * @return YOUME_SUCCESS - 成功
     *      其他 - 具体错误码
     */
    YouMeErrorCode reportAudio( )
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    /**
     * 功能描述：给用户一个需要录音权限的提示。用户同意或者拒绝后会收到YOUME_EVENT_SHOW_RECORD_ALERT事件回调。
     *  @param context:用于弹出提示的Activity对应的jobject。如果整个app不会切换Activity，则可以不填，SDK使用初始化的context来弹界面。
     *  @param title：提示的title，不能为空
     *  @param message:提示的正文,不能为空
     *  @param okBtnText:确认按钮的文字，不能为空
     *  @param cancleBtnText:拒绝按钮的文字，可以为空，不显示该按钮。
     */
    YouMeErrorCode showRecordAlert( void* context, const char* title, const char* message, const char* okBtnText, const char* cancleBtnText )
#ifdef YOUME_MAC
	{
		YouMeErrorCode errorcode = (YouMeErrorCode_t)YOUME_SUCCESS;
		return errorcode;
	}
#else
    ;
#endif
    
    IYouMeVoiceEngine ();
    ~IYouMeVoiceEngine ();
};


#endif
