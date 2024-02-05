#include <strings.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include "Socket.hpp"
#include "Logger.hpp"
#include "InetAddress.hpp"

Socket::~Socket()
{
    close(sockfd_);
}

void Socket::bind_address(const InetAddress &loacladdr)
{
    if (bind(sockfd_, (sockaddr *)loacladdr.get_sockaddr(), sizeof(sockaddr_in)) != 0)
    {
        LOG_FATAL("bind sockfd:%d fail \n", sockfd_);
    }
}

void Socket::listen()
{
    if (::listen(sockfd_, 1024) != 0)
    {
        LOG_FATAL("listen sockfd:%d fail \n", sockfd_);
    }
}

int Socket::accept(InetAddress *peeraddr)
{
    /*
    *   1.accept 参数不合法
    *   2.对返回的connfd没有设置非阻塞
    */
    sockaddr_in addr;
    bzero(&addr, sizeof(addr));

    socklen_t len = sizeof(addr);
    int connfd = ::accept4(sockfd_, (sockaddr *)&addr, &len, SOCK_NONBLOCK | SOCK_CLOEXEC);
    if (connfd >= 0)
    {
        peeraddr->set_sockaddr(addr);
    }
    return connfd;
}

void Socket::shutdown_write()
{
    if (::shutdown(sockfd_, SHUT_WR) < 0) {
        LOG_ERROR("shutdown write error");
    }
}
/*
#include <sys/socket.h>
int setsockopt( int socket, 
                int level,  //
                int option_name,
                const void *option_value, 
                size_t ，
                ption_len);
*/

/*

*/
void Socket::set_tcp_noDelay(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));
}

/*
这个函数用来设置是否允许地址重用（SO_REUSEADDR 选项），
当 on 为 true 时表示允许地址重用。允许地址重用可以在服务器意外退出后迅速重新启动服务器而不需要等待一段时间。
这对于服务器的高可用性和快速重启是很有用的。
*/
void Socket::set_reuseAddr(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
}

/*
这个函数用来设置是否允许端口重用（SO_REUSEPORT 选项），
当 on 为 true 时表示允许端口重用。允许端口重用可以使多个套接字绑定到相同的 IP 地址和端口上，
适用于实现负载均衡和高性能服务器。
*/
void Socket::set_reusePort(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
}

void Socket::set_keepAlive(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval));
}