/*
muduo网络库的使用:
主要提供的三个类:
1. EventLoop: 事件循环类, 负责事件的分发和处理
2. TcpServer: 服务器类, 负责管理连接, 以及接收新连接
3. TcpClient: 客户端类, 负责连接服务器, 以及发送数据

muduo库里面的核心思想:
epool + 线程池 + 事件驱动

好处: 能够把网络I/O和业务处理分开, 使得网络I/O和业务处理能够并行执行,
提高了程序的并发性能
*/

#include <functional>
#include <iostream>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpServer.h>

using namespace muduo;
using namespace muduo::net;
using namespace std::placeholders;

// 基于muduo网络库开发服务器程序:
// 1. 组合TcpServer对象;
// 2. 创建EventLoop事件循环对象;
// 3. 明确TcpServer构造函数需要什么参数,输出CharServer的构造函数;
// 4.
// 在当前服务器类的构造函数当中，注册处理连接的回调函数和处理读写事件的回调函数;
// 5. set the number of thread on server;

class ChatServer {
public:
  // @param loop: 事件循环对象;
  // @param listenAddr: 服务器的地址;
  // @param nameArg: 服务器的名字;
  ChatServer(EventLoop *loop, const InetAddress &listenAddr,
             const std::string &nameArg)
      : _server(loop, listenAddr, nameArg), _loop(loop) {
    // 给服务器注册用户连接的创建和销毁的回调
    // 这里是利用std::bind来创建一个std::function对象, 用于注册回调函数,
    // 由于相应库里面声明的回调函数参数只有一个
    // 但是由于我们的成员函数onConnection有两个参数,
    // 所以我们需要用std::bind来绑定成员函数的this指针, 并且设置一个参数
    // 从而使得生成的函数对象满足条件!
    _server.setConnectionCallback(
        std::bind(&ChatServer::onConnection, this, _1));

    // 给服务器注册用户读写事件的回调
    _server.setMessageCallback(
        std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    // 设置服务器的线程数量
    // 一个I/O线程, 7个工作线程
    _server.setThreadNum(8);
  }

  // enable event loop
  void start() { _server.start(); }

private:
  // out attention is mainly on the following two functions: onConnection and
  // onMessage 专门处理用户的连接创建和销毁:
  void onConnection(const TcpConnectionPtr &connection) {
    // output the message about the connection
    if (connection->connected()) {
      std::cout << connection->peerAddress().toIpPort() << "->"
                << connection->localAddress().toIpPort() << " status is ONLINE"
                << std::endl;

    } else {
      std::cout << connection->peerAddress().toIpPort() << "->"
                << connection->localAddress().toIpPort() << " status is OFFLINE"
                << std::endl;
      connection->shutdown();
      // _loop->quit();
    }
  }
  // 专门处理用户的读写事件:
  void onMessage(const TcpConnectionPtr &connection, Buffer *buffer,
                 Timestamp timestamp) {
    std::string buf = buffer->retrieveAllAsString();
    std::cout << "recv data: " << buf << "time:" << timestamp.toString()
              << std::endl;
    connection->send(buf);
  }
  TcpServer _server;
  EventLoop *_loop;
};

int main(int argc, char **argv) {
  EventLoop loop; // epoll
  InetAddress addr("127.0.0.1", 6000);
  ChatServer server(&loop, addr, "ChatServer");
  // listenfd epoll_ctl => epoll
  server.start(); 
  // set the event loop to run
  // the same as epoll_wait
  loop.loop();
}