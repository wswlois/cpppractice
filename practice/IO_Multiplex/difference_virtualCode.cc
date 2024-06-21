#include <func.h>
listenfd = socket();//创建套接字
setsockopt(addr);//地址复用与端口复用
setsockopt(port);//地址复用与端口复用

bind(seraddr);//绑定服务器的ip与端口号
listen();

//如果是select
fd_set allset;
FD_SET(listenfd, &allset);//位图

//如果是poll
struct pollfd  pfd[];
pfd[0].fd = listenfd;
pfd[0].event = POLLIN;

//如果是epoll
epfd = epoll_create();

struct epoll_event  evt;
evt.fd = listenfd;
evt.events = EPOLLIN;
epoll_ctl(listenfd, &evt);//红黑树


while(1)
{
    //如果是select
    rset = allset;
    nready = select(&rset);
    
    //如果是poll
    nready = poll(pfd);
    
    //epoll
    nready = epoll_wait(_evtList);
    
    //需要查看就绪的文件描述符是哪一种
    //如果listenfd就绪了
    //如果是select
    if(FD_ISSET(listenfd, rset))
    {
        connfd = accept();
        FD_SET(connfd, &allset);//继续监听
    }
    
    //如果是poll
    if(pfd[0].revents & POLLIN)
    {
        connfd = accept();
        pfd[i].fd = connfd;//继续监听
        pfd[i].event = POLLIN;
    }
    
     //如果是epoll
    if(listenfd == _evtList[i].fd)
    {
        connfd = accept();
        struct epoll_event  evt;
        evt.fd = connfd;
        evt.events = EPOLLIN;
        epoll_ctl(connfd, &evt);//红黑树，继续监听      
    }
    
    
    //另外一类就是看就绪的文件描述符是不是之前监听的connfd，也就是accept返回的结果对应的文件描述符
    //如果connfd就绪了，就表明客户端有数据发过来了，服务器就可以读客户端发送的数据
    nByte = read(connfd);
    if(nByte > 0)
    {
        //正常的业务逻辑的处理
    }
    else if(nByte == 0)
    {
        //表明客户端已经断开
        //需要将文件描述符从对应的数据结构中删除
    }
    else if(nByte < 0)
    {
        //表明文件描述符异常
        //需要做异常的处理
    }
}
