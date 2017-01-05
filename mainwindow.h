#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dbmanager.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QKeyEvent>
#include <Qt>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void test();

private slots:

    void on_comboBox_activated(int index);

    void on_saveBtn_clicked();

    void on_changeSettingsBtn_clicked();

    void on_listWidgetMeasure_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    DbManager *db;

    void populateComboBox();

    void toogleInput(bool b);

    void clearInput();

    void printInput();

    void populateListWidget();

    void addChart();
    
protected:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
