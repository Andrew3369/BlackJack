#include "../inc/AuthSystem.hpp"
using namespace std;

bool AuthSystem::TestDBConnection()
{
    Aws::DynamoDB::DynamoDBClient dynamoClient;
    Aws::DynamoDB::Model::ListTablesRequest request;
    auto outcome = dynamoClient.ListTables(request);

    if (!outcome.IsSuccess()) 
    {
        cout << "Failed to connect to DynamoDB: " << outcome.GetError().GetMessage() << std::endl;
        return false;
    }
    //cout << "Successfully connected to DynamoDB!" << std::endl;
    return true;
}

bool AuthSystem::Login()
{
    if (!m_client)
    {
        cout << "Client not initialized\n";
        return false;
    }

    if (!TestDBConnection()) 
    {
        std::cout << "Unable to connect to DynamoDB. Please check your AWS configuration." << std::endl;
        return false;
    }

    string username, password; 
    cout << "Username: ";
    cin >> username;
	if (cin.fail()) //handle any bad input
    {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }

    cout << "Password: "; cin >> password;
	if (cin.fail()) //handle any bad input
    {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }

	// Query DynamoDB for user
    Aws::DynamoDB::Model::GetItemRequest request;
    request.SetTableName(TABLE_NAME);

	// Set the key
    Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue> key;
    key.emplace("UserID", Aws::DynamoDB::Model::AttributeValue().SetS(username.c_str()));
    request.SetKey(move(key));

    auto outcome = m_client->GetItem(request);
    if (!outcome.IsSuccess()) 
    {
        cout << "Failed to query DynamoDB: " << outcome.GetError().GetMessage() << endl;
        return false;
    }

    const auto& item = outcome.GetResult().GetItem();
    if (item.empty()) 
    {
        cout << "User not found.\n";
        return false;
    }

    auto passwordIter = item.find("password");
    if (passwordIter == item.end()) 
    {
        cout << "Invalid user data.\n";
        return false;
    }


    const Aws::String& storedPassword = passwordIter->second.GetS();
    return (storedPassword == password.c_str());
}

bool AuthSystem::Register() 
{
    if (!m_client)
    {
        cout << "Client not initialized\n";
        return false;
    }

    if (!TestDBConnection())
    {
        std::cout << "Unable to connect to DynamoDB. Please check your AWS configuration." << std::endl;
        return false;
    }


    string username, password;
    cout << "Create username: "; cin >> username;
    if (cin.fail()) 
    {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }

    cout << "Create password: "; cin >> password;
    if (cin.fail()) 
    {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }

    Aws::DynamoDB::Model::PutItemRequest request;
    request.SetTableName(TABLE_NAME);

    Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue> item;
    item.emplace("UserID", Aws::DynamoDB::Model::AttributeValue().SetS(username.c_str()));
    item.emplace("password", Aws::DynamoDB::Model::AttributeValue().SetS(password.c_str()));
    //item.emplace("chips", Aws::DynamoDB::Model::AttributeValue().SetN("10000"));
    request.SetItem(move(item));

    auto outcome = m_client->PutItem(request);
    if (!outcome.IsSuccess()) 
        cout << "Failed to register: " << outcome.GetError().GetMessage() << endl; return false;

    cout << "Registration successful!\n";
    return true;
}
