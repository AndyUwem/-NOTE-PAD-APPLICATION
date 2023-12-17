#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>
#include <QDir>
#include <QColor>
#include <regex>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoadApplicationDependences();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString File_name = QFileDialog::getOpenFileName(this,"Open a file",QDir::homePath(),this->Filter_Extentions);
    QFile file(this->File_path = File_name);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        this->CallErrorMassage();
        return;
    }

    QTextStream readStream(&file);
    QString File_content = readStream.readAll();
    ui->TextEditBox->setText(File_content);
    file.close();  
    ui->statusbar->showMessage("File Path: "+this->File_path);
}


void MainWindow::on_actionSave_File_triggered()
{
    QFile file(this->File_path);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        this->CallErrorMassage();
        return;
    }

    QTextStream writeStream(&file);
    QString file_content = ui->TextEditBox->toPlainText();
    writeStream << file_content;
    file.flush();
    file.close();
}


void MainWindow::on_actionSave_As_triggered()
{
    QString File_name = QFileDialog::getSaveFileName(this,"Save a file",QDir::homePath(),this->Filter_Extentions);
    QFile file(File_name);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        this->CallErrorMassage();
        return;
    }

    QTextStream writeStream(&file);
    QString file_content = ui->TextEditBox->toPlainText();
    writeStream << file_content;
    file.flush();
    file.close();
}


void MainWindow::CallErrorMassage(){
    QMessageBox::critical(this,"Invalid File","No file name specified!");
}

void MainWindow::on_actionCopy_triggered()
{
    ui->TextEditBox->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->TextEditBox->paste();
}


void MainWindow::on_actionCut_triggered()
{
    ui->TextEditBox->cut();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->TextEditBox->redo();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->TextEditBox->undo();
}


void MainWindow::on_actionNew_File_triggered()
{
    File_path = "";
    ui->TextEditBox->setText("");
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::CheckForOpenFiles(){


    if(this->File_path.isEmpty() || ui->TextEditBox->document()->isEmpty())
        ui->actionSave_File->setEnabled(false);

        else ui->actionSave_File->setEnabled(true);


    if(this->CheckForWhiteSpaces(ui->TextEditBox->document()->toPlainText().toStdString())){
        ui->actionCut->setEnabled(false);
        ui->actionCopy->setEnabled(false);
        ui->actionSave_As->setEnabled(false);
    }
     else{
         ui->actionCut->setEnabled(true);
         ui->actionCopy->setEnabled(true);
         ui->actionSave_As->setEnabled(true);
     }

}

bool MainWindow::CheckForWhiteSpaces(const std::string &str)
{
    if(str.empty()) return true;

    return std::all_of(str.begin(), str.end(), [](unsigned char ch){
        return std::isspace(ch);
    });
}

void MainWindow::LoadApplicationDependences()
{
    CheckForOpenFiles();
    Filter_Extentions = "Text Document(*.txt);; Hyptext Markup(*.html);; Extensible Markup(*.xml)";
    File_path = "";
    setWindowTitle("ANDY NOTES");
    setWindowIcon(QIcon(":/img/img/1998540.png"));
}

void MainWindow::on_TextEditBox_textChanged()
{
   CheckForOpenFiles();
}



void MainWindow::on_actionAbout_triggered()
{
    QString aboutText = "App: ANDY NOTE.";
            aboutText += "\nCompany: DICTECH";
            aboutText += "\n Version: 1.0";
             QMessageBox::information(this,"App Information",aboutText);

}



