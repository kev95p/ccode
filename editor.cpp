#include "editor.h"
#include "Qsci/qscilexerpython.h"
#include "Qsci/qscilexercpp.h"


Editor::Editor(MainWindow* parent):QsciScintilla(parent)
{
    this->padre = parent;
    activarNumLinea();
    setFuente();
    setSintaxis();
    activarFolding();

    connect(this, SIGNAL(textChanged()), this, SLOT(editando()));
    connect(this, SIGNAL(selectionChanged()), this, SLOT(textoMarcado()));

    this->modificado = true;

}

Editor::~Editor() {
    delete this->fuente;
}

void Editor::textoMarcado() {
    QString textoMarcado = this->selectedText();
    if(textoMarcado!="") {
        this->padre->getAcciones()->getActCortar()->setEnabled(true);
        this->padre->getAcciones()->getActCopiar()->setEnabled(true);
    } else {
        this->padre->getAcciones()->getActCortar()->setEnabled(false);
        this->padre->getAcciones()->getActCopiar()->setEnabled(false);
    }
}

void Editor::editando() {
    this->modificado = true;
    if(this->padre !=NULL) {
        this->padre->getAcciones()->getActGuardar()->setEnabled(true);
        this->padre->getAcciones()->getActGuardarTodo()->setEnabled(true);
    }
}

void Editor::activarNumLinea() {
    QFontMetrics fontmetrics = QFontMetrics(this->font());
       this->setMarginsFont(this->font());
       this->setMarginWidth(0, fontmetrics.width(QString::number(this->lines())) + 6);
       this->setMarginLineNumbers(0, true);
       this->setMarginsBackgroundColor(QColor("#cccccc"));

       connect(this, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
}

void Editor::onTextChanged()
{
    QFontMetrics fontmetrics = this->fontMetrics();
    this->setMarginWidth(0, fontmetrics.width(QString::number(this->lines())) + 20);
}

void Editor::leerArchivo(){
    QFile inputFile(this->archivo.fileName());
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       QString texto;
       while (!in.atEnd())
       {
          texto += in.readLine()+"\n";
       }
       this->setText(texto);
       inputFile.close();
    }
}

void Editor::setFuente() {
    this->fuente = new QFont;
    fuente->setFamily("Courier");
    fuente->setFixedPitch(true);
    fuente->setPointSize(10);
    this->setFont(*fuente);
}

void Editor::activarFolding() {
    QsciScintilla::FoldStyle state = static_cast<QsciScintilla::FoldStyle>((!this->folding()) * 5);
    if (!state)
        this->foldAll(false);
    this->setFolding(state);
}

void Editor::setSintaxis() {
    QsciLexerCPP* lexer = new QsciLexerCPP();
    lexer->setDefaultFont(this->font());
    lexer->setFoldComments(true);
        lexer->setFoldCompact(false);
        this->setLexer(lexer);

}

