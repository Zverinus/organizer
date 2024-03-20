#include "catalogtile.h"
#include "ui_catalogtile.h"

CatalogTile::CatalogTile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CatalogTile)
{
    ui->setupUi(this);
}

CatalogTile::~CatalogTile()
{
    delete ui;
}
