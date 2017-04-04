#include "acercade.h"
#include "ui_acercade.h"
#include <QDesktopWidget>

AcercaDe::AcercaDe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AcercaDe)
{

    ui->setupUi(this);

    this->setGeometry(0,0,this->width(),this->height());
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->move( screen.center() - this->rect().center() );
    setFixedWidth(525);
    setFixedHeight(130);
}

AcercaDe::~AcercaDe()
{
    delete ui;
}

void AcercaDe::on_btnAceptar_clicked()
{
    this->close();
}
