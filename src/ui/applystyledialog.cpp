#include "applystyledialog.h"
#include "ui_applystyledialog.h"

#include<QObject>
#include<QDebug>
#include<QEvent>
#include<QKeyEvent>
#include<QStringList>
#include<QString>
#include<QRegularExpression>

#include "plugins/scribusAPI/scribusAPIDocument.h"

ApplyStyleDialog::ApplyStyleDialog(QWidget *parent, ScribusAPIDocument* document) :
    QDialog(parent),
    ui(new Ui::ApplyStyleDialog),
    document(document)
{
    foreach (QString styleName, document->getParagraphStyleNames())
    {
        styles.append(ApplyStyleDialogListItem("paragraph", styleName));
    }
    // paragraphStyles = document->getParagraphStyleNames();
    // qDebug() << paragraphStyles;
    foreach (QString styleName, document->getCharacterStyleNames())
    {
        styles.append(ApplyStyleDialogListItem("character", styleName));
    }
    // characterStyles = document->getCharacterStyleNames();
    // qDebug() << characterStyles;

    ui->setupUi(this);

    updateLabel();
	ui->lineEdit->installEventFilter(this);
	installEventFilter(this);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, static_cast<void (ApplyStyleDialog::*)(const QString &)>(&ApplyStyleDialog::updateLabel));

}

ApplyStyleDialog::~ApplyStyleDialog()
{
    delete ui;
}

ApplyStyleDialogListItem ApplyStyleDialog::getStyle()
{
    return (stylesSelected.size() > 0 ? stylesSelected.at(currentStyleSelected) : ApplyStyleDialogListItem("", ""));
}

/**
 * @brief capture return, esc, and tab and mouse clicks
 */
bool ApplyStyleDialog::eventFilter(QObject *obj, QEvent *event)
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
                if (currentStyleSelected < styles.size() - 1)
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

QString ApplyStyleDialog::getStylesFiltered(const QString filterText)
{
    QStringList styleNamesSelected;
    stylesSelected.clear();
    QList<ApplyStyleDialogListItem> stylesNotSelected;

    // todo: probably we have to escape filterText:
    // QRegExp::escape(filterText);
	QRegularExpression re(filterText, QRegularExpression::CaseInsensitiveOption);

    foreach (ApplyStyleDialogListItem style, styles)
    {
        QRegularExpressionMatch match = re.match(style.name);
        if (match.hasMatch())
            stylesSelected.append(style);
        else
            stylesNotSelected.append(style);
    }

    // Find the word boundaries matching each letter in the filter
	QRegularExpression reWords(filterText, QRegularExpression::CaseInsensitiveOption);

    // TODO: disable the apply button if no style selected
    // TODO: separate the creation of the string list from the selection of the styles

    // TODO: sort alphabetically the stylesSelected

    int i = 0;
    foreach (ApplyStyleDialogListItem style, stylesSelected)
    {
        QString item;
        item += style.name;
        if (i == currentStyleSelected)
            item = "<b>"+item+"</b>";
        item = (style.type == "paragraph" ? "¶ " : "T ") + item;
        styleNamesSelected.append(item);
        stylesSelected.append(style);
        ++i;
    }

    return styleNamesSelected.join(" ");
}

void ApplyStyleDialog::updateLabel()
{
    updateLabel(ui->lineEdit->text());
}

void ApplyStyleDialog::updateLabel(const QString& inputText)
{
    ui->label->setText(getStylesFiltered(inputText));
}
