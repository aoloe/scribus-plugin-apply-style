#ifndef APPLYSTYLEDIALOG_H
#define APPLYSTYLEDIALOG_H

#include <QDialog>

class ScribusAPIDocument;

namespace Ui {
class ApplyStyleDialog;
}

class ApplyStyleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ApplyStyleDialog(QWidget *parent, ScribusAPIDocument* document);
    ~ApplyStyleDialog();

protected:
    bool eventFilter(QObject *obj, QEvent *ev);
private:
    Ui::ApplyStyleDialog *ui;
    ScribusAPIDocument* document;
};

#endif // APPLYSTYLEDIALOG_H
