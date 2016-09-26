#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_fsModel(new QFileSystemModel(this))
    //m_pathIndex(new QModelIndex())
{
    ui->setupUi(this);
    QString homePath;
    homePath=QDir::homePath();
    qDebug() << homePath;
    m_pathIndex = m_fsModel->setRootPath(homePath);
    //m_fsModel->setFilter(QDir::AllEntries); //expand will crash
    ui->treeView->setModel(m_fsModel);
    ui->treeView->setRootIndex(m_pathIndex);
    ui->treeView->setColumnWidth(0, 300);
    connect(m_fsModel, SIGNAL(directoryLoaded(QString)), this, SLOT(on_fsModel_directoryLoaded(QString)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_fsModel_directoryLoaded(const QString &path)
{
    // not done correctly it's loading multiple directories when there is something expanded
    //QModelIndex rootIndex = m_fsModel->setRootPath(path);
//        QMessageBox::information(this, "Information", path);
  ui->label_2->setText(QString::number(m_fsModel->rowCount(m_pathIndex)));
}

void Dialog::on_expandAllButton_clicked()
{
   // expandAll
    ui->treeView->expandToDepth(4);
}

void Dialog::on_collapseAllButton_clicked()
{
        ui->treeView->collapseAll();
}

void Dialog::on_treeView_clicked(const QModelIndex &index)
{
   QFileInfo fileInfo =  m_fsModel->fileInfo(index);
   QString path = fileInfo.absoluteFilePath();
   if(fileInfo.isFile())
        QMessageBox::information(this, "Information", path);
   else if(fileInfo.isDir())
   {
       m_pathIndex = m_fsModel->setRootPath(path);
       ui->treeView->setRootIndex(m_pathIndex);
   }
   else
        QMessageBox::information(this, "WTF", path);
}
