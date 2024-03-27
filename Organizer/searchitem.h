#ifndef SEARCHITEM_H
#define SEARCHITEM_H

#include <QListWidgetItem>

class SearchItem : public QListWidgetItem
{
public:
    SearchItem(int id, QString name, QString document);

    int getId();


private:
    int id;
    QString name;
    QString document;
};

#endif // SEARCHITEM_H
