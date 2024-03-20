#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "notepad.h"
#include <QFileSystemModel>
#include "catalogtreeitem.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QPrinter>
#include <QDialogButtonBox>
#include "passwordgenerator.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupActions();

    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(qApp->applicationDirPath() + "/notes.sqlite");
    if (!db.open()) {
        qDebug() << "can't open db";
        return;
    }

    buildTree();


    notepad = new Notepad;

    ui->stackedWidget->addWidget(notepad);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setupActions() {
    connect(ui->treeWidget, &QTreeWidget::itemChanged, this, &MainWindow::on_treeWidget_itemClicked);
}


void MainWindow::buildTree() {
    ui->treeWidget->clear();
    items.clear();
    QSqlQuery query;

    query.exec("SELECT * FROM tree ORDER BY level");
    while (query.next()) {
        QStringList name;
        name.append(query.value(1).toString());
        int id = query.value(0).toInt();
        QString path = query.value(2).toString();
        bool isNote = query.value(3).toBool();

        CatalogTreeItem* item = new CatalogTreeItem(name, id, path, isNote, (isNote ? query.value(4).toString() : nullptr));

        if (item->getId() == 0) {
            ui->treeWidget->addTopLevelItem(item);
            items.append(item);
        } else {

            foreach (auto parent, items) {
                if (item->getParentId() == parent->getId()) {
                    parent->addChild(item);
                    items.append(item);
                    break;
                }
            }

        }

        ui->treeWidget->expandAll();
        ui->treeWidget->topLevelItem(0)->setSelected(true);
    }
}


void MainWindow::addItem(CatalogTreeItem* parent, QString name, bool isNote, QString document) {
    QSqlQuery query;

    query.exec("SELECT MAX(id) FROM tree");
    query.first();
    int id = query.value(0).toInt() + 1;

    QString path = parent->getPath();
    path = path + "/" + QString::number(id);

    int level = parent->getLevel() + 1;

    query.prepare("INSERT INTO tree (id, name, path, is_note, document, level)"
                  "VALUES (?, ?, ?, ?, ?, ?)");

    query.addBindValue(id);
    query.addBindValue(name);
    query.addBindValue(path);
    query.addBindValue(isNote);
    query.addBindValue(document);
    query.addBindValue(level);

    if (query.exec()) {
        db.commit();

        CatalogTreeItem* item = new CatalogTreeItem(QStringList(name), id, path, isNote, "");
        items.append(item);
        parent->addChild(item);
    } else {
        qDebug() << query.lastError() << ' ' << query.lastQuery();
    }
}


void MainWindow::deleteItem(CatalogTreeItem* item) {
    if (item->getId() == 0) {
        QMessageBox::warning(this,
                             QString("Поытка изменения корневой папки"),
                             QString("Вы не можете удалить корневую папку!"),
                             QMessageBox::Ok);

        return;
    }

    QSqlQuery query;
    query.prepare(QString("DELETE FROM tree "
                          "WHERE path LIKE '%1%'").arg(item->getPath()));

    if (query.exec()) {
        db.commit();

        QString path = item->getPath();
        CatalogTreeItem* parent = getItemParent(item);
        parent->removeChild(item);
        for (auto i = items.begin(); i != items.end();) {
            if ((*i)->getPath().startsWith(path)) {
                i = items.erase(i);
            } else {
                ++i;
            }
        }
    }  else {
        qDebug() << query.lastError() << ' ' << query.lastQuery();
    }
}


CatalogTreeItem* MainWindow::getItemParent(CatalogTreeItem* item) {
    return *std::find_if(items.begin(), items.end(),
                         [item](CatalogTreeItem* i) {return i->getId() == item->getParentId();});
}


void MainWindow::fillBuffer(CatalogTreeItem* item) {
    if (item == nullptr) {
        return;
    }

    buffer.name = item->text(0);
    buffer.isNote = item->getIsNote();
    buffer.document = item->getDocument();
}


void MainWindow::renameItem(CatalogTreeItem* item, QString newName) {
    if (item->getId() == 0) {
        return;
    }

    QSqlQuery query;
    query.prepare(QString("UPDATE tree "
                          "SET name='%1' "
                          "WHERE id=%2")
                  .arg(newName)
                  .arg(item->getId()));

    if (query.exec()) {
        item->setText(0, newName);
    } else {
        qDebug() << query.lastError() << ' ' << query.lastQuery();
    }
}


void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    CatalogTreeItem* i = static_cast<CatalogTreeItem*>(item);

    if (i->getIsNote()) {
        ui->stackedWidget->setCurrentWidget(notepad);
        notepad->setText(i->getDocument());
    } else {

    }

}


void MainWindow::on_newNote_triggered()
{
    if (ui->treeWidget->currentItem() == nullptr) {
        ui->treeWidget->topLevelItem(0)->setSelected(true);
    }

    bool isOk;
    QString name = QInputDialog::getText(this,
                                         QString("Создание заметки"),
                                         QString("Введите название:"),
                                         QLineEdit::Normal,
                                         QString("Заметка"),
                                         &isOk);


    if (isOk && !name.isEmpty()) {
        CatalogTreeItem* item = static_cast<CatalogTreeItem*>(ui->treeWidget->currentItem());

        if (item->getIsNote()) {
            addItem(getItemParent(item), name, true, "");
        } else {
            addItem(item, name, true, "");
        }
    }
}


void MainWindow::on_newFolder_triggered()
{
    if (ui->treeWidget->currentItem() == nullptr) {
        ui->treeWidget->topLevelItem(0)->setSelected(true);
    }

    bool isOk;
    QString name = QInputDialog::getText(this,
                                         QString("Создание папки"),
                                         QString("Введите название:"),
                                         QLineEdit::Normal,
                                         QString("Папка"),
                                         &isOk);


    if (isOk && !name.isEmpty()) {
        CatalogTreeItem* item = static_cast<CatalogTreeItem*>(ui->treeWidget->currentItem());

        if (item->getIsNote()) {
            addItem(getItemParent(item), name, false, "");
        } else {
            addItem(item, name, false, "");
        }
    }
}


void MainWindow::on_copy_triggered()
{
    if (ui->treeWidget->currentItem() == nullptr) {
        return;
    }

    fillBuffer(static_cast<CatalogTreeItem*>(ui->treeWidget->currentItem()));
}


void MainWindow::on_paste_triggered()
{
    if (buffer.name == nullptr || ui->treeWidget->currentItem() == nullptr) {
        return;
    }

    CatalogTreeItem* item = static_cast<CatalogTreeItem*>(ui->treeWidget->currentItem());

    if (item->getIsNote()) {
        addItem(getItemParent(item), buffer.name, buffer.isNote, buffer.document);
    } else {
        addItem(item, buffer.name, buffer.isNote, buffer.document);
    }
}


void MainWindow::on_del_triggered()
{
    if (ui->treeWidget->currentItem() == nullptr) {
        return;
    }

    if (QMessageBox::question(this, "Удаление", "Вы уверены, что хотите удалить выбранный объект?", QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }


    CatalogTreeItem* item = static_cast<CatalogTreeItem*>(ui->treeWidget->currentItem());
    deleteItem(item);
}


void MainWindow::on_rename_triggered()
{
    CatalogTreeItem* item = static_cast<CatalogTreeItem*>(ui->treeWidget->currentItem());

    if (ui->treeWidget->currentItem() == nullptr || item->getId() == 0) {
        return;
    }

    bool isOk;
    QString name = QInputDialog::getText(this,
                                         QString("Переименование"),
                                         QString("Введите название:"),
                                         QLineEdit::Normal,
                                         ui->treeWidget->currentItem()->text(0),
                                         &isOk);


    if (isOk && !name.isEmpty()) {
        renameItem(item, name);
    }
}


void MainWindow::on_password_triggered()
{
    PasswordGenerator* generator = new PasswordGenerator;

    generator->exec();
}


void MainWindow::on_exportto_triggered()
{
    if (ui->treeWidget->currentItem() == nullptr) {
        return;
    }

    CatalogTreeItem* item = static_cast<CatalogTreeItem*>(ui->treeWidget->currentItem());

    QFileDialog exportDialog(this, QString("Экспорт в html"));
    exportDialog.setAcceptMode(QFileDialog::AcceptSave);
    exportDialog.setMimeTypeFilters(QStringList("text/html"));
    exportDialog.selectFile(item->text(0));

    if (exportDialog.exec() != QDialog::Accepted) {
        return;
    }

    QString s = exportDialog.selectedFiles().first();

    QFile file(s);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);

        const QString html = notepad->getHtml();
        stream << html;
        stream.flush();

        file.close();
    }
}


void MainWindow::on_save_triggered()
{
    if (ui->treeWidget->currentItem() == nullptr) {
        return;
    }

    CatalogTreeItem* item = static_cast<CatalogTreeItem*>(ui->treeWidget->currentItem());
    if (!item->getIsNote()) {
        return;
    }

    QSqlQuery query;
    QString html = notepad->getHtml().replace("'", "\"");
    query.prepare(QString("UPDATE tree "
                          "SET document='%1' "
                          "WHERE id=%2")
                      .arg(html)
                      .arg(item->getId()));

    if (query.exec()) {
        item->setDocument(html);
        qDebug() << "saved successfully";
    } else {
        qDebug() << query.lastError() << ' ' << query.lastQuery();
    }
}

