#ifndef APPLYSTYLEDIALOG_H
#define APPLYSTYLEDIALOG_H

#include<QObject>
#include <QDialog>

class QString;
class ScribusAPIDocument;

struct ApplyStyleDialogListItem
{
    ApplyStyleDialogListItem(QString type, QString name): type{type}, name{name} {}
    QString type; // todo: use a constant from APIDocumentStyle
    QString name;
};

namespace Ui {
class ApplyStyleDialog;
}

class ApplyStyleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ApplyStyleDialog(QWidget *parent, ScribusAPIDocument* document);
    ~ApplyStyleDialog();
    ApplyStyleDialogListItem getStyle();

protected:
    bool eventFilter(QObject *obj, QEvent *ev);
private:
    Ui::ApplyStyleDialog *ui;
    ScribusAPIDocument* document;
    QList<ApplyStyleDialogListItem> styles;
    QList<ApplyStyleDialogListItem> stylesSelected;
    int currentStyleSelected = 0;
    // QStringList paragraphStyles;
    // QStringList characterStyles;
    void updateLabel();
    QString getStylesFiltered(const QString filterText);
private slots:
    void updateLabel(const QString& inputText);
};

#endif // APPLYSTYLEDIALOG_H
