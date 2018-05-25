#ifndef APPLYSTYLEDIALOG_H
#define APPLYSTYLEDIALOG_H

#include<QObject>
#include <QDialog>
#include <QString>
#include <QMainWindow>

#include <vector>
#include <string>

namespace ScribusAPI { class Document; }

struct ApplyStyleDialogListItem
{
    ApplyStyleDialogListItem(std::string type, std::string name): type{type}, name{name} {}
    std::string type; // todo: use a constant from APIDocumentStyle
    std::string name;
};

namespace Ui {
class ApplyStyleDialog;
}

class ApplyStyleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ApplyStyleDialog(QMainWindow *parent, ScribusAPI::Document& document);
    ~ApplyStyleDialog();
    ApplyStyleDialogListItem getStyle();

protected:
    bool eventFilter(QObject *obj, QEvent *ev);
private:
    Ui::ApplyStyleDialog *ui;
    ScribusAPI::Document& document;
    std::vector<ApplyStyleDialogListItem> styles;
    std::vector<ApplyStyleDialogListItem> stylesSelected;
    size_t currentStyleSelected = 0;
    // QStringList paragraphStyles;
    // QStringList characterStyles;
    void updateLabel();
    std::string getStylesFiltered(const std::string filterText);
private slots:
    void updateLabel(const QString& inputText);
};

#endif // APPLYSTYLEDIALOG_H
