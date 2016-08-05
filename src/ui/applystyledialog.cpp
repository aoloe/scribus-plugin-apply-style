#include "applystyledialog.h"
#include "ui_applystyledialog.h"

#include<QDebug>
#include<QEvent>
#include<QKeyEvent>

ApplyStyleDialog::ApplyStyleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApplyStyleDialog)
{
    ui->setupUi(this);
	ui->lineEdit->installEventFilter(this);
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
                return false;
            }
        } else if (event->type() == QEvent::MouseButtonRelease) {
			this->reject();
            return true;
		} else {
            return false;
        }
    } else {
        // pass the event on to the parent class
        return QDialog::eventFilter(obj, event);
    }
}
