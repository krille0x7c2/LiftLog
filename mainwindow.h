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

    void on_bmiBtn_clicked();

    void on_bmrBtn_clicked();

    void on_cal_menu_lst_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    enum FAILCODES {
        ENTER_KG_CM = 0,
        ENTER_CM = 1,
        ENTER_KG = 2,
    };

    enum GENDER {
        MAN = 0,
        WOMAN = 1,
    };

    QString error_codes[10] = {
        "BMI ERROR: Missing lenght and weight",
        "BMI ERROR: Missing lenght",
        "BMI ERROR: Missign weight"
    };

    DbManager *db;

    float bmi_calculate(float cm_len, float kg_am);

    float bmr_calculate(float cm_len, float kg_am, int age, int gender = 0);

    void populateComboBox();

    void toogleInput(bool b);

    void clearInput();

    void printInput();

    void populateListWidget();

    void addChart();

    void populateCalculateLst();
    
    void populateBmrGender();

    void populateBmrActivity();

    void setActivityLevel(float &cal_need, float bmr_res);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
