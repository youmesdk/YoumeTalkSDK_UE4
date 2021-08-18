# Talk SDK for UnrealEngine4 使用指南

## 适用范围

***

本规范仅适应于使用游戏实时语音引擎UnrealEngine4插件（C++接口、蓝图接口）开发多人实时语音功能的开发者。

## SDK目录概述

***

Talk SDK以UnrealEngine4的Plugin形式集成到UnrealEngine4当中，插件的文件格式如下：

├─ YouMeTalk
    ├─ Content
    ├─ Resources
    ├─ Source
    	├─ YouMeTalk
   	     ├─ Private
    		├─ Public
    		├─ YouMeTalkLibrary
    			├─ include
    			└─ lib

- Content：包含一个使用TalkSDK的Demo，使用蓝图方法，快速演示如何使用TalkSDK。
- Resources：包含插件资源文件，如插件封面图。
- Public：封装UE4可用的TalkSDK接口的头文件。
- Private：封装UE4可用的TalkSDK接口的源代码。
- include：TalkSDK原始接口的头文件。
- lib：TalkSDK原始接口的库文件，分为Android平台和iOS平台。Android平台下包括ARMv5、ARMv7和X86三种CPU架构下的libyoume_voice_engine.so文件，还包括youme_voice_engine.jar。iOS平台下包含libyoume_voice_engine.a文件和libYouMeCommon.a文件。

## 开发环境集成

***

1. 将YouMeTalk插件复制到工程根目录的Plugins文件夹中，如下图。（如果没有Plugins文件夹，那就创建一个）

   ![image-20210706105939642](/Images/image_1.png)

2. 重新生成文件结构，并编译工程。

   ![image-20210706110619003](/Images/image_2.png)

   ![image-20210706110737713](/Images/image_3.png)

3. 蓝图中引入插件：打开UE4引擎编辑器，在（Edit | Plugins | Project | Other）选项中勾选启用YouMeTalk插件，重启引擎，即可使用插件。

   ![image-20210706111009744](/Images/image_4.png)

4. C++中引入插件：打开工程的Visual Studio，在工程主模块的build.cs（文件路径：[ ProjectName / Source / ProjectName / ]）文件中，包含TalkSDK插件，代码如下：

```C++
PrivateDependencyModuleNames.AddRange(new string[] { "YouMeTalk" });
```

## API接口调用流程

***

API调用的基本流程如下图所示，具体接口说明参见 <u>**TalkSDKforUnrealEngine4 API接口手册**</u>。

![img](/Images/image_5.png)

