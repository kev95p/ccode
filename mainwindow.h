#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "highlighter.h"
#include "editor.h"
#include "pestanaseditor.h"
#include "arboldir.h"
#include <QProcess>
#include <widgettabsinferior.h>
#include <acciones.h>
#include "acercade.h"
#include "barramenu.h"


class PestanasEditor;
class ArbolDir;
class Acciones;
class BarraMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //Pestanas
    PestanasEditor *pestanasEditor;
    Acciones* getAcciones();
    void closeEvent(QCloseEvent *event);
    void verificarGuardadoCerrar(QCloseEvent* evento);
    void guardarDocumentoSalir(QCloseEvent* evento);
private slots:
    void ejecutarArchivo();
    void abrirArchivo();
    void documentoNuevo();
    void cerrarAplicacion();
    void crearPanelInferior();
    void guardarDocumento();
    void guardarTodosLosDocumentos();
    void abrirCarpeta();
    void cut();
    void copy();
    void paste();
    void cambioTab(int indice);
    void abrirAcercaDe();
private:
    //prueba

    //BarraMenu* barraMenu;

    //
    AcercaDe* dialogo;
    //acciones
    Acciones* acciones;
    //arbol de archivos
    ArbolDir* arbol;
    //splitter
    QSplitter *split1;
    //menus
    QMenu* mArchivo;
    QMenu* mEditar;
    QMenu* mHerramientas;
    QMenu* mAyuda;
    QMenu* mVentana;

    //elementos
    QToolBar *toolbar;
    //panel inferior
    WidgetTabsInferior *panelInferior;
    //docks
    QDockWidget *dockArbol;
    QDockWidget *dockPrincipal;
    //metodos
    void crearBarraMenu();
    void crearAcciones();
    void crearToolbar();
    void crearDockWindows();
    void crearEditor();
    void crearTabsEditor();
    void crearArbolDir();
    void crearStatusBar();

};

#endif // MAINWINDOW_H
