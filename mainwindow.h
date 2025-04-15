#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QVector>
#include <QFileDialog>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include "node.h"
#include "imageprocessor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addNode();
    void removeNode(Node* node);
    void browseInputImage();
    void selectOutputFile();
    void renderImage();
    void updatePreview();

private:
    void setupUI();
    void setupInputOutputNodes();
    void processImage();

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QPushButton *addButton;
    QPushButton *renderButton;
    QVBoxLayout *nodesLayout;
    QVector<Node*> nodes;
    QSpacerItem *spacer;

    // Input/Output
    QPushButton *inputButton;
    QPushButton *outputButton;
    QLabel *inputPreview;
    QLabel *outputPreview;
    QString inputFilePath;
    QString outputFilePath;

    // Image data
    cv::Mat originalImage;
    cv::Mat processedImage;
};

#endif // MAINWINDOW_H
