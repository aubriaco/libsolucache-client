#ifndef __CLIENT_INCLUDED__
#define __CLIENT_INCLUDED__
#include <solusek/solusek.h>
#include <solucache/client.h>

namespace solucache
{
  class CClient : public IClient
  {
  private:
    solusek::INetHandlerSocket *Socket;
  public:
    CClient() {}
    ~CClient();

    bool connect(const std::string& host, int port = 18001);
    void put(const std::string& key, std::vector<unsigned char>& data);
    std::vector<unsigned char> get(const std::string& key);
  };
}

#endif
