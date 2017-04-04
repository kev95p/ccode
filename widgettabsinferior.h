#ifndef WIDGETTABSINFERIOR_H
#define WIDGETTABSINFERIOR_H

#include <QtWidgets>

class WidgetTabsInferior : public QTabWidget
{

    Q_OBJECT

public:
    WidgetTabsInferior(QWidget *parent = 0);
    ~WidgetTabsInferior();
    void setPosicion(int pos);
    void setTextoSalidaNormal(QString texto);
    void setTextoSalidaErrores(QString texto);
    QPlainTextEdit* getSalidaNormal();
    QPlainTextEdit* getSalidaErrores();
private:
    QPlainTextEdit *salidaNormal;
    QPlainTextEdit *salidaErrores;
};

#endif // WIDGETTABSINFERIOR_H
