#include "dbmanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
        qDebug() << "Error: connection with database failed";
    else
        qDebug() << "Database: connection ok";
}

DbManager::~DbManager()
{

    if (m_db.isOpen())
        m_db.close();

}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

bool DbManager::createTable()
{

}

bool DbManager::addEntry(const int date, const QString &exercise, const int reps, const int sets, const float weight)
{

}

bool DbManager::removeEntry(const int date)
{

}

bool DbManager::entryExists(const int date) const
{

}

void DbManager::printDatabase() const
{

}

bool DbManager::removeAllEntrys()
{

}
