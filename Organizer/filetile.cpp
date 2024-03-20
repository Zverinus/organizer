#include "filetile.h"
#include "ui_filetile.h"

FileTile::FileTile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FileTile)
{
    ui->setupUi(this);
}

FileTile::~FileTile()
{
    delete ui;
}
