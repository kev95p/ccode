#include <acciones.h>

Acciones::Acciones(QWidget* parent) : QObject(parent){
    this->padre = parent;
    crearAcciones();
}

Acciones::~Acciones() {
    delete this->act_nuevo;
    delete this->act_guardar;
    delete this->act_abrirArchivo;
    delete this->act_cerrar;
    delete this->act_ejecutar;
    delete this->act_guardarTodo;
    delete this->act_abrirCarpeta;
    delete this->act_copiar;
    delete this->act_pegar;
    delete this->act_cortar;
}

void Acciones::crearAcciones() {
    this->act_guardar = new QAction(QIcon(":/imgs/disk.png"), trUtf8("&Guardar"), padre);
    this->act_guardar->setShortcuts(QKeySequence::Save);
    this->act_guardar->setStatusTip(trUtf8("Guardar"));

    this->act_nuevo = new QAction(QIcon(":/imgs/nuevo.png"), tr("&Nuevo"), padre);
    this->act_nuevo->setShortcuts(QKeySequence::New);
    this->act_nuevo->setStatusTip(tr("Crear un nuevo archivo"));

    this->act_abrirArchivo = new QAction(QIcon(":/imgs/abrir.png"), tr("&Abrir archivo"), padre);
    this->act_abrirArchivo->setShortcuts(QKeySequence::Open);
    this->act_abrirArchivo->setStatusTip(tr("Abrir un archivo"));

    this->act_cerrar = new QAction(QIcon(":/imgs/cerrar.png"), tr("&Cerrar"), padre);
    this->act_cerrar->setShortcuts(QKeySequence::Close);
    this->act_cerrar->setStatusTip(tr("Cerrar editor."));

    this->act_ejecutar = new QAction(QIcon(":/imgs/play.png"), tr("&Ejecutar"), padre);
    this->act_ejecutar->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    this->act_ejecutar->setStatusTip(tr("Ejecutar"));

    this->act_guardarTodo = new QAction(QIcon(":/imgs/disk_todo.png"), trUtf8("&Guardar todo"), padre);
    this->act_guardarTodo->setStatusTip(trUtf8("Guardar todo"));

    this->act_ejecutar = new QAction(QIcon(":/imgs/play.png"), trUtf8("&Ejecutar"), padre);
    this->act_ejecutar->setStatusTip(trUtf8("Ejecutar"));

    this->act_abrirCarpeta = new QAction(QIcon(":/imgs/folder_add.png"), trUtf8("&Abrir Carpeta"), padre);
    this->act_abrirCarpeta->setStatusTip(trUtf8("Abrir carpeta"));

    this->act_copiar = new QAction(QIcon(":/imgs/page_copy.png"), trUtf8("&Copiar"), padre);
    this->act_copiar->setShortcuts(QKeySequence::Copy);
    this->act_copiar->setStatusTip(trUtf8("Copiar texto"));

    this->act_cortar = new QAction(QIcon(":/imgs/cut.png"), trUtf8("&Cortar"), padre);
    this->act_cortar->setShortcuts(QKeySequence::Cut);
    this->act_cortar->setStatusTip(trUtf8("Cortar texto"));

    this->act_pegar = new QAction(QIcon(":/imgs/paste_plain.png"), trUtf8("&Pegar"), padre);
    this->act_pegar->setShortcuts(QKeySequence::Paste);
    this->act_pegar->setStatusTip(trUtf8("Pegar texto"));

    this->act_acercaDe = new QAction(QIcon(":/imgs/info.png"), trUtf8("&Acerca de CCode"), padre);
    this->act_acercaDe->setStatusTip(trUtf8("Acerca de CCode"));
}

QAction* Acciones::getActAbrirCarpeta() {
    return this->act_abrirCarpeta;
}

QAction* Acciones::getActGuardar() {
    return this->act_guardar;
}

QAction* Acciones::getActAcercaDe() {
    return this->act_acercaDe;
}

QAction* Acciones::getActNuevo() {
    return this->act_nuevo;
}

QAction* Acciones::getActAbrirArchivo() {
    return this->act_abrirArchivo;
}

QAction* Acciones::getActCerrar() {
    return this->act_cerrar;
}

QAction* Acciones::getActGuardarTodo() {
    return this->act_guardarTodo;
}

QAction* Acciones::getActEjecutar() {
    return this->act_ejecutar;
}

QAction* Acciones::getActCopiar() {
    return this->act_copiar;
}

QAction* Acciones::getActCortar() {
    return this->act_cortar;
}

QAction* Acciones::getActPegar() {
    return this->act_pegar;
}
