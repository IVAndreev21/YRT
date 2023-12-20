#pragma once
#include "pch.hpp"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

namespace YRT
{
	class AccManagement
	{
	public:

		void ConnectToDatabaseServer();
		void RegisterAccount(const std::string& email, const std::string& username, const std::string& password);

		bool VerifyAccount(const std::string& username, const std::string& password);
		AccManagement();
		~AccManagement();
	private:
		sql::Driver* driver;
		sql::Connection* con;
		sql::PreparedStatement* pstmt;
		sql::ResultSet* result;

		std::string server;
		std::string username;
		std::string password;
	};
}