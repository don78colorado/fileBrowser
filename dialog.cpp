#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_fsModel(new QFileSystemModel(this))
{
    ui->setupUi(this);
    QString homePath;
    homePath=QDir::homePath();
    qDebug() << homePath;
    QModelIndex rootIndex = m_fsModel->setRootPath(homePath);
    //m_fsModel->setFilter(QDir::AllEntries);
    ui->treeView->setModel(m_fsModel);
    ui->treeView->setRootIndex(rootIndex);
    ui->treeView->setColumnWidth(0, 300);
    ui->label_2->setText(QString::number(m_fsModel->rowCount(rootIndex)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_expandAllButton_clicked()
{
   // expandAll
}

void Dialog::on_collapseAllButton_clicked()
{

}

void Dialog::on_treeView_clicked(const QModelIndex &index)
{
   ui->treeView->setRootIndex(index);
}
