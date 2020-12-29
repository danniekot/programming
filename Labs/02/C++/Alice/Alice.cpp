#include <iostream>
#include <fstream>
#include "cpp-httplib/httplib.h"
using namespace httplib;

void webhooks_get(const Request& req, Response& res);
void webhooks_post(const Request& req, Response& res);
void yandex_hook(const Request& req, Response& res);

int main() {
	Server srv;
	srv.Get("/webhooks", webhooks_get);
	srv.Post("/webhooks", webhooks_post);
	srv.Post("/yandex_hook", yandex_hook);
<<<<<<< HEAD
	srv.listen("localhost", 3000);
=======
	srv.listen("localhost", 1234);
>>>>>>> ae1dae6fe2dbfacb351d51a981dff3691550d403
}