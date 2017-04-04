#include "arboldir.h"

#include <QSortFilterProxyModel>




ArbolDir::ArbolDir(MainWindow *parent) :QTreeView(parent)
{

    this->padre = parent;

    this->model = new QFileSystemModel();
    this->model->setRootPath("");

    this->setModel(model);
    this->setRootIndex(model->index(""));

    this->model->setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
    this->model->setNameFilterDisables(true);

    // Demonstrating look and feel features
    this->setAnimated(true);
    this->setIndentation(20);
    this->setSortingEnabled(true);
    this->hideColumn(1);
    this->hideColumn(2);
    this->hideColumn(3);
    this->header()->hide();

    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(abrirDocumento(QModelIndex)));

}

ArbolDir::~ArbolDir() {
    delete this->model;
}

QFileSystemModel* ArbolDir::getModelo() {
    return this->model;
}

void ArbolDir::abrirDocumento(QModelIndex index) {

    QMimeDatabase mimeDatabase;
    QMimeType mimeType;

    mimeType = mimeDatabase.mimeTypeForFile(model->fileInfo(index));

     if (mimeType.inherits("text/plain")) {
         qDebug() << model->fileInfo(index).absoluteFilePath();
            if(model->fileInfo(index).isFile()) {
                bool control = false;
                for(int i = 0; i < padre->pestanasEditor->count(); i++) {
                    if(model->fileInfo(index).absoluteFilePath() == padre->pestanasEditor->editores[i]->archivo.fileName()) {
                        this->padre->pestanasEditor->setCurrentIndex(i);
                        control = true;
                    }
                }
                if(!control) {
                    padre->pestanasEditor->addPestanaMethod(model->fileInfo(index).absoluteFilePath());
                }
            }
     } else {
         if(model->fileInfo(index).isFile()) {
            QMessageBox::critical(this->padre, "Aviso", "Formato no soportado.", QMessageBox::Ok, QMessageBox::Ok);
         }
     }



}
