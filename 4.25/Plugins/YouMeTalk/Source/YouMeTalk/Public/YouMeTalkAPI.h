// Copyright © 2014-2021 YouMe. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "YouMeTalkDefine.h"
#include "YouMeTalkObserver.h"
#include "YouMeTalkAPI.generated.h"

/**
 * 
 */
UCLASS()
class YOUMETALK_API UYouMeTalkAPI : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	*  funcDesc: Bind observer in callback
	*  @param  Observer: YouMeTalkObserver interface
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static void BindObserver(TScriptInterface<IYouMeTalkObserver> Observer);

	/**
	*  funcDesc: Unbind observer in callback
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static void UnbindObserver();
		
	/**
	*  funcDesc: YouMeTalk plugin init
	*  @param  strAppKey: The app key obtained when applying for SDK registration can also be sent to the http://gmx.dev.net/createApp.html query
	*  @param  strAPPSecret: The app secret obtained when applying for SDK registration can also be sent to the http://gmx.dev.net/createApp.html query
	*  @param  youMeRTCServerRegion: Server region
	*  @param  strExtServerRegionName: Server region name
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode Init(const FString strAppKey, const FString strAPPSecret, EYouMeRTCServerRegion youMeRTCServerRegion, const FString strExtServerRegionName);

	/**
	*  funcDesc: YouMeTalk plugin is init
	*  @return true——complete，false——incomplete
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static bool IsInited();

	/**
	*  funcDesc: Join voice channel (single channel mode, only one voice channel at any time)
	*  @param  strUserID: The user ID must be globally unique
	*  @param  strChannelID: Channel ID, to ensure global uniqueness
	*  @param  userRole: User role, which is used to decide the right to speak / play background music, etc
	*  @param  bCheckRoomExist: Check whether to join only when the channel exists. The default value is false: true. Error is returned when the channel exists or does not exist (mostly for audience roles). False: join the channel regardless of whether the channel exists
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode JoinChannelSingleMode(const FString strUserID, const FString strChannelID, EYouMeUserRole userRole, bool bCheckRoomExist);

	/**
	*  funcDesc: Join voice channel (multi-channel mode, can be in multiple voice channels at the same time)
	*  @param  strUserID: The user ID must be globally unique
	*  @param  strChannelID: Channel ID, to ensure global uniqueness
	*  @param  eUserRole: User role, which is used to decide the right to speak / play background music, etc
	*  @param  bCheckRoomExist: Check whether to join only when the channel exists. The default value is false: true. Error is returned when the channel exists or does not exist (mostly for audience roles). False: join the channel regardless of whether the channel exists
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode JoinChannelMultiMode(const FString strUserID, EYouMeUserRole eUserRole, const FString strChannelID, bool bCheckRoomExist);

	/**
	*  funcDesc: Speak to the designated channel
	*  @param  strChannelID: Channel ID, to ensure global uniqueness
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SpeakToChannel(const FString strChannelID);

	/**
	*  funcDesc: Exit a voice channel in multi-channel mode
	*  @param  strChannelID: Channel ID, to ensure global uniqueness
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode LeaveChannelMultiMode(const FString strChannelID);

	/**
	*  funcDesc: Exit all voice channels
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode LeaveChannelAll();

	/**
	*  funcDesc: Switch identity (only support single channel mode, set after entering the room)
	*  @param  eUserRole: User role, which is used to decide the right to speak / play background music, etc
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetUserRole(EYouMeUserRole eUserRole);

	/**
	*  funcDesc: Get identity (single channel mode only)
	*  @return Identity definition
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeUserRole GetUserRole();

	/**
	*  funcDesc: Query whether it is in the voice channel
	*  @return true——On channel，false——It's not on the channel
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static bool IsInChannel();

	/**
	*  funcDesc: Query whether it is in a voice channel
	*  @param pChannelID: Channel ID to query
	*  @return true——On channel，false——It's not on the channel
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static bool IsInCertainChannel(const FString pChannelID);

	/**
	*  funcDesc: Query the user list of the channel
	*  @param pChannelID: Channel ID to query
	*  @param maxCount: The maximum number you want to get, - 1 means get all
	*  @param notifyMemChange: Do other users need to be informed when they enter or leave the room
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode GetChannelUserList(const FString  channelID, int32 maxCount, bool notifyMemChange);

	/**
	*  funcDesc: Control other people's microphone switch
	*  @param pUserID: The user ID must be globally unique
	*  @param mute: True to mute the other party's microphone, false to unmute the other party's microphone
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetOtherSpeakerMute(const FString pUserID, bool mute);

	/**
	*  funcDesc: Set whitelist users for channels
	*  @param strChannelID: Channel to set
	*  @param vecWhiteUserList: White list user list
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetWhiteUserList(const FString strChannelID, const FString vecWhiteUserList);


	/**
	*  funcDesc: Switching voice output devices
	*  @param bOutputToSpeaker: True -- use the speaker, false -- use the receiver
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetOutputToSpeaker(bool bOutputToSpeaker);

	/**
	*  funcDesc: Mute speakers
	*  @param mute: True -- mute, false -- unmute
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static void SetSpeakerMute(bool mute);

	/**
	*  funcDesc: Get speaker mute status
	*  @return True -- mute, false -- unmute
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static bool GetSpeakerMute();

	/**
	*  funcDesc: Mute microphone
	*  @param mute: True -- mute, false -- unmute
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static void SetMicrophoneMute(bool mute);

	/**
	*  funcDesc: Get microphone mute status
	*  @return True -- mute, false -- unmute
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static bool GetMicrophoneMute();

	/**
	*  funcDesc: Set whether to notify others of the status of their own on-off microphones and speakers
	*  @param bAutoSend: True -- notify, false -- not notify
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static void SetAutoSendStatus(bool bAutoSend);

	/**
	*  funcDesc: Increase the volume by 1
	*  @param uiVolume: volume
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static void SetVolume(const int32 &uiVolume);

	/**
	*  funcDesc: Get the volume value, which is the volume inside the program, and multiply it with the system volume to get the actual volume used by the program
	*  @return Volume value [0-100]
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static int32 GetVolume();

	/**
	*  funcDesc: Enable / disable mobile network
	*  @param bEnabled: True - can be enabled, false - disabled, disabled by default
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static void SetUseMobileNetworkEnabled(bool bEnabled);

	/**
	*  funcDesc: Is mobile network available
	*  @return True - available, false disabled
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static bool GetUseMobileNetworkEnabled();

	/**
	*  funcDesc: Control other people's microphone switch
	*  @param pUserID: The user ID must be globally unique
	*  @param mute: True - can be enabled, false - disabled, disabled by default
	*  @return True - available, false disabled
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetOtherMicMute(const FString pUserID, bool mute);

	/**
	*  funcDesc: Choose to eliminate other people's voice
	*  @param userID: The user ID must be globally unique
	*  @param on: False to block the other party's voice, true to cancel the blocking
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetListenOtherVoice(const FString userID, bool on);

	/**
	*  funcDesc: When the microphone is mute, does it release the microphone device? After initialization, add the room before calling.
	*  @param enabled:
	*	   true -- When the microphone is silent, release the microphone device and allow the third-party module to use the microphone device for recording. On Android, voice is output through the media track, not the call track.
	*      false -- Whether the microphone is muted or not, the microphone device will be occupied.
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetReleaseMicWhenMute(bool enabled);

	/**
	*  funcDesc: Set channel audio mode
	*  @param audioMode:
	*	   CHANNEL_AUDIO_MODE_CALL -- Call mode, activate the call mode of the system, optimize the call experience of human voice
	*      CHANNEL_AUDIO_MODE_HQ_MUSIC -- High quality music mode, focusing on optimizing the effect of music playback, may incur additional costs
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetChannelAudioMode(EChannelAudioMode audioMode);

	/**
	*  funcDesc: Set whether to automatically exit the system call mode when the headset is inserted (disable the hardware signal preprocessing of the mobile phone system)
	*	   The pre-processing effects provided by the system include echo cancellation, automatic gain, etc., which help to suppress echo noise such as background music, reduce the consumption of system resources, and have no effect on Windows system
	*	   Since the earphone can physically block the echo generation, it can be set to disable the effect to retain the original sound quality of the background music
	*      default is false, after initialization, before calling room.
	*  @param enabled:
	*      true -- When the headset is inserted, the system hardware signal preprocessing is automatically disabled and restored when it is pulled out
	*      false -- Plug and unplug headphones without handling
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetExitCommModeWhenHeadsetPlugin(bool enabled);

	/**
	*  funcDesc: Set whether it is the external sound card mode. In the external sound card mode, the software audio signal preprocessing (including noise cancellation / filter, etc.) is forced to be turned off. In the scene of playing music in the sound card internal recording mode, it can be forced to turn off when wearing headphones to improve the music quality
	*  @param isExternalSoundCard:
	*      true -- Declare the external sound card, and forcibly disable some software audio signal preprocessing
	*      false -- Cancel the mandatory disable software audio signal preprocessing
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetExternalSoundCardMode(bool isExternalSoundCard);

	/**
	*  funcDesc: Set whether the software AEC processing is forced to be turned off. When playing music in the sound card recording mode, it can be forced to turn off when wearing headphones to improve the music quality
	*  @param disable:
	*      true -- Disable software AEC by force
	*      false -- Cancel the mandatory disable of software AEC
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetForceDisableAEC(bool disable);

	/**
	*  funcDesc: Set whether the software AGC processing is forced to be turned off. If the music is played in the sound card recording mode, it can be forced to turn off when wearing headphones to improve the music quality
	*  @param disable:
	*      true -- Disable software AEC by force
	*      false -- Cancel the mandatory disable of software AEC
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetForceDisableAGC(bool disable);

	/**
	*  funcDesc: After the call, the microphone release is completed synchronously, only to switch the microphone usage right when using IM recording interface.
	*  @return bool - true Success
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static bool ReleaseMicSync();

	/**
	*  funcDesc: After calling, restore the microphone to the state before releasing, just for the convenience of switching the right to use the microphone when using the im recording interface.
	*  @return bool - true Success
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static bool ResumeMicSync();

	/**
	*  funcDesc: Get the microphone volume gain value, which is the microphone volume gain value inside the program, and multiply it with the system volume to get the actual volume used by the program
	*  @return Volume value[0,1000]
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static int32 GetMicVolume();

	/**
	*  funcDesc: Set the microphone volume gain (0-1000), 100 as the normal value
	*  @param uiVolume: Volume value[0,1000]
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static void SetMicVolume(const int32 &uiVolume);

	/**
	*  funcDesc: Pause the call and release the microphone and other device resources
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode PauseChannel();

	/**
	*  funcDesc: Resume call
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode ResumeChannel();

	/**
	*  funcDesc: Set whether to turn on voice detection callback
	*  @param enabled, true open，false close
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetVadCallbackEnabled(bool enabled);

	/**
	*  funcDesc: Set whether to turn on the speaker recording function, which is mainly used to play songs to the host computer and send them to the audience after singing
	*  @param enabled, true -- Open internal recording，false -- Close internal recording
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetSpeakerRecordOn(bool enable);

	/**
	*  funcDesc: Get whether the speaker recording function has been turned on or not
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static bool IsSpeakerRecording();

	/**
	*  funcDesc: Clear the cache data, mainly used to play songs to the host computer for a period of time, feel the delay, manually clear the cache data
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode CleanSpeakerRecordCache();

	/**
	*  funcDesc: Set whether to turn on the remote voice volume callback, and set the corresponding parameters
	*  @param maxLevel: The level corresponding to the maximum volume can be set to 100.
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetFarendVoiceLevelCallback(int32 maxLevel);

	/**
	*  funcDesc: Set whether to turn on speech volume callback and set corresponding parameters
	*  @param maxLevel: The level corresponding to the maximum volume can be set to 100. According to the actual needs, setting a value less than 100 can reduce the number of callbacks.
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode Talk_SetMicLevelCallback(int32 maxLevel);

	/**
	*  funcDesc: Play background music and allow selection to blend to speaker output and microphone input
	*  @param pFilePath: Path to music files
	*  @param bRepeat: Repeat
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode PlayBackgroundMusic(const FString pFilePath, bool bRepeat);

	/**
	*  funcDesc: Pause if background music is currently playing
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode PauseBackgroundMusic();

	/**
	*  funcDesc: 如果当前背景音乐处于暂停状态的话，恢复播放
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode ResumeBackgroundMusic();

	/**
	*  funcDesc: Stop playing if background music is currently playing
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode StopBackgroundMusic();

	/**
	*  funcDesc: Is background music playing
	*  @return true —— playing，false—— not playing
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static bool IsBackgroundMusicPlaying();

	/**
	*  funcDesc: Set the volume of background music
	*  @param vol: Background music volume, range 0-100
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetBackgroundMusicVolume(int32 vol);

	/**
	*  funcDesc: Get the volume of background music
	*  @return vol Background music volume, range 0-100
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static int32 GetBackgroundMusicVolume();

	/**
	*  funcDesc: Set the volume of background music
	*  @param pFilePath: Path of music file
	*  @param repeatCount: Repeat times, - 1 means infinite loop, 0 plays once, 1 plays twice
	*  @param pEffectId: Returns the identification of the sound effect
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode PlayEffect(const FString pFilePath, int32 repeatCount, int32 & pEffectId);

	/**
	*  funcDesc: Stop the sound
	*  @param effectId: ID of the effect to stop
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode StopEffect(int32 effectId);

	/**
	*  funcDesc: Stop all sound effects
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode StopAllEffects();

	/**
	*  funcDesc: Pause effect
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode PauseEffect(int effectId);

	/**
	*  funcDesc: Resume all effect
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode ResumeAllEffects();

	/**
	*  funcDesc: Set the volume for sound playback
	*  @param vol: Volume of sound effect, range 0-100
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetEffectVolume(int vol);

	/**
	*  funcDesc: Get the volume of sound effect playback
	*  @return vol: the volume of the sound effect in the range of 0-100
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static int32 GetEffectVolume();

	/**
	*  funcDesc: Set whether to listen to your own voice or background music
	*  @param micEnabled: Do you want to monitor the microphone? True monitor, false do not monitor
	*  @param bgmEnabled: Do you want to monitor background music? True monitor, false do not monitor
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetHeadsetMonitorOn(bool micEnabled, bool bgmEnabled = true);

	/**
	*  funcDesc: Get voice changing tone (value-added service, need background configuration to start)
	*  @return vol: Tone of variation, range is -12-12, 0 is original sound, and the higher the value is, the higher the pitch is
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static float GetSoundtouchPitchSemiTones();

	/**
	*  funcDesc: Set the tone change (value-added service, need to be enabled by background configuration), reset to 0 when you exit the room
	*  @param fPitchSemiTones: The range is - 12 ~ 12. 0 is the original tone. The higher the value is, the higher the tone is
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetSoundtouchPitchSemiTones(float fPitchSemiTones);

	/**
	*  funcDesc: Set whether to turn on the host reverb mode
	*  @param enabled: True on, false off
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetReverbEnabled(bool enabled);

	/**
	*  funcDesc: Set anchor audio effect type
	*  @param effectType: 1 ~ 6 audio effects
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetAudioEffectType(int32 effectType);

	/**
	*  funcDesc: Set the timestamp of the current recording
	*  @param timeMs: timestamp 
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static void SetRecordingTimeMs(int32 timeMs);

	/**
	*  funcDesc: Set the timestamp of the current playback
	*  @param timeMs: timestamp
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static void SetPlayingTimeMs(int32 timeMs);

	//UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
	//	static EYouMeErrorCode SetPcmCallbackEnable();

	/**
	*  funcDesc:Get SDK version number
	*  @return Plastic digit version number
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static int32 GetSDKVersion();

	/**
	*  funcDesc: Set server zone
	*  @param region: server region
	*  @param extRegionName: extRegionName
	*  @param bAppend: bAppend
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static void SetServerRegion(EYouMeRTCServerRegion regionId, const FString extRegionName, bool bAppend);

	/**
	*  funcDesc: Rest API , Request additional data from the server
	*  @param requestID: Return ID, return when callback, identify message
	*  @param strCommand: The requested command string
	*  @param strQueryBody: The data required by the request, in JSON format, refer to rest API for content
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode RequestRestApi(const FString strCommand, const FString strQueryBody, int32 requestID);

	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static void SetRestApiCallback();
		
	/**
	*  funcDesc: Set the token of authentication and the time when the user joins the room
	*  @param pToken: The token is used for authentication, which is set to null or empty string, and the token value is cleared.
	*  @param uTimeStamp: Time when the user joined the room
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static void SetToken(const FString pToken);

	/**
	*  funcDesc: Broadcast a message to the room
	*  @param pChannelID: Broadcasting room
	*  @param pContent: Broadcast content - text string
	*  @param requestID: Returns the message ID, which will be returned during callback
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SendMessage(const FString pChannelID, const FString pContent, int32 requestID);

	/**
	*  funcDesc: Kick sb out of the room
	*  @param  pUserID: Kicked user ID
	*  @param  pChannelID: From which room
	*  @param  lastTime: After kicking out, how long is it not allowed to enter again
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode KickOtherFromChannel(const FString pUserID, const FString pChannelID, int32 lastTime);

	/**
	*  funcDesc:Anti initialization engine
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode UnInit();

	/**
	*  funcDesc:Set whether voice change is available
	*
	*  @param enabled: Set whether the sound change is available. When it is turned on, the sound delay will be slightly increased
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetMagicVoiceEnable(bool enabled);

	/**
	*  funcDesc: Check whether the device is muted, call back asynchronously (), only IOS is valid
	*           This function is limited. IOS does not support the mute key (such as entering recording mode). It can be detected before entering the room.
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode CheckIsDeviceMute();

	/**
	*  funcDesc: Grab the wheat related settings (call the interface before the start of the wheat shooting activity).
	*  @param const char * pChannelID: Channel ID of wheat snatching activity
	*  @param int mode: Wheat snatching mode (1: first come first served mode; 2: Distribution by weight mode)
	*  @param int maxAllowCount: The maximum number of people allowed to grab wheat
	*  @param int maxTalkTime: Maximum time allowed to use wheat after seizing wheat (seconds)
	*  @param unsigned int voteTime: The arbitration time for grabbing wheat (seconds). After x seconds, the server will arbitrate who finally gets wheat (only valid in weight distribution mode)
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetGrabMicOption(const FString pChannelID, int32 mode, int32 maxAllowCount, int32 maxTalkTime, int32 voteTime);

	/**
	* funcDesc: Launching wheat snatching activities
	* @param const char * pChannelID: Channel ID of wheat snatching activity
	* @param const char * pContent: The notification callback will return the context content of the game (only plain text format is supported at present)
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode StartGrabMicAction(const FString pChannelID, const FString pContent);

	/**
	* funcDesc: Stop robbing wheat
	* @param const char * pChannelID: Channel ID of wheat snatching activity
	* @param const char * pContent: The notification callback will return the context content of the game (only plain text format is supported at present)
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode StopGrabMicAction(const FString pChannelID, const FString pContent);

	/**
	* funcDesc: Request for wheat
	* @param const char * pChannelID: The channel ID of Rob Mai
	* @param int score: Points (effective in weight distribution mode, the game is set according to the actual situation)
	* @param bool isAutoOpenMic: Do you want to automatically turn on the microphone permission after the successful scramble
	* @param const char * pContent: The notification callback will return the context content of the game (only plain text format is supported at present)
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode RequestGrabMic(const FString pChannelID, int32 score, bool isAutoOpenMic, const FString pContent);

	/**
	* funcDesc: Release the stolen wheat
	* @param const char * pChannelID: Channel ID of wheat snatching activity
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode ReleaseGrabMic(const FString pChannelID);

	/**
	* funcDesc: Related settings of Lianmai (when the role is the channel manager or anchor, call this interface to set Lianmai in the channel)
	* @param const char * pChannelID: Lianmai's channel ID
	* @param int waitTimeout: Waiting for response timeout (seconds)
	* @param int maxTalkTime: Maximum talk time (seconds)
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode SetInviteMicOption(const FString pChannelID, int32 waitTimeout, int32 maxTalkTime);

	/**
	* funcDesc: Initiate a connection request with sb
	* @param const char * pUserID: User ID of the called party
	* @param const char * pContent: The notification callback will return the context content of the game (only plain text format is supported at present)
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode RequestInviteMic(const FString pChannelID, const FString pUserID, const FString pContent);

	/**
	* funcDesc: Respond to the request of Lianmai (passive response)
	* @param const char * pUserID: Caller's user ID
	* @param bool isAccept: Do you agree with Lianmai
	* @param const char * pContent: The notification callback will return the context content of the game (only plain text format is supported at present)
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode ResponseInviteMic(const FString pUserID, bool isAccept, const FString pContent);

	/**
	* funcDesc: Stop Lianmai
	*  @return YOUME_SUCCESS - Success
	*          Other - Specific error code
	*/
	UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
		static EYouMeErrorCode StopInviteMic();

};
