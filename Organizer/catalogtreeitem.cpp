#include "catalogtreeitem.h"
#include <QCommonStyle>

CatalogTreeItem::CatalogTreeItem(const QStringList& name, int id, QString path, bool isNote, QString document) :
    QTreeWidgetItem(name), id(id), path(path), isNote(isNote) {

    if (document != nullptr)
        this->document = document;

    QStringList splitted = path.split("/");
    if (id != 0) {
        parentId = splitted[splitted.size() - 2].toInt();
    } else {
        parentId = 0;
    }
    this->name = name[0];
    level = splitted.size() - 1;


    QCommonStyle style;
    if (isNote) {
        this->setIcon(0, style.standardIcon(QStyle::SP_FileIcon));
    } else {
        this->setIcon(0, style.standardIcon(QStyle::SP_DirIcon));
    }
}

void CatalogTreeItem::setDocument(QString doc) {
    document = doc;
}


QString CatalogTreeItem::getPath() {
    return path;
}

bool CatalogTreeItem::getIsNote() {
    return isNote;
}

QString CatalogTreeItem::getDocument() {
    return document;
}

int CatalogTreeItem::getId() {
    return id;
}

int CatalogTreeItem::getParentId() {
    return parentId;
}

int CatalogTreeItem::getLevel() {
    return level;
}

QString CatalogTreeItem::getName() {
    return name;
}
