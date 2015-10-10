#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "enhance.h"

#include <QDebug>

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->splitter->setSizes(QList<int>() << 1 << 3);
}

void MainWindow::on_loadButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                "Select an image",
                                                QDir::homePath(),
                                                "JPEG (*.jpg *.jpeg);; PNG (*.png);; All files (*.*)");

    qDebug() << path;

    if(path.isEmpty())
        return;

    if(image.load(path))
    {
        Enhance::convertToGray(&image);
        showImage();

        // take a copy
        imageCopy = image.copy();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Can't load image, choose a correct format (jpg, png) and try again.");
    }
}

void MainWindow::showImage()
{
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_applyButton_clicked()
{
    switch(ui->tabEnhance->currentIndex())
    {
    case 0:
        Enhance::applyNegative(&image, 8);
        break;
    case 1:
        Enhance::applyPower(&image, ui->powConstSping->value(), ui->powGammaSpin->value());
        break;
    case 2:
        if(ui->logRadio->isChecked())
            Enhance::applyLog(&image, ui->logConstSpin->value());
        else
            Enhance::applyInverseLog(&image, ui->logConstSpin->value());
        break;
    case 3:
        Enhance::applyStretching(&image, ui->stretchSMin->value(), ui->stretchSMax->value());
        break;
    default: break;
    }

    showImage();
}

void MainWindow::on_undoButton_clicked()
{
    image = imageCopy;
    showImage();
}

void MainWindow::on_saveButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this,
                                                "Select an image",
                                                QDir::homePath(),
                                                "PNG (*.png);; All files (*.*)");

    if(path.isEmpty())
        return;

    qDebug() << path;

    QFileInfo info(path);

    if(info.suffix().isEmpty())
        path += ".png";

    if(!image.save(path))
    {
        QMessageBox::critical(this, "Error", "Can't save image, check the file name and the extenstion (format) then try again.");
    }

}

void MainWindow::on_quitButton_clicked()
{
    QApplication::exit();
}


void MainWindow::on_aboutAction_triggered(bool checked)
{
    Q_UNUSED(checked)
    QMessageBox::about(this , "About Image Enhancement",
                       "<b>Image Enhancement</b> <br>Version: 0.0.1<br>"
                       "<b>Computer Vision</b> Project"
                       "<br>By: Abdelrahman Ghanem <br>Mahmoud Sayed Zainhom");
}

void MainWindow::on_quitAction_triggered(bool checked)
{
    Q_UNUSED(checked)
    QApplication::exit();
}


MainWindow::~MainWindow()
{
    delete ui;
}
