# README

`src`中为Qt工程文件。

**编译需求**：本实验工程在Qt 5.12.0环境下编写，编译时建议在5.12.0以上版本的Qt下进行。且由于工程连接了MySQL，编译使用的Qt环境必须装载有QSQLMYSQL驱动，且要将相应的库文件添加到Qt所在的文件夹中（详细方法可查阅如何在Qt中使用MySQL）。

**编译注意事项：**

1. 编译时应将文件拷贝到无中文目录下。中文目录下会编译出错。
2. 注意，若编译不成功，可能是本机的编译设置在其他机器上不能正常使用。可以删除工程目录下的Library.pro.user文件后重新打开工程，设置编译配置。

为了方便助教测试，这里给出编译完成的发行版程序。我将编译好的文件打包至`release`文件夹中，打开`release`文件夹中的`Library.exe`即可运行。

**运行注意事项：**

1. `release`文件夹中的其他文件是.exe运行所依赖的文件，不能单独把.exe文件拿出来运行。
2.  GUI界面是在显示放大150%下绘制的，如果出现缩放比例失常、元件偏移，建议将显示放大至150%后进行测试。