#ifndef GLOBALSEARCH_H
#define GLOBALSEARCH_H

#include <QDialog>
#include <QStackedWidget>
#include <QTreeWidget>
#include "catalogtreeitem.h"
#include "searchitem.h"


namespace Ui {
class GlobalSearch;
}

class GlobalSearch : public QDialog
{
    Q_OBJECT

public:
    explicit GlobalSearch(QWidget *parent = nullptr, QVector<CatalogTreeItem*>* items = nullptr, QStackedWidget* st = nullptr, QTreeWidget* tree = nullptr);
    ~GlobalSearch();

private slots:
    void on_searchButton_clicked();

    void on_moveToChosen_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::GlobalSearch *ui;
    QVector<CatalogTreeItem*>* items;
    QStackedWidget* st;
    QTreeWidget* tree;
};

#endif // GLOBALSEARCH_H
