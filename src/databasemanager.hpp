#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>

class DatabaseManager
{
public:
    DatabaseManager();
    QSqlDatabase getDatabase();
    bool openConnection();
    void closeConnection();
private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_HPP
