#include "client.h"

namespace solucache
{
  std::string readKey(solusek::INetHandlerSocket *socket)
  {
  	std::string key;
  	size_t sz = 0;
  	socket->readBuffer(&sz, 8);
  	for(size_t n = 0; n < sz; n++)
  	{
  		char c;
  		socket->readBuffer(&c, 1);
  		key.push_back(c);
  	}
  	return key;
  }

  std::vector<unsigned char> readData(solusek::INetHandlerSocket *socket)
  {
  	std::vector<unsigned char> data;
  	size_t sz = 0;
  	socket->readBuffer(&sz, 8);
    if(sz > 0)
    {
      data.reserve(sz);
      for(size_t n = 0; n < sz; n++)
      {
     	 unsigned char c;
     	 socket->readBuffer(&c, 1);
     	 data.push_back(c);
      }
    }
  	return data;
  }

  void writeAction(solusek::INetHandlerSocket *socket, int action)
  {
    socket->writeBuffer(&action, 4);
  }

  void writeKey(solusek::INetHandlerSocket *socket, std::string data)
  {
  	size_t sz = data.size();
  	socket->writeBuffer(&sz, 8);
  	for(std::string::iterator it = data.begin(); it != data.end(); ++it)
  	{
  		socket->writeBuffer(&(*it), 1);
  	}
  }

  void writeData(solusek::INetHandlerSocket *socket, std::vector<unsigned char>& data)
  {
  	size_t sz = data.size();
  	socket->writeBuffer(&sz, 8);
  	for(std::vector<unsigned char>::iterator it = data.begin(); it != data.end(); ++it)
  	{
  		socket->writeBuffer(&(*it), 1);
  	}
  }

  CClient::~CClient()
  {
    Socket->dispose();
  }

  bool CClient::connect(const std::string& host, int port)
  {
    Socket = solusek::createNetHandlerSocket();
    return Socket->connect(host.c_str(), port);
  }

  void CClient::put(const std::string& key, std::vector<unsigned char>& data)
  {
    writeAction(Socket, 1);
    writeKey(Socket, key);
    writeData(Socket, data);
  }

  std::vector<unsigned char> CClient::get(const std::string& key)
  {
    writeAction(Socket, 2);
    writeKey(Socket, key);
    return readData(Socket);
  }

  void CClient::expires(const std::string& key, time_t t)
  {
    writeAction(Socket, 5);
    writeKey(Socket, key);
    Socket->writeBuffer(&t, 8);
  }

  void CClient::dispose()
  {
    delete this;
  }

  IClient *createClient()
  {
    return new CClient();
  }
}
