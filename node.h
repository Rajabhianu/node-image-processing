#ifndef NODE_H
#define NODE_H

#include <QWidget>
#include <QComboBox>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QStackedWidget>

class Node : public QWidget
{
    Q_OBJECT

public:
    enum FunctionType {
        BrightnessContrast,
        GaussianBlur,
        Threshold,
        GaussianNoise,
        FUNCTION_COUNT
    };

    explicit Node(QWidget *parent = nullptr);
    ~Node() = default;

    FunctionType currentFunction() const;
    QVariantList getParameters() const;
    void setTitle(const QString &title);

    static QString functionName(FunctionType type);

signals:
    void deleteRequested(Node* node);
    void functionChanged();

private slots:
    void updateFunctionUI(int index);

private:
    void setupBrightnessContrastUI();
    void setupGaussianBlurUI();
    void setupThresholdUI();
    void setupGaussianNoiseUI();

    QComboBox *functionCombo;
    QLabel *titleLabel;
    QPushButton *deleteButton;
    QVBoxLayout *mainLayout;
    QHBoxLayout *titleLayout;
    QStackedWidget *parameterStack;

    // Parameter widgets for each function
    QWidget *brightnessContrastWidget;
    QDoubleSpinBox *alphaSpin;
    QSlider *betaSlider;

    QWidget *gaussianBlurWidget;
    QSlider *kernelSizeSlider;

    QWidget *thresholdWidget;
    QSlider *thresholdSlider;

    QWidget *gaussianNoiseWidget;
    QDoubleSpinBox *stddevSpin;
};

#endif // NODE_H
