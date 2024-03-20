#include "passwordgenerator.h"
#include "ui_passwordgenerator.h"
#include <QRandomGenerator>
#include <QClipboard>

PasswordGenerator::PasswordGenerator(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PasswordGenerator)
{
    ui->setupUi(this);
    this->setWindowTitle("Генератор паролей");
    this->setWindowIcon(QIcon(":/images/icons/key.png"));
}

PasswordGenerator::~PasswordGenerator()
{
    delete ui;
}

void PasswordGenerator::on_minBox_valueChanged(int arg1)
{
    if (arg1 > ui->maxBox->value()) {
        ui->maxBox->setValue(arg1);
    }
}


void PasswordGenerator::on_maxBox_valueChanged(int arg1)
{
    if (arg1 < ui->minBox->value()) {
        ui->minBox->setValue(arg1);
    }
}

PasswordGenerator::Cases PasswordGenerator::translateComboBox(QString text) {
    if (text == "Верхний") {
        return Cases::UPPERCASE;
    } else if (text == "Нижний") {
        return Cases::LOWERCASE;
    } else {
        return Cases::MIXEDCASE;
    }
}


void PasswordGenerator::on_generate_clicked()
{
    int minLength = ui->minBox->value();
    int maxLength = ui->maxBox->value();
    bool hasDigits = ui->digitsCheckBox->isChecked();
    bool hasSpecial = ui->symbolsCheckBox->isChecked();
    Cases cs = translateComboBox(ui->caseComboBox->currentText());

    QString alphabet("");

    if (hasDigits) {
        alphabet.append("0123456789");
    }

    if (hasSpecial) {
        alphabet.append("!@#$%^&*()-_+=;:,./?|`~[]{}\\");
    }

    if (cs == Cases::LOWERCASE || cs == Cases::MIXEDCASE) {
        alphabet.append("abcdefghijklmnopqrstuvwxyz");
    }

    if (cs == Cases::UPPERCASE || cs == Cases::MIXEDCASE) {
        alphabet.append("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    }

    ui->listWidget->clear();

    for (int i = 0; i < PASSWORDS_COUNT; ++i) {
        int length = QRandomGenerator::global()->bounded(minLength, maxLength + 1);
        QString password("");

        for (int ind = 0; ind < length; ++ind) {
            password += alphabet.at(QRandomGenerator::global()->bounded(0, alphabet.length()));
        }

        ui->listWidget->addItem(password);
    }
}


void PasswordGenerator::on_copy_clicked()
{
    if (ui->listWidget->currentItem() == nullptr) {
        return;
    }

    QClipboard* clipboard = QApplication::clipboard();

    clipboard->setText(ui->listWidget->currentItem()->text());
}

