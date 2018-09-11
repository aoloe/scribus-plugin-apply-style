#ifndef APPLYSTYLEDIALOG_H
#define APPLYSTYLEDIALOG_H

#include<QObject>
#include <QDialog>
#include <QString>
#include <QMainWindow>

#include <vector>
#include <string>

namespace ScribusAPI { class Document; }

namespace Ui {
class ApplyStyleDialog;
}

namespace ScribusPlugin {
namespace ApplyStyle {

struct ListItem
{
    ListItem(std::string type, std::string name): type{type}, name{name} {}
    std::string type; // todo: use a constant from APIDocumentStyle
    std::string name;
};


class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QMainWindow *parent, ScribusAPI::Document& document);
    ~Dialog();
    ListItem getStyle();

protected:
    bool eventFilter(QObject *obj, QEvent *ev);
private:
    Ui::ApplyStyleDialog *ui;
    ScribusAPI::Document& document;
    std::vector<ListItem> styles;
    std::vector<ListItem> stylesSelected;
    size_t currentStyleSelected = 0;
    // QStringList paragraphStyles;
    // QStringList characterStyles;
    void updateLabel();
    std::string getStylesFiltered(const std::string filterText);
private slots:
    void updateLabel(const QString& inputText);
};

} // ScribusPlugin::ApplyStyle
}

#endif // APPLYSTYLEDIALOG_H
