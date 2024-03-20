#ifndef FILETILE_H
#define FILETILE_H

#include <QWidget>

namespace Ui {
class FileTile;
}

class FileTile : public QWidget
{
    Q_OBJECT

public:
    explicit FileTile(QWidget *parent = nullptr);
    ~FileTile();

private:
    Ui::FileTile *ui;
};

#endif // FILETILE_H
