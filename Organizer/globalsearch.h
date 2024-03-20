#ifndef GLOBALSEARCH_H
#define GLOBALSEARCH_H

#include <QDialog>

namespace Ui {
class GlobalSearch;
}

class GlobalSearch : public QDialog
{
    Q_OBJECT

public:
    explicit GlobalSearch(QWidget *parent = nullptr);
    ~GlobalSearch();

private:
    Ui::GlobalSearch *ui;
};

#endif // GLOBALSEARCH_H
