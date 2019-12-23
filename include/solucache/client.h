#ifndef __SOLUCACHE_CLIENT_INCLUDED__
#define __SOLUCACHE_CLIENT_INCLUDED__
#include <string>
#include <vector>

namespace solucache
{
  class IClient
  {
  public:
    virtual bool connect(const std::string& host, int port = 18001) = 0;
    virtual void put(const std::string& key, std::vector<unsigned char>& data) = 0;
    virtual std::vector<unsigned char> get(const std::string& key) = 0;
    virtual void expires(const std::string& key, time_t t) = 0;
    virtual void push(const std::string& key, std::vector<unsigned char>& data) = 0;
    virtual std::vector<unsigned char> pop(const std::string& key) = 0;
    virtual void dispose() = 0;
  };

  IClient *createClient();
}

#endif
