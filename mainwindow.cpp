#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setupInputOutputNodes();

    // Add initial processing node
    addNode();
}

void MainWindow::setupUI() {
    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);

    // Input/Output section
    QHBoxLayout *ioLayout = new QHBoxLayout();

    // Input
    QVBoxLayout *inputLayout = new QVBoxLayout();
    inputButton = new QPushButton("Select Input Image", centralWidget);
    inputPreview = new QLabel(centralWidget);
    inputPreview->setAlignment(Qt::AlignCenter);
    inputPreview->setMinimumSize(200, 150);
    inputPreview->setStyleSheet("border: 1px solid gray;");
    inputLayout->addWidget(inputButton);
    inputLayout->addWidget(inputPreview);
    ioLayout->addLayout(inputLayout);

    // Output
    QVBoxLayout *outputLayout = new QVBoxLayout();
    outputButton = new QPushButton("Select Output File", centralWidget);
    outputPreview = new QLabel(centralWidget);
    outputPreview->setAlignment(Qt::AlignCenter);
    outputPreview->setMinimumSize(200, 150);
    outputPreview->setStyleSheet("border: 1px solid gray;");
    outputLayout->addWidget(outputButton);
    outputLayout->addWidget(outputPreview);
    ioLayout->addLayout(outputLayout);

    mainLayout->addLayout(ioLayout);

    // Processing nodes
    nodesLayout = new QVBoxLayout();
    spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    // Buttons
    buttonLayout = new QHBoxLayout();
    addButton = new QPushButton("Add Node", centralWidget);
    renderButton = new QPushButton("Render", centralWidget);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(renderButton);

    // Add layouts to main layout
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(nodesLayout);
    mainLayout->addItem(spacer);

    // Set central widget
    setCentralWidget(centralWidget);

    // Connections
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addNode);
    connect(renderButton, &QPushButton::clicked, this, &MainWindow::renderImage);
    connect(inputButton, &QPushButton::clicked, this, &MainWindow::browseInputImage);
    connect(outputButton, &QPushButton::clicked, this, &MainWindow::selectOutputFile);
}

void MainWindow::setupInputOutputNodes() {
    // These are fixed and can't be removed
    // The actual processing nodes will be added between them
}

void MainWindow::addNode() {
    Node *node = new Node(centralWidget);
    nodes.append(node);
    nodesLayout->insertWidget(nodesLayout->count() - 1, node); // Insert before spacer

    connect(node, &Node::deleteRequested, this, &MainWindow::removeNode);
    connect(node, &Node::functionChanged, this, &MainWindow::updatePreview);
}

void MainWindow::removeNode(Node* node) {
    nodes.removeOne(node);
    node->deleteLater();
    updatePreview();
}

void MainWindow::browseInputImage() {
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Select Input Image",
                                                    QDir::homePath(),
                                                    "Images (*.png *.jpg *.jpeg *.bmp)");

    if (!filePath.isEmpty()) {
        inputFilePath = filePath;
        originalImage = ImageProcessor::loadImage(filePath);

        // Update preview
        QImage qimg(originalImage.data, originalImage.cols, originalImage.rows,
                    originalImage.step, QImage::Format_BGR888);
        inputPreview->setPixmap(QPixmap::fromImage(qimg).scaled(
            inputPreview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        updatePreview();
    }
}

void MainWindow::selectOutputFile() {
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Select Output File",
                                                    QDir::homePath(),
                                                    "Images (*.png *.jpg *.jpeg *.bmp)");

    if (!filePath.isEmpty()) {
        outputFilePath = filePath;
    }
}

void MainWindow::renderImage() {
    if (originalImage.empty()) {
        qDebug() << "No input image selected";
        return;
    }

    if (outputFilePath.isEmpty()) {
        qDebug() << "No output file selected";
        return;
    }

    processImage();

    // Save the result
    if (!processedImage.empty()) {
        if (ImageProcessor::saveImage(processedImage, outputFilePath)) {
            qDebug() << "Image saved successfully to" << outputFilePath;

            // Update output preview
            QImage qimg(processedImage.data, processedImage.cols, processedImage.rows,
                        processedImage.step, processedImage.channels() == 1 ?
                            QImage::Format_Grayscale8 : QImage::Format_BGR888);
            outputPreview->setPixmap(QPixmap::fromImage(qimg).scaled(
                outputPreview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            qDebug() << "Failed to save image";
        }
    }
}

void MainWindow::processImage() {
    if (originalImage.empty()) return;

    cv::Mat result = originalImage.clone();

    // Apply each node's operation in sequence
    for (Node* node : nodes) {
        QVariantList params = node->getParameters();

        switch(node->currentFunction()) {
        case Node::BrightnessContrast:
            if (params.size() >= 2) {
                result = ImageProcessor::applyBrightnessContrast(
                    result, params[0].toDouble(), params[1].toInt());
            }
            break;
        case Node::GaussianBlur:
            if (params.size() >= 1) {
                result = ImageProcessor::applyGaussianBlur(
                    result, params[0].toInt());
            }
            break;
        case Node::Threshold:
            if (params.size() >= 1) {
                result = ImageProcessor::applyThreshold(
                    result, params[0].toDouble());
            }
            break;
        case Node::GaussianNoise:
            if (params.size() >= 1) {
                result = ImageProcessor::addGaussianNoise(
                    result, params[0].toDouble());
            }
            break;
        default:
            break;
        }
    }

    processedImage = result;
}

void MainWindow::updatePreview() {
    if (originalImage.empty()) return;

    processImage();

    // Update output preview with processed image
    if (!processedImage.empty()) {
        QImage qimg(processedImage.data, processedImage.cols, processedImage.rows,
                    processedImage.step, processedImage.channels() == 1 ?
                        QImage::Format_Grayscale8 : QImage::Format_BGR888);
        outputPreview->setPixmap(QPixmap::fromImage(qimg).scaled(
            outputPreview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

MainWindow::~MainWindow() {
    qDeleteAll(nodes);
}
