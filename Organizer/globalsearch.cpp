#include "globalsearch.h"
#include "ui_globalsearch.h"
#include "searchitem.h"
#include <QTextDocumentFragment>

GlobalSearch::GlobalSearch(QWidget *parent, QVector<CatalogTreeItem*>* items, QStackedWidget* st, QTreeWidget* tree)
    : QDialog(parent)
    , ui(new Ui::GlobalSearch)
{
    ui->setupUi(this);

    this->items = items;
    this->st = st;
    this->tree = tree;

    this->setWindowTitle("Глобальный поиск");
    this->setWindowIcon(QIcon(":/images/icons/searchdialog.png"));
}

GlobalSearch::~GlobalSearch()
{
    delete ui;
}



void GlobalSearch::on_searchButton_clicked()
{
    if (ui->searchLine->text().isEmpty()) {
        return;
    }

    ui->listWidget->clear();
    QString searchText = ui->searchLine->text();

    if (!ui->caseCheckBox->isChecked()) {
        searchText = searchText.toLower();
    }

    for (CatalogTreeItem* t_item: *items) {
        if (!t_item->getIsNote()) {
            continue;
        }

        QString itemText = QTextDocumentFragment::fromHtml(t_item->getDocument()).toPlainText();
        if (!ui->caseCheckBox->isChecked()) {
            itemText = itemText.toLower();
        }

        if (itemText.contains(searchText)) {
            SearchItem* item = new SearchItem(t_item->getId(), t_item->getName(), t_item->getDocument());
            ui->listWidget->addItem(item);
        }
    }

    QString docsCount = ui->foundDocsCount->text();
    auto splittedCount = docsCount.split(" ");
    splittedCount[0] = QString::number(ui->listWidget->count());
    docsCount = splittedCount.join(" ");
    ui->foundDocsCount->setText(docsCount);
}


void GlobalSearch::on_moveToChosen_clicked()
{
    if (!ui->listWidget->currentItem()) {
        return;
    }


    SearchItem* listItem = static_cast<SearchItem*>(ui->listWidget->currentItem());
    CatalogTreeItem* treeItem;

    for (CatalogTreeItem* i: *items) {
        if (i->getId() == listItem->getId()) {
            treeItem = i;
            break;
        }
    }

    if (!treeItem) {
        return;
    }

    tree->setCurrentItem(treeItem);
    this->close();
}


void GlobalSearch::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    on_moveToChosen_clicked();
}

