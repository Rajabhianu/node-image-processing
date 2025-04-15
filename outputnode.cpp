#include "outputnode.h"

OutputNode::OutputNode(QWidget *parent)
    : QWidget(parent)
{
    // Create layouts
    mainLayout = new QVBoxLayout(this);

    // Create title label
    titleLabel = new QLabel("Output File", this);
    titleLabel->setAlignment(Qt::AlignCenter);

    // Create path edit and browse button
    QHBoxLayout *pathLayout = new QHBoxLayout();
    pathEdit = new QLineEdit(this);
    browseButton = new QPushButton("Browse...", this);

    pathLayout->addWidget(pathEdit);
    pathLayout->addWidget(browseButton);

    // Add widgets to layout
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(pathLayout);

    // Connections
    connect(browseButton, &QPushButton::clicked, this, &OutputNode::selectOutputFile);
    connect(pathEdit, &QLineEdit::textChanged, [this](const QString &text) {
        output_file = text;
        emit fileChanged(text);
    });
}

void OutputNode::selectOutputFile()
{
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Select Output File",
                                                    QDir::homePath(),
                                                    "Images (*.png *.jpg *.jpeg *.bmp)");

    if (!filePath.isEmpty()) {
        output_file = filePath;
        pathEdit->setText(filePath);
        emit fileChanged(filePath);
    }
}

QString OutputNode::getFilePath() const
{
    return output_file;
}
