# Talk SDK for UnrealEngine4 典型实现方案

## **实现语音通话**

****

### 相关接口

- BindObserver：绑定回调对象
- UnBindObserver：解绑回调对象
- OnEvent：回调监听
- Init：初始化SDK
- JoinChannelSingleMode：加入语音频道（单频道）
- SetSpeakerMute：设置扬声器状态
- SetMicrophoneMute：设置麦克风状态
- LeaveChannelAll：离开频道
- UnInit：反初始化SDK

### 实现步骤

> 实现步骤分为蓝图和C++，用户可根据自己需求，选择对应的方式实现

1. #### 继承YoumeTalkObserver接口类，绑定回调对象

   - 蓝图实现

     - 在（想要实现监听的）蓝图中的 **ClassSettings** 选项中继承 **YouMeTalkObserver** 接口，如下图所示：
     - ![image-20210706143937430](/Images/image_6.png)
     - ![image-20210706143824326](/Images/image_7.png)
     - 在蓝图中调用 BindObserver 蓝图节点，如下图所示：
     - ![image-20210706144238413](/Images/image_8.png)

   - C++实现

     - 继承回调接口 **IYouMeTalkObserver**，注意引入头文件。

     - ![image-20210707154001415](/Images/image_9.png)

     - 入头文件。(已引入可忽略)

     - ```
       #include "YouMeTalkAPI.h"
       ```

     - 调用 **BindObserver** 接口。

     - ```
       UYouMeTalkAPI::BindObserver(this);
       ```

   - 注意：绑定回调监听时，只允许一个对象进行监听。

2. #### 回调监听

   - 蓝图实现

     -  在继承 **YouMeTalkObserver** 接口的蓝图中，调用 **EventOnEvent** 蓝图节点。
     - ![image-20210706145856668](/Images/image_10.png)

   - C++实现

     - 在继承回调接口 **IYouMeTalkObserver** 的类中，实现 **回调事件OnEvent虚函数**。

       ```C++
       virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
       ```

       注：如果在C++中实现了回调事件虚函数，就不要在蓝图中再实现一次。否则会覆盖C++的回调，导致C++接收不到回调。

     - 完成上述回调事件绑定，即可在后续的API调用中，实现API相关回调。

3. #### 初始化SDK

   - 蓝图实现

     - 在蓝图中调用 Init 蓝图节点，如下图所示：
     - ![image-20210813104256676](/Images/image_12.png)
     - 成功初始化后，将触发 OnEvent 事件回调，蓝图回调如下图：
     - ![image-20210812172632285](/Images/image_29.png)

   - C++实现

     - 引入头文件。(已引入可忽略)

       ```C++
       #include "YouMeTalkAPI.h"
       ```

     - 调用 **YouMeTalkInit** 接口。

       ```C++
       FString strAppKey = "";
       FString strAPPSecret = "";
       EYouMeRTCServerRegion youMeRTCServerRegion = EYouMeRTCServerRegion::RTC_CN_SERVER;
       FString strExtServerRegionName = "";
       UYouMeTalkAPI::Init(strAppKey, strAPPSecret, youMeRTCServerRegion, strExtServerRegionName);
       ```

     - 成功初始化后，将触发 OnEvent_Implementation 函数回调，需要实现OnEvent_Implementation虚函数，才能触发回调。

     - ```
       //涉及到的主要回调事件有：
       // YOUME_EVENT_INIT_OK  - 表明初始化成功
       // YOUME_EVENT_INIT_FAILED - 表明初始化失败，最常见的失败原因是网络错误或者 AppKey-AppSecret 错误
       virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
       ```

4. #### 加入语音频道

   - 蓝图实现

     - 在蓝图中调用 **JoinChannelSingleMode** 蓝图节点，如下图所示：（节点参数如何填写，请参考API接入手册）
     - ![image-20210706161445437](/Images/image_14.png)
     - 成功加入房间后，将触发 OnEvent 事件回调，蓝图回调如下图：
     - ![image-20210812174751162](/Images/image_31.png)

   - C++实现

     - 引入头文件。(已引入可忽略)

     - ```
       #include "YouMeTalkAPI.h"
       ```

     - 调用 **JoinChannelSingleMode** 接口。

     - ```
       FString strUserID = "";
       FString strChannelID = "";
       EYouMeUserRole userRol = EYouMeUserRole::YOUME_USER_HOST;
       bool bCheckRoomExis = true;
       UYouMeTalkAPI::JoinChannelSingleMode(strUserID, strChannelID, userRol, bCheckRoomExis);
       ```

     - 成功初始化后，将触发 OnEvent_Implementation 函数回调，需要实现OnEvent_Implementation虚函数，才能触发回调。

     - ```
       //涉及到的主要回调事件有：
       //YOUME_EVENT_JOIN_OK - 成功进入语音频道
       //YOUME_EVENT_JOIN_FAILED - 进入语音频道失败，可能原因是网络或服务器有问题，或是bCheckRoomExist为true时频道还未创建
       virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
       ```

5. #### 打开扬声器和麦克风

   - 蓝图实现

     - 在蓝图中调用 **SetSpeakerMute**（设置扬声器状态） 和 SetMicrophoneMute（设置麦克风状态） 蓝图节点，如下图所示：（节点参数如何填写，请参考API接入手册，设置Mute参数为false将打开扬声器或麦克风）
     - <img src="/Images/image_17.png" alt="image-20210706175311140" style="zoom:150%;" />
     - <img src="/Images/image_41.png" alt="image-20210813114738223" style="zoom:80%;" />
     - 成功设置扬声器和麦克风状态后，将触发 OnEvent 事件回调，蓝图回调如下图：
     - ![image-20210818165227588](E:\Work\YouMeTalkSDK_UE4\Images\image_71.png)

   - C++实现

     - 引入头文件。(已引入可忽略)

     - ```
       #include "YouMeTalkAPI.h"
       ```

     - 调用 **SetSpeakerMute** 和 SetMicrophoneMute 接口

     - ```
       bool mute = true;
       UYouMeTalkAPI::SetSpeakerMute(mute);
       UYouMeTalkAPI::SetMicrophoneMute(mute);
       ```

     - 成功初始化后，将触发 OnEvent_Implementation 函数回调，需要实现OnEvent_Implementation虚函数，才能触发回调。

     - ```
       //涉及到的主要回调事件有：
       //YOUME_EVENT_LOCAL_MIC_ON - 自己麦克风打开
       //YOUME_EVENT_LOCAL_MIC_OFF - 自己麦克风关闭
       //YOUME_EVENT_LOCAL_SPEAKER_ON - 自己扬声器打开
       //YOUME_EVENT_LOCAL_SPEAKER_OFF - 自己扬声器关闭
       virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
       ```

6. #### 离开频道

   - 蓝图实现
     - 在蓝图中调用 **LeaveChannelAll**蓝图节点，如下图所示：
     - ![image-20210706163317849](/Images/image_15.png)
     - 成功离开频道后，将触发 OnEvent 事件回调，蓝图回调如下图：
     - ![image-20210813110605947](/Images/image_36.png)
     
   - C++实现

     - 引入头文件。(已引入可忽略)

     - ```
       #include "YouMeTalkAPI.h"
       ```

     - 调用 **LeaveChannelAll** 接口。

     - ```
       UYouMeTalkAPI::LeaveChannelAll();
       ```

     - 成功初始化后，将触发 OnEvent_Implementation 函数回调，需要实现OnEvent_Implementation虚函数，才能触发回调。

     - ```
       //涉及到的主要回调事件有：
       //YOUME_EVENT_LEAVED_ALL - 成功退出所有语音频道
       virtual void OnEvent_Implementation(const EYouMeEvent event, const EYouMeErrorCode error, const FString& channel, const FString& param) override;
       ```

7. #### 解绑回调对象

   - 蓝图实现

     - 在蓝图中调用 **UnbindObserver** 蓝图节点，如下图所示：
     - ![image-20210706151016776](/Images/image_11.png)

   - C++实现

     - 引入头文件。(已引入可忽略)

     - ```
       #include "YouMeTalkAPI.h"
       ```

     - 调用 **UnbindObserver** 接口。

     - ```
       UYouMeTalkAPI::UnbindObserver();
       ```

8. #### 反初始化SDK

   - 蓝图实现

     - 在蓝图中调用 **UnInit** 蓝图节点，如下图所示：
     - ![image-20210706154502112](/Images/image_13.png)

   - C++实现

     - 引入头文件。(已引入可忽略)

     - ```
       #include "YouMeTalkAPI.h"
       ```

     - 调用 **UnInit** 接口。

     - ```
       UYouMeTalkAPI::UnInit();
       ```

       

