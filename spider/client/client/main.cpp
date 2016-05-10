#include	<sstream>
#include	"Core.h"

int			main(void)
{
	try {
		Core core("127.0.0.1", 4241);
		core.initialize();
		core.loop();
	}
	catch (const std::exception &msg) {
		std::cerr << msg.what() << std::endl;
		getchar();
		return 1;
	}
	getchar();
	return 0;
}