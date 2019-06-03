# 设计规范
1. 屏幕设计分辨率
960*540
2. 游戏总场景地图大小
1920*1080
3. 游戏具体场景地图大小
960*540
4. IDE：Microsoft Visual Studio Enterprise 2019 版本 16.1.1
VisualStudio.16.Release/16.1.1+28922.388
5. 二维游戏引擎：Cocos 3.17.2
QE V2.0 for Baby's_36_Skills
6. Tiled：Tiled for Windows (64-bit), snapshot Version 2019.05.08
说明：为了增强兼容性，地图使用Tiled铺设，不用Cocos Studio
7. 服务器开发
服务器应用开发使用 Node.js v12.3.1
socket.io 2.2.0
8. 数据库
数据库为关系型数据库，数据库管理系统为MySQL Community Server version: 8.0.16
9. 许可证：GUN GPL3.0
许可概要：他人修改后源码后也必须开源并且新增代码要同样采用GUN GPL3.0许可证

# 说明
* 打包支持
Cocos2d-x 3.3与3.10、3.17.1、3.17.2打包到安卓教程：
[点击进入](https://blog.csdn.net/COCO56/article/details/89392349)

* 特色
自主研发了QE（Quick Engine），大大减少了代码的重复率，使代码看起来更简洁，开发起来更高效。

* 代码仓与文档：
文档更新地址：https://blog.csdn.net/COCO56/article/details/90384628
代码托管地址 ：https://github.com/COCO5666/Baby-s_36_Skills

<!-- 安装包下载方式
* 安卓
链接一：https://www.pgyer.com/J5iR
或扫码：
![图片无法正常加载，请联系作者](https://www.pgyer.com/app/qrcode/J5iR)
链接二：[点此跳转](https://uinedu-my.sharepoint.com/:f:/g/personal/a19635_myoffice_site/EgusrLTRZ9ZFi0_aSduJW_4B5wokGfa1PuhXvUoHeo3Adg?e=qWUnl7)
* Windows
[点此跳转](https://uinedu-my.sharepoint.com/:f:/g/personal/a19635_myoffice_site/EgusrLTRZ9ZFi0_aSduJW_4B5wokGfa1PuhXvUoHeo3Adg?e=qWUnl7) -->

# 游戏简介
* 英文名：Baby's_36_Skills
* 宝贝三十六计是一款针对3-6岁儿童的益智策略类游戏，主要用来教会宝宝识别坏人的伎俩，不轻易相信坏人。
# 基本玩法：
* 单机模式下：宝宝可以在地图上随意走动，当碰到坏人时会切换到与坏人交流的场景（类似于回合制游戏，你打我一下，我打你一下，不过这里是两个人对话交流），如果宝宝最终识破了坏人的伎俩，没有跟随坏人离去，则坏人从地图上消失，当当前关卡所有坏人全部消失时，游戏胜利。如果宝宝跟随坏人离去，则游戏失败，需要重新开始游戏。每个坏人随机采用一种内置的一种策略来尝试诱骗宝宝。
* 联网模式下：其他人（如孩子父母，或者别人的父母）可以自定义扮演坏人角色来尝试与宝宝交流，来诱骗宝宝，宝宝成功识破，游戏胜利，如未成功识破，游戏失败。