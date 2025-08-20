#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_browseTextButton_clicked();
    void on_compressButtonlabel_clicked();
    void on_downloadCompressedButton_clicked();
    void on_browseCompressedButton_clicked();
    void on_decompressButton_clicked();
    void on_downloadDecompressedButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
