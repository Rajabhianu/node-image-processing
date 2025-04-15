#include "inputnode.h"

InputNode::InputNode(QWidget *parent)
    : QWidget(parent)
{
    // Create layouts
    mainLayout = new QVBoxLayout(this);

    // Create title label
    titleLabel = new QLabel("Input Image", this);
    titleLabel->setAlignment(Qt::AlignCenter);

    // Create image label
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setMinimumSize(200, 150);
    imageLabel->setStyleSheet("border: 1px solid gray;");

    // Create browse button
    browseButton = new QPushButton("Browse...", this);

    // Add widgets to layout
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(imageLabel);
    mainLayout->addWidget(browseButton);

    // Connections
    connect(browseButton, &QPushButton::clicked, this, &InputNode::browseImage);
}

void InputNode::browseImage()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Select Input Image",
                                                    QDir::homePath(),
                                                    "Images (*.png *.jpg *.jpeg *.bmp)");

    if (!filePath.isEmpty()) {
        input_file = filePath;
        QPixmap pixmap(filePath);
        if (!pixmap.isNull()) {
            imageLabel->setPixmap(pixmap.scaled(imageLabel->size(),
                                                Qt::KeepAspectRatio, Qt::SmoothTransformation));
            emit fileChanged(filePath);
        }
    }
}

QString InputNode::getFilePath() const
{
    return input_file;
}
