#include "../inc/GameEngine.hpp"
using namespace std;


int main(int argc, char* argv[])
{
    Aws::SDKOptions options;
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
                cout << "debugging\n";
                loggedIn = auth.Login(); break;
            case 2:
                cout << "debugging\n";
                if (auth.Register())
                {
                    std::cout << "Please login with your new credentials.\n";
                }
                break;
            case 3:
                Aws::ShutdownAPI(options); return 0;

            default: std::cout << "Invalid choice.\n";
            }
        }
    }
	Aws::ShutdownAPI(options);
    //try
    //{
    //    Aws::InitAPI(options);
    //    {
    //        auto client = std::make_unique<Aws::DynamoDB::DynamoDBClient>();
    //        AuthSystem auth(client.get());  // Pass pointer to client

    //        bool loggedIn = false;
    //        while (!loggedIn)
    //        {
    //            cout << "1. Login\n2. Register\n3. Exit\nChoice: ";
    //            int choice;
    //            cin >> choice;
    //            switch (choice)
    //            {
    //            case 1:
    //                cout << "hi\n";
    //                loggedIn = auth.Login(); break;
    //            case 2:
    //                if (auth.Register())
    //                {
    //                    std::cout << "Please login with your new credentials.\n";
    //                }
    //                break;
    //            case 3:
    //                Aws::ShutdownAPI(options); return 0;

    //            default: std::cout << "Invalid choice.\n";
    //            }
    //        }
    //    }
    //}
    //catch (_exception error)
    //{
    //    std::cerr << "Error: " << error.what() << std::endl;
    //    Aws::ShutdownAPI(options);
    //    return ERROR;
    //}

    // once logged in, start the game !!!! :D
	unique_ptr<GameEngine> engine = make_unique<GameEngine>(10000);
	engine->MainGameLoop();

	return 0;
}
