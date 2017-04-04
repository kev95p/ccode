#include "mainwindow.h"
#include <iostream>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    this->acciones = new Acciones(this);

    this->pestanasEditor = new PestanasEditor(this);

    this->panelInferior = new WidgetTabsInferior;

    this->dockArbol = new QDockWidget(trUtf8("Explorador"), this);

    this->arbol = new ArbolDir(this);

    this->split1 = new QSplitter();
    this->split1->setOrientation(Qt::Vertical);
    this->split1->setStretchFactor(0, 1);
    this->setCentralWidget(split1);

    this->dockPrincipal = new QDockWidget(trUtf8("Salida"), split1);

    crearAcciones();
    //this->barraMenu = new BarraMenu(this);
    crearBarraMenu();
    crearToolbar();
    crearDockWindows();
    crearStatusBar();

    connect(this->pestanasEditor , SIGNAL(currentChanged(int)),this,SLOT(cambioTab(int)));

    this->setWindowIcon(QIcon(":/imgs/logo.png"));

    this->setWindowTitle("CCode - nuevo 1");
}

void MainWindow::closeEvent(QCloseEvent *event) {
    event->ignore();

    verificarGuardadoCerrar(event);
}

void MainWindow::verificarGuardadoCerrar(QCloseEvent* evento) {
    bool control = false;
    int numTabs = this->pestanasEditor->count();
    for(int i = numTabs-1; i>=0; i--) {
        this->pestanasEditor->setCurrentIndex(i);
        if(this->pestanasEditor->editores[i]->modificado) {
            if(this->pestanasEditor->editores[i]->archivo.fileName()!="") {
                guardarDocumento();
            } else {
                QMessageBox pregunta(QMessageBox::Question,
                                     tr("Confirmación"),
                                     tr("Desea guardar el documento?"),
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                     this);
                pregunta.setButtonText(QMessageBox::Yes, tr("Sí"));
                pregunta.setButtonText(QMessageBox::No, tr("No"));
                pregunta.setButtonText(QMessageBox::Cancel, tr("Cancelar"));
                int resultado = pregunta.exec();

                if(QMessageBox::Yes == resultado) {
                    QString url_archivo = QFileDialog::getSaveFileName(this,tr("Guardar documento"),QDir::homePath());
                    if(url_archivo=="") {
                        evento->ignore();
                        break;
                    } else {
                        QFile archivo;
                        archivo.setFileName(url_archivo);
                        archivo.open( QIODevice::WriteOnly );
                        QTextStream TextStream(&archivo);
                        TextStream << this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->text();
                        QFileInfo fileInfo(archivo.fileName());
                        QString filename(fileInfo.fileName());
                        this->pestanasEditor->setTabText(this->pestanasEditor->currentIndex(), filename);
                        this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->modificado = false;
                        this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->archivo.setFileName(url_archivo);
                        archivo.close();
                        this->statusBar()->showMessage(trUtf8("Archivo guardado."));
                        this->acciones->getActGuardar()->setEnabled(this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->modificado);
                    }
                } else if (QMessageBox::No == resultado) {
                    this->pestanasEditor->eliminarPestanaCerrar(i, evento);
                    numTabs = this->pestanasEditor->count();
                } else if (QMessageBox::Cancel ==  resultado) {
                    evento->ignore();
                    break;
                }

            }
        }
    }

    int cont = 0;
    for(int i = 0; i<pestanasEditor->count(); i++) {
        if(pestanasEditor->editores[i]->modificado) {
            cont++;
        }
    }
    if(cont>0) {
        evento->ignore();
    } else {
        evento->accept();
    }
}

void MainWindow::guardarDocumentoSalir(QCloseEvent* evento) {


    //QString url_archivo = QFileDialog::getSaveFileName(this,tr("Guardar documento"),QDir::homePath());
}

MainWindow::~MainWindow()
{
    delete this->panelInferior;
    delete this->acciones;
    delete this->mArchivo;
    delete this->mEditar;
    delete this->mAyuda;
    delete this->mHerramientas;
    delete this->arbol;
    delete this->pestanasEditor;
    delete this->dockArbol;
    delete this->dockPrincipal;
    delete this->toolbar;
    delete this->split1;
    //delete this->barraMenu;

}

void MainWindow::cambioTab(int indice) {
    if(indice!=-1) {
        this->acciones->getActGuardar()->setEnabled(this->pestanasEditor->editores[indice]->modificado);
        if(this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->archivo.fileName()!="") {
            this->setWindowTitle("CCode - " + this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->archivo.fileName());
        } else {
            this->setWindowTitle("CCode - " + this->pestanasEditor->tabText(this->pestanasEditor->currentIndex()));
        }
    }
}

void MainWindow::abrirAcercaDe() {
    this->dialogo = new AcercaDe(this);
    this->dialogo->show();
    this->dialogo->raise();
    this->dialogo->activateWindow();
}

Acciones* MainWindow::getAcciones() {
    return this->acciones;
}

void MainWindow::crearArbolDir() {
    this->arbol = new ArbolDir(this);
}

void MainWindow::guardarTodosLosDocumentos() {
    for(int i = 0; i < this->pestanasEditor->count(); i++) {
        this->pestanasEditor->setCurrentIndex(i);
        guardarDocumento();
    }

    for(int i=0; i<this->pestanasEditor->count(); i++) {
        if(this->pestanasEditor->editores[i]->modificado) {
            this->acciones->getActGuardarTodo()->setEnabled(true);
            break;
        } else {
            this->acciones->getActGuardarTodo()->setEnabled(false);
        }
    }

}

void MainWindow::cut() {
    QWidget* focused = QApplication::focusWidget();
    if( focused != 0 )
    {
        QApplication::postEvent( focused,
                                 new QKeyEvent( QEvent::KeyPress,
                                                Qt::Key_X,
                                                Qt::ControlModifier ));
        QApplication::postEvent( focused,
                                 new QKeyEvent( QEvent::KeyRelease,
                                                Qt::Key_X,
                                                Qt::ControlModifier ));
    }
}

void MainWindow::copy() {
    QWidget* focused = QApplication::focusWidget();
    if( focused != 0 )
    {
        QApplication::postEvent( focused,
                                 new QKeyEvent( QEvent::KeyPress,
                                                Qt::Key_C,
                                                Qt::ControlModifier ));
        QApplication::postEvent( focused,
                                 new QKeyEvent( QEvent::KeyRelease,
                                                Qt::Key_C,
                                                Qt::ControlModifier ));
    }
}

void MainWindow::paste() {
    QWidget* focused = QApplication::focusWidget();
        if( focused != 0 )
        {
            QApplication::postEvent( focused,
                                     new QKeyEvent( QEvent::KeyPress,
                                                    Qt::Key_V,
                                                    Qt::ControlModifier ));
            QApplication::postEvent( focused,
                                     new QKeyEvent( QEvent::KeyRelease,
                                                    Qt::Key_C,
                                                    Qt::ControlModifier ));
}
}

void MainWindow::crearBarraMenu() {


    this->mArchivo = menuBar()->addMenu(tr("&Archivo"));
    this->mArchivo->addAction(this->acciones->getActNuevo());
    this->mArchivo->addAction(this->acciones->getActGuardar());
    this->mArchivo->addAction(this->acciones->getActAbrirArchivo());
    this->mArchivo->addAction(this->acciones->getActAbrirCarpeta());
    this->mArchivo->addAction(this->acciones->getActGuardarTodo());
    this->mArchivo->addSeparator();
    this->mArchivo->addAction(this->acciones->getActCerrar());

    this->mEditar = menuBar()->addMenu(trUtf8("&Editar"));
    this->mEditar->addAction(this->acciones->getActCopiar());
    this->mEditar->addAction(this->acciones->getActCortar());
    this->mEditar->addAction(this->acciones->getActPegar());
    this->mEditar->addSeparator();

    this->mVentana = menuBar()->addMenu(trUtf8("&Ventana"));

    this->mHerramientas = menuBar()->addMenu(trUtf8("&Proyecto"));
    this->mHerramientas->addAction(this->acciones->getActEjecutar());

    this->mAyuda = menuBar()->addMenu(tr("&Ayuda"));
    this->mAyuda->addAction(this->acciones->getActAcercaDe());

}

void MainWindow::crearAcciones() {
    this->acciones = new Acciones(this);
    connect(this->acciones->getActGuardar(), SIGNAL(triggered()), this, SLOT(guardarDocumento()));
    connect(this->acciones->getActNuevo(), SIGNAL(triggered()), this, SLOT(documentoNuevo()));
    connect(this->acciones->getActAbrirArchivo(), SIGNAL(triggered()), this, SLOT(abrirArchivo()));
    connect(this->acciones->getActCerrar(), SIGNAL(triggered()), this, SLOT(cerrarAplicacion()));
    connect(this->acciones->getActEjecutar(), SIGNAL(triggered()), this, SLOT(ejecutarArchivo()));
    connect(this->acciones->getActGuardarTodo(), SIGNAL(triggered()), this, SLOT(guardarTodosLosDocumentos()));
    connect(this->acciones->getActAbrirCarpeta(), SIGNAL(triggered()), this, SLOT(abrirCarpeta()));
    connect(this->acciones->getActCortar(), SIGNAL(triggered()), this, SLOT(cut()));
    connect(this->acciones->getActCopiar(), SIGNAL(triggered()), this, SLOT(copy()));
    connect(this->acciones->getActPegar(), SIGNAL(triggered()), this, SLOT(paste()));
    connect(this->acciones->getActAcercaDe(), SIGNAL(triggered()), this, SLOT(abrirAcercaDe()));
}



void MainWindow::abrirCarpeta() {
    QString dir = QFileDialog::getExistingDirectory(this, trUtf8("Abrir Carpeta"),
                                                    "",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    this->arbol->setRootIndex(this->arbol->getModelo()->index(dir));
    this->dockArbol->setWindowTitle("Explorador: "+QFileInfo(dir).fileName()+"");
    this->dockArbol->setToolTip(QFileInfo(dir).absoluteFilePath());

}

void MainWindow::guardarDocumento() {
    if(this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->archivo.fileName()=="") {
        QString url_archivo = QFileDialog::getSaveFileName(this,tr("Guardar documento"),QDir::homePath());
        if(url_archivo != "") {
            QFile archivo;
            archivo.setFileName(url_archivo);
            archivo.open( QIODevice::WriteOnly );
            QTextStream TextStream(&archivo);
            TextStream << this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->text();
            QFileInfo fileInfo(archivo.fileName());
            QString filename(fileInfo.fileName());
            this->pestanasEditor->setTabText(this->pestanasEditor->currentIndex(), filename);
            this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->modificado = false;
            this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->archivo.setFileName(url_archivo);
            archivo.close();
            this->statusBar()->showMessage(trUtf8("Archivo guardado."));
            this->acciones->getActGuardar()->setEnabled(this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->modificado);
            this->setWindowTitle("CCode - "+this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->archivo.fileName());
        }
    } else {
        this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->archivo.resize(0);
        if (this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->archivo.open(QIODevice::ReadWrite) )
        {
            QTextStream TextStream(&(this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->archivo));
            TextStream << this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->text() ;
            this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->modificado = false;
            this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->archivo.close();
            this->statusBar()->showMessage(trUtf8("Archivo guardado."));
            this->acciones->getActGuardar()->setEnabled(this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->modificado);
        }
    }

    for(int i=0; i<this->pestanasEditor->count(); i++) {
        if(this->pestanasEditor->editores[i]->modificado) {
            this->acciones->getActGuardarTodo()->setEnabled(true);
            break;
        } else {
            this->acciones->getActGuardarTodo()->setEnabled(false);
        }
    }

}



void MainWindow::abrirArchivo() {
    QString archivo = QFileDialog::getOpenFileName(this,tr("Abrir Archivo"),QDir::currentPath());
    if(archivo == "") {
        qDebug() << "No seleccionó nada.";
    } else {
        qDebug() << archivo;
        pestanasEditor->addPestanaMethod(archivo);
    }
}

void MainWindow::crearToolbar() {
    this->toolbar = addToolBar(tr("Archivo"));
    this->toolbar->addAction(this->acciones->getActNuevo());
    this->toolbar->addAction(this->acciones->getActAbrirArchivo());
    this->toolbar->addAction(this->acciones->getActAbrirCarpeta());
    this->toolbar->addAction(this->acciones->getActGuardar());
    this->toolbar->addAction(this->acciones->getActGuardarTodo());
    this->toolbar->addSeparator();
    this->toolbar->addAction(this->acciones->getActCopiar());
    this->toolbar->addAction(this->acciones->getActCortar());
    this->toolbar->addAction(this->acciones->getActPegar());
    this->toolbar->addSeparator();
    this->toolbar->addAction(this->acciones->getActEjecutar());

    this->toolbar->setMovable(false);

}

void MainWindow::documentoNuevo() {
    this->pestanasEditor->addPestanaMethod();
}

void MainWindow::cerrarAplicacion() {
    QCloseEvent* closeEvent = new QCloseEvent();
    MainWindow::closeEvent(closeEvent);
}

void MainWindow::ejecutarArchivo() {

        this->panelInferior->setTextoSalidaNormal("");
        this->panelInferior->setTextoSalidaErrores("");
        guardarDocumento();

        if(this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->archivo.fileName()!= "") {

            QFileInfo fileInfo(this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->archivo.fileName());
            if(fileInfo.suffix()=="cc") {

            QProcess* nasmVerificacion = new QProcess();
            QString programaNasm = "nasm -v";
            nasmVerificacion->start(programaNasm);
            nasmVerificacion->waitForFinished();

            QString nasmTextoVerif = "";

            nasmTextoVerif = nasmVerificacion->readAllStandardOutput();
            if(nasmTextoVerif=="") {
                this->panelInferior->getSalidaErrores()->appendHtml("<b style='color: red'>"+trUtf8("No se encuentra NASM en el sistema: No está instalado o no está agregado al path. Compruebe ambas situaciones.")+"</b>");
                this->panelInferior->setPosicion(1);
            }

            QProcess* gccVerificacion = new QProcess();
            QString programaGcc = "gcc --version";
            gccVerificacion->start(programaGcc);
            gccVerificacion->waitForFinished();

            QString gccTextoVerif = "";

            gccTextoVerif = gccVerificacion->readAllStandardOutput();
            if(gccTextoVerif=="") {
                this->panelInferior->getSalidaErrores()->appendHtml("<b style='color: red'>"+trUtf8("No se encuentra GCC en el sistema: No está instalado o no está agregado al path. Compruebe ambas situaciones.")+"</b>");
                this->panelInferior->setPosicion(1);
            }

            if(nasmTextoVerif == "" || gccTextoVerif == "") {
                this->panelInferior->getSalidaErrores()->appendHtml("<i><b style='color: red'>"+trUtf8("*******Ejecución cancelada.*******</b></i>"));
                this->panelInferior->setPosicion(1);
            } else {
                QFileInfo fileInfo(this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->archivo.fileName());
                QProcess* cc = new QProcess();
                QString ccString = "\""+QDir::currentPath()+"/bin/cc.exe\" \""+this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->archivo.fileName()+"\"";
                this->panelInferior->getSalidaNormal()->appendHtml("<b>*******Intentando llamar compilador*******</b>");
                this->panelInferior->getSalidaNormal()->appendHtml("INVOCANDO A cc.exe...");
                this->panelInferior->getSalidaNormal()->appendHtml("<b>"+ccString+"</b>");
                cc->start(ccString);
                cc->waitForFinished();

                int resultadoCC = cc->exitCode();



                QString ccErrores = "";
                ccErrores = cc->readAllStandardError()+"";

                if(ccErrores!="" && resultadoCC!=0) {
                    this->panelInferior->getSalidaErrores()->appendHtml("<b style='color: red'>"+ccErrores.replace("\n", "<br>")+"</b>");
                    this->panelInferior->getSalidaErrores()->appendHtml("<i><b style='color: red'>"+trUtf8("*******Ejecución cancelada.*******</b></i>"));
                    this->panelInferior->setPosicion(1);
                } else {
                    QFileInfo fileInfo(this->pestanasEditor->editores[this->pestanasEditor->currentIndex()]->archivo.fileName());
                    QString filename(fileInfo.baseName());
                    QString url(fileInfo.absolutePath());


                    QString nasmString("nasm -fwin32 \""+url+"/"+filename+".asm\"");
                    QString gccString("gcc \""+url+"/"+filename+".obj\" -o \""+url+"/"+filename+".exe\"");
                    QString consolaString("\""+QDir::currentPath()+"/bin/consola.exe\" \""+url.replace(" ", "^ ")+"/"+filename+".exe\"");

                    QProcess* nasm = new QProcess();
                    this->panelInferior->getSalidaNormal()->appendHtml("<b>*******Intentando ejecutar NASM*******</b>");
                    this->panelInferior->getSalidaNormal()->appendHtml("INVOCANDO A nasm...");
                    this->panelInferior->getSalidaNormal()->appendHtml("<b>"+nasmString+"</b>");
                    nasm->start(nasmString);
                    nasm->waitForFinished();

                    QString nasmErrores = "";
                    nasmErrores = nasm->readAllStandardError()+"";
                    if(nasmErrores!="") {
                        this->panelInferior->getSalidaErrores()->appendHtml("<b style='color: red'>"+nasmErrores.replace("\n", "<br>")+"</b>");
                        this->panelInferior->getSalidaErrores()->appendHtml("<i><b style='color: red'>"+trUtf8("*******Ejecución cancelada.*******</b></i>"));
                        this->panelInferior->setPosicion(1);
                    } else {

                        QProcess* gcc = new QProcess();
                        this->panelInferior->getSalidaNormal()->appendHtml("<b>*******Intentando ejecutar GCC*******</b>");
                        this->panelInferior->getSalidaNormal()->appendHtml("INVOCANDO A gcc...");
                        this->panelInferior->getSalidaNormal()->appendHtml("<b>"+gccString+"</b>");
                        gcc->start(gccString);
                        gcc->waitForFinished();
                        QString gccErrores = "";
                        gccErrores = gcc->readAllStandardError()+"";
                        if(gccErrores!="") {
                            this->panelInferior->getSalidaErrores()->appendHtml("<b style='color: red'>"+gccErrores.replace("\n", "<br>")+"</b>");
                            this->panelInferior->getSalidaErrores()->appendHtml("<i><b style='color: red'>"+trUtf8("*******Ejecución cancelada.*******</b></i>"));
                            this->panelInferior->setPosicion(1);
                        } else {

                            QProcess* consola = new QProcess();
                            this->panelInferior->getSalidaNormal()->appendHtml("<b>*******Intentando llamar consola*******</b>");
                            this->panelInferior->getSalidaNormal()->appendHtml("INVOCANDO al "+filename+".exe...");
                            this->panelInferior->getSalidaNormal()->appendHtml("<b>"+consolaString+"</b>");
                            consola->startDetached(consolaString);
                            consola->waitForFinished();
                            QString consolaErrores = "";
                            consolaErrores = consola->readAllStandardError();
                            QString consolaSalida = "";
                            consolaSalida = consola->readAllStandardOutput();
                            if(consolaErrores!="") {
                                this->panelInferior->getSalidaErrores()->appendHtml("<b style='color: red'>"+consolaErrores.replace("\n", "<br>")+"</b>");
                                this->panelInferior->getSalidaErrores()->appendHtml("<i><b style='color: red'>"+trUtf8("*******Ejecución cancelada.*******</b></i>"));
                                this->panelInferior->setPosicion(1);
                            } else {
                                this->panelInferior->getSalidaNormal()->appendHtml("<b style='color: green'>*******Compilado correctamente ^_^ *******</b>");
                                this->panelInferior->setPosicion(0);
                            }

                        }


                    }
                }

            }
            } else {
                QMessageBox::critical(this, "Error :(", "Solo puede ejecutar archivos con extension .cc", QMessageBox::Ok, QMessageBox::Ok);
            }

        }

}


void MainWindow::crearPanelInferior() {

}

void MainWindow::crearDockWindows()
{
    addDockWidget(Qt::LeftDockWidgetArea, this->dockArbol);

    this->dockPrincipal->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    this->dockPrincipal->setWidget(new QTextEdit("hola", this));

    this->dockArbol->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    this->dockArbol->setFeatures(QDockWidget::DockWidgetClosable |
    QDockWidget::DockWidgetMovable);
    this->dockArbol->setWidget(this->arbol);

    this->mVentana->addAction(this->dockArbol->toggleViewAction());

    this->panelInferior->setPosicion(0);
    this->dockPrincipal->setWidget(this->panelInferior);

    this->split1->addWidget(pestanasEditor);
    this->split1->addWidget(this->dockPrincipal);


    this->mVentana->addAction(this->dockPrincipal->toggleViewAction());
}

void MainWindow::crearTabsEditor() {
    this->pestanasEditor = new PestanasEditor(this);
}

void MainWindow::crearStatusBar() {
    this->statusBar()->showNormal();
    QLabel* label = new QLabel("Listo");
    QLabel* label2 = new QLabel("");
    this->statusBar()->showMessage(trUtf8("Listo"));
    this->statusBar()->addPermanentWidget(label);
    this->statusBar()->addPermanentWidget(label2);
}
