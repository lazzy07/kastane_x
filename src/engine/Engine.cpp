#include <httplib/httplib.h>
#include "Engine.hpp"

void KX::Engine::Engine::PrintWelcomeScreen()
{
  std::cout << "\n***********************************************************************\n" << std::endl;
  std::cout << m_Banner << std::endl;
  std::cout << "\nCreated by @lazzy07 (https://www.github.com/lazzy07)" << std::endl;
  std::cout << "***********************************************************************\n" << std::endl;
}

void KX::Engine::Engine::StartServer(std::string server, int port)
{
  httplib::Server svr;

  svr.Get("/hello", [](const httplib::Request&, httplib::Response& res) {
      res.set_content("Hello from Kastane‑X!", "text/plain");
  });

  std::cout << "HTTP server listening on " + server + ":" + std::to_string(port) << std::endl;
  svr.listen("0.0.0.0", 8080);
}