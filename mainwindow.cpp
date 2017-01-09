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
    ui->cal_menu_lst->addItem("BMR");
    ui->cal_menu_lst->addItem("BMI");
    ui->cal_menu_lst->addItem("TDDE");
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    db = new DbManager("lifts.db");
    ui->setupUi(this);
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




void MainWindow::on_changeSettingsBtn_clicked()
{

}

void MainWindow::on_listWidgetMeasure_doubleClicked(const QModelIndex &index)
{
    bool ok;
    int i = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"),
                                     tr("Value:"), 25, 0, 500, 1, &ok);
    if (ok)
        qDebug() << index.row() << i;
}

void MainWindow::on_bmiBtn_clicked()
{
    float bmi_m, bmi_cm, bmi_kg, bmi_res;
    QString str_res;

    if (ui->bmi_cm_in->text().isEmpty() && ui->bmi_kg_in->text().isEmpty())
        ui->statusBar->showMessage(error_codes[ENTER_KG_CM]);
    else if (ui->bmi_cm_in->text().isEmpty())
        ui->statusBar->showMessage(error_codes[ENTER_CM]);
    else if (ui->bmi_kg_in->text().isEmpty())
        ui->statusBar->showMessage(error_codes[ENTER_KG]);
    else{
        ui->statusBar->clearMessage();
        bmi_cm = ui->bmi_cm_in->text().toFloat();
        bmi_kg = ui->bmi_kg_in->text().toFloat();
        bmi_m = bmi_cm / 100;
        bmi_res = bmi_calculate(bmi_m, bmi_kg);
        str_res = QString::number(bmi_res);
        ui->bmi_res_out->setText("Your BMI is: " + str_res);
    }
}

float MainWindow::bmi_calculate(float cm_len, float kg_am)
{
    return (kg_am / (cm_len * cm_len));
}

void MainWindow::on_bmrBtn_clicked()
{

}

void MainWindow::on_cal_menu_lst_clicked(const QModelIndex &index)
{
    qDebug() << index.row();
    ui->stackedWidget->setCurrentIndex(index.row());
}
