# Talk SDK for UnrealEngine4 API接口手册

## 相关异步/同步处理方法介绍

***

游密语音引擎SDK for UnrealEngine4提供了C++和蓝图接口，接口调用都会立即返回，凡是本身需要较长耗时的接口调用都会采用异步回调的方式，所有接口都可以在主线程中直接使用。回调在主线程。

## API调用说明

***

API使用的基本流程：（初始化 -> 收到初始化成功回调通知 -> 加入语言频道 -> 收到加入频道成功回调通知 -> 使用其他接口 -> 离开语音频道 -> 反初始化），要确保严格按照上述的顺序使用接口。



## 绑定回调

****

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



## TalkSDK初始化

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
  	static EYouMeErrorCode YouMeTalkInit(const FString strAppKey, const FString strAPPSecret, EYouMeRTCServerRegion youMeRTCServerRegion, const FString strExtServerRegionName);
  ```

- ### 功能

  初始化语音引擎，做APP验证和资源初始化。（只有appkey,appsecret,serverRegionId 都一样时,才可以进行语音互通,改任意一个视为另外一个区服）。

- ### 参数说明

  - `strAPPKey`：从游密后台申请到的 app key, 这个是你们应用程序的唯一标识。 

  - `strAPPSecret`：对应 strAPPKey 的私钥, 这个需要妥善保存，不要暴露给其他人。 

  - `serverRegionId`：设置首选连接服务器的区域码，如果在初始化时不能确定区域，可以填RTC_CN_SERVER，后面确定时通过 SetServerRegion 设置。如果YOUME_RTC_SERVER_REGION定义的区域码不能满足要求，可以把这个参数设为 RTC_EXT_SERVER，然后通过后面的参数strExtServerRegionName 设置一个自定的区域值（如中国用 "cn" 或者 “ch"表示），然后把这个自定义的区域值同步给游密，我们将通过后台配置映射到最佳区域的服务器。

  -  `strExtServerRegionName`：自定义的扩展的服务器区域名。不能为null，可为空字符串“”。只有前一个参数serverRegionId设为RTC_EXT_SERVER时，此参数才有效（否则都将当空字符串“”处理）。

- ### 返回值 

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  调用 **YouMeTalkInit** 蓝图节点。

![image-20210706153123730](/Images/image_12.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)

     ```C++
     #include "YouMeTalkAPI.h"
     ```
  
  2. 调用 **YouMeTalkInit** 接口。
  
     ```C++
     FString strAppKey = "";
     FString strAPPSecret = "";
     EYouMeRTCServerRegion youMeRTCServerRegion = EYouMeRTCServerRegion::RTC_CN_SERVER;
     FString strExtServerRegionName = "";
     
     UYouMeTalkAPI::YouMeTalkInit(strAppKey, strAPPSecret, youMeRTCServerRegion, strExtServerRegionName);
     ```
  
     

## Talk反初始化

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



## 加入语音频道（单频道）

***

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
  
     

## 退出所以语言频道

***

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

  多频道模式下，退出指定的语音频道。

- ### 参数说明

  - `strChannelID`：全局唯一的频道标识，全局指在当前应用程序的范围内。

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 异步回调

  涉及到的主要回调事件有：

  - YOUME_EVENT_LEAVED_ONE - 成功退出指定语音频道。

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



## 设置白名单用户

***

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

- ### 异步回调

  涉及到的主要回调事件有：

  - YOUME_EVENT_SET_WHITE_USER_LIST_OK - 成功在指定语音频道设置白名单，有异常用户会返回错误码YOUME_ERROR_WHITE_SOMEUSER_ABNORMAL。
  - YOUME_EVENT_SET_WHITE_USER_LIST_FAILED - 在指定语音频道设置白名单失败，可能原因是网络或服务器有问题。

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



## 设置扬声器的状态

***

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
     bool mute = true;
     
     UYouMeTalkAPI::SetSpeakerMute(mute);
     ```
  
  

## 获取扬声器状态

***

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

  获取当前麦克风状态。（该接口为异步接口,尽量避免逻辑上设置了扬声器状态后立刻调用该接口）。

- ### 返回值

  `Value`：true——麦克风关闭，false——麦克风开启。

- ### 蓝图用法

  在蓝图中调用 **GetSpeakerMute** 蓝图节点。

  ![image-20210706175822609](/Images/image_18.png)

- ### C++ 用法

  1. 引入头文件。(已引入可忽略)
  
     ```C++
     #include "YouMeTalkAPI.h"
     ```
  
  2. 调用 **GetSpeakerMute** 接口。
  
     ```C++
     UYouMeTalkAPI::GetSpeakerMute();
     ```



## 设置音量

***

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



## 获取音量

***

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

  

## 暂停通话

***

- ### 接口定义

  ```C++
  /**
  *  funcDesc: Pause the call and release the microphone and other device resources
  *  @return YOUME_SUCCESS - SuccessC++
  *          Other - Specific error code
  */
  UFUNCTION(BlueprintCallable, Category = "YouMeTalkAPI")
  	static EYouMeErrorCode PauseChannel();
  ```

- ### 功能

  暂停通话，释放对麦克风等设备资源的占用。当需要用第三方模块临时录音时，可调用这个接口。

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 异步回调

  YOUME_EVENT_RESUMED - 恢复语音频道完成。

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
  
  

## 恢复通话

***

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



## 播放背景音乐

***

- ### 接口定义

  ```c++
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

- ### 参数s说明

  - `pFilePath`：音乐文件的路径。
  -  `bRepeat`：是否重复播放，true——重复播放，false——只播放一次就停止播放。

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。

- ### 异步回调

  - YOUME_EVENT_BGM_STOPPED - 通知背景音乐播放结束
  - YOUME_EVENT_BGM_FAILED - 通知背景音乐播放失败

- ### 蓝图用法

  在蓝图中调用 **PlayBackgroundMusic** 蓝图节点。

  ![image-20210706182614536](/Images/image_23.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)
  
     ```C++
     #include "YouMeTalkAPI.h"
     ```
  
  2. 调用 **PlayBackgroundMusic** 接口。
  
     ```C++
     FString pFilePath = "";
     bool bRepeat = true;
     
     UYouMeTalkAPI::PlayBackgroundMusic(pFilePath, bRepeat);
     ```
  
     

## 停止播放背景音乐

***

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

- ### 参数说明

  `vol`:背景音乐的音量，范围 [0-100]。

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
  
  

## 设置背景音乐播放音量

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
  
  

## 查询频道用户列表

***

- ### 接口定义

  ```c++
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

  - `channelID`：频道ID。 
  - `maxCount`：想要获取的最大人数。-1表示获取全部列表。 
  - `notifyMemChange`：其他用户进出房间时，是否要收到通知。（设置为true，自己所在频道有人进出 都会有对应回调产生，反之false就没有对应回调）

- ### 返回值

  返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](https://www.youme.im/doc/TalkCocosC++StatusCode-v2.5.php#YouMeErrorCode类型定义)。

- ### 蓝图用法

  在蓝图中调用 **GetChannelUserList** 蓝图节点。

  ![image-20210706192241225](/Images/image_26.png)

- ### C++用法

  1. 引入头文件。(已引入可忽略)
  
     ```C++
     #include "YouMeTalkAPI.h"
     ```
  
  2. 调用 **GetChannelUserList** 接口。
  
     ```C++
     FString  channelID = "";
     int32 maxCount = 10;
     bool notifyMemChange = true;
     
     UYouMeTalkAPI::GetChannelUserList(channelID, maxCount, notifyMemChange);
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

- ### 异步回调

  发送方会收到YOUME_EVENT_SEND_MESSAGE_RESULT回调，通知发送消息的结果。 频道内其他人收到YOUME_EVENT_MESSAGE_NOTIFY回调，通知消息内容。

  - event:YOUME_EVENT_SEND_MESSAGE_RESULT: 发送消息的结果回调，param为requestID的字符串
  - event:YOUME_EVENT_MESSAGE_NOTIFY:频道内其他人收到消息的通知。param为文本内容
  
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

- ### 异步回调
  
  - event:YOUME_EVENT_KICK_RESULT: 踢人方收到，发送消息的结果回调，param为被踢者ID。
  - event:YOUME_EVENT_KICK_NOTIFY: 被踢方收到，被踢通知，会自动退出所在频道。param: （踢人者ID，被踢原因，被禁时间）。

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
