#ifndef APPLYSTYLEDIALOG_H
#define APPLYSTYLEDIALOG_H

#include<QObject>
#include <QDialog>

class QString;
class QStringList;
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
    QStringList paragraphStyles;
    QStringList characterStyles;
    void initLabel();
    QString getStylesFiltered(const QString filterText);
private slots:
    void updateLabel(const QString& inputText);
};

#endif // APPLYSTYLEDIALOG_H
