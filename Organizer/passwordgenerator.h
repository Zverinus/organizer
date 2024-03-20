#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <QDialog>

namespace Ui {
class PasswordGenerator;
}

class PasswordGenerator : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordGenerator(QWidget *parent = nullptr);
    ~PasswordGenerator();

    const int PASSWORDS_COUNT = 12;

private slots:
    void on_minBox_valueChanged(int arg1);

    void on_maxBox_valueChanged(int arg1);

    void on_generate_clicked();

    void on_copy_clicked();

private:
    Ui::PasswordGenerator *ui;

    enum Cases {
        LOWERCASE,
        UPPERCASE,
        MIXEDCASE,
    };

    Cases translateComboBox(QString text);
};

#endif // PASSWORDGENERATOR_H
