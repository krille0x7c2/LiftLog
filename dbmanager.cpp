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
    bool is_success = true;

    QSqlQuery query;
    query.prepare("CREATE TABLE data(id INTEGER PRIMARY KEY, date TEXT, exercise TEXT, reps INTEGER, sets INTEGER, weight REAL);");

    if (!query.exec()){
        qDebug() << "Couldn't create tabel 'data' one might already exist.";
        is_success = false;
    }
    return is_success;
}

bool DbManager::addEntry(const QString &date, const QString &exercise, const int reps, const int sets, const float weight)
{
    bool is_success = false;

    if (!date.isEmpty()) {
        QSqlQuery query;
        query.prepare("INSERT INTO data (date, exercise, reps, sets ,weight) VALUES (:date, :exercise, :reps, :sets, :weight)");
        query.bindValue(":date", date);
        query.bindValue(":exercise", exercise);
        query.bindValue(":reps", reps);
        query.bindValue(":sets", sets);
        query.bindValue(":weight", weight);

        if (query.exec())
            is_success = true;
        else
            qDebug() << "new entry failed: " << query.lastError();
    } else {
        qDebug() << "new entry failed date cannot be empty";
    }
    return is_success;
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
