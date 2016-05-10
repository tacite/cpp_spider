//
// main.cpp for main.cpp in /home/beauraF/Documents/Epitech/TEK3/CPP/cpp_spider/spider/server/src
//
// Made by Florent BEAURAIN
// Login   <beauraF@epitech.net>
//
// Started on  Sun Oct 18 18:30:11 2015 Florent BEAURAIN
// Last update Sun Oct 18 18:30:23 2015 Florent BEAURAIN
//

#include      "Server.hpp"

int           main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage : ./server <port>" << std::endl;
    return 1;
   }

   Server		server;

	try {
		server.init(argv[1]);
		server.run();
  }
  catch (const std::exception &e) {
    	std::cerr << e.what() << std::endl;
    	return 1;
  }
}
