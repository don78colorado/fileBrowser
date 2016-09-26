#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include <QDirModel>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_expandAllButton_clicked();

    void on_collapseAllButton_clicked();

    void on_treeView_clicked(const QModelIndex &index);

    void on_fsModel_directoryLoaded(const QString &path);
    void on_pushButton_clicked();

    void cd(const QString &path);
    void cdUp();
    void cdHome();
    void expand(QModelIndex index, int depth);
    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    QDirModel *m_fsModel;
    QModelIndex m_pathIndex;
    int m_loadCounter;
    int m_expandDepth;

};

#endif // DIALOG_H
