// Copyright © 2014-2021 YouMe. All Rights Reserved.

#include "YouMeTalkAPI.h"
#include "YouMeConstDefine.h"
#include "IYouMeVoiceEngine.h"
#include "YouMeTalkEngineCallback.h"

void UYouMeTalkAPI::BindObserver(TScriptInterface<IYouMeTalkObserver> Observer)
{
	FYouMeTalkCallback::GetInstance()->BindObserver(Observer);
}

void UYouMeTalkAPI::UnbindObserver()
{
	FYouMeTalkCallback::GetInstance()->UnbindObserver();
}

EYouMeErrorCode UYouMeTalkAPI::Init(const FString strAppKey, const FString strAPPSecret, EYouMeRTCServerRegion youMeRTCServerRegion, const FString strExtServerRegionName)
{
	youMeRTCServerRegion = EYouMeRTCServerRegion::RTC_DEFAULT_SERVER;
	YouMeErrorCode errorcode;
	if (IYouMeVoiceEngine::getInstance()->isInited())
	{
		return EYouMeErrorCode::YOUME_SUCCESS;
	}
	else
	{
		errorcode = IYouMeVoiceEngine::getInstance()->init(FYouMeTalkCallback::GetInstance(),
			TCHAR_TO_ANSI(*strAppKey),
			TCHAR_TO_ANSI(*strAPPSecret),
			RTC_DEFAULT_SERVER, "");
	}
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::JoinChannelSingleMode(const FString strUserID, const FString strChannelID, EYouMeUserRole userRole, bool bCheckRoomExist)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->joinChannelSingleMode(TCHAR_TO_ANSI(*strUserID), TCHAR_TO_ANSI(*strChannelID), YouMeTalkDefineConvert::YouMeUserRoleConvert(userRole), bCheckRoomExist);

	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::JoinChannelMultiMode(const FString strUserID, EYouMeUserRole eUserRole, const FString strChannelID, bool bCheckRoomExist)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->joinChannelMultiMode(TCHAR_TO_ANSI(*strUserID), TCHAR_TO_ANSI(*strChannelID), YouMeTalkDefineConvert::YouMeUserRoleConvert(eUserRole), bCheckRoomExist);

	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SpeakToChannel(const FString strChannelID)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->speakToChannel(TCHAR_TO_ANSI(*strChannelID));

	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::LeaveChannelMultiMode(const FString strChannelID)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->leaveChannelMultiMode(TCHAR_TO_ANSI(*strChannelID));
	
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::LeaveChannelAll()
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->leaveChannelAll();

	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetUserRole(EYouMeUserRole eUserRole)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setUserRole(YouMeTalkDefineConvert::YouMeUserRoleConvert(eUserRole));

	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeUserRole UYouMeTalkAPI::GetUserRole()
{
	YouMeUserRole youMeUserError = IYouMeVoiceEngine::getInstance()->getUserRole();
	return YouMeTalkDefineConvert::YouMeUserRoleConvert(youMeUserError);
}

bool UYouMeTalkAPI::IsInChannel()
{
	return IYouMeVoiceEngine::getInstance()->isInChannel();
}

bool UYouMeTalkAPI::IsInCertainChannel(const FString pChannelID)
{
	return IYouMeVoiceEngine::getInstance()->isInChannel(TCHAR_TO_ANSI(*pChannelID));
}

EYouMeErrorCode UYouMeTalkAPI::GetChannelUserList(const FString channelID, int32 maxCount, bool notifyMemChange)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->getChannelUserList(TCHAR_TO_ANSI(*channelID), maxCount, notifyMemChange);

	IYouMeVoiceEngine::getInstance()->setMemberChangeCallback(FYouMeTalkCallback::GetInstance());

	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetOtherSpeakerMute(const FString pUserID, bool mute)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setOtherSpeakerMute(TCHAR_TO_ANSI(*pUserID), mute);

	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetWhiteUserList(const FString strChannelID, const FString vecWhiteUserList)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setWhiteUserList(TCHAR_TO_ANSI(*strChannelID), TCHAR_TO_ANSI(*vecWhiteUserList));

	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetOutputToSpeaker(bool bOutputToSpeaker)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setOutputToSpeaker(bOutputToSpeaker);
	
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

void UYouMeTalkAPI::SetSpeakerMute(bool mute)
{
	IYouMeVoiceEngine::getInstance()->setSpeakerMute(mute);

}

bool UYouMeTalkAPI::GetSpeakerMute()
{
	return IYouMeVoiceEngine::getInstance()->getSpeakerMute();
}

void UYouMeTalkAPI::SetMicrophoneMute(bool mute)
{
	IYouMeVoiceEngine::getInstance()->setMicrophoneMute(mute);
}

bool UYouMeTalkAPI::GetMicrophoneMute()
{
	return IYouMeVoiceEngine::getInstance()->getMicrophoneMute();
}

void UYouMeTalkAPI::SetAutoSendStatus(bool bAutoSend)
{
	IYouMeVoiceEngine::getInstance()->setAutoSendStatus(bAutoSend);
}

void UYouMeTalkAPI::SetVolume(const int32 & uiVolume)
{
	IYouMeVoiceEngine::getInstance()->setVolume(uiVolume);
}

int32 UYouMeTalkAPI::GetVolume()
{
	return IYouMeVoiceEngine::getInstance()->getVolume();
}

void UYouMeTalkAPI::SetUseMobileNetworkEnabled(bool bEnabled)
{
	IYouMeVoiceEngine::getInstance()->setUseMobileNetworkEnabled(bEnabled);
}

bool UYouMeTalkAPI::GetUseMobileNetworkEnabled()
{
	return IYouMeVoiceEngine::getInstance()->getUseMobileNetworkEnabled();
}

EYouMeErrorCode UYouMeTalkAPI::SetOtherMicMute(const FString pUserID, bool mute)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setOtherMicMute(TCHAR_TO_ANSI(*pUserID), mute);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetListenOtherVoice(const FString userID, bool on)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setListenOtherVoice(TCHAR_TO_ANSI(*userID), on);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetReleaseMicWhenMute(bool enabled)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setReleaseMicWhenMute(enabled);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetChannelAudioMode(EChannelAudioMode audioMode)
{
	ChannelAudioMode channelAudioMode = YouMeTalkDefineConvert::ChannelAudioModeConvert(audioMode);
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setChannelAudioMode(channelAudioMode);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetExitCommModeWhenHeadsetPlugin(bool enabled)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setExitCommModeWhenHeadsetPlugin(enabled);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetExternalSoundCardMode(bool isExternalSoundCard)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setExternalSoundCardMode(isExternalSoundCard);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetForceDisableAEC(bool disable)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setForceDisableAEC(disable);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetForceDisableAGC(bool disable)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setForceDisableAGC(disable);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

bool UYouMeTalkAPI::ReleaseMicSync()
{
	return IYouMeVoiceEngine::getInstance()->releaseMicSync();
}

int32 UYouMeTalkAPI::GetMicVolume()
{
	return IYouMeVoiceEngine::getInstance()->getMicVolume();
}

void UYouMeTalkAPI::SetMicVolume(const int32 & uiVolume)
{
	return IYouMeVoiceEngine::getInstance()->setMicVolume(uiVolume);
}

EYouMeErrorCode UYouMeTalkAPI::PauseChannel()
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->pauseChannel();
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::ResumeChannel()
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->resumeChannel();
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetVadCallbackEnabled(bool enabled)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setVadCallbackEnabled(enabled);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetSpeakerRecordOn(bool enable)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setSpeakerRecordOn(enable);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

bool UYouMeTalkAPI::IsSpeakerRecording()
{
	return IYouMeVoiceEngine::getInstance()->isSpeakerRecording();
}

EYouMeErrorCode UYouMeTalkAPI::CleanSpeakerRecordCache()
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->cleanSpeakerRecordCache();
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetFarendVoiceLevelCallback(int32 maxLevel)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setFarendVoiceLevelCallback(maxLevel);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::Talk_SetMicLevelCallback(int32 maxLevel)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setMicLevelCallback(maxLevel);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::PlayBackgroundMusic(const FString pFilePath, bool bRepeat)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->playBackgroundMusic(TCHAR_TO_ANSI(*pFilePath), bRepeat);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::PauseBackgroundMusic()
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->pauseBackgroundMusic();
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::ResumeBackgroundMusic()
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->resumeBackgroundMusic();
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::StopBackgroundMusic()
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->stopBackgroundMusic();
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

bool UYouMeTalkAPI::IsBackgroundMusicPlaying()
{
	return IYouMeVoiceEngine::getInstance()->isBackgroundMusicPlaying();
}

EYouMeErrorCode UYouMeTalkAPI::SetBackgroundMusicVolume(int32 vol)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setBackgroundMusicVolume(vol);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

int32 UYouMeTalkAPI::GetBackgroundMusicVolume()
{
	return IYouMeVoiceEngine::getInstance()->getBackgroundMusicVolume();
}

EYouMeErrorCode UYouMeTalkAPI::PlayEffect(const FString pFilePath, int32 repeatCount, int32 & pEffectId)
{
	int *ptrEffectId = &pEffectId;
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->playEffect(TCHAR_TO_ANSI(*pFilePath), repeatCount, ptrEffectId);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::StopEffect(int32 effectId)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->stopEffect(effectId);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::StopAllEffects()
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->stopAllEffects();
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::PauseEffect(int effectId)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->pauseEffect(effectId);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::ResumeAllEffects()
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->resumeAllEffects();
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetEffectVolume(int vol)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setEffectVolume(vol);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

int32 UYouMeTalkAPI::GetEffectVolume()
{
	return IYouMeVoiceEngine::getInstance()->getEffectVolume();
}

EYouMeErrorCode UYouMeTalkAPI::SetHeadsetMonitorOn(bool micEnabled, bool bgmEnabled)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setHeadsetMonitorOn(micEnabled, bgmEnabled);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

float UYouMeTalkAPI::GetSoundtouchPitchSemiTones()
{
	return IYouMeVoiceEngine::getInstance()->getSoundtouchPitchSemiTones();
}

EYouMeErrorCode UYouMeTalkAPI::SetSoundtouchPitchSemiTones(float fPitchSemiTones)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setSoundtouchPitchSemiTones(fPitchSemiTones);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetReverbEnabled(bool enabled)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setReverbEnabled(enabled);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetAudioEffectType(int32 effectType)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setAudioEffectType(effectType);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

void UYouMeTalkAPI::SetRecordingTimeMs(int32 timeMs)
{
	IYouMeVoiceEngine::getInstance()->setRecordingTimeMs(timeMs);
}

void UYouMeTalkAPI::SetPlayingTimeMs(int32 timeMs)
{
	IYouMeVoiceEngine::getInstance()->setPlayingTimeMs(timeMs);
}

int32 UYouMeTalkAPI::GetSDKVersion()
{
	return IYouMeVoiceEngine::getInstance()->getSDKVersion();
}

EYouMeErrorCode UYouMeTalkAPI::RequestRestApi(const FString strCommand, const FString strQueryBody, int32 requestID)
{
	int * requestIDPtr= new int(requestID);
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->requestRestApi(TCHAR_TO_ANSI(*strCommand), TCHAR_TO_ANSI(*strQueryBody), requestIDPtr);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

void UYouMeTalkAPI::SetRestApiCallback()
{
	
}

void UYouMeTalkAPI::SetToken(const FString pToken)
{
	IYouMeVoiceEngine::getInstance()->setToken(TCHAR_TO_ANSI(*pToken));
}

bool UYouMeTalkAPI::IsInited()
{
	return IYouMeVoiceEngine::getInstance()->isInited();
}

void UYouMeTalkAPI::SetServerRegion(EYouMeRTCServerRegion regionId, const FString extRegionName, bool bAppend)
{
	IYouMeVoiceEngine::getInstance()->setServerRegion(YouMeTalkDefineConvert::YouMeRTCServerRegionConvert(regionId), TCHAR_TO_ANSI(*extRegionName), bAppend);
}

EYouMeErrorCode UYouMeTalkAPI::SendMessage(const FString pChannelID, const FString pContent, int32 requestID)
{
	int * requestIDPtr = new int(requestID);
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->sendMessage(TCHAR_TO_ANSI(*pChannelID), TCHAR_TO_ANSI(*pContent), requestIDPtr);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::KickOtherFromChannel(const FString pUserID, const FString pChannelID, int32 lastTime)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->kickOtherFromChannel(TCHAR_TO_ANSI(*pUserID), TCHAR_TO_ANSI(*pChannelID), lastTime);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::UnInit()
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->unInit();
	FYouMeTalkCallback::Destroy();
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

bool UYouMeTalkAPI::ResumeMicSync()
{
	return IYouMeVoiceEngine::getInstance()->resumeMicSync();
}

EYouMeErrorCode UYouMeTalkAPI::SetMagicVoiceEnable(bool enabled)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setMagicVoiceEnable(enabled);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::CheckIsDeviceMute()
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->checkIsDeviceMute();
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetGrabMicOption(const FString pChannelID, int32 mode, int32 maxAllowCount, int32 maxTalkTime, int32 voteTime)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setGrabMicOption(TCHAR_TO_ANSI(*pChannelID), mode, maxAllowCount, maxTalkTime, voteTime);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::StartGrabMicAction(const FString pChannelID, const FString pContent)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->startGrabMicAction(TCHAR_TO_ANSI(*pChannelID), TCHAR_TO_ANSI(*pContent));
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::StopGrabMicAction(const FString pChannelID, const FString pContent)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->stopGrabMicAction(TCHAR_TO_ANSI(*pChannelID), TCHAR_TO_ANSI(*pContent));
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::RequestGrabMic(const FString pChannelID, int32 score, bool isAutoOpenMic, const FString pContent)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->requestGrabMic(TCHAR_TO_ANSI(*pChannelID), score, isAutoOpenMic, TCHAR_TO_ANSI(*pContent));
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::ReleaseGrabMic(const FString pChannelID)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->releaseGrabMic(TCHAR_TO_ANSI(*pChannelID));
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::SetInviteMicOption(const FString pChannelID, int32 waitTimeout, int32 maxTalkTime)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->setInviteMicOption(TCHAR_TO_ANSI(*pChannelID), waitTimeout, maxTalkTime);
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::RequestInviteMic(const FString pChannelID, const FString pUserID, const FString pContent)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->requestInviteMic(TCHAR_TO_ANSI(*pChannelID), TCHAR_TO_ANSI(*pContent), TCHAR_TO_ANSI(*pContent));
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::ResponseInviteMic(const FString pUserID, bool isAccept, const FString pContent)
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->responseInviteMic(TCHAR_TO_ANSI(*pUserID), isAccept, TCHAR_TO_ANSI(*pContent));
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}

EYouMeErrorCode UYouMeTalkAPI::StopInviteMic()
{
	YouMeErrorCode errorcode = IYouMeVoiceEngine::getInstance()->stopInviteMic();
	return YouMeTalkDefineConvert::YouMeErrorCodeConvert(errorcode);
}
