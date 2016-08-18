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
    connect(ui->lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateLabel(const QString&)));

}

ApplyStyleDialog::~ApplyStyleDialog()
{
    delete ui;
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
                this->accept();
                return true;
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

    // todo: probably we have to escape filterText:
    // QRegExp::escape(filterText);
	QRegularExpression re(filterText, QRegularExpression::CaseInsensitiveOption);

    int i = 0;
    foreach (ApplyStyleDialogListItem style, styles)
    {
        QRegularExpressionMatch match = re.match(style.name);
        if (match.hasMatch())
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
