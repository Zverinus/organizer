#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QWidget>
#include <QTextCharFormat>

namespace Ui {
class Notepad;
}

class Notepad : public QWidget
{
    Q_OBJECT

public:
    explicit Notepad(QWidget *parent = nullptr);
    ~Notepad();

    void setText(QString document);
    QString getHtml();

private:
    Ui::Notepad *ui;

    void setupFromSave();
    void setupToolButtons();
    void setAlignment(Qt::Alignment alignment);
    void setDefault();

private slots:
    void bold();
    void italic();
    void underline();
    void strikeout();
    void fontColor();
    void alignBlock();
    void alignLeft();
    void alignCenter();
    void alignRight();
    void currentDate();
    void currentTime();
    void bulletList();
    void numericList();
    void imageInsert();


    void onCurrentCharFormatChanged(const QTextCharFormat& format);
    void onCursorPositionChanged();
    void on_fontSize_valueChanged(double arg1);
};


#endif // NOTEPAD_H
