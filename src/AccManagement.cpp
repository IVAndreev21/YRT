#include "AccManagement.hpp"
namespace YRT
{
	AccManagement::AccManagement()
	{
		con = nullptr;
		pstmt = nullptr;
		driver = nullptr;
		result = nullptr;
	}
	AccManagement::~AccManagement()
	{
	}
	void AccManagement::ConnectToDatabaseServer()
	{
		server = "tcp://sql-900.mysql.database.azure.com:3306";
		username = "sqladmin";
		password = "Homework!";
		try
		{
			driver = get_driver_instance();
			con = driver->connect(server, username, password);
		}
		catch (sql::SQLException e)
		{
			std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
			system("pause");
			exit(1);
		}
	}
	void AccManagement::RegisterAccount(const std::string& email, const std::string& username, const std::string& password)
	{
		try
		{
			con->setSchema("sfml");

			pstmt = con->prepareStatement("INSERT INTO users(email, username, password) VALUES(?,?,?)");
			pstmt->setString(1, email);
			pstmt->setString(2, username);
			pstmt->setString(3, password);
			pstmt->execute();

			std::cout << "Account Registered" << std::endl;
		}
		catch (sql::SQLException& e)
		{
			std::cerr << "Error inserting data: " << e.what() << std::endl;
		}
		delete pstmt;
		delete con;
	}

	// Inside the CheckAccount function definition
	bool AccManagement::VerifyAccount(const std::string& username, const std::string& password)
	{
		try
		{
			con->setSchema("sfml");

			pstmt = con->prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
			pstmt->setString(1, username);
			pstmt->setString(2, password);

			result = pstmt->executeQuery();

			// Check if any result was returned
			return result->next();
		}
		catch (sql::SQLException& e)
		{
			std::cerr << "Error checking account: " << e.what() << std::endl;
			return false; // Return false in case of an exception
		}
		delete pstmt;
	}
}