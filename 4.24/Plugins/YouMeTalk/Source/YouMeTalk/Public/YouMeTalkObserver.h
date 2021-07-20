// Copyright © 2014-2021 YouMe. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IYouMeEventCallback.h"
#include "YouMeTalkDefine.h"
#include "YouMeTalkObserver.generated.h"

USTRUCT(BlueprintType)
struct FChannelMemberState
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
		bool bisJoin;

	UPROPERTY(BlueprintReadOnly)
		FString userID;

};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UYouMeTalkObserver : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class YOUMETALK_API IYouMeTalkObserver
{
	GENERATED_BODY()

public:
	/**
	*  funcDesc: event callback
	*  @param  event: callback event type
	*  @param  error: YOUME_SUCCESS - Success
					  Other - Specific error code
	*  @param  channel: call channel
	*  @param  param: other param
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "YouMeTalkAPI")
		void OnEvent(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param);
	virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "YouMeTalkAPI")
		void OnMemberChange(const FString& channel, const TMap<FString, FString>& listMemberChangeMap, const TArray<FChannelMemberState>& channelMemberStates, bool bUpdate);
	virtual void OnMemberChange_Implementation(const FString& channel, const TMap<FString, FString>& listMemberChangeMap, const TArray<FChannelMemberState>& channelMemberStates, bool bUpdate) {};
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

};
