#include "node.h"
#include <QDebug>

Node::Node(QWidget *parent)
    : QWidget(parent)
{
    // Create layouts
    mainLayout = new QVBoxLayout(this);
    titleLayout = new QHBoxLayout();

    // Create title label
    titleLabel = new QLabel("Node", this);

    // Create delete button
    deleteButton = new QPushButton("X", this);
    deleteButton->setFixedSize(20, 20);

    // Add to title layout
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(deleteButton);

    // Create function selection combo
    functionCombo = new QComboBox(this);
    for (int i = 0; i < FUNCTION_COUNT; i++) {
        functionCombo->addItem(functionName(static_cast<FunctionType>(i)));
    }

    // Create parameter stack
    parameterStack = new QStackedWidget(this);

    // Setup parameter UIs for each function
    setupBrightnessContrastUI();
    setupGaussianBlurUI();
    setupThresholdUI();
    setupGaussianNoiseUI();

    // Add widgets to main layout
    mainLayout->addLayout(titleLayout);
    mainLayout->addWidget(functionCombo);
    mainLayout->addWidget(parameterStack);

    // Connections
    connect(deleteButton, &QPushButton::clicked, [this]() {
        emit deleteRequested(this);
    });

    connect(functionCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &Node::updateFunctionUI);

    // Set initial function
    functionCombo->setCurrentIndex(0);
}

QString Node::functionName(FunctionType type) {
    switch(type) {
    case BrightnessContrast: return "Brightness/Contrast";
    case GaussianBlur: return "Gaussian Blur";
    case Threshold: return "Threshold";
    case GaussianNoise: return "Gaussian Noise";
    default: return "Unknown";
    }
}

Node::FunctionType Node::currentFunction() const {
    return static_cast<FunctionType>(functionCombo->currentIndex());
}

QVariantList Node::getParameters() const {
    QVariantList params;

    switch(currentFunction()) {
    case BrightnessContrast:
        params << alphaSpin->value() << betaSlider->value();
        break;
    case GaussianBlur:
        params << kernelSizeSlider->value();
        break;
    case Threshold:
        params << thresholdSlider->value();
        break;
    case GaussianNoise:
        params << stddevSpin->value();
        break;
    default:
        break;
    }

    return params;
}

void Node::setTitle(const QString &title) {
    titleLabel->setText(title);
}

void Node::updateFunctionUI(int index) {
    parameterStack->setCurrentIndex(index);
    emit functionChanged();
}

void Node::setupBrightnessContrastUI() {
    brightnessContrastWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(brightnessContrastWidget);

    // Alpha parameter (Contrast)
    QHBoxLayout *alphaLayout = new QHBoxLayout();
    alphaLayout->addWidget(new QLabel("Contrast:"));
    alphaSpin = new QDoubleSpinBox();
    alphaSpin->setRange(0.0, 3.0);
    alphaSpin->setSingleStep(0.1);
    alphaSpin->setValue(1.0);
    alphaLayout->addWidget(alphaSpin);
    layout->addLayout(alphaLayout);

    // Beta parameter (Brightness)
    QHBoxLayout *betaLayout = new QHBoxLayout();
    betaLayout->addWidget(new QLabel("Brightness:"));
    betaSlider = new QSlider(Qt::Horizontal);
    betaSlider->setRange(-100, 100);
    betaSlider->setValue(0);
    betaLayout->addWidget(betaSlider);
    layout->addLayout(betaLayout);

    parameterStack->addWidget(brightnessContrastWidget);
}

void Node::setupGaussianBlurUI() {
    gaussianBlurWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(gaussianBlurWidget);

    // Kernel size parameter
    QHBoxLayout *kernelLayout = new QHBoxLayout();
    kernelLayout->addWidget(new QLabel("Kernel Size:"));
    kernelSizeSlider = new QSlider(Qt::Horizontal);
    kernelSizeSlider->setRange(1, 31);
    kernelSizeSlider->setSingleStep(2);
    kernelSizeSlider->setValue(3);
    kernelLayout->addWidget(kernelSizeSlider);
    layout->addLayout(kernelLayout);

    parameterStack->addWidget(gaussianBlurWidget);
}

void Node::setupThresholdUI() {
    thresholdWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(thresholdWidget);

    // Threshold value
    QHBoxLayout *threshLayout = new QHBoxLayout();
    threshLayout->addWidget(new QLabel("Threshold:"));
    thresholdSlider = new QSlider(Qt::Horizontal);
    thresholdSlider->setRange(0, 255);
    thresholdSlider->setValue(127);
    threshLayout->addWidget(thresholdSlider);
    layout->addLayout(threshLayout);

    parameterStack->addWidget(thresholdWidget);
}

void Node::setupGaussianNoiseUI() {
    gaussianNoiseWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(gaussianNoiseWidget);

    // Standard deviation
    QHBoxLayout *stddevLayout = new QHBoxLayout();
    stddevLayout->addWidget(new QLabel("Noise StdDev:"));
    stddevSpin = new QDoubleSpinBox();
    stddevSpin->setRange(0.0, 100.0);
    stddevSpin->setSingleStep(1.0);
    stddevSpin->setValue(10.0);
    stddevLayout->addWidget(stddevSpin);
    layout->addLayout(stddevLayout);

    parameterStack->addWidget(gaussianNoiseWidget);
}
