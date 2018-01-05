Camel_FileTransfer: 高性能可靠UDP数据传输P2P通讯框架

自主研发的点对点可靠网络传输中间件, 非开源 属于CamelSoft系列基础开发组件.

作用： UDP和TCP协议下的可靠数据通讯组件，可用于建立P2P环境，文件传输，数据通讯。基于UDP/TCP协议的内网穿透解决方案, 轻松实现音视频会议中心, 直播, 远程桌面/文档演示等功能.

特点：

轻量级通讯组件，数据通讯实现简单，快速，高效。
高层协议实现数据通讯的稳定可靠，可动态修改参数调整通讯策略。
可使用同一套接字初始化多个组件进行多线程数据通讯。
解决丢包：采用自行研发的并行滑动窗口协议，保证数据的稳定可靠传输。

动态调整：数据通讯可行效率动态评估和计算获得当前环境下的最佳通讯表现。

数据组帧：通讯数据包发送分包，接收组包，保证数据顺序完整。

支持平台：Windows/Android/IOS/MacOS/Linux

编译环境:

Windows:
Visual Studio 2017 15.5.2 Visual C++ 2017 14.11.25325

Android:
android-ndk-r15c

IOS:
Apple LLVM version 7.3.0 (clang-703.0.31)

Ubuntu:
gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.5)

Mac:
Apple LLVM version 7.3.0 (clang-703.0.31)
