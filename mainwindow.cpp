#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"
#include <iostream>
#include <string>
#include <QDebug>
#include <QInputDialog>
#include <QDir>
#include <QHBoxLayout>
#include <QtCharts>

using namespace QtCharts;

void MainWindow::populateComboBox()
{
    ui->comboBox->addItem("Select");
    ui->comboBox->addItem("Squat");
    ui->comboBox->addItem("Deadlift");
    ui->comboBox->addItem("Bench Press");
    ui->comboBox->addItem("OHP");
    ui->comboBox->addItem("Row");
}

void MainWindow::populateListWidget()
{
    ui->listWidgetMeasure->addItem("Bicep L");
    ui->listWidgetMeasure->addItem("Bicep R");
    ui->listWidgetMeasure->addItem("Body Fat");
    ui->listWidgetMeasure->addItem("Hips");
    ui->listWidgetMeasure->addItem("Lean Mass");
    ui->listWidgetMeasure->addItem("Thigh L");
    ui->listWidgetMeasure->addItem("Thigh R");
    ui->listWidgetMeasure->addItem("Weight");
    ui->listWidgetMeasure->addItem("Waist");
}

void MainWindow::addChart()
{
    QHBoxLayout *hbox = new QHBoxLayout();
    QLineSeries *series = new QLineSeries();
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    hbox->addWidget(chartView);
    ui->tab_stat->setLayout(hbox);
}

void MainWindow::populateCalculateLst()
{
    ui->cal_menu_lst->addItem("BMR/TDEE");
    ui->cal_menu_lst->addItem("BMI");
}

void MainWindow::populateBmrGender()
{
    ui->bmr_gender->addItem("Man");
    ui->bmr_gender->addItem("Woman");
}

void MainWindow::populateBmrActivity()
{
    ui->bmr_activity->addItem("Little or no exercise");
    ui->bmr_activity->addItem("Light exercise");
    ui->bmr_activity->addItem("Moderate exercise");
    ui->bmr_activity->addItem("Hard exercise");
    ui->bmr_activity->addItem("Very hard exercise");
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    db = new DbManager("lifts.db");
    ui->setupUi(this);

    populateBmrActivity();
    populateBmrGender();
    populateCalculateLst();
    addChart();
    populateComboBox();
    populateListWidget();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearInput()
{
    ui->lineEditReps->clear();
    ui->lineEditSets->clear();
    ui->lineEditWeight->clear();
    ui->comboBox->clear();
}

void MainWindow::printInput()
{
    qDebug() << ui->calendarWidget->selectedDate().toString("ddMMyyyy");
    qDebug() << ui->comboBox->currentText();
    qDebug() << ui->lineEditWeight->text();
    qDebug() << ui->lineEditReps->text();
    qDebug() << ui->lineEditSets->text();
}

void MainWindow::on_saveBtn_clicked()
{
     ui->statusBar->showMessage("Saving lift...",1000);
     db->addEntry("Christian");
     printInput();
     clearInput();
     populateComboBox();
     toogleInput(false);

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //Check active tab
    switch(ui->tabWidget->currentIndex()){
    case 0:
        if (event->key() == Qt::Key_Return)
            emit on_saveBtn_clicked();
        break;
    case 1:
        //Free slot
        break;
    case 2:
        //Free slot
        break;
    case 3:
        //Free slot
    default:
        break;
    }
}

void MainWindow::toogleInput(bool b)
{
    ui->lineEditReps->setEnabled(b);
    ui->lineEditSets->setEnabled(b);
    ui->lineEditWeight->setEnabled(b);
    ui->saveBtn->setEnabled(b);
}

void MainWindow::on_comboBox_activated(int index)
{
    qDebug() << index;
    if (index != 0)
       toogleInput(true);
}

void MainWindow::on_listWidgetMeasure_doubleClicked(const QModelIndex &index)
{
    bool ok;
    int i = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"),
                                     tr("Value:"), 25, 0, 500, 1, &ok);
    if (ok)
        qDebug() << index.row() << i;
}

bool MainWindow::isComplete(int calculator)
{
    switch(calculator){
    case 0:
        if (ui->bmr_cm_in->text().isEmpty() && ui->bmr_kg_in->text().isEmpty()) {
            ui->statusBar->showMessage(error_codes[ENTER_KG_CM]);
            return false;
        }
        else if (ui->bmr_cm_in->text().isEmpty()) {
            ui->statusBar->showMessage(error_codes[ENTER_CM]);
            return false;
        }
        else if (ui->bmr_kg_in->text().isEmpty()) {
            ui->statusBar->showMessage(error_codes[ENTER_KG]);
            return false;
        }
        else {
            return true;
        }
        break;
    case 1:
        if (ui->bmi_cm_in->text().isEmpty() && ui->bmi_kg_in->text().isEmpty()) {
            ui->statusBar->showMessage(error_codes[ENTER_KG_CM]);
            return false;
        }
        else if (ui->bmi_cm_in->text().isEmpty()) {
            ui->statusBar->showMessage(error_codes[ENTER_CM]);
            return false;
        }
        else if (ui->bmi_kg_in->text().isEmpty()) {
            ui->statusBar->showMessage(error_codes[ENTER_KG]);
            return false;
        }
        else {
            return true;
        }
        break;
    default:
        return false;
    }
}

void MainWindow::on_bmiBtn_clicked()
{
    float bmi_m, bmi_cm, bmi_kg, bmi_res;
    QString str_res;

    if (isComplete(fit.BMI)) {
        ui->statusBar->clearMessage();
        bmi_cm = ui->bmi_cm_in->text().toFloat();
        bmi_kg = ui->bmi_kg_in->text().toFloat();
        bmi_m = bmi_cm / 100;
        bmi_res = fit.bmiCalc(bmi_m, bmi_kg);
        str_res = QString::number(bmi_res);
        ui->bmi_res_out->setText("Your BMI is: " + str_res);
    }

}

void MainWindow::setActivityLevel(float &cal_need, float bmr_res)
{
    switch(ui->bmr_activity->currentIndex()){
    case 0: cal_need = bmr_res * 1.2; break;
    case 1: cal_need = bmr_res * 1.375; break;
    case 2: cal_need = bmr_res * 1.55; break;
    case 3: cal_need = bmr_res * 1.725; break;
    case 4: cal_need = bmr_res * 1.9; break;
    default:
        break;
    }
}

void MainWindow::on_bmrBtn_clicked()
{
    float bmr_cm = 0, bmr_kg = 0, bmr_age = 0, bmr_res = 0, cal_need = 0;
    QString str_res, cal_res;

    if (isComplete(fit.BMR)) {
        ui->statusBar->clearMessage();
        bmr_cm = ui->bmr_cm_in->text().toFloat();
        bmr_kg = ui->bmr_kg_in->text().toFloat();
        bmr_age = !ui->bmr_age_in->text().isEmpty() ? ui->bmr_age_in->text().toFloat() : 30;

        bmr_res = ui->bmr_gender->currentIndex() == 1 ?
                   fit.bmrCalc(bmr_cm, bmr_kg,bmr_age,1) :
                    fit.bmrCalc(bmr_cm, bmr_kg,bmr_age);

        setActivityLevel(cal_need, bmr_res);
        str_res = QString::number(bmr_res);
        cal_res = QString::number(cal_need);
        ui->bmr_res_out->setText("Your BMR is: " + str_res + "\nCalorie need: " + cal_res);
    }
}

void MainWindow::on_cal_menu_lst_clicked(const QModelIndex &index)
{
    qDebug() << index.row();
    ui->stackedWidget->setCurrentIndex(index.row());
}
