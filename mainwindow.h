#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chart.h"
#include "chartview.h"
#include "dbmanager.h"
#include "fitnesscalculator.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QKeyEvent>
#include <Qt>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QDateTimeAxis>

QT_CHARTS_USE_NAMESPACE

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

    void on_exerciseBox_activated(int index);

    void on_saveBtn_clicked();

    void on_listWidgetMeasure_doubleClicked(const QModelIndex &index);

    void on_bmiBtn_clicked();

    void on_bmrBtn_clicked();

    void on_cal_menu_lst_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    FitnessCalculator fit;
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
        "Please enter lenght and weight",
        "Please enter lenght",
        "Please enter weight"
    };

    DbManager *db;

    QLineSeries *squatSeries, *deadSeries,
    *benchSeries, *ohpSeries, *rowSeries,
    *weightSeries;

    ChartView *chartView;

    QDateTimeAxis *axisX;

    QValueAxis *axisY;

    float bmi_calculate(float cm_len, float kg_am);

    float bmr_calculate(float cm_len, float kg_am, int age, int gender = 0);

    void populateExerciseBox();

    void toogleInput(bool b);

    void clearInput();

    void printInput();

    void populateListWidget();

    void addChart();

    void populateCalculateLst();
    
    void populateBmrGender();

    void populateBmrActivity();

    void setActivityLevel(float &cal_need, float bmr_res);

    bool isComplete(int calculator);

    void updateChart(QLineSeries *serie);

    void updateAllCharts();

    void changeSeries(QLineSeries *serie, const QString &date, const float weight);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
