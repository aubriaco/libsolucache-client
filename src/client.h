/*
** SoluCache Client by Alessandro Ubriaco
**
** Copyright (c) 2019 Alessandro Ubriaco
**
*/
#ifndef __CLIENT_INCLUDED__
#define __CLIENT_INCLUDED__
#include <solunet.h>
#include <solucache/client.h>

namespace solucache
{
  class CClient : public IClient
  {
  private:
    solunet::ISocket *Socket;
  public:
    CClient() {}
    ~CClient();

    bool connect(const std::string& host, int port = 18001);
    void put(const std::string& key, std::vector<unsigned char>& data);
    std::vector<unsigned char> get(const std::string& key);
    void expires(const std::string& key, time_t t);
    void push(const std::string& key, std::vector<unsigned char>& data);
    std::vector<unsigned char> pop(const std::string& key);
    void dispose();
  };
}

#endif
