#include "applystyledialog.h"
#include "ui_applystyledialog.h"

#include<QDebug>
#include<QEvent>
#include<QKeyEvent>
#include<QStringList>
#include<QString>

#include "plugins/scribusAPI/scribusAPIDocument.h"

ApplyStyleDialog::ApplyStyleDialog(QWidget *parent, ScribusAPIDocument* document) :
    QDialog(parent),
    ui(new Ui::ApplyStyleDialog),
    document(document)
{
    QStringList paragraphStyles = document->getParagraphStyleNames();
    qDebug() << paragraphStyles;
    QStringList characterStyles = document->getCharacterStyleNames();
    qDebug() << characterStyles;
    QString labelText;
    if (!paragraphStyles.empty())
    {
        labelText = "¶ " + paragraphStyles.join(" ¶ ");
    }
    if (!characterStyles.empty())
    {
        if (labelText != "")
        {
            labelText += " ";
        }
        labelText += "T " + characterStyles.join(" T ");
    }
    qDebug() << labelText;
    ui->setupUi(this);
    // close if click outside of the dialog
    // setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
	ui->lineEdit->installEventFilter(this);
    ui->label->setText(labelText);
	installEventFilter(this);
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
                qDebug() << "Ate key press" << keyEvent->key();
                ui->label->setText(ui->lineEdit->text());
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
