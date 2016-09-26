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
    //m_fsModel->setFilter(QDir::AllEntries); //expand will crash
    ui->treeView->setModel(m_fsModel);
    m_fsModel->setReadOnly(true); // read-only
    cd(homePath);
    ui->treeView->setColumnWidth(0, 300);
    connect(m_fsModel, SIGNAL(directoryLoaded(QString)), this, SLOT(on_fsModel_directoryLoaded(QString)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::cd(const QString &path)
{
    m_pathIndex = m_fsModel->setRootPath(path);
    ui->treeView->setRootIndex(m_pathIndex);
}

void Dialog::on_fsModel_directoryLoaded(const QString &path)
{
    // not done correctly it's loading multiple directories when there is something expanded
    //QModelIndex rootIndex = m_fsModel->setRootPath(path);
//        QMessageBox::information(this, "Information", path);
    QString text;
    text.append("Parent Rows: ");
    text.append(QString::number(m_fsModel->rowCount(m_pathIndex)));
    m_loadCounter++;
    text.append(" Load Count: " + QString::number(m_loadCounter));
    ui->label_2->setText(text);
}

void Dialog::expand(QModelIndex index, int depth)
{
    if(depth==0)
        return;
    for(int row =0;row<m_fsModel->rowCount(index);row++)
    {
        QModelIndex currentIndex = m_fsModel->index(row,0,index);
        QFileInfo fileInfo = m_fsModel->fileInfo(currentIndex);
        QString path = fileInfo.absoluteFilePath();
        qDebug() << path;
        //logic to test if it's a directory
        ui->treeView->expand(currentIndex);
        if(m_fsModel->hasChildren(currentIndex))
        {
          qDebug() << path << "has children";
          expand(currentIndex, depth-1);
        }
    }
}

void Dialog::on_expandAllButton_clicked()
{
   // expandAll
    ui->treeView->expandToDepth(8);
    //expand(m_pathIndex, 8);
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
 //      m_pathIndex = m_fsModel->setRootPath(path);
       //ui->treeView->setRootIndex(m_pathIndex);
       cd(path);
   }
   else
        QMessageBox::information(this, "WTF", path);
}

void Dialog::on_pushButton_clicked()
{
   QDir dir = m_fsModel->rootDirectory();
   dir.cdUp();
   cd(dir.absolutePath());
}
