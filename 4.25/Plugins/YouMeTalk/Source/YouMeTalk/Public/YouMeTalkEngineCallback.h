// Copyright © 2014-2021 YouMe. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IYouMeEventCallback.h"
#include "YouMeConstDefine.h"
#include "YouMeTalkObserver.h"

class FYouMeTalkCallback : public IYouMeEventCallback, public IRestApiCallback, public IYouMeMemberChangeCallback, public IYouMePcmCallback {
public:
	static FYouMeTalkCallback* GetInstance();

	static void Destroy();

	void BindObserver(TScriptInterface<IYouMeTalkObserver> Listener);

	void UnbindObserver();

private:
	static FYouMeTalkCallback* YimWork;

	UObject* YimObserver;

public:

	virtual void onEvent(const YouMeEvent event, const YouMeErrorCode error, const char * channel, const char * param) override;

	virtual void onRequestRestAPI(int requestID, const YouMeErrorCode &iErrorCode, const char* strQuery, const char*  strResult) override;

	virtual void onMemberChange(const char* channel, const char* listMemberChange, bool bUpdate) override;

	virtual void onPcmDataRemote(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte) override;

	virtual void onPcmDataRecord(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte) override;

	virtual void onPcmDataMix(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte) override;
};