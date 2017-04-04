#ifndef ARBOLDIR_H
#define ARBOLDIR_H

#include <QTreeView>
#include <QtWidgets>
#include "mainwindow.h"

class MainWindow;

class ArbolDir : public QTreeView
{

    Q_OBJECT

public:
    ArbolDir(MainWindow *parent = 0);
    ~ArbolDir();
    QFileSystemModel* getModelo();
    MainWindow *padre;
private:
    QFileSystemModel* model;
private slots:
    void abrirDocumento(QModelIndex index);
};

#endif // ARBOLDIR_H
