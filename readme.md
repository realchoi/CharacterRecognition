# 基于数字图像处理技术的理工科选择题自动判分系统

> **一些说明**

* 本系统在开源框架的帮助下完成，包括著名的[OpenCV库](http://opencv.org/)，以及[HOG+SVM方法](http://blog.csdn.net/u014114990/article/details/49746773)，在此感谢开源，本程序也开源于[Github](https://github.com/poorcai/CharacterRecognition)。

- 本程序由本人在导师莫绪涛老师的帮助下完成，系毕业设计附属程序，在此感谢莫绪涛老师的指导。
- 本程序所使用的OpenCV版本为2.4.9，Visual Studio的版本为2013，如若想完美使用本程序，建议您使用对应的OpenCV和Visual Studio。

> **使用方法**

* 克隆本工程到您的Visual Studio中，并务必配置好计算机的环境变量，以及在Visual Stuio中配置好OpenCV的相关路径（参考链接：[【OpenCV入门教程之一】 安装OpenCV：OpenCV 3.0、OpenCV 2.4.8、OpenCV 2.4.9 +VS 开发环境配置](http://blog.csdn.net/poem_qianmo/article/details/19809337)）。
* 确保配置工作完成后，按电脑的F5键（Debug），将会弹出一个控制台窗口，提示用户输入“本次考试的正确答案”，直接输入即可（本程序中要求选择题答案为10个，且为大写英文字母，限于A、B、C、D，后续可自行修改）。
* 紧接着，会提示用户输入“单个选项的分值”，亦可直接输入（限于阿拉伯数字，支持小数）。
* 接下来，会出现一个简单的提示界面，根据提示，按下相关的热键，即可进行相关的操作：按下T键，进行样本的训练；按下R键，进行识别，这时需要输入待识别图片的绝对路径；按下Q键，退出程序。
* 如图：![](https://github.com/poorcai/CharacterRecognition/blob/master/ImageTips/window.png)
* 本程序只是对字母识别思想的一个简单实现，并不具有强大的功能，因此，待识别的图片的像素大小必须为3610*610，而且需要裁剪整齐（后续可自行优化代码），如图所示：![](https://github.com/poorcai/CharacterRecognition/blob/master/ImageTips/exam.jpg)
* 如有相关疑问，可点击此处给我发邮件：<caidecent@gmail.com>。