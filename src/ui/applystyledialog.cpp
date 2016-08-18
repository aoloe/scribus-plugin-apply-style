#include "applystyledialog.h"
#include "ui_applystyledialog.h"

#include<QObject>
#include<QDebug>
#include<QEvent>
#include<QKeyEvent>
#include<QStringList>
#include<QString>
#include<QRegExp>

#include "plugins/scribusAPI/scribusAPIDocument.h"

ApplyStyleDialog::ApplyStyleDialog(QWidget *parent, ScribusAPIDocument* document) :
    QDialog(parent),
    ui(new Ui::ApplyStyleDialog),
    document(document)
{
    paragraphStyles = document->getParagraphStyleNames();
    // qDebug() << paragraphStyles;
    characterStyles = document->getCharacterStyleNames();
    // qDebug() << characterStyles;

    ui->setupUi(this);

    initLabel();
	ui->lineEdit->installEventFilter(this);
	installEventFilter(this);
    connect(ui->lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateLabel(const QString&)));

}

ApplyStyleDialog::~ApplyStyleDialog()
{
    delete ui;
}

/*
void ApplyStyleDialog::keyPressEvent(QKeyEvent *evt)
{
    if(evt->key() == Qt::Key_Enter || evt->key() == Qt::Key_Return)
		evt->accept();
    QDialog::keyPressEvent(evt);
}
*/

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
                qDebug() << "Tab key press" << keyEvent->key();
                return true;
            } else {
                /*
                qDebug() << "A key press" << keyEvent->key();
                qDebug() << "A key press" << keyEvent->text();
                */
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
    QString styles = "";

	QRegExp rx(filterText, Qt::CaseInsensitive);

    // QStringList pSelected = filterText.isEmpty() ? paragraphStyles : paragraphStyles.filter(rx);
    // QStringList cSelected = filterText.isEmpty() ? characterStyles : characterStyles.filter(rx);
    QStringList pSelected = paragraphStyles.filter(rx);
    QStringList cSelected = characterStyles.filter(rx);

    if (!pSelected.empty())
    {
        styles += "¶ " + pSelected.join(" ¶ ") + " ";
    }
    if (!cSelected.empty())
    {
        styles += "T " + cSelected.join(" T ");
    }
    return styles;
}

void ApplyStyleDialog::updateLabel(const QString& inputText)
{
    ui->label->setText(getStylesFiltered(inputText));
}

void ApplyStyleDialog::initLabel()
{

    ui->label->setText(getStylesFiltered(""));
}
