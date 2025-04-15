#ifndef INPUTNODE_H
#define INPUTNODE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QPixmap>

class InputNode : public QWidget
{
    Q_OBJECT

public:
    explicit InputNode(QWidget *parent = nullptr);
    QString getFilePath() const;

signals:
    void fileChanged(const QString &filePath);

private slots:
    void browseImage();

private:
    QLabel *titleLabel;
    QLabel *imageLabel;
    QPushButton *browseButton;
    QVBoxLayout *mainLayout;
    QString input_file;
};

#endif // INPUTNODE_H
