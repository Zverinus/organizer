#include "globalsearch.h"
#include "ui_globalsearch.h"

GlobalSearch::GlobalSearch(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GlobalSearch)
{
    ui->setupUi(this);
}

GlobalSearch::~GlobalSearch()
{
    delete ui;
}
