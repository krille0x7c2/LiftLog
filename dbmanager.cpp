#include "dbmanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

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

    if (!entryDuplicate(date,exercise)){
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
    } else {
        if (updateEntry(date, exercise, reps, sets, weight))
            is_success = true;
    }
    return is_success;
}

bool DbManager::removeEntry(const QString &date)
{
    bool is_success = false;

    if (entryExists(date)) {
        QSqlQuery query;
        query.prepare("DELETE FROM data WHERE date = (:date)");
        query.bindValue(":date", date);
        is_success = query.exec();

        if (!is_success)
            qDebug() << "entry deletion failed: " << query.lastError();
    } else {
        qDebug() << "entry deletion failed: entry dosent exist";
    }
    return is_success;

}

bool DbManager::entryExists(const QString &date) const
{
    bool exists = false;

    QSqlQuery query;
    query.prepare("SELECT date FROM data WHERE date = (:date)");
    query.bindValue(":date", date);

    if (query.exec()) {
        if (query.next())
            exists = true;
    } else {
        qDebug() << "entry exists failed: " << query.lastError();
    }
    return exists;
}

bool DbManager::entryDuplicate(const QString &date, const QString &exercise) const
{
    bool duplicate = false;

    QSqlQuery query;
    query.prepare("SELECT date, exercise FROM data WHERE date = (:date) AND exercise = (:exercise)");
    query.bindValue(":date", date);
    query.bindValue(":exercise", exercise);

    if (query.exec()) {
        if (query.next())
            duplicate = true;
    } else {
        qDebug() << "entry exists failed: " << query.lastError();
    }
    return duplicate;
}

bool DbManager::updateEntry(const QString &date, const QString &exercise, const int reps, const int sets, const float weight)
{
    bool success = false;

    QSqlQuery query;
    query.prepare("UPDATE data SET reps=:reps, sets=:sets, weight=:weight WHERE date =:date AND exercise =:exercise");
    query.bindValue(":reps", reps);
    query.bindValue(":sets", sets);
    query.bindValue(":weight", weight);
    query.bindValue(":date", date);
    query.bindValue(":exercise", exercise);

    if (query.exec())
        success = true;
    else
        qDebug() << "update failed: " << query.lastError();
    return success;
}

void DbManager::printDatabase() const
{
    qDebug() << "Entries in db:";
    QSqlQuery query("SELECT * FROM data");
    int idDate = query.record().indexOf("date");
    int idExercise = query.record().indexOf("exercise");
    int idReps = query.record().indexOf("reps");
    int idSets = query.record().indexOf("sets");
    int idWeight = query.record().indexOf("weight");

    while(query.next()) {
        QString date = query.value(idDate).toString();
        QString exercise = query.value(idExercise).toString();
        QString sets = query.value(idReps).toString();
        QString reps = query.value(idSets).toString();
        QString weight = query.value(idWeight).toString();
        qDebug() << "===" << date << exercise << sets << reps << weight;
    }
}

bool DbManager::removeAllEntries()
{
    bool success = false;

    QSqlQuery query;
    query.prepare("DELETE FROM data");

    if (query.exec())
        success = true;
    else
        qDebug() << "remove all entries failed: " << query.lastError();
    return success;
}
