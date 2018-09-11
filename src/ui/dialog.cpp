#include "dialog.h"
#include "ui_applystyledialog.h"

#include<QObject>
#include<QDebug>
#include<QEvent>
#include<QKeyEvent>
#include<QStringList>
#include<QString>
// #include<QRegularExpression>

#include <vector>
#include <string>
#include <regex>

#include "plugins/scribusAPI/utilsstring.h"
#include "plugins/scribusAPI/document.h"

namespace ScribusPlugin {
namespace ApplyStyle {

Dialog::Dialog(QMainWindow *parent, ScribusAPI::Document& document) :
    QDialog(parent),
    ui(new Ui::ApplyStyleDialog),
    document(document)
{
    for (auto styleName: document.getParagraphStyleNames()) {
        styles.push_back(ListItem("paragraph", styleName));
    }
    for (auto styleName: document.getCharacterStyleNames()) {
        styles.push_back(ListItem("character", styleName));
    }

    ui->setupUi(this);

    updateLabel();
	ui->lineEdit->installEventFilter(this);
	installEventFilter(this);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, static_cast<void (Dialog::*)(const QString &)>(&Dialog::updateLabel));

}

Dialog::~Dialog()
{
    delete ui;
}

ListItem Dialog::getStyle()
{
    return (stylesSelected.size() > 0 ? stylesSelected.at(currentStyleSelected) : ListItem("", ""));
}

/**
 * @brief capture return, esc, and tab and mouse clicks
 */
bool Dialog::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->lineEdit) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return) {
                if (styles.size() > 0)
                {
                    this->accept();
                    return true;
                } else {
                    return false;
                }
            } else if (keyEvent->key() == Qt::Key_Escape) {
                this->reject();
                return true;
            } else if (keyEvent->key() == Qt::Key_Tab) {
                // qDebug() << "Tab key press" << keyEvent->key();
                if (currentStyleSelected <= styles.size())
                    ++currentStyleSelected;
                else
                    currentStyleSelected = 0;
                updateLabel();
                return true;
            } else {
                /*
                qDebug() << "A key press" << keyEvent->key();
                qDebug() << "A key press" << keyEvent->text();
                */
                currentStyleSelected = 0;
                return false;
            }
		} else {
            return false;
        }
    } else if (obj == this) {
        if (event->type() == QEvent::MouseButtonRelease) {
			this->reject();
            return true;
        }
    }
    return false;
}

std::string Dialog::getStylesFiltered(const std::string filterText)
{
    std::vector<std::string> styleNamesSelected;
    stylesSelected.clear();

    std::regex pattern(filterText, std::regex::icase);
    std::smatch match;

    for (auto style: styles) {
        std::regex_search(style.name, match, pattern);
        if (!match.empty()) {
            stylesSelected.push_back(style);
        }
    }

    /*
    // the algorithm way
    std::regex pattern{filterText, std::regex::icase};
    std::smatch match{};

    std::copy_if(styles.begin(), styles.end(),
        std::back_insterter(stylesSelected),
        [&pattern, &match](std::string style) {
            std::regex_search(style, match, pattern);
            return !match.empty();
        });
    */

    /*
    // std::string.find way
    // #include <algorithm>
    std::transform(filterText.begin(), filterText.end(), filterText.begin(), std::tolower)

    for (auto style: styles) {
        std::string = styleName{};
        std::transform(style.begin(), style.end(), styleName.begin(), std::tolower)
        auto found = styleName.find(filterText)
        if (found != std::string::npos) {
            stylesSelected.push_back(style);
        }
    }
    */

    size_t i = 0;
    for (auto style: stylesSelected) {
        std::string item{style.name};
        if (i == currentStyleSelected) {
            item = "<b>"+item+"</b>";
        }
        item = (style.type == "paragraph" ? "¶ " : "T ") + item;
        styleNamesSelected.push_back(item);
        ++i;
    }

    // TODO: Find the word boundaries matching each letter in the filter

    // TODO: disable the apply button if no style selected
    // TODO: separate the creation of the string list from the selection of the styles

    // TODO: sort the stylesSelected alphabetically

    return ScribusAPI::String::join(styleNamesSelected.begin(), styleNamesSelected.end(), " ");
}

void Dialog::updateLabel()
{
    updateLabel(ui->lineEdit->text());
}

void Dialog::updateLabel(const QString& inputText)
{
    ui->label->setText(QString::fromStdString(getStylesFiltered(inputText.toUtf8().constData())));
}

} // ScribusPlugin::ApplyStyle
}
