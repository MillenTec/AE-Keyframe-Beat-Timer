# Ae Frame Time Helper

一个用于帮助After Effects用户根据节奏计算关键帧时间间隔的C++控制台应用程序

自己突发奇想做的小工具，目前只做了最基础的功能，现在使用[MIT协议](https://mit-license.org/)开源

## 项目简介
对于Ae新手来说，可能不太清楚多少帧大约有多长时间，无法高效地将自己心中想地节奏应用为关键帧

Ae帧时间助手是一个简单实用的工具，旨在帮助视频编辑师和动画师更好地掌握After Effects中关键帧的时间节奏。用户可以通过按空格键来标记关键帧的时间点，程序会自动计算每两个关键帧之间的时间间隔，并转换为不同帧率下的帧数

## 第三方
项目使用了[nlohmann/json库](https://github.com/nlohmann/json)（[MIT协议](https://github.com/nlohmann/json/blob/develop/LICENSE.MIT)）

## 功能

- 🕐 通过空格键标记时间点，使用ALT键结束标记
- 📊 自动计算时间点间地时间间隔（精确到微秒）
- 🎬 自动转换为多种帧率下的帧数（向下取整）（120fps、60fps、30fps、24fps）
- 📝 以JSON格式输出结果

## 使用方法

1. 运行程序后，根据提示按下空格键开始记录
2. 在您认为需要设置关键帧的时刻按下空格键进行标记
3. 按下ALT键结束记录
4. 程序将自动计算并显示所有关键帧之间的时间间隔及对应的帧数

按键说明：
- **空格键**：标记关键帧时间点
- **ALT键**：结束记录
- **ESC键**：退出程序

## 输出格式

程序会以JSON格式输出结果，包含以下信息：
- 每两个关键帧之间的时间间隔（单位毫秒）
- 对应于不同帧率的帧数：
  - 120fps
  - 60fps
  - 30fps
  - 24fps

## 技术实现

- 使用C++标准库中的chrono库进行高精度时间测量
- 使用Windows API处理键盘输入
- 使用nlohmann/json库处理JSON数据格式
- 支持UTF-8编码的中文输出

## 适用场景

- After Effects动画制作
- 视频编辑节奏控制
- 动作捕捉时间点记录
- 任何需要精确时间间隔测量的场景

## 编译环境

- C++23标准
- Windows平台
- 需要链接Windows系统库

## 使用示例

程序运行后会显示操作提示，用户只需按照提示操作即可：
1. 想好关键帧的节奏
2. 在需要的位置按空格键标记
3. ALT键结束，即可看到所有时间间隔数据

这些数据可以直接用于After Effects等视频编辑软件中，帮助您精确设置关键帧的时间位置。

## 未来
- 添加自定义帧速率支持
- 可导出JSON文件
- 使用Qt制作GUI界面

## 关于我
联系我：
- [MillenTec@outlook.com](mailto:MillenTec@outlook.com)
- [GitHub](https://github.com/MillenTec)
- [Bilibili](https://space.bilibili.com/3546591566760474)
