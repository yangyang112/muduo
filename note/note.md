//--------------------------------
心得
１．虽然使用了面向对象．但是业务还是跳来跳去的
２．
//--------------------------------

Buffer
EventLoop
TcpConnection
TcpClient
TcpServer　

１．明白解决了什么问题
２．大概的解决思路


//-----------------reactor---------------
这个类别中主要讲解reactor中要实现的类

1 .Channel 封装数据　fd, 回调handler．
２．Poller (_ctl, _wait). 然后调用Channel
	a. channel 和 poll 这两者怎么联系
	b. xxx


3. 对于EventLoop而言，　需要满足以下功能
	a. 需要有一个wakeup_fd,和wakeup_channel_
	b. 再初始化的时候，new　一个poller 
在里面，有一个问题我不太清楚，就是wakeup_channel是什么时候注册进poller的．
	a. 在loop函数，　使用poll 和channel

4.EventLoopThread
	1.线程作为成员变量
	2.通过start_loop 开启线程．返回loop?
    3.loop 前的回调　

５．EventLoopThreadPool　线程池相关
	1.记录线程．和所有loop对象．新建相关内容EventLoopThreadPool::start
	2.


EventLoop::loop()
	EpollPoller::poll
	Channel::handle_event

//-------------------main Reactor--------------------
这个类别则主要是main reactor中实现的类，跟客户端的分发有关。

Acceptor （loop, socket_path） 然后新建channel. 


//-------------------问题--------------------
1. accept_channel_ 什么时候进入的是loop的fd
　  accept_channel_.enable_reading(); // 循环依赖

2. 没有其它内容了