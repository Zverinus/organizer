#include "notepad.h"
#include "ui_notepad.h"
#include <chrono>
#include <QColorDialog>
#include <QTextList>

Notepad::Notepad(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);

    setupToolButtons();
}

void Notepad::setupToolButtons() {
    ui->bold->setCheckable(true);
    connect(ui->bold, &QToolButton::clicked, this, &Notepad::bold);

    ui->italic->setCheckable(true);
    connect(ui->italic, &QToolButton::clicked, this, &Notepad::italic);

    ui->underline->setCheckable(true);
    connect(ui->underline, &QToolButton::clicked, this, &Notepad::underline);

    ui->strikeout->setCheckable(true);
    connect(ui->strikeout, &QToolButton::clicked, this, &Notepad::strikeout);

    ui->italic->setCheckable(true);
    connect(ui->italic, &QToolButton::clicked, this, &Notepad::italic);

    ui->alignBlock->setCheckable(true);
    connect(ui->alignBlock, &QToolButton::clicked, this, &Notepad::alignBlock);
    ui->alignLeft->setCheckable(true);
    connect(ui->alignLeft, &QToolButton::clicked, this, &Notepad::alignLeft);
    ui->alignCenter->setCheckable(true);
    connect(ui->alignCenter, &QToolButton::clicked, this, &Notepad::alignCenter);
    ui->alignRight->setCheckable(true);
    connect(ui->alignRight, &QToolButton::clicked, this, &Notepad::alignRight);

    connect(ui->currentDate, &QToolButton::clicked, this, &Notepad::currentDate);

    connect(ui->currentTime, &QToolButton::clicked, this, &Notepad::currentTime);


    connect(ui->fontColor, &QToolButton::clicked, this, &Notepad::fontColor);

    connect(ui->textField, &QTextEdit::currentCharFormatChanged, this, &Notepad::onCurrentCharFormatChanged);
    connect(ui->textField, &QTextEdit::cursorPositionChanged, this, &Notepad::onCursorPositionChanged);


    connect(ui->bulletList, &QToolButton::clicked, this, &Notepad::bulletList);
    connect(ui->numericList, &QToolButton::clicked, this, &Notepad::numericList);
}


void Notepad::setupFromSave() {
    setAlignment(Qt::AlignCenter);
}


void Notepad::bold() {
    QTextCharFormat format;

    if (ui->bold->isChecked())
        format.setFontWeight(QFont::Bold);
    else
        format.setFontWeight(QFont::Normal);

    QTextCursor cursor = ui->textField->textCursor();

    cursor.mergeCharFormat(format);
    ui->textField->mergeCurrentCharFormat(format);
}


void Notepad::italic() {
    QTextCharFormat format;

    if (ui->italic->isChecked())
        format.setFontItalic(true);
    else
        format.setFontItalic(false);

    QTextCursor cursor = ui->textField->textCursor();

    cursor.mergeCharFormat(format);
    ui->textField->mergeCurrentCharFormat(format);
}


void Notepad::underline() {
    QTextCharFormat format;

    if (ui->underline->isChecked())
        format.setFontUnderline(true);
    else
        format.setFontUnderline(false);

    QTextCursor cursor = ui->textField->textCursor();

    cursor.mergeCharFormat(format);
    ui->textField->mergeCurrentCharFormat(format);
}

void Notepad::strikeout() {
    QTextCharFormat format;

    if (ui->strikeout->isChecked())
        format.setFontStrikeOut(true);
    else
        format.setFontStrikeOut(false);

    QTextCursor cursor = ui->textField->textCursor();

    cursor.mergeCharFormat(format);
    ui->textField->mergeCurrentCharFormat(format);
}

void Notepad::fontColor() {
    QTextCharFormat format;

    QColor color = QColorDialog::getColor(QColor(0, 0, 0), this);
    format.setForeground(color);

    QTextCursor cursor = ui->textField->textCursor();

    cursor.mergeCharFormat(format);
    ui->textField->mergeCurrentCharFormat(format);
}

void Notepad::alignBlock() {
    ui->textField->setAlignment(Qt::AlignJustify);
    ui->alignBlock->setChecked(true);

    ui->alignCenter->setChecked(false);
    ui->alignLeft->setChecked(false);
    ui->alignRight->setChecked(false);
}

void Notepad::alignLeft() {
    ui->textField->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    ui->alignLeft->setChecked(true);

    ui->alignBlock->setChecked(false);
    ui->alignCenter->setChecked(false);
    ui->alignRight->setChecked(false);
}

void Notepad::alignCenter() {
    ui->textField->setAlignment(Qt::AlignCenter);
    ui->alignCenter->setChecked(true);

    ui->alignBlock->setChecked(false);
    ui->alignLeft->setChecked(false);
    ui->alignRight->setChecked(false);
}

void Notepad::alignRight() {
    ui->textField->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    ui->alignRight->setChecked(true);

    ui->alignCenter->setChecked(false);
    ui->alignLeft->setChecked(false);
    ui->alignBlock->setChecked(false);
}

void Notepad::setAlignment(Qt::Alignment alignment) {
    if (alignment & Qt::AlignJustify)
        alignBlock();
    if (alignment & Qt::AlignLeft)
        alignLeft();
    if (alignment & Qt::AlignCenter)
        alignCenter();
    if (alignment & Qt::AlignRight)
        alignRight();

}

void Notepad::currentDate() {
    QTextCursor cursor = ui->textField->textCursor();

    cursor.movePosition(QTextCursor::EndOfLine);
    cursor.insertHtml("\n");
    cursor.movePosition(QTextCursor::NextRow);


    auto dateChrono = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto dateLocal = std::localtime(&dateChrono);
    char buf[std::size("ddd dd-mm-yyyy")];
    std::strftime(buf, std::size(buf), "%a %d-%m-%Y", dateLocal);

    QString dateString(buf);

    cursor.insertHtml("<br><p align=\"left\">" + dateString + "</p><hr><br>");
}

void Notepad::currentTime() {
    QTextCursor cursor = ui->textField->textCursor();

    cursor.movePosition(QTextCursor::EndOfLine);
    cursor.insertHtml("\n");
    cursor.movePosition(QTextCursor::NextRow);

    auto timeChrono = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto timeLocal = std::localtime(&timeChrono);
    char buf[std::size("HH:MM:SS")];
    std::strftime(buf, std::size(buf), "%T", timeLocal);

    QString timeString(buf);
    cursor.insertHtml("<br><p align=\"left\">" + timeString + "</p><hr><br>");
}

void Notepad::bulletList() {
    QTextCursor cursor = ui->textField->textCursor();
    QTextListFormat format;
    QTextBlockFormat blockFormat = cursor.blockFormat();

    cursor.beginEditBlock();

    if (cursor.currentList()) {
        format = cursor.currentList()->format();
    } else {
        format.setIndent(blockFormat.indent() + 1);
        blockFormat.setIndent(0);
        cursor.setBlockFormat(blockFormat);
    }

    format.setStyle(QTextListFormat::ListCircle);
    cursor.createList(format);

    cursor.endEditBlock();

}

void Notepad::numericList() {
    QTextCursor cursor = ui->textField->textCursor();
    QTextListFormat format;
    QTextBlockFormat blockFormat = cursor.blockFormat();

    cursor.beginEditBlock();

    if (cursor.currentList()) {
        format = cursor.currentList()->format();
    } else {
        format.setIndent(blockFormat.indent() + 1);
        blockFormat.setIndent(0);
        cursor.setBlockFormat(blockFormat);
    }

    format.setStyle(QTextListFormat::ListDecimal);
    cursor.createList(format);

    cursor.endEditBlock();
}


void Notepad::onCurrentCharFormatChanged(const QTextCharFormat& format) {
    QFont font = format.font();

    ui->bold->setChecked(font.bold());
    ui->italic->setChecked(font.italic());
    ui->underline->setChecked(font.underline());
    ui->strikeout->setChecked(font.strikeOut());
    ui->fontSize->setValue(font.pointSizeF());
}

void Notepad::onCursorPositionChanged() {
    setAlignment(ui->textField->alignment());
}

void Notepad::setText(QString document) {
    ui->textField->setHtml(document);
    setDefault();
    ui->textField->textCursor().movePosition(QTextCursor::StartOfLine);
    setAlignment(ui->textField->alignment());
    QFont font = ui->textField->font();

    ui->fontSize->setValue(font.pointSize());

}

QString Notepad::getHtml() {
    return ui->textField->toHtml();
}

Notepad::~Notepad()
{
    delete ui;
}


void Notepad::on_fontSize_valueChanged(double arg1)
{
    QTextCharFormat format;
    format.setFontPointSize(arg1);

    QTextCursor cursor = ui->textField->textCursor();

    cursor.mergeCharFormat(format);
    ui->textField->mergeCurrentCharFormat(format);
}


void Notepad::setDefault() {
    ui->bold->setChecked(false);
    ui->italic->setChecked(false);
    ui->strikeout->setChecked(false);
    ui->underline->setChecked(false);
}
