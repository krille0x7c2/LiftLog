#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"
#include <iostream>
#include <string>
#include <QDebug>
#include <QInputDialog>
#include <QDir>

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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    db = new DbManager("lifts.db");
    ui->setupUi(this);
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
    if (event->key() == Qt::Key_Return)
        emit on_saveBtn_clicked();
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
