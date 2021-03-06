#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QDirModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include "newprojectwindow.h"
#include "settingwindow.h"
#include <QDebug>
#include "filehelper.h"
#include <QJsonObject>
#include "jsonhelper.h"
#include "project.h"
#include <QSpacerItem>
#include <QSignalMapper>

 QLabel *q;
void MainWindow::initUi(){

    ui->setupUi(this);
    q = new QLabel("Col:  Row: ");
    this->statusBar()->addWidget(q);

    QFile qssfile(":/styles/base.qss");
        qssfile.open(QFile::ReadOnly);
        QString qss;
        qss = qssfile.readAll();
       // this->setStyleSheet(qss);


        this->setupEditor();

}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    initUi();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupEditor()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(20);

    ui->textEdit->setFont(font);

   highlighter = new Highlighter(ui->textEdit->document());

   for(int i = 0;i<9;i++){
       QPushButton* editorTopB = new QPushButton("");
       editorTopB->setStyleSheet("background:rgba(0, 128, 255,0);color:rgb(255, 255, 255);border:none;margin:0;padding:4px;padding-left:20px;padding-right:20px;margin-left:1px;");
       this->editorTop[i] = editorTopB;
       connect(editorTop[i], SIGNAL(clicked()), this->signalMapper, SLOT(map()));
   }
   connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(onTopClicked(QString)));
   this->editorTop[0]->setStyleSheet("background:rgb(0, 128, 255);color:rgb(255, 255, 255);border:none;margin:0;padding:4px;padding-left:20px;padding-right:20px;margin-left:1px;");
   this->editorTop[0]->setText("欢迎页");


   for (int i = 0;i<9;i++){
       this->ui->edit_title->addWidget(editorTop[i]);
   }

}

void MainWindow::on_actionNew_Project_triggered()
{
    NewProjectWindow newProjectWindow;
    newProjectWindow.show();
    newProjectWindow.exec();
}

void MainWindow::on_actionSetting_triggered()
{
    SettingWindow setting;
    setting.show();
    setting.exec();
}

void MainWindow::on_actionOpen_Project_triggered()
{
    QFileDialog projectDialog;
    QString path = projectDialog.getOpenFileName(this, tr("Open Nide project"), ".", tr("Nide project Files(*.nproj)"));
          if(path.length() != 0) {
                QFile file(path);
                FileHelper fileHelper;
                JsonHelper jsonHelper;
                QString buffer =  fileHelper.loadFileToString(path);
                this->projectOBJ = jsonHelper.getJsonObjectFromString(buffer);

                this->pp =  new Project(this->projectOBJ);
                this->ui->projectName->setText(this->pp->getProjectName());
                this->ui->listView_undo->setModel(this->pp->getTaskUndo());
                this->ui->listView_doing->setModel(this->pp->getTaskDoing());
                this->ui->listView_done->setModel(this->pp->getTaskDone());
                this->ui->treeViewProject->setModel(this->pp->getProjectTree());



                this->projectPath = QFileInfo(path).absolutePath()+"/";
                projectDialog.close();

          }

}

void MainWindow::on_textEdit_textChanged()
{
        QTextCursor cursor = ui->textEdit->textCursor();
        int ColNum = cursor.columnNumber();
        int RowNum = cursor.blockNumber();
        q->setText("Col: "+QString::number(ColNum,10)+" Row: "+QString::number(RowNum,10));
}
void MainWindow::EditAddFileTitle(QString filename){
        if(!this->editorManager.isFileOpened(filename,this->projectPath)){
                    QPushButton* push = new QPushButton(filename);
                    push->setStyleSheet("background:rgb(0, 128, 255);color:rgb(255, 255, 255);border:none;margin:0;padding:4px;padding-left:20px;padding-right:20px;margin-left:1px;");
                    this->ui->edit_title->addWidget(push,0);
        }
}


void MainWindow::onTopClicked(QString index){
    renderTitle(index);
    this->ui->textEdit->setText(fileManager.getBufferedFile(index,this->projectPath));
}

void MainWindow::renderTitle(QString file){
    std::vector<QString> opened = this->editorManager.getOpenedFile();

    for(int i = 0;i<opened.size();i++){
        this->editorTop[i]->setText(opened.at(i));
         if(opened.at(i)==file){
            this->editorTop[i]->setStyleSheet("background:rgb(0, 128, 255);color:rgb(255, 255, 255);border:none;margin:0;padding:4px;padding-left:20px;padding-right:20px;margin-left:1px;");
        }else{
             this->editorTop[i]->setStyleSheet("background:rgb(45, 45, 48);color:rgb(255, 255, 255);border:none;margin:0;padding:4px;padding-left:20px;padding-right:20px;margin-left:1px;");

        }
        QString ff = editorTop[i]->text();
        this->signalMapper->setMapping(editorTop[i], ff);

     }

}


void MainWindow::on_treeViewProject_clicked(const QModelIndex &index)
{
    QString str;

    str = QStringLiteral("%1").arg(index.data().toString());

    if(str!="Sources"&&str!="Headers"){

        this->ui->textEdit->setFontPointSize(20);

        this->ui->textEdit->setText(fileManager.getBufferedFile(str,this->projectPath));

        this->ui->markList->setModel(this->pp->getMark(str));

        //this->EditAddFileTitle(str);
        this->editorManager.openFile(str,this->projectPath);
        renderTitle(str);


        //ui->editor_file_name->setText(str);

    }





}
