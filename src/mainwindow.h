#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void showImage();

public slots:
    void on_loadButton_clicked();
    void on_applyButton_clicked();
    void on_undoButton_clicked();
    void on_saveButton_clicked();
    void on_quitButton_clicked();

    void on_quitAction_triggered(bool);
    void on_aboutAction_triggered(bool);

private:
    QImage image, imageCopy;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
