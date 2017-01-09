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

}

bool DbManager::addEntry(const QString &name)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO data (name) VALUES (:name)");
    query.bindValue(":name", name);

    if(query.exec())
        success = true;
    else
        qDebug() << "addEntry Error: " << query.lastError();
    return success;
}

