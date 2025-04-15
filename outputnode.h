#ifndef OUTPUTNODE_H
#define OUTPUTNODE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QLineEdit>

class OutputNode : public QWidget
{
    Q_OBJECT

public:
    explicit OutputNode(QWidget *parent = nullptr);
    QString getFilePath() const;

signals:
    void fileChanged(const QString &filePath);

private slots:
    void selectOutputFile();

private:
    QLabel *titleLabel;
    QLineEdit *pathEdit;
    QPushButton *browseButton;
    QVBoxLayout *mainLayout;
    QString output_file;
};

#endif // OUTPUTNODE_H
