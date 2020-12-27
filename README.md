### 新的修改

### 1、登陆服务器修改DNS，使其能通过互联网yum安装
编辑域名解析配置，将内网的DNS服务器注释掉，增加公网dns  202.101.172.35
vi /etc/resolv.conf
options timeout:1 attempts:1 rotate
nameserver 202.101.172.35      
#nameserver 10.126.13.104
#nameserver 10.126.13.103

### 2、修改yum源
//云内的yum没有相关的软件包，改到阿里云的yum源。
cd /etc/yum.repos.d/
//老的文件先备份下
cp CentOS-Base.repo CentOS-Base.repo.bak
cp epel.repo epel.repo.bak
//centos 7 的文件
wget -O /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-7.repo
wget -O /etc/yum.repos.d/epel.repo http://mirrors.aliyun.com/repo/epel-7.repo
//如果是centos 6的用下面的文件
wget -O /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-6.repo
wget -O /etc/yum.repos.d/epel.repo http://mirrors.aliyun.com/repo/epel-6.repo
//生成缓存
yum makecache

### 3、查看yum grouplist
//查看下可用的安装包
yum grouplist
要有包括有
X Window System
以及图形界面下列等
MATE Desktop 
Xfce
GNOME Desktop
我装了GNOME Desktop

### 4、安装软件包
//安装图形界面包
yum groupinstall "X Window System"
yum groupinstall "GNOME Desktop"

### 5、安装vncserver
yum install vnc vnc-server

### 6、配置相关参数
//采用gnome 桌面，其实也可以选其他的，
vi  ~/.vnc/xstartup
#!/bin/sh
unset SESSION_MANAGER
unset DBUS_SESSION_BUS_ADDRESS
#exec /etc/X11/xinit/xinitrc
gnome-session &                

如果用Xface
见 https://blog.csdn.net/qq_22918577/article/details/69817646

// 配置登录帐号、桌面分辨率、连接方式
vi /etc/sysconfig/vncserver
加入
VNCSERVERS="1:root" VNCSERVERARGS[1]="-geometry 1024x768"

### 7、启动vncserver
//第一次启动过程中需要你输入后续登陆密码
vncserver

ps –ef | more
可以看到vncserver 已经启动了，端口是5901
 
//后面也可以通过下面命令关闭服务
Killall Xvnc

### 8、客户端连接vncserver
 
![1](https://user-images.githubusercontent.com/68214934/103147201-19e07280-478e-11eb-9873-f2d591ac54ee.png)

输入密码登陆OK
![2](https://user-images.githubusercontent.com/68214934/103147216-3381ba00-478e-11eb-8377-93f42a42d3f2.png)

