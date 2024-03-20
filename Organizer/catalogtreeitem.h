#ifndef CATALOGTREEITEM_H
#define CATALOGTREEITEM_H

#include <QTreeWidgetItem>

class CatalogTreeItem : public QTreeWidgetItem
{
public:
    CatalogTreeItem(const QStringList& name, int id, QString path, bool isNote, QString document=nullptr);


    QString getPath();
    bool getIsNote();
    QString getDocument();
    int getId();
    int getParentId();
    int getLevel();
    void setDocument(QString doc);

private:
    int id;
    int parentId;
    int level;
    QString path;
    bool isNote;
    QString document;
};

#endif // CATALOGTREEITEM_H
