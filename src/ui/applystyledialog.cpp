#include "applystyledialog.h"
#include "ui_applystyledialog.h"

ApplyStyleDialog::ApplyStyleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApplyStyleDialog)
{
    ui->setupUi(this);
}

ApplyStyleDialog::~ApplyStyleDialog()
{
    delete ui;
}
