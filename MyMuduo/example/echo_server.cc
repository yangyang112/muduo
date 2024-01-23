#include <functional>
#include <string>
#include <mymuduo/TcpServer.hpp>

void onMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer *buf, muduo::Timestamp time)
{
    conn->send(buf);
}

int main()
{
    EventLoop loop;
    InetAddress listenAddr(2007);
    TcpServer server(&loop, listenAddr);
    server.setMessageCallback(onMessage);
    server.start();
    loop.loop();
}