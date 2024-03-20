#ifndef CATALOGTILE_H
#define CATALOGTILE_H

#include <QWidget>

namespace Ui {
class CatalogTile;
}

class CatalogTile : public QWidget
{
    Q_OBJECT

public:
    explicit CatalogTile(QWidget *parent = nullptr);
    ~CatalogTile();

private:
    Ui::CatalogTile *ui;
};

#endif // CATALOGTILE_H
