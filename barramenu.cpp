#include "barramenu.h"

BarraMenu::BarraMenu(MainWindow* parent) : QObject(parent)
{
    this->padre = parent;
    this->mArchivo = this->padre->menuBar()->addMenu(tr("&Archivo"));
    this->mEditar =  this->padre->menuBar()->addMenu(tr("&Editar"));
    this->mVentana = this->padre->menuBar()->addMenu(tr("&Ventana"));
    this->mHerramientas = this->padre->menuBar()->addMenu(tr("&Proyecto"));
    this->mAyuda = this->padre->menuBar()->addMenu(tr("&Ayuda"));
}

BarraMenu::~BarraMenu() {
    delete this->mArchivo;
    delete this->mEditar;
    delete this->mVentana;
    delete this->mHerramientas;
    delete this->mAyuda;
}
