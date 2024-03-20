#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QTreeWidgetItem>
#include "catalogtreeitem.h"
#include "notepad.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void buildTree();
    void addItem(CatalogTreeItem* parent, QString name, bool isNote, QString document);
    void deleteItem(CatalogTreeItem* item);
    void copyItem(CatalogTreeItem* item);
    void renameItem(CatalogTreeItem* item, QString newName);
    void fillBuffer(CatalogTreeItem* item);
    CatalogTreeItem* getItemParent(CatalogTreeItem* item);

    void setupActions();

private slots:
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_newNote_triggered();

    void on_newFolder_triggered();

    void on_copy_triggered();

    void on_paste_triggered();

    void on_del_triggered();

    void on_rename_triggered();

    void on_password_triggered();

    void on_exportto_triggered();

    void on_save_triggered();

private:
    struct Buffer
    {
        QString name;
        bool isNote;
        QString document;
    };
    QSqlDatabase db;
    QVector<CatalogTreeItem*> items;
    Buffer buffer;
    Notepad* notepad;
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
