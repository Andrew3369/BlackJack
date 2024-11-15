#include "../inc/GameEngine.hpp"
using namespace std;


int main(int argc, char* argv[])
{
	Aws::SDKOptions options;
    try
    {
        Aws::InitAPI(options);
        {
            auto client = std::make_unique<Aws::DynamoDB::DynamoDBClient>();
            AuthSystem auth(client.get());  // Pass pointer to client

            bool loggedIn = false;
            while (!loggedIn)
            {
                cout << "1. Login\n2. Register\n3. Exit\nChoice: ";
                int choice;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    cout << "Attempting login...\n";
                    loggedIn = auth.Login();
                    cout << "Login result: " << (loggedIn ? "success" : "failed") << endl;
                    break;
                case 2:
                    if (auth.Register())
                    {
                        std::cout << "Please login with your new credentials.\n";
                        cout << "Registered result: " << (auth.Register() ? "success" : "failed") << endl;
                    }
                    break;
                case 3:
                    Aws::ShutdownAPI(options); return 0;

                default: std::cout << "Invalid choice.\n";
                }
            }
        }
    }
    catch (exception error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
        Aws::ShutdownAPI(options);
        //return ERROR;
        return -1;
    }

    // once logged in, start the game !!!! :D
	system("clear");
	unique_ptr<GameEngine> engine = make_unique<GameEngine>(10000);
    engine->MainDisplayPrint();
	engine->MainGameLoop();

	return 0;
}
