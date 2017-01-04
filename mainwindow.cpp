#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>

void MainWindow::populateComboBox()
{
    ui->comboBox->addItem("Select");
    ui->comboBox->addItem("Squat");
    ui->comboBox->addItem("Deadlift");
    ui->comboBox->addItem("Bench Press");
    ui->comboBox->addItem("OHP");
    ui->comboBox->addItem("Row");
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    populateComboBox();
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

void MainWindow::on_saveBtn_clicked()
{
     ui->statusBar->showMessage("Saving lift...",1000);
     std::cout << ui->calendarWidget->selectedDate().toString("ddMMyyyy").toStdString() << std::endl;
     std::cout << ui->comboBox->currentText().toStdString() << std::endl;
     std::cout << ui->lineEditWeight->text().toStdString() << std::endl;
     std::cout << ui->lineEditReps->text().toStdString() << std::endl;
     std::cout << ui->lineEditSets->text().toStdString() << std::endl;
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
    std::cout << index << std::endl;
    if (index != 0)
       toogleInput(true);
}



