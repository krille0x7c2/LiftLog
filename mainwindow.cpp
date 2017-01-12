#include "chart.h"
#include "chartview.h"
#include "lift.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"
#include <iostream>
#include <string>
#include <QDebug>
#include <QInputDialog>
#include <QDir>
#include <QHBoxLayout>
#include <QList>
#include <QDateTime>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>

void MainWindow::populateExerciseBox()
{
    ui->exerciseBox->addItem("Select");
    ui->exerciseBox->addItem("Squat");
    ui->exerciseBox->addItem("Deadlift");
    ui->exerciseBox->addItem("Bench Press");
    ui->exerciseBox->addItem("OHP");
    ui->exerciseBox->addItem("Row");
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

void MainWindow::initChart()
{
    chart = new Chart();
    chartView = new ChartView(chart, this);
    QGridLayout *c_layout = new QGridLayout();
    c_layout->addWidget(chartView, 0, 1, 3, 1);
    ui->tab_stat->setLayout(c_layout);

    //TODO add series
    addSeries();
    addSeries();
    addSeries();
    addSeries();
    addSeries();

    //Set title and misc settings
    chart->setTitle("Weight progression");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView->setRenderHint(QPainter::Antialiasing);
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

    exerciseLst << "Squat" << "Deadlift" << "Bench Press" << "OHP" << "Row";
    dbManager = new DbManager("lifts.db");

    if (dbManager->isOpen()) {
        dbManager->createTable();
    }
    ui->setupUi(this);

    populateBmrActivity();
    populateBmrGender();
    populateCalculateLst();
    initChart();
    populateExerciseBox();
    populateListWidget();
}


MainWindow::~MainWindow()
{
    delete dbManager;
    delete ui;
}

void MainWindow::clearInput()
{
    ui->lineEditReps->clear();
    ui->lineEditSets->clear();
    ui->lineEditWeight->clear();
    ui->exerciseBox->clear();
}

void MainWindow::printInput()
{
    qDebug() << ui->calendarWidget->selectedDate().toString("ddMMyyyy");
    qDebug() << ui->exerciseBox->currentText();
    qDebug() << ui->lineEditWeight->text();
    qDebug() << ui->lineEditReps->text();
    qDebug() << ui->lineEditSets->text();
}

void MainWindow::toogleInput(bool b)
{
    ui->lineEditReps->setEnabled(b);
    ui->lineEditSets->setEnabled(b);
    ui->lineEditWeight->setEnabled(b);
    ui->saveBtn->setEnabled(b);
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

void MainWindow::addSeries()
{
    QLineSeries *series = new QLineSeries();
    exerciseSeries.append(series);

    series->setName(exerciseLst.at(exerciseSeries.count() - 1));

    QString exercise = exerciseLst.at(exerciseSeries.count() - 1);
    QList<Lift *> lst = dbManager->getExerciseData(exercise);
    QList<QPointF> data;
    if (!lst.isEmpty()) {
        foreach (Lift *d, lst) {
            data.append(QPointF(convertStrToDateTime(d->getDate()).toMSecsSinceEpoch(), d->getWeight()));
        }
    }

    series->append(data);
    chart->addSeries(series);

    //Ignore all but first series
    if (exerciseSeries.count() == 1) {
        //Add X axis as dates
        axisX = new QDateTimeAxis;
        axisX->setTickCount(10);
        axisX->setFormat("dd MMM yyyy");
        axisX->setTitleText("Date");
        //Add Y axis as integers
        axisY = new QValueAxis;
        axisY->setTickCount(5);
        axisY->setLabelFormat("%i");
        axisY->setTitleText("Kg");
        //Set the axis in place
        chart->addAxis(axisX, Qt::AlignBottom);
        chart->addAxis(axisY, Qt::AlignLeft);
    }
    //Attach axis to each series
    series->attachAxis(axisX);
    series->attachAxis(axisY);
}

void MainWindow::removeSeries()
{
    //Remove the last series from chart
    if (exerciseSeries.count() > 0) {
        QLineSeries *series = exerciseSeries.last();
        chart->removeSeries(series);
        exerciseSeries.removeLast();
        delete series;
    }
}

void MainWindow::updateSeries(const QString &exercise, const QString &d, float w)
{
    foreach (QLineSeries *s, exerciseSeries) {
       if ( exercise == s->name()) {
           s->append(QPointF(convertStrToDateTime(d).toMSecsSinceEpoch(), w));
           chartView->update();
       }
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

void MainWindow::on_saveBtn_clicked()
{
    int reps, sets;
    float weight;
    QString date, exercise;

    date = ui->calendarWidget->selectedDate().toString("ddMMyyyy");
    exercise = ui->exerciseBox->currentText();
    reps = ui->lineEditReps->text().toInt();
    sets = ui->lineEditSets->text().toInt();
    weight = ui->lineEditWeight->text().toFloat();

    ui->statusBar->showMessage("Saving lift...",1000);
    dbManager->addEntry(date, exercise, reps, sets, weight);
    dbManager->printDatabase();
    clearInput();
    populateExerciseBox();
    toogleInput(false);
    updateSeries(exercise, date, weight);
}

void MainWindow::on_exerciseBox_activated(int index)
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

void MainWindow::on_bmiBtn_clicked()
{
    float bmi_m, bmi_cm, bmi_kg, bmi_res;
    QString str_res;

    if (isComplete(fitnessCalculator.BMI)) {
        ui->statusBar->clearMessage();
        bmi_cm = ui->bmi_cm_in->text().toFloat();
        bmi_kg = ui->bmi_kg_in->text().toFloat();
        bmi_m = bmi_cm / 100;
        bmi_res = fitnessCalculator.bmiCalc(bmi_m, bmi_kg);
        str_res = QString::number(bmi_res);
        ui->bmi_res_out->setText("Your BMI is: " + str_res);
    }

}

void MainWindow::on_bmrBtn_clicked()
{
    float bmr_cm = 0, bmr_kg = 0, bmr_age = 0, bmr_res = 0, cal_need = 0;
    QString str_res, cal_res;

    if (isComplete(fitnessCalculator.BMR)) {
        ui->statusBar->clearMessage();
        bmr_cm = ui->bmr_cm_in->text().toFloat();
        bmr_kg = ui->bmr_kg_in->text().toFloat();
        bmr_age = !ui->bmr_age_in->text().isEmpty() ? ui->bmr_age_in->text().toFloat() : 30;

        bmr_res = ui->bmr_gender->currentIndex() == 1 ?
                   fitnessCalculator.bmrCalc(bmr_cm, bmr_kg,bmr_age,1) :
                    fitnessCalculator.bmrCalc(bmr_cm, bmr_kg,bmr_age);

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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //Check active tab
    switch(ui->tabWidget->currentIndex()){
    case 0:
        if (event->key() == Qt::Key_Return)
            on_saveBtn_clicked();
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

QDateTime MainWindow::convertStrToDateTime(const QString &dateStr)
{
    QDateTime momentInTime;
    momentInTime.setDate(QDateTime::fromString(dateStr,"ddMMyyyy").date());
    return momentInTime;
}
