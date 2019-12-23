/*
** SoluCache Client by Alessandro Ubriaco
**
** Copyright (c) 2019 Alessandro Ubriaco
**
*/
#include <solucache/client.h>

int main(int argc, char *argv[])
{
  if(argc < 2)
  {
    fprintf(stderr, "Missing parameters.\n");
    return 1;
  }
  std::string action(argv[1]);

  solucache::IClient *client = solucache::createClient();
  if(client->connect("127.0.0.1"))
  {
    fprintf(stdout, "Connected!\n");
    std::vector<unsigned char> data, resp;
    data.push_back(1);

    if(action == "put")
      client->put(argv[2], data);
    else if(action == "get")
    {
      resp = client->get(argv[2]);

      if(resp.size() > 0)
        fprintf(stdout, "Byte %i\n", resp[0]);
      else
        fprintf(stdout, "Not set.\n");
    }
    else if(action == "expires")
      client->expires(argv[2], 5);
    else if(action == "push")
    {
      client->push(argv[2], data);
    }
    else if(action == "pop")
    {
      resp = client->pop(argv[2]);
      if(resp.size() > 0)
        fprintf(stdout, "Byte %i\n", resp[0]);
      else
        fprintf(stdout, "Empty.\n");
    }
  }
  else
    fprintf(stderr, "Failed to connect.\n");
  client->dispose();
}
