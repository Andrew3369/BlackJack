#pragma once
#include "../inc/GameEngine.hpp"


class AuthSystem 
{
private:
    Aws::DynamoDB::DynamoDBClient* m_client;
    const char* TABLE_NAME = "BlackjackUsers";

public:
    AuthSystem(Aws::DynamoDB::DynamoDBClient* client) : m_client(client) {}

	bool TestDBConnection();

    bool Login();
    bool Register();
};