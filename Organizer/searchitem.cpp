#include "searchitem.h"

SearchItem::SearchItem(int id, QString name, QString document) : QListWidgetItem(name) {
    this->document = document;
    this->id = id;
    this->name = name;
}


int SearchItem::getId() {
    return id;
}
