#include "../inc/GameEngine.hpp"
using namespace std;

int main(int argc, char* argv[])
{

	unique_ptr<GameEngine> engine = make_unique<GameEngine>(10000);
	engine->MainGameLoop();

	/*auto engine = make_unique<Engine>(10000);
	engine->MainGameLoop();*/

	return 0;
}
