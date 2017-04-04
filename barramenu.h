#ifndef BARRAMENU_H
#define BARRAMENU_H
#include <QtWidgets>
#include <mainwindow.h>

class MainWindow;

class BarraMenu: public QObject
{
    Q_OBJECT
public:
    BarraMenu(MainWindow* padre=0);
    ~BarraMenu();
private:
    //padre
    MainWindow* padre;
    //menus
    QMenu* mArchivo;
    QMenu* mEditar;
    QMenu* mHerramientas;
    QMenu* mAyuda;
    QMenu* mVentana;
};

#endif // BARRAMENU_H
