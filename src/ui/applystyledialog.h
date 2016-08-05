#ifndef APPLYSTYLEDIALOG_H
#define APPLYSTYLEDIALOG_H

#include <QDialog>

namespace Ui {
class ApplyStyleDialog;
}

class ApplyStyleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ApplyStyleDialog(QWidget *parent = 0);
    ~ApplyStyleDialog();

protected:
    bool eventFilter(QObject *obj, QEvent *ev);
private:
    Ui::ApplyStyleDialog *ui;
};

#endif // APPLYSTYLEDIALOG_H
