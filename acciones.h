#ifndef BARRAMENU_H
#define BARRAMENU_H

#include <QtWidgets>
#include <mainwindow.h>

class MainWindow;

class Acciones : public QObject
{
    Q_OBJECT
public:
    Acciones(QWidget *parent = 0);
    ~Acciones();
    QAction* getActGuardar();
    QAction* getActNuevo();
    QAction* getActCerrar();
    QAction* getActAbrirArchivo();
    QAction* getActGuardarTodo();
    QAction* getActEjecutar();
    QAction* getActAbrirCarpeta();
    QAction* getActCopiar();
    QAction* getActCortar();
    QAction* getActPegar();
    QAction* getActAcercaDe();
private:
    QWidget *padre;
    //Acciones
    QAction *act_nuevo;
    QAction *act_guardar;
    QAction *act_abrirArchivo;
    QAction *act_cerrar;
    QAction *act_ejecutar;
    QAction *act_guardarTodo;
    QAction *act_abrirCarpeta;
    QAction *act_copiar;
    QAction *act_pegar;
    QAction *act_cortar;
    QAction *act_acercaDe;
    //Metodos
    void crearAcciones();
};

#endif // BARRAMENU_H
