#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "huffman.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Browse original text file
void MainWindow::on_browseTextButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Text File", "", "Text Files (*.txt)");
    if (!fileName.isEmpty())
        ui->inputFileLineEdit->setText(fileName);
}

// Compress file
void MainWindow::on_compressButtonlabel_clicked()
{
    QString inputFile = ui->inputFileLineEdit->text();

    if (inputFile.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select an input file!");
        return;
    }

    QString outputFile = QFileDialog::getSaveFileName(this, "Save Compressed File", "", "Compressed Files (*.bin)");
    if (outputFile.isEmpty()) return;

    HuffmanCoding huffman;
    huffman.compress(inputFile.toStdString(), outputFile.toStdString());

    ui->compressedFileLineEdit->setText(outputFile);

    QFileInfo fi(inputFile);
    QFileInfo fo(outputFile);
    ui->statusLabel->setText(QString("Compression complete! Original size: %1 bytes, Compressed size: %2 bytes").arg(fi.size()).arg(fo.size()));
}

// Download Compressed File
void MainWindow::on_downloadCompressedButton_clicked()
{
    QString compressedFile = ui->compressedFileLineEdit->text();

    if (compressedFile.isEmpty()) {
        QMessageBox::warning(this, "Warning", "No compressed file to download!");
        return;
    }

    QString savePath = QFileDialog::getSaveFileName(this, "Save Compressed File", "", "Compressed Files (*.bin)");
    if (savePath.isEmpty()) return;

    if (QFile::copy(compressedFile, savePath))
        QMessageBox::information(this, "Success", "Compressed file saved.");
    else
        QMessageBox::warning(this, "Error", "Failed to save compressed file.");
}

// Browse compressed file for decompression
void MainWindow::on_browseCompressedButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Compressed File", "", "Compressed Files (*.bin)");
    if (!fileName.isEmpty())
        ui->compressedFileLineEdit->setText(fileName);
}

// Decompress function
void MainWindow::on_decompressButton_clicked()
{
    QString inputFile = ui->compressedFileLineEdit->text();

    if (inputFile.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a compressed file!");
        return;
    }

    QString outputFile = QFileDialog::getSaveFileName(this, "Save Decompressed File", "", "Text Files (*.txt)");
    if (outputFile.isEmpty()) return;

    HuffmanCoding huffman;
    huffman.decompress(inputFile.toStdString(), outputFile.toStdString());

    ui->decompressedFileLineEdit->setText(outputFile);
    ui->statusLabel->setText("Decompression complete!");
}

// Download Decompressed File
void MainWindow::on_downloadDecompressedButton_clicked()
{
    QString decompressedFile = ui->decompressedFileLineEdit->text();

    if (decompressedFile.isEmpty()) {
        QMessageBox::warning(this, "Warning", "No decompressed file to download!");
        return;
    }

    QString savePath = QFileDialog::getSaveFileName(this, "Save Decompressed File", "", "Text Files (*.txt)");
    if (savePath.isEmpty()) return;

    if (QFile::copy(decompressedFile, savePath))
        QMessageBox::information(this, "Success", "Decompressed file saved.");
    else
        QMessageBox::warning(this, "Error", "Failed to save decompressed file.");
}
