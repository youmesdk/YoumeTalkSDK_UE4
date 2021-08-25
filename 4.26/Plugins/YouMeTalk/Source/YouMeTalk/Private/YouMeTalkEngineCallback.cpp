// Copyright © 2014-2021 YouMe. All Rights Reserved.

#include "YouMeTalkEngineCallback.h"
#include "YouMeTalkObserver.h"
#include "YouMeTalkDefine.h"
#include "Json.h"

static bool IsImplementFunc(UObject* Obj, const FName& name) {
	if (!Obj) {
		return false;
	}

	UClass* pCls = Obj->GetClass();
	if (!pCls) {
		return false;
	}

	bool bImplementsInterface = pCls->ImplementsInterface(UYouMeTalkObserver::StaticClass());
	// bool bImplementedFunction = pCls->IsFunctionImplementedInScript(name);
	return bImplementsInterface;
}

FYouMeTalkCallback* FYouMeTalkCallback::YimWork;

FYouMeTalkCallback::FYouMeTalkCallback()
{
}

FYouMeTalkCallback::~FYouMeTalkCallback()
{
}

FYouMeTalkCallback * FYouMeTalkCallback::GetInstance()
{
	if (YimWork == nullptr)
	{
		YimWork = new FYouMeTalkCallback();
	}
	return YimWork;
}

void FYouMeTalkCallback::Destroy()
{
	if (YimWork != nullptr)
	{
		delete YimWork;
		YimWork = nullptr;
	}
}

void FYouMeTalkCallback::BindObserver(TScriptInterface<IYouMeTalkObserver> Listener)
{
	if (Listener.GetObject() != nullptr)
	{
		YimObserver = Listener.GetObject();
	}
}

void FYouMeTalkCallback::UnbindObserver()
{
	YimObserver = NULL;
}

void FYouMeTalkCallback::onEvent(const YouMeEvent event, const YouMeErrorCode error, const char * channel, const char * param)
{
	if (YimObserver == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("YimObserver is nullptr, please bind a valid observer"));
		return;
	}
	bool bIsImplemented = IsImplementFunc(YimObserver, FName(TEXT("OnEvent")));

	if (bIsImplemented == true)
	{
		UObject* tmpObt = YimObserver;
		const EYouMeErrorCode errorCode = YouMeTalkDefineConvert::YouMeErrorCodeConvert(error);
		const EYouMeEvent youMeEvent = YouMeTalkDefineConvert::YouMeEventConvert(event);
		FString channel_fs = UTF8_TO_TCHAR(channel);
		FString param_fs = UTF8_TO_TCHAR(param);

		AsyncTask(ENamedThreads::GameThread, [tmpObt, youMeEvent, errorCode, channel_fs, param_fs] {
			if (tmpObt != nullptr) {
				IYouMeTalkObserver::Execute_OnEvent(tmpObt, youMeEvent, errorCode, channel_fs, param_fs);
			}
		});
	}

	switch (event)
	{
	case YOUME_EVENT_INIT_OK:
		UE_LOG(LogTemp, Log, TEXT("YOUME_EVENT_INIT_OK"));
		break;
	case YOUME_EVENT_INIT_FAILED:
		break;
	case YOUME_EVENT_JOIN_OK:
		UE_LOG(LogTemp, Log, TEXT("YOUME_EVENT_JOIN_OK"));
		break;
	case YOUME_EVENT_JOIN_FAILED:
		break;
	case YOUME_EVENT_LEAVED_ONE:
		break;
	case YOUME_EVENT_LEAVED_ALL:
		break;
	case YOUME_EVENT_PAUSED:
		break;
	case YOUME_EVENT_RESUMED:
		break;
	case YOUME_EVENT_SPEAK_SUCCESS:
		break;
	case YOUME_EVENT_SPEAK_FAILED:
		break;
	case YOUME_EVENT_RECONNECTING:
		break;
	case YOUME_EVENT_RECONNECTED:
		break;
	case YOUME_EVENT_REC_PERMISSION_STATUS:
		break;
	case YOUME_EVENT_BGM_STOPPED:
		break;
	case YOUME_EVENT_BGM_FAILED:
		break;
	case YOUME_EVENT_OTHERS_MIC_ON:
		break;
	case YOUME_EVENT_OTHERS_MIC_OFF:
		break;
	case YOUME_EVENT_OTHERS_SPEAKER_ON:
		break;
	case YOUME_EVENT_OTHERS_SPEAKER_OFF:
		break;
	case YOUME_EVENT_OTHERS_VOICE_ON:
		break;
	case YOUME_EVENT_OTHERS_VOICE_OFF:
		break;
	case YOUME_EVENT_MY_MIC_LEVEL:
		break;
	case YOUME_EVENT_MIC_CTR_ON:
		break;
	case YOUME_EVENT_MIC_CTR_OFF:
		break;
	case YOUME_EVENT_SPEAKER_CTR_ON:
		break;
	case YOUME_EVENT_SPEAKER_CTR_OFF:
		break;
	case YOUME_EVENT_LISTEN_OTHER_ON:
		break;
	case YOUME_EVENT_LISTEN_OTHER_OFF:
		break;
	case YOUME_EVENT_LOCAL_MIC_ON:
		break;
	case YOUME_EVENT_LOCAL_MIC_OFF:
		break;
	case YOUME_EVENT_LOCAL_SPEAKER_ON:
		break;
	case YOUME_EVENT_LOCAL_SPEAKER_OFF:
		break;
	case YOUME_EVENT_GRABMIC_START_OK:
		break;
	case YOUME_EVENT_GRABMIC_START_FAILED:
		break;
	case YOUME_EVENT_GRABMIC_STOP_OK:
		break;
	case YOUME_EVENT_GRABMIC_STOP_FAILED:
		break;
	case YOUME_EVENT_GRABMIC_REQUEST_OK:
		break;
	case YOUME_EVENT_GRABMIC_REQUEST_FAILED:
		break;
	case YOUME_EVENT_GRABMIC_REQUEST_WAIT:
		break;
	case YOUME_EVENT_GRABMIC_RELEASE_OK:
		break;
	case YOUME_EVENT_GRABMIC_RELEASE_FAILED:
		break;
	case YOUME_EVENT_GRABMIC_ENDMIC:
		break;
	case YOUME_EVENT_GRABMIC_NOTIFY_START:
		break;
	case YOUME_EVENT_GRABMIC_NOTIFY_STOP:
		break;
	case YOUME_EVENT_GRABMIC_NOTIFY_HASMIC:
		break;
	case YOUME_EVENT_GRABMIC_NOTIFY_NOMIC:
		break;
	case YOUME_EVENT_INVITEMIC_SETOPT_OK:
		break;
	case YOUME_EVENT_INVITEMIC_SETOPT_FAILED:
		break;
	case YOUME_EVENT_INVITEMIC_REQUEST_OK:
		break;
	case YOUME_EVENT_INVITEMIC_REQUEST_FAILED:
		break;
	case YOUME_EVENT_INVITEMIC_RESPONSE_OK:
		break;
	case YOUME_EVENT_INVITEMIC_RESPONSE_FAILED:
		break;
	case YOUME_EVENT_INVITEMIC_STOP_OK:
		break;
	case YOUME_EVENT_INVITEMIC_STOP_FAILED:
		break;
	case YOUME_EVENT_INVITEMIC_CAN_TALK:
		break;
	case YOUME_EVENT_INVITEMIC_CANNOT_TALK:
		break;
	case YOUME_EVENT_INVITEMIC_NOTIFY_CALL:
		break;
	case YOUME_EVENT_INVITEMIC_NOTIFY_ANSWER:
		break;
	case YOUME_EVENT_INVITEMIC_NOTIFY_CANCEL:
		break;
	case YOUME_EVENT_SEND_MESSAGE_RESULT:
		break;
	case YOUME_EVENT_MESSAGE_NOTIFY:
		break;
	case YOUME_EVENT_SET_WHITE_USER_LIST_OK:
		break;
	case YOUME_EVENT_SET_WHITE_USER_LIST_FAILED:
		break;
	case YOUME_EVENT_KICK_RESULT:
		break;
	case YOUME_EVENT_KICK_NOTIFY:
		break;
	case YOUME_EVENT_FAREND_VOICE_LEVEL:
		break;
	case YOUME_EVENT_OTHERS_BE_KICKED:
		break;
	case YOUME_EVENT_SPEAK_RECORD_ON:
		break;
	case YOUME_EVENT_SPEAK_RECORD_OFF:
		break;
	case YOUME_EVENT_SPEAK_RECORD_RESET:
		break;
	case YOUME_EVENT_EFFECT_PLAY_COMPLETE:
		break;
	case YOUME_EVENT_SWITCH_OUTPUT:
		break;
	case YOUME_EVENT_CHECK_DEVICE_MUTE_RESULT:
		break;
	case YOUME_EVENT_EOF:
		break;
	default:
		break;
	}
}

void FYouMeTalkCallback::onRequestRestAPI(int requestID, const YouMeErrorCode & iErrorCode, const char * strQuery, const char * strResult)
{
}

void FYouMeTalkCallback::onMemberChange(const char * channel, const char * listMemberChange, bool bUpdate)
{
	if (YimObserver == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("YimObserver is nullptr, please bind a valid observer"));
		return;
	}

	bool bIsImplemented = IsImplementFunc(YimObserver, FName(TEXT("OnMemberChange")));

	if (bIsImplemented == true)
	{
		UObject* tmpObt = YimObserver;
		FString channel_fs = channel;

		FString listMemberChange_fs = UTF8_TO_TCHAR(listMemberChange);

		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<TCHAR>::Create(listMemberChange_fs);
		TSharedPtr<FJsonObject> JsonObject;
		FJsonSerializer::Deserialize(JsonReader, JsonObject);
		TArray<TSharedPtr<FJsonValue>> data = JsonObject->GetArrayField("memchange");

		FString channelID = JsonObject->GetStringField("channelid");
		
		FChannelMemberState channelMemberState;
		TArray<FChannelMemberState> channelMemberStates;

		for (int i = 0; i < data.Num(); i++)
		{
			FString isJoin = data[i]->AsObject()->GetStringField("isJoin");
			if (isJoin == "true")
			{
				channelMemberState.bisJoin = true;
			}else if (isJoin == "false")
			{
				channelMemberState.bisJoin = false;
			}
			channelMemberState.userID = data[i]->AsObject()->GetStringField("userid");
			channelMemberStates.Add(channelMemberState);
		}
		FString type = JsonObject->GetStringField("type");

		TMap<FString, FString> listMemberChangeMap;
		listMemberChangeMap.Add(TEXT("channelid"), channelID);
		listMemberChangeMap.Add(TEXT("type"), type);

		AsyncTask(ENamedThreads::GameThread, [tmpObt, channel_fs, listMemberChangeMap, channelMemberStates, bUpdate] {
			if (tmpObt != nullptr) {
				IYouMeTalkObserver::Execute_OnMemberChange(tmpObt, channel_fs, listMemberChangeMap, channelMemberStates, bUpdate);
			}
		});
	}
}

void FYouMeTalkCallback::onPcmDataRemote(int channelNum, int samplingRateHz, int bytesPerSample, void * data, int dataSizeInByte)
{
}

void FYouMeTalkCallback::onPcmDataRecord(int channelNum, int samplingRateHz, int bytesPerSample, void * data, int dataSizeInByte)
{
}

void FYouMeTalkCallback::onPcmDataMix(int channelNum, int samplingRateHz, int bytesPerSample, void * data, int dataSizeInByte)
{
}
