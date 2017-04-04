#ifndef EDITOR_H
#define EDITOR_H

#include <QtWidgets>
#include <QObject>
#include "highlighter.h"
#include "mainwindow.h"
#include <Qsci/qscilexercpp.h>

#include <Qsci/qsciscintilla.h>



//class QsciScintilla;
//class LineNumberArea;
class MainWindow;
class Editor : public QsciScintilla
{

Q_OBJECT

public:
    Editor(MainWindow *parent = 0);
    ~Editor();

    void activarNumLinea();
    void setFuente();
    void setSintaxis();
    void leerArchivo();

    QFile archivo;
    QFont* fuente;
    bool modificado;
    MainWindow* padre;
private:
    void activarFolding();

private slots:
    void onTextChanged();
    void editando();
    void textoMarcado();
};

#endif // EDITOR_H
