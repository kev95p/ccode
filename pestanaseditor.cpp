#include "pestanaseditor.h"

PestanasEditor::PestanasEditor(MainWindow *parent) :
    QTabWidget(parent)
{
    this->padre = parent;
    this->cont_nuevo=0;
    this->setTabsClosable(true);
    this->addPestanaMethod();

    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(cerrarPestana(int)));
}

PestanasEditor::~PestanasEditor() {

}

void PestanasEditor::addPestanaMethod(QString url) {

    Editor *editor = new Editor(padre);

    editor->archivo.setFileName(url);
    editor->leerArchivo();
    editor->modificado = false;
    editores.append(editor);
    QFileInfo fileInfo(editor->archivo.fileName());
    QString filename(fileInfo.fileName());
    this->addTab(editor, filename);
    this->setCurrentIndex(this->count()-1);
    this->padre->getAcciones()->getActGuardar()->setEnabled(false);
    for(int i=0; i<this->count(); i++) {
        if(this->editores[i]->modificado) {
            this->padre->getAcciones()->getActGuardarTodo()->setEnabled(true);
            break;
        } else {
            this->padre->getAcciones()->getActGuardarTodo()->setEnabled(false);
        }
    }
}


void PestanasEditor::eliminarPestana(int indice) {

     QWidget* tabItem = this->widget(indice);
     this->removeTab(indice);

     delete(tabItem);
     tabItem = NULL;

     this->editores.remove(indice);
     if(this->count()==0) {
         this->addPestanaMethod();
     }
     for(int i=0; i<this->count(); i++) {
         if(this->editores[i]->modificado) {
             this->padre->getAcciones()->getActGuardarTodo()->setEnabled(true);
             this->padre->getAcciones()->getActGuardar()->setEnabled(true);
             break;
         } else {
             this->padre->getAcciones()->getActGuardarTodo()->setEnabled(false);
             this->padre->getAcciones()->getActGuardar()->setEnabled(false);
         }
     }

}

void PestanasEditor::eliminarPestanaCerrar(int indice, QCloseEvent* event) {
    QWidget* tabItem = this->widget(indice);
    this->removeTab(indice);

    delete(tabItem);
    tabItem = NULL;

    this->editores.remove(indice);
    if(this->count() == 0) {
        event->accept();
    }
}

void PestanasEditor::cerrarPestana(int indice) {

    if(this->editores[indice]->modificado) {
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon(":imgs/logo.png"));
        msgBox.setWindowTitle("Guardar");
        msgBox.setText("¿Desea guardar el documento?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        msgBox.setButtonText(QMessageBox::Yes, trUtf8("Sí"));
        msgBox.setButtonText(QMessageBox::No, trUtf8("No"));
        msgBox.setButtonText(QMessageBox::Cancel, trUtf8("Cancelar"));
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Question);

        int resultado = msgBox.exec();
        if (resultado == QMessageBox::Yes) {
            if(this->editores[indice]->archivo.fileName() == "") {
                QString archivo = QFileDialog::getSaveFileName(this,tr("Guardar documento"),QDir::homePath());
                if(archivo != "") {
                    QFile archivo_temp;
                    archivo_temp.setFileName(archivo);
                    archivo_temp.open( QIODevice::WriteOnly );
                    QTextStream TextStream(&archivo_temp);
                    TextStream << this->editores[indice]->text();
                    archivo_temp.close();
                    this->eliminarPestana(indice);
                }
            } else {
                QFile *archivo = &(this->editores[this->currentIndex()]->archivo);
                archivo->resize(0);
                if (archivo->open(QIODevice::ReadWrite) )
                {
                      QTextStream TextStream(archivo);
                      TextStream << this->editores[this->currentIndex()]->text() ;
                      archivo->close();
                      eliminarPestana(indice);
                }
            }
        } else if (resultado == QMessageBox::No) {
             this->eliminarPestana(indice);
        }
    } else {
        this->eliminarPestana(indice);
    }
}

void PestanasEditor::addPestanaMethod(){
    Editor *editor = new Editor(this->padre);
    editor->setText("");    
    editores.append(editor);
    cont_nuevo++;
    QString nuevo = "nuevo "+QString::number(this->cont_nuevo);
    this->addTab(editor, nuevo);
    editor->modificado = true;
    this->setCurrentIndex(this->count()-1);
    this->padre->getAcciones()->getActGuardar()->setEnabled(true);
    for(int i=0; i<this->count(); i++) {
        if(this->editores[i]->modificado) {
            this->padre->getAcciones()->getActGuardarTodo()->setEnabled(true);
            break;
        } else {
            this->padre->getAcciones()->getActGuardarTodo()->setEnabled(false);
        }
    }
}

void PestanasEditor::addPestana() {
    Editor *editor = new Editor(this->padre);
    editores.append(editor);
    this->cont_nuevo++;
    QString nuevo = "nuevo "+QString::number(this->cont_nuevo);
    this->addTab(editor, nuevo);
    editor->modificado = true;
    this->setCurrentIndex(this->count()-1);
    this->padre->getAcciones()->getActGuardar()->setEnabled(true);
    for(int i=0; i<this->count(); i++) {
        if(this->editores[i]->modificado) {
            this->padre->getAcciones()->getActGuardarTodo()->setEnabled(true);
            break;
        } else {
            this->padre->getAcciones()->getActGuardarTodo()->setEnabled(false);
        }
    }
}
