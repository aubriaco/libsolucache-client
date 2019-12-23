#include <solucache/client.h>

int main(int argc, char *argv[])
{
  solucache::IClient *client = solucache::createClient();
  if(client->connect("127.0.0.1"))
  {
    fprintf(stdout, "Connected!\n");
    std::vector<unsigned char> data, resp;
    data.push_back(1);
    client->put("test", data);

    resp = client->get("test");

    client->expires("test", 5);

    if(resp.size() > 0)
      fprintf(stdout, "Byte %i\n", resp[0]);
    else
      fprintf(stdout, "Error getting test.\n");
  }
  else
    fprintf(stderr, "Failed to connect.\n");
  client->dispose();
}
