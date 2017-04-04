#include "widgettabsinferior.h"

WidgetTabsInferior::WidgetTabsInferior(QWidget *parent) : QTabWidget(parent)
{
    this->salidaNormal = new QPlainTextEdit;
    this->salidaNormal->setReadOnly(true);
    this->salidaErrores = new QPlainTextEdit;
    this->salidaErrores->setReadOnly(true);

    this->addTab(salidaNormal, "Consola");
    this->addTab(salidaErrores, "Errores");
}

WidgetTabsInferior::~WidgetTabsInferior() {
    delete this->salidaNormal;
    delete this->salidaErrores;
}

void WidgetTabsInferior::setPosicion(int pos) {
    this->setCurrentIndex(pos);
}

void WidgetTabsInferior::setTextoSalidaNormal(QString texto) {
    this->salidaNormal->document()->setPlainText(texto);
}

void WidgetTabsInferior::setTextoSalidaErrores(QString texto) {
    this->salidaErrores->document()->setPlainText(texto);
}

QPlainTextEdit* WidgetTabsInferior::getSalidaNormal() {
    return this->salidaNormal;
}

QPlainTextEdit* WidgetTabsInferior::getSalidaErrores() {
    return this->salidaErrores;
}
