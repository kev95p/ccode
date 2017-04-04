#ifndef PESTANASEDITOR_H
#define PESTANASEDITOR_H

#include <QtWidgets>
#include <QVector>
#include <mainwindow.h>
#include <editor.h>

class Editor;
class MainWindow;

class PestanasEditor : public QTabWidget
{
    Q_OBJECT
public:
    int cont_nuevo;
    PestanasEditor(MainWindow *parent = 0);
    ~PestanasEditor();
    QVector<Editor*> editores;
    void addPestanaMethod();
    void addPestanaMethod(QString url);
    MainWindow *padre;
    void eliminarPestanaCerrar(int indice, QCloseEvent* evento);
private slots:
    void addPestana();
    void cerrarPestana(int indice);
    void eliminarPestana(int indice);
};

#endif // PESTANASEDITOR_H
