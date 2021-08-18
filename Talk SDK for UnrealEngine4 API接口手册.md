# Talk SDK for UnrealEngine4 API接口手册

## 相关异步/同步处理方法介绍

***

游密语音引擎SDK for UnrealEngine4提供了C++和蓝图接口，接口调用都会立即返回，凡是本身需要较长耗时的接口调用都会采用异步回调的方式，所有接口都可以在主线程中直接使用。回调在主线程。

## API调用说明

***

API使用的基本流程：（初始化 -> 收到初始化成功回调通知 -> 加入语言频道 -> 收到加入频道成功回调通知 -> 使用其他接口 -> 离开语音频道 -> 反初始化），要确保严格按照上述的顺序使用接口。

## 实现回调

****

使用者首先要继承IYouMeTalkObserver类，绑定回调对象，具体蓝图和C++的操作如下：

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Bind observer in callback
  *  @param  Observer: YouMeTalkObserver interface
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
  	static void BindObserver(TScriptInterface<IYouMeTalkObserver> Observer);
  ```

- ### 功能

  用于绑定监听回调的对象。

- ### 参数说明

  `Observer`：继承 **IYouMeTalkObserver** 的类。

- ### 蓝图用法

  1. 在蓝图的 **ClassSettings** 选项中继承 **YouMeTalkObserver** 接口，如下图所示：

     ![image-20210706143937430](/Images/image_6.png)

     

     ![image-20210706143824326](/Images/image_7.png)

  2. 在蓝图中调用 **BindObserver** 蓝图节点，如下图所示：

![image-20210706144238413](/Images/image_8.png)

- ### C++用法

  1. 继承回调接口 **IYouMeTalkObserver**，注意引入头文件。

     ![image-20210707154001415](/Images/image_9.png)

  2. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  3. 调用 **BindObserver** 接口。

     ```c++
     UYouMeTalkAPI::BindObserver(this);
     ```

- 绑定回调监听时，只允许一个对象进行监听。

## 回调监听

***

- ### 接口定义

  ```C++
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
  ```

- ### 功能

  回调监听事件，用于监听后续TalkSDK操作的相关回调。

- ### 参数说明

  - `event`：回调的事件类型。
  - `error`：回调的错误码
  - `channel`：回调的频道
  - `param`：其他参数

- ### 蓝图用法

  在继承 **YouMeTalkObserver** 接口的蓝图中，调用 **EventOnEvent** 蓝图节点。

![image-20210706145856668](/Images/image_10.png)

- ### C++用法

  在继承回调接口 **IYouMeTalkObserver** 的类中，实现 **回调事件OnEvent虚函数**。

  ```C++
  virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
  ```

  注：如果在C++中实现了回调事件虚函数，就不要在蓝图中再实现一次。否则会覆盖C++的回调，导致C++接收不到回调。

- 完成上述回调事件绑定，即可在后续的API调用中，实现API相关回调。


## 移除监听

***

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Unbind observer in callback
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
  	static void UnbindObserver();
  ```

- ### 功能

  解绑监听对象。

- ### 蓝图用法

  在绑定监听的蓝图中调用 **UnbindObserver** 蓝图节点，进行解绑，如下图所示：

![image-20210706151016776](/Images/image_11.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **UnbindObserver** 接口。

     ```c++
     UYouMeTalkAPI::UnbindObserver();
     ```

## 初始化

***

- ### 接口定义

  ```C++
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
  ```

- ### 功能

  初始化语音引擎，做APP验证和资源初始化。（只有appkey,appsecret,serverRegionId 都一样时,才可以进行语音互通,改任意一个视为另外一个区服）。

- ### 参数说明

  - `strAPPKey`：从游密后台申请到的 app key, 这个是你们应用程序的唯一标识。 

  - `strAPPSecret`：对应 strAPPKey 的私钥, 这个需要妥善保存，不要暴露给其他人。 

  - `serverRegionId`：设置首选连接服务器的区域码，如果在初始化时不能确定区域，可以填RTC_CN_SERVER，后面确定时通过 SetServerRegion 设置。如果YOUME_RTC_SERVER_REGION定义的区域码不能满足要求，可以把这个参数设为 RTC_EXT_SERVER，然后通过后面的参数strExtServerRegionName 设置一个自定的区域值（如中国用 "cn" 或者 “ch"表示），然后把这个自定义的区域值同步给游密，我们将通过后台配置映射到最佳区域的服务器。

  - `strExtServerRegionName`：自定义的扩展的服务器区域名。不能为null，可为空字符串“”。只有前一个参数serverRegionId设为RTC_EXT_SERVER时，此参数才有效（否则都将当空字符串“”处理）。

- ### 返回值 

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **Init** 蓝图节点。

![image-20210813104256676](/Images/image_12.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **Init** 接口。

     ```C++
     FString strAppKey = "";
     FString strAPPSecret = "";
     EYouMeRTCServerRegion youMeRTCServerRegion = EYouMeRTCServerRegion::RTC_CN_SERVER;
     FString strExtServerRegionName = "";
     UYouMeTalkAPI::Init(strAppKey, strAPPSecret, youMeRTCServerRegion, strExtServerRegionName);
     ```

- ### 异步回调

  蓝图回调：

  ![image-20210812172632285](/Images/image_29.png)

  

  C++回调：

  ```C++
  //涉及到的主要回调事件有：
  // YOUME_EVENT_INIT_OK  - 表明初始化成功
  // YOUME_EVENT_INIT_FAILED - 表明初始化失败，最常见的失败原因是网络错误或者 AppKey-AppSecret 错误
  virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
  ```


## 语音频道管理

***

### 加入语音频道（单频道）

- ### 接口定义

  ```C++
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
  ```

- ### 功能

  加入语音频道（单频道模式，每个时刻只能在一个语音频道里面）。

- ### 参数说明

  - `strUserID`：全局唯一的用户标识，全局指在当前应用程序的范围内。

  - `strChannelID`：全局唯一的频道标识，全局指在当前应用程序的范围内。 

  - `userRole`：用户在语音频道里面的角色，见YouMeUserRole定义。 

  - `bCheckRoomExist`：是否检查频道存在时才加入，默认为false: true 当频道存在时加入、不存在时返回错误（多用于观众角色），false 无论频道是否存在都加入频道。

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **JoinChannelSingleMode** 蓝图节点。

![image-20210706161445437](/Images/image_14.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **JoinChannelSingleMode** 接口。

     ```C++
     FString strUserID = "";
     FString strChannelID = "";
     EYouMeUserRole userRol = EYouMeUserRole::YOUME_USER_HOST;
     bool bCheckRoomExis = true;
     UYouMeTalkAPI::JoinChannelSingleMode(strUserID, strChannelID, userRol, bCheckRoomExis);
     ```

- ### 异步回调

  蓝图回调：

  ![image-20210812174751162](/Images/image_31.png)

  

  C++回调：

  ```C++
  //涉及到的主要回调事件有：
  //YOUME_EVENT_JOIN_OK - 成功进入语音频道
  //YOUME_EVENT_JOIN_FAILED - 进入语音频道失败，可能原因是网络或服务器有问题，或是bCheckRoomExist为true时频道还未创建
  virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
  ```

### 加入语音频道（多频道）

- ### 接口定义

  ```C++
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
  		static EYouMeErrorCode JoinChannelMultiMode(const FString strUserID, EYouMeUserRole eUserRole, const FString strChannelID, bool bCheckRoomExist);
  ```

- ### 功能

  加入语音频道（单频道模式，每个时刻只能在一个语音频道里面）。

- ### 参数说明

  - `strUserID`：全局唯一的用户标识，全局指在当前应用程序的范围内。

  - `strChannelID`：全局唯一的频道标识，全局指在当前应用程序的范围内。 

  - `userRole`：用户角色，用于决定讲话/播放背景音乐等权限。 

  - `bCheckRoomExist`：是否检查频道存在时才加入，默认为false: true 当频道存在时加入、不存在时返回错误（多用于观众角色），false 无论频道是否存在都加入频道。

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **JoinChannelMultiMode** 蓝图节点。

![image-20210812174228945](/Images/image_30.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **JoinChannelSingleMode** 接口。

     ```C++
     FString strUserID = "";
     FString strChannelID = "";
     EYouMeUserRole userRol = EYouMeUserRole::YOUME_USER_HOST;
     bool bCheckRoomExis = true;UYouMeTalkAPI::JoinChannelMultiMode(strUserID, userRol, strChannelID, bCheckRoomExis);
     ```

- ### 异步回调

  蓝图回调：

  ![image-20210812174751162](/Images/image_31.png)

  

  C++回调：

  ```C++
  //涉及到的主要回调事件有：
  //YOUME_EVENT_JOIN_OK - 成功进入语音频道
  //YOUME_EVENT_JOIN_FAILED - 进入语音频道失败，可能原因是网络或服务器有问题，或是bCheckRoomExist为true时频道还未创建
  virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
  ```

### 指定讲话频道

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Speak to the designated channel
  *  @param  strChannelID: Channel ID, to ensure global uniqueness
  *  @return YOUME_SUCCESS - Success
  *          Other - Specific error code
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static EYouMeErrorCode SpeakToChannel(const FString strChannelID);
  ```

- ### 功能

  多频道模式下，指定当前要讲话的频道。

- ### 参数说明

  - `strChannelID`：全局唯一的频道标识，全局指在当前应用程序的范围内。 

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **SpeakToChannel** 蓝图节点。

![image-20210813103415443](/Images/image_32.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SpeakToChannel** 接口。

     ```C++
     FString strChannelID = "";
     UYouMeTalkAPI::SpeakToChannel(strChannelID);
     ```

- ### 异步回调

  蓝图回调：

  ![image-20210813105230089](/Images/image_33.png)

  

  C++回调：

  ```C++
  //涉及到的主要回调事件有：
  //YOUME_EVENT_SPEAK_SUCCESS - 成功切入到指定语音频道
  //YOUME_EVENT_SPEAK_FAILED - 切入指定语音频道失败，可能原因是网络或服务器有问题
  virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
  ```


### 退出指定的语音频道

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Exit a voice channel in multi-channel mode
  *  @param  strChannelID: Channel ID, to ensure global uniqueness
  *  @return YOUME_SUCCESS - Success
  *          Other - Specific error code
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static EYouMeErrorCode LeaveChannelMultiMode(const FString strChannelID);
  ```

- ### 功能

  多频道模式下，退出指定的语音频道。

- ### 参数说明

  - `strChannelID`：全局唯一的频道标识，全局指在当前应用程序的范围内。 

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **LeaveChannelMultiMode** 蓝图节点。

![image-20210813105734972](/Images/image_34.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SpeakToChannel** 接口。

     ```C++
     FString strChannelID = "";
     UYouMeTalkAPI::LeaveChannelMultiMode(strChannelID);
     ```

- ### 异步回调

  蓝图回调：

  ![image-20210813105921626](/Images/image_35.png)

  

  C++回调：

  ```C++
  //涉及到的主要回调事件有：
  //YOUME_EVENT_LEAVED_ONE - 成功退出指定语音频道
  virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
  ```


### 退出所有语音频道

- ### 接口定义

```C++
/**
*  funcDesc: Exit all voice channels
*  @return YOUME_SUCCESS - Success
*          Other - Specific error code
*/
UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
    static EYouMeErrorCode LeaveChannelAll();
```

- ### 功能

  退出所有的语音频道（单频道模式下直接调用此函数离开频道即可）。

- ### 参数说明

  - `strChannelID`：全局唯一的频道标识，全局指在当前应用程序的范围内。

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **LeaveChannelAll** 蓝图节点。

![image-20210706163317849](/Images/image_15.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```c++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **LeaveChannelAll** 接口。

     ```C++
     UYouMeTalkAPI::LeaveChannelAll();
     ```

- ### 异步回调

  蓝图回调：

  ![image-20210813110605947](/Images/image_36.png)

  

  C++回调：

  ```C++
  //涉及到的主要回调事件有：
  //YOUME_EVENT_LEAVED_ALL - 成功退出所有语音频道
  virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
  ```

### 设置白名单用户

- ### 接口定义


```C++
/**
*  funcDesc: Set whitelist users for channels
*  @param strChannelID: Channel to set
*  @param vecWhiteUserList: White list user list
*  @return YOUME_SUCCESS - Success
*          Other - Specific error code
*/
UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
	static EYouMeErrorCode SetWhiteUserList(const FString strChannelID, const FString vecWhiteUserList);
```

- ### 功能

  设置当前用户的语音消息接收白名单，其语音消息只会转发到白名单的用户，不设置该接口则默认转发至频道内所有人。

- ### 参数说明

  - `strChannelID`：要设置的频道(兼容多频道模式，单频道模式下传入当前频道即可)。 
  - `strWhiteUserList`：白名单用户列表, 以|分隔，如：User1|User2|User3；表示语音消息只发送到User1,User2,User3. "all"表示转发至频道内所有人；""（空字符串）表示不转发至任何用户。

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **SetWhiteUserList** 蓝图节点。

![image-20210706164212503](/Images/image_16.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetWhiteUserList** 接口。

     ```C++
     FString strChannelID = "";
     FString vecWhiteUserList = "";
     UYouMeTalkAPI::SetWhiteUserList(strChannelID, vecWhiteUserList);
     ```

- ### 异步回调

  蓝图回调：

  ![image-20210813111624602](/Images/image_37.png)

  ![image-20210813111548846](/Images/image_38.png)

  

  C++回调：

  ```C++
  //涉及到的主要回调事件有：
  //YOUME_EVENT_SET_WHITE_USER_LIST_OK - 成功在指定语音频道设置白名单，有异常用户会返回错误码YOUME_ERROR_WHITE_SOMEUSER_ABNORMAL
  //YOUME_EVENT_SET_WHITE_USER_LIST_FAILED - 在指定语音频道设置白名单失败，可能原因是网络或服务器有问题
  virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
  ```

## 设备状态管理

***

### 切换语音输出设备

- ### 接口定义

```C++
/**
*  funcDesc: Switching voice output devices
*  @param bOutputToSpeaker: True -- use the speaker, false -- use the receiver
*  @return YOUME_SUCCESS - Success
*          Other - Specific error code
*/
UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
    static EYouMeErrorCode SetOutputToSpeaker(bool bOutputToSpeaker);
```

- ### 功能

  默认输出到扬声器，在加入房间成功后设置（iOS受系统限制，如果已释放麦克风则无法切换到听筒）

- ### 参数说明

  - `bOutputToSpeaker`：true——输出到扬声器，false——输出到听筒。

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **SetOutputToSpeaker** 蓝图节点。

![image-20210813113754397](/Images/image_39.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetOutputToSpeaker** 接口。

     ```C++
     bool bOutputToSpeaker = true;
     UYouMeTalkAPI::SetOutputToSpeaker(bOutputToSpeaker);
     ```

### 设置扬声器状态

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Mute speakers
  *  @param mute: True -- mute, false -- unmute
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static void SetSpeakerMute(bool mute);
  ```

- ### 功能

  打开/关闭扬声器，该状态值在加入房间成功后设置才有效。（该接口是异步接口,调用后会有一段时间生效）

- ### 参数说明

  `mute`：true——关闭扬声器，false——开启扬声器。

- ### 蓝图用法

  ![image-20210706175311140](/Images/image_17.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```c++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetSpeakerMute** 接口。

     ```c++
     bool mute = true;UYouMeTalkAPI::SetSpeakerMute(mute);
     ```

- ### 异步回调

  蓝图回调：

  ![image-20210813111624602](/Images/image_37.png)

  ![image-20210818174159793](E:\Work\YouMeTalkSDK_UE4\Images\image_72.png)

  C++回调：

  ```
  //涉及到的主要回调事件有：
  //YOUME_EVENT_LOCAL_SPEAKER_ON - 自己扬声器打开
  //YOUME_EVENT_LOCAL_SPEAKER_OFF - 自己扬声器关闭
  virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
  ```

### 获取扬声器状态

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Get speaker mute status
  *  @return True -- mute, false -- unmute
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static bool GetSpeakerMute();
  ```

- ### 功能

  获取当前扬声器状态。（该接口为异步接口,尽量避免逻辑上设置了扬声器状态后立刻调用该接口）

- ### 返回值

  true——扬声器关闭，false——扬声器开启。

- ### 蓝图用法

  ![image-20210813114342420](/Images/image_40.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```c++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **GetSpeakerMute** 接口。

     ```c++
     bool bSpeakerMute = UYouMeTalkAPI::GetSpeakerMute();
     ```


### 设置麦克风状态

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Mute microphone
  *  @param mute: True -- mute, false -- unmute
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static void SetMicrophoneMute(bool mute);
  ```

- ### 功能

  打开／关闭麦克风，该状态值在加入房间成功后设置才有效。（该接口是异步接口,调用后会有一段时间生效）

- ### 参数说明

  `mute`：true——关闭麦克风，false——开启麦克风。

- ### 蓝图用法

  ![image-20210813114738223](/Images/image_41.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```c++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetMicrophoneMute** 接口。

     ```c++
     bool mute = true;UYouMeTalkAPI::SetMicrophoneMute(mute);
     ```

- ### 异步回调

  蓝图回调：

  ![image-20210813111624602](/Images/image_37.png)

  ![image-20210818174521412](E:\Work\YouMeTalkSDK_UE4\Images\image_73.png)

  C++回调：

  ```
  //涉及到的主要回调事件有：
  //YOUME_EVENT_LOCAL_MIC_ON - 自己麦克风打开
  //YOUME_EVENT_LOCAL_MIC_OFF - 自己麦克风关闭
  virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
  ```

### 获取麦克风状态

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Get microphone mute status
  *  @return True -- mute, false -- unmute
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static bool GetMicrophoneMute();
  ```

- ### 功能

  获取当前麦克风状态。（该接口为异步接口,尽量避免逻辑上设置了扬声器状态后立刻调用该接口）

- ### 返回值

  true——麦克风关闭，false——麦克风开启。

- ### 蓝图用法

  ![image-20210813114939831](/Images/image_42.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```c++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **GetMicrophoneMute** 接口。

     ```c++
     bool bMicrophoneMute = UYouMeTalkAPI::GetMicrophoneMute();
     ```


### 设置是否通知别人麦克风和扬声器的开关

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Set whether to notify others of the status of their own on-off microphones and speakers
  *  @param bAutoSend: True -- notify, false -- not notify
  *  @return YOUME_SUCCESS - Success
  *          Other - Specific error code
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static void SetAutoSendStatus(bool bAutoSend);
  ```

- ### 功能

  设置是否通知别人,自己麦克风和扬声器的开关状态（建议进入频道后调用，设置后，其他当前在同一个频道的用户可以获取该用户的麦克风和扬声器的开关状态。 对应回调事件YouMeEvent.YOUME_EVENT_OTHERS_MIC_ON，YouMeEvent.YOUME_EVENT_OTHERS_MIC_OFF，YouMeEvent.YOUME_EVENT_OTHERS_SPEAKER_ON，YouMeEvent.YOUME_EVENT_OTHERS_SPEAKER_OFF）

- ### 蓝图用法

  ![image-20210813115257933](/Images/image_43.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```c++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetAutoSendStatus** 接口。

     ```c++
     UYouMeTalkAPI::SetAutoSendStatus();
     ```


### 设置音量

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Increase the volume by 1
  *  @param uiVolume: volume
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
  	static void SetVolume(const int32 &uiVolume);
  ```

- ### 功能

  设置当前程序输出音量大小。建议该状态值在加入房间成功后按需再重置一次。

- ### 参数说明

  `uiVolume`:当前音量大小，范围[0-100]。

- ### 蓝图用法

  在蓝图中调用 **SetVolume** 蓝图节点。

  ![image-20210706180112430](/Images/image_19.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```c++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetVolume** 接口。

     ```C++
     int32 uiVolume = 50;
     UYouMeTalkAPI::SetVolume(uiVolume);
     ```

### 获取音量

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Get the volume value, which is the volume inside the program, and multiply it with the system volume to get the actual volume used by the program
  *  @return Volume value [0-100]
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static int32 GetVolume();
  ```

- ### 功能

  获取当前程序输出音量大小。

- ### 返回值

  `Value`：当前音量大小，范围[0-100]。

- ### 蓝图用法

  在蓝图中调用 **GetVolume** 蓝图节点。

  ![image-20210706180551024](/Images/image_20.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **GetVolume** 接口。

     ```C++
     UYouMeTalkAPI::GetVolume();
     ```


## 设置通话

***

### 设置是否允许使用移动网络

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Enable / disable mobile network
  *  @param bEnabled: True - can be enabled, false - disabled, disabled by default
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
  	static void SetUseMobileNetworkEnabled(bool bEnabled);
  ```

- ### 功能

  设置是否允许使用移动网络。在WIFI和移动网络都可用的情况下会优先使用WIFI，在没有WIFI的情况下，如果设置允许使用移动网络，那么会使用移动网络进行语音通信，否则通信会失败。

- ### 参数说明

  `bEnabled`:true——允许使用移动网络，false——禁止使用移动网络。

- ### 蓝图用法

  在蓝图中调用 **SetUseMobileNetworkEnabled** 蓝图节点。

  ![image-20210813115857548](/Images/image_44.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **GetVolume** 接口。

     ```C++
     bool bEnabled = true;
     UYouMeTalkAPI::SetUseMobileNetworkEnabled(bEnabled);
     ```

### 获取是否允许使用移动网络

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Is mobile network available
  *  @return True - available, false disabled
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static bool GetUseMobileNetworkEnabled();
  ```

- ### 功能

  获取是否允许SDK在没有WIFI的情况使用移动网络进行语音通信。

- ### 返回值

  true——允许使用移动网络，false——禁止使用移动网络，默认情况下允许使用移动网络。

- ### 蓝图用法

  在蓝图中调用 **GetUseMobileNetworkEnabled** 蓝图节点。

  ![image-20210813120141479](/Images/image_45.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **GetVolume** 接口。

     ```C++
     bool bUseMobileNetworkEnabled = UYouMeTalkAPI::GetUseMobileNetworkEnabled();
     ```

## 控制他人麦克风

***

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Control other people's microphone switch
  *  @param pUserID: The user ID must be globally unique
  *  @param mute: True - can be enabled, false - disabled, disabled by default
  *  @return True - available, false disabled
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static EYouMeErrorCode SetOtherMicMute(const FString pUserID, bool mute);
  ```

- ### 功能

  控制他人的麦克风状态（也就是关闭或者开启他人的麦克风）

- ### 参数说明

  `pUserID`：要控制的用户ID `mute`：是否静音。true:静音别人的扬声器，false：开启别人的扬声器

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **SetOtherMicMute** 蓝图节点。

  ![image-20210813144502145](/Images/image_48.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetOtherMicMute** 接口。

     ```c++
     FString pUserID = " ";
     bool bOtherMicMute = true;
     UYouMeTalkAPI::SetOtherMicMute(pUserID, bOtherMicMute);
     ```

## 控制他人扬声器

***

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Control other people's microphone switch
  *  @param pUserID: The user ID must be globally unique
  *  @param mute: True to mute the other party's microphone, false to unmute the other party's microphone
  *  @return YOUME_SUCCESS - Success
  *          Other - Specific error code
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static EYouMeErrorCode SetOtherSpeakerMute(const FString pUserID, bool mute);
  ```

- ### 功能

  控制他人的扬声器状态（也就是关闭或者开启他人的扬声器）

- ### 参数说明

  `pUserID`：要控制的用户ID `mute`：是否静音。true:静音别人的扬声器，false：开启别人的扬声器

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **SetOtherSpeakerMute** 蓝图节点。

  ![image-20210813150343954](/Images/image_49.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetOtherSpeakerMute** 接口。

     ```c++
     FString pUserID = " ";
     bool bOtherMicMute = true;
     UYouMeTalkAPI::SetOtherSpeakerMute(pUserID, bOtherMicMute);
     ```

## 设置是否听某人的语音

***

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Choose to eliminate other people's voice
  *  @param userID: The user ID must be globally unique
  *  @param on: False to block the other party's voice, true to cancel the blocking
  *  @return YOUME_SUCCESS - Success
  *          Other - Specific error code
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static EYouMeErrorCode SetListenOtherVoice(const FString userID, bool on);
  ```

- ### 功能

  设置是否听某人的语音。

- ### 参数说明

  `userID`：要控制的用户ID。 `on`：true表示开启接收指定用户的语音，false表示屏蔽指定用户的语音。

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **SetListenOtherVoice** 蓝图节点。

  ![image-20210813151201121](/Images/image_69.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetListenOtherVoice** 接口。

     ```c++
     FString userID = " ";
     bool bOn = true;
     UYouMeTalkAPI::SetListenOtherVoice(userID, bOn);
     ```

## 设置当麦克风静音时，是否释放麦克风设备

***

- ### 接口定义

  ```C++
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
  ```

- ### 功能

  设置当麦克风静音时，是否释放麦克风设备（需要在初始化成功后，加入房间之前调用）

- ### 参数说明

  `enabled`： true--当麦克风静音时，释放麦克风设备，此时允许第三方模块使用麦克风设备录音。在Android和iOS上，语音由通话音轨切换到媒体音轨，回归到双声道高音质输出体验（如果媒体音量和通话音量不同时切换会产生音量变大变小的感觉）；false--不管麦克风是否静音，麦克风设备都会被占用。

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **SetReleaseMicWhenMute** 蓝图节点。

  ![image-20210813150757060](/Images/image_50.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetReleaseMicWhenMute** 接口。

     ```c++
     bool bReleaseMicWhenMute = true;
     UYouMeTalkAPI::SetReleaseMicWhenMute(bReleaseMicWhenMute);
     ```

## 设置插入耳机时，是否自动退出系统通话模式(禁用手机系统硬件信号前处理)

***

- ### 接口定义

  ```C++
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
  ```

- ### 功能

  设置插入耳机时，是否自动退出系统通话模式(禁用手机系统硬件信号前处理) 系统提供的前处理效果包括回声消除、自动增益等，有助于抑制背景音乐等回声噪音，减少系统资源消耗，对Windows系统无效 由于插入耳机可从物理上阻断回声产生，故可设置禁用该效果以保留背景音乐的原生音质效果 默认为false，在初始化之后、加入房间之前调用

- ### 参数说明

  `enabled`： true--当插入耳机时，自动禁用系统硬件信号前处理，拔出时还原；false--插拔耳机不做处理。

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **SetExitCommModeWhenHeadsetPlugin** 蓝图节点。

  ![image-20210813151548943](/Images/image_51.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetExitCommModeWhenHeadsetPlugin** 接口。

     ```c++
     bool bEnabled = true;
     UYouMeTalkAPI::SetExitCommModeWhenHeadsetPlugin(bEnabled);
     ```

## 快速同步的临时释放麦克风

***

- ### 接口定义

  ```C++
  /**
  *  funcDesc: After the call, the microphone release is completed synchronously, only to switch the microphone usage right when using IM recording interface.
  *  @return bool - true Success
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static bool ReleaseMicSync();
  ```

- ### 功能

  调用后同步完成麦克风释放，只是为了方便使用 IM 的录音接口时，临时切换麦克风使用权。

- ### 返回值

  返回true，表示释放成功，可以认为只要在占用麦克风的状态肯定能释放成功。

- ### 蓝图用法

  在蓝图中调用 **ReleaseMicSync** 蓝图节点。

  ![image-20210813152042968](/Images/image_52.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **ReleaseMicSync** 接口。

     ```c++
     UYouMeTalkAPI::ReleaseMicSync(pUserID, bOtherMicMute);
     ```

## 快速同步恢复麦克风录音状态

***

- ### 接口定义

  ```C++
  /**
  *  funcDesc: After calling, restore the microphone to the state before releasing, just for the convenience of switching the right to use the microphone when using the im recording interface.
  *  @return bool - true Success
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static bool ResumeMicSync();
  ```

- ### 功能

  调用后恢复麦克风到释放前的状态，只是为了方便使用 IM 的录音接口时，临时切换麦克风使用权。

- ### 返回值

  返回true，表示恢复成功，可以认为只要在释放的状态，肯定可以恢复成功。

- ### 蓝图用法

  在蓝图中调用 **ResumeMicSync** 蓝图节点。

  ![image-20210813152343601](/Images/image_53.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **ReleaseMicSync** 接口。

     ```c++
     UYouMeTalkAPI::ResumeMicSync();
     ```

## 通话控制

***

### 暂停通话

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Pause the call and release the microphone and other device resources
  *  @return YOUME_SUCCESS - Success
  *          Other - Specific error code
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static EYouMeErrorCode PauseChannel();
  ```

- ### 功能

  暂停通话，释放对麦克风等设备资源的占用。当需要用第三方模块临时录音时，可调用这个接口。

- ### 参数说明

  `pUserID`：要控制的用户ID 

  `mute`：是否静音。true:静音别人的扬声器，false：开启别人的扬声器

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **PauseChannel** 蓝图节点。

  ![image-20210706181707718](/Images/image_21.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **PauseChannel** 接口。

     ```c++
     UYouMeTalkAPI::PauseChannel();
     ```

- ### 异步回调

  蓝图回调

  ![image-20210813142543318](/Images/image_46.png)

  

  C++回调

  ```C++
  //涉及到的主要回调事件有：
  //YOUME_EVENT_PAUSED - 暂停语音频道完成
  virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
  ```

### 恢复通话

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Resume call
  *  @return YOUME_SUCCESS - Success
  *          Other - Specific error code
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static EYouMeErrorCode ResumeChannel();
  ```

- ### 功能

  恢复通话，调用PauseChannel暂停通话后，可调用这个接口恢复通话。

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。

- ### 异步回调

  YOUME_EVENT_RESUMED - 恢复语音频道完成。

- ### 蓝图用法

  在蓝图中调用 **ResumeChannel** 蓝图节点。

  ![image-20210706182043884](/Images/image_22.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **ResumeChannel** 接口。

     ```c++
     UYouMeTalkAPI::ResumeChannel();
     ```

## 设置语音检测

***

- ### 接口定义

  ```c++
  /**
  *  funcDesc: Set whether to turn on voice detection callback
  *  @param enabled, true open，false close
  *  @return YOUME_SUCCESS - Success
  *          Other - Specific error code
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static EYouMeErrorCode SetVadCallbackEnabled(bool enabled);
  ```

- ### 功能

  设置是否开启语音检测回调，开启后频道内有人正在讲话与结束讲话都会发起相应回调通知。（该状态值在加入房间成功后设置才有效，并且需要频道内所有用户都设置才生效）

- ### 参数说明

  - `bEnabled`：true——打开，false——关闭。

- ### 返回值

  如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](https://youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **SetVadCallbackEnabled** 蓝图节点。

  ![image-20210813143707381](/Images/image_47.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **PlayBackgroundMusic** 接口。

     ```C++
     bool bVadCallbackEnabled = true;
     UYouMeTalkAPI::SetVadCallbackEnabled(bVadCallbackEnabled);
     ```


## 设置是否开启讲话音量回调

***

- ### 接口定义

  ```c++
  /**
  *  funcDesc: Set whether to turn on speech volume callback and set corresponding parameters
  *  @param maxLevel: The level corresponding to the maximum volume can be set to 100. According to the actual needs, setting a value less than 100 can reduce the number of callbacks.
  *  @return YOUME_SUCCESS - Success
  *          Other - Specific error code
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static EYouMeErrorCode Talk_SetMicLevelCallback(int32 maxLevel);
  ```

- ### 功能

  设置是否开启监听自己讲话音量回调, 并设置相应的参数。

- ### 参数说明

  - `maxLevel`:音量最大时对应的级别，最大可设100。根据实际需要设置小于100的值可以减少回调的次数（注意设置较高的值可能会产生大量回调，特别在Unity上会影响其它事件到达，一般建议不超过30）。比如你只在UI上呈现10级的音量变化，那就设10就可以了。设 0 表示关闭回调。

- ### 返回值

  如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](https://youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **Talk_SetMicLevelCallback** 蓝图节点。

  ![image-20210813143707381](/Images/image_47.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **Talk_SetMicLevelCallback** 接口。

     ```C++
     bool bEnabled = true;
     UYouMeTalkAPI::Talk_SetMicLevelCallback(bEnabled);
     ```


## 背景音乐

***

### 播放背景音乐

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Play background music and allow selection to blend to speaker output and microphone input
  *  @param pFilePath: Path to music files
  *  @param bRepeat: Repeat
  *  @return YOUME_SUCCESS - Success
  *          Other - Specific error code
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static EYouMeErrorCode PlayBackgroundMusic(const FString pFilePath, bool bRepeat);
  ```

- ### 功能

  播放指定的音乐文件。播放的音乐将会通过扬声器输出，并和语音混合后发送给接收方。这个功能必须进入频道传入身份为主播/指挥才能使用。

- ### 参数说明

  `pFilePath`：音乐文件的路径。 `bRepeat`：是否重复播放，true——重复播放，false——只播放一次就停止播放。

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **PlayBackgroundMusic** 蓝图节点。

  ![image-20210813153523694](/Images/image_54.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **PlayBackgroundMusic** 接口。

     ```C++
     FString pFilePath = " ";
     bool bRepeat = true;
     UYouMeTalkAPI::PlayBackgroundMusic(pFilePath, bRepeat);
     ```

- ### 异步回调

  蓝图回调

  ![image-20210813154843885](/Images/image_55.png)

  

  C++回调

  ```C++
  //涉及到的主要回调事件有：
  //YOUME_EVENT_BGM_STOPPED - 通知背景音乐播放结束
  //YOUME_EVENT_BGM_FAILED - 通知背景音乐播放失败
  virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
  ```

### 停止播放背景音乐

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Stop playing if background music is currently playing
  *  @return YOUME_SUCCESS - Success
  *          Other - Specific error code
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static EYouMeErrorCode StopBackgroundMusic();
  ```

- ### 功能

  停止播放当前正在播放的背景音乐。 这是一个同步调用接口，函数返回时，音乐播放也就停止了。

- ### 返回值

  如果成功（表明成功设置了背景音乐的音量）返回YOUME_SUCCESS，否则返回错误码，具体请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **StopBackgroundMusic** 蓝图节点。

  ![image-20210706184723391](/Images/image_24.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **StopBackgroundMusic** 接口。

     ```
     UYouMeTalkAPI::StopBackgroundMusic();
     ```


### 设置背景音乐播放音量

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Set the volume of background music
  *  @param vol: Background music volume, range 0-100
  *  @return YOUME_SUCCESS - Success
  *          Other - Specific error code
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
  	static EYouMeErrorCode SetBackgroundMusicVolume(int32 vol);
  ```

- ### 功能

  设定背景音乐的音量。这个接口用于调整背景音乐和语音之间的相对音量，使得背景音乐和语音混合听起来协调。 这是一个同步调用接口。

- ### 参数说明

  `vol`:背景音乐的音量，范围 [0-100]。

- ### 返回值

  如果成功（表明成功设置了背景音乐的音量）返回YOUME_SUCCESS，否则返回错误码，具体请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **SetBackgroundMusicVolume** 蓝图节点。

  ![image-20210706185529784](/Images/image_25.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetBackgroundMusicVolume** 接口。

     ```C++
     int32 vol = 50;
     UYouMeTalkAPI::SetBackgroundMusicVolume(vol);
     ```


## 设置监听

***

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Set whether to listen to your own voice or background music
  *  @param micEnabled: Do you want to monitor the microphone? True monitor, false do not monitor
  *  @param bgmEnabled: Do you want to monitor background music? True monitor, false do not monitor
  *  @return YOUME_SUCCESS - Success
  *          Other - Specific error code
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static EYouMeErrorCode SetHeadsetMonitorOn(bool micEnabled, bool bgmEnabled = true);
  ```

- ### 功能

  设置是否用耳机监听自己的声音或背景音乐，当不插耳机时，这个设置不起作用 这是一个同步调用接口。

- ### 参数说明

  `micEnabled`:是否监听麦克风 true 监听，false 不监听。 

  `bgmEnabled`:是否监听背景音乐 true 监听，false 不监听。

- ### 返回值

  如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](https://youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **SetHeadsetMonitorOn** 蓝图节点。

  ![image-20210813155327007](/Images/image_56.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetBackgroundMusicVolume** 接口。

     ```C++
     bool bMicEnabled = false;
     bool bBgmEnabled = false;
     UYouMeTalkAPI::SetHeadsetMonitorOn(bMicEnabled, bBgmEnabled);
     ```


## 获取变声音调

***

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Get voice changing tone (value-added service, need background configuration to start)
  *  @return vol: Tone of variation, range is -12-12, 0 is original sound, and the higher the value is, the higher the pitch is
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static float GetSoundtouchPitchSemiTones();
  ```

- ### 功能

  获取变声音调（增值服务，需要后台配置开启）

- ### 返回值

  当前变声音调的值，范围[-12 ~ +12]。

- ### 蓝图用法

  在蓝图中调用 **GetSoundtouchPitchSemiTones** 蓝图节点。

  ![image-20210813155725396](/Images/image_57.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **GetSoundtouchPitchSemiTones** 接口。

     ```C++
     UYouMeTalkAPI::GetSoundtouchPitchSemiTones();
     ```




## 设置变声音调

***

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Set the tone change (value-added service, need to be enabled by background configuration), reset to 0 when you exit the room
  *  @param fPitchSemiTones: The range is - 12 ~ 12. 0 is the original tone. The higher the value is, the higher the tone is
  *  @return YOUME_SUCCESS - Success
  *          Other - Specific error code
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static EYouMeErrorCode SetSoundtouchPitchSemiTones(float fPitchSemiTones);
  ```

- ### 功能

  设置变声音调（增值服务，需要后台配置开启），需在进入房间成功后调用，仅对当前房间有效，退出房间时重置为0

- ### 	参数说明

  `fPitchSemiTones`:变声音调的值，范围[-12 ~ +12]。

- ### 返回值

  如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](https://youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **SetSoundtouchPitchSemiTones** 蓝图节点。

  ![image-20210813155936408](/Images/image_58.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetSoundtouchPitchSemiTones** 接口。

     ```C++
     float fPitchSemiTones = 0;
     UYouMeTalkAPI::SetSoundtouchPitchSemiTones(fPitchSemiTones);
     ```




## 设置混响音效

***

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Set whether to turn on the host reverb mode
  *  @param enabled: True on, false off
  *  @return YOUME_SUCCESS - Success
  *          Other - Specific error code
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static EYouMeErrorCode SetReverbEnabled(bool enabled);
  ```

- ### 功能

  设置是否开启混响音效，这个主要对主播/指挥有用。

- ### 	参数说明

  `bEnabled`:true——打开，false——关闭。

- ### 返回值

  如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](https://youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **SetReverbEnabled** 蓝图节点。

  ![image-20210813160448447](/Images/image_59.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetReverbEnabled** 接口。

     ```C++
     bool bEnabled = false;
     UYouMeTalkAPI::SetReverbEnabled(bEnabled);
     ```



## 设置时间戳

***

### 设置录音时间戳

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Set the timestamp of the current recording
  *  @param timeMs: timestamp 
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static void SetRecordingTimeMs(int32 timeMs);
  ```

- ### 功能

  设置当前录音的时间戳。当通过录游戏脚本进行直播时，要保证观众端音画同步，在主播端需要进行时间对齐。 这个接口设置的就是当前游戏画面录制已经进行到哪个时间点了。

- ### 	参数说明

  `timeMs`:当前游戏画面播放对应的时间点，单位为毫秒。

- ### 返回值

  无

- ### 蓝图用法

  在蓝图中调用 **SetRecordingTimeMs** 蓝图节点。

  ![image-20210813161243578](/Images/image_60.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetRecordingTimeMs** 接口。

     ```C++
     int timeMs = 0;
     UYouMeTalkAPI::SetRecordingTimeMs(timeMs);
     ```



### 设置播放时间戳

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Set the timestamp of the current playback
  *  @param timeMs: timestamp
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static void SetPlayingTimeMs(int32 timeMs);
  ```

- ### 功能

  设置当前声音播放的时间戳。当通过录游戏脚本进行直播时，要保证观众端音画同步，游戏画面的播放需要和声音播放进行时间对齐。 这个接口设置的就是当前游戏画面播放已经进行到哪个时间点了。

- ### 	参数说明

  `timeMs`:当前游戏画面对应的时间点，单位为毫秒。

- ### 返回值

  无

- ### 蓝图用法

  在蓝图中调用 **SetPlayingTimeMs** 蓝图节点。

  ![image-20210813161651238](/Images/image_61.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetPlayingTimeMs** 接口。

     ```C++
     int timeMs = 0;
     UYouMeTalkAPI::SetPlayingTimeMs(timeMs);
     ```



## 服务器区域

***

### 设置服务器区域

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Set server zone
  *  @param region: server region
  *  @param extRegionName: extRegionName
  *  @param bAppend: bAppend
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
      static void SetServerRegion(EYouMeRTCServerRegion regionId, const FString extRegionName, bool bAppend);
  ```

- ### 功能

  设置首选连接服务器的区域码,初始化前调用，新版本以集成到Init里面，参数三，不填默认为中国

- ### 	参数说明

  `serverRegionId`：如果YOUME_RTC_SERVER_REGION定义的区域码不能满足要求，可以把这个参数设为 RTC_EXT_SERVER，然后通过后面的参数strExtServerRegionName 设置一个自定的区域值（如中国用 "cn" 或者 “ch"表示），然后把这个自定义的区域值同步给游密，我们将通过后台配置映射到最佳区域的服务器。 

  `strExtServerRegionName`：自定义的扩展的服务器区域名。不能为null，可为空字符串“”。只有前一个参数serverRegionId设为RTC_EXT_SERVER时，此参数才有效（否则都将当空字符串“”处理）。

  `bAppend`：

- ### 返回值

  无

- ### 蓝图用法

  在蓝图中调用 **SetServerRegion** 蓝图节点。

  ![image-20210813162329144](/Images/image_62.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetServerRegion** 接口。

     ```C++
     EYouMeRTCServerRegion regionId;
     FString extRegionName = " ";
     bool bAppend = false;
     UYouMeTalkAPI::SetServerRegion(regionId, extRegionName, bAppend);
     ```



## RestApi——支持主播相关信息查询

***

- ### 接口定义

  ```
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
  ```

- ### 功能

  Rest API , 向服务器请求额外数据。支持主播信息，主播排班等功能查询。需要的话，请联系我们获取命令详情文档。

- ### 	参数说明

  `strCommand`：请求的命令字符串，标识命令类型。 

  `strQueryBody`：请求需要的参数,json格式。 

  `requestID`：回传id,回调的时候传回，标识消息。不关心可以填NULL。

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 ****RequestRestApi** ** 蓝图节点。

  ![image-20210813162943123](/Images/image_63.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **RequestRestApi** 接口。

     ```C++
     FString strCommand = "query_talk_channel_user_count";
     FString strQueryBody = "{\"ChannelID\":\"123456\",\"AreaID\":0}";
     int32 requestID = 0;
     UYouMeTalkAPI::RequestRestApi(strCommand, strQueryBody, requestID);
     ```



## 安全验证码设置

------

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Set the token of authentication and the time when the user joins the room
  *  @param pToken: The token is used for authentication, which is set to null or empty string, and the token value is cleared.
  *  @param uTimeStamp: Time when the user joined the room
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
  	static void SetToken(const FString pToken);
  ```

- ### 功能

  设置身份验证的token，需要配合后台接口。

- ### 参数说明

  - `pToken`：身份验证用token，设置为NULL或者空字符串，清空token值，不进行身份验证。

- ### 蓝图用法

  在蓝图中调用 **SetToken** 蓝图节点。

  ![image-20210813183111628](/Images/image_64.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SetToken** 接口。

     ```C++
     FString pToken = " ";
     UYouMeTalkAPI::SetToken(pToken);
     ```



## 查询频道用户列表

- ### 接口定义

  ```C++
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
  ```

- ### 功能

  查询频道当前的用户列表， 并设置是否获取频道用户进出的通知。（必须自己在频道中）

- ### 参数说明

  `channelID`：频道ID。 

  `maxCount`：想要获取的最大人数。-1表示获取全部列表。 

  `notifyMemChange`：其他用户进出房间时，是否要收到通知。（设置为true，自己所在频道有人进出 都会有对应回调产生，反之false就没有对应回调）

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **GetChannelUserList** 蓝图节点。

  ![image-20210813183731677](/Images/image_65.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **GetChannelUserList** 接口。

     ```C++
     FString channelID = " ";
     int32 maxCount = 0;
     bool bNotifyMemChange = false;
     UYouMeTalkAPI::GetChannelUserList(channelID, maxCount, bNotifyMemChange);
     ```

- ### 异步回调

  蓝图回调

  ![image-20210813184057280](/Images/image_66.png)

  

  C++回调

  ```C++
  //涉及到的主要回调事件有：
  // channel:频道ID
  // memberChangeJsonStr:查询获得的用户列表，或变更列表
  // isUpdate: false为第一次查询，true为增量通知
  virtual void OnMemberChange_Implementation(const FString& channel, const TMap<FString, FString>& listMemberChangeMap, const TArray<FChannelMemberState>& channelMemberStates, bool bUpdate) override;
  ```



## 广播消息

***

- ### 接口定义

  ```C++
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
  ```

- ### 功能

  在语音频道内，广播一个文本消息。

- ### 参数说明

  - `pChannelID`：频道ID（自己需要进入这个频道）。 
  - `pContent`：要广播的文本内容。 
  - `requestID`：用于标识消息的ID。

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **SendMessage** 蓝图节点。

  ![image-20210707102953612](/Images/image_27.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```c++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **SendMessage** 接口。

     ```C++C++
     FString pChannelID = "";
     FString pContent = "";
     int32 requestID = 1;
     
     UYouMeTalkAPI::SendMessage(pChannelID, pContent, requestID);
     ```


- ### 异步回调

  蓝图回调

  ![image-20210813184740399](/Images/image_68.png)

  ![image-20210813184659832](/Images/image_67.png)

  

  C++回调

  ```C++
  //涉及到的主要回调事件有：
  //event:YOUME_EVENT_SEND_MESSAGE_RESULT: 发送消息的结果回调，param为requestID的字符串
  //event:YOUME_EVENT_MESSAGE_NOTIFY:频道内其他人收到消息的通知。param为文本内容
  virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
  ```

  

## 把人踢出房间

***

- ### 接口定义

  ```C++
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
  ```

- ### 功能

  把人踢出房间。

- ### 参数说明

  - `pUserID`：被踢的用户ID。 
  - `pChannelID`：从哪个房间踢出（自己需要在房间）。 
  - `lastTime`：踢出后，多长时间内不允许再次进入（单位：秒）。

  

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **KickOtherfromChannel** 蓝图节点。

  ![image-20210707103316119](/Images/image_28.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **KickOtherfromChannel** 接口。

     ```C++
     FString pUserID = "";
     FString pChannelID = "";
     int32 lastTime = 10;
     
     UYouMeTalkAPI::KickOtherfromChannel(pUserID, pChannelID, lastTime);
     ```

- ### 异步回调

  蓝图回调

  ![image-20210813184740399](/Images/image_68.png)

  ![image-20210817164346586](E:\Work\YouMeTalk_UE4\Docs\中文\Images\image_70.png)

  

  C++回调

  ```C++
  //涉及到的主要回调事件有：
  // YOUME_EVENT_KICK_RESULT  - 踢人方收到，发送消息的结果回调，param为被踢者ID
  // YOUME_EVENT_KICK_NOTIFY - 被踢方收到，被踢通知，会自动退出所在频道。param: （踢人者ID，被踢原因，被禁时间）
  virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
  ```

## 反初始化

***

- ### 接口定义

  ```C++
  /**
  *  funcDesc:Anti initialization engine
  *  @return YOUME_SUCCESS - Success
  *          Other - Specific error code
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
  	static EYouMeErrorCode UnInit();
  ```

- ### 功能

  反初始化引擎，可在退出游戏时调用，以释放SDK所有资源。

- ### 返回值

  如果成功则返回YOUME_SUCCESS，其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **UnInit** 蓝图节点。

![image-20210706154502112](/Images/image_13.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```

  2. 调用 **UnInit** 接口。

     ```C++
     UYouMeTalkAPI::UnInit();
     ```

