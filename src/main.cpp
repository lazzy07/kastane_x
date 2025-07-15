#include <iostream>
#include <httplib/httplib.h>

int main(){

  std::cout << "================== Kastane-X Engine Started ==================" << std::endl;
  
  httplib::Server svr;

  svr.Get("/hello", [](const httplib::Request&, httplib::Response& res) {
      res.set_content("Hello from Kastane‑X!", "text/plain");
  });

  std::cout << "HTTP server listening on 0.0.0.0:8080" << std::endl;
  svr.listen("0.0.0.0", 8080);
}


