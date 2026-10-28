#ifndef READWINDOW_H
#define READWINDOW_H

#include <QMainWindow>
#include <QString>
#include <fpdfview.h>

class QLabel;

class ReadWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReadWindow(const QString &pdfPath, QWidget *parent = nullptr);
    ~ReadWindow() override;

private:
    FPDF_DOCUMENT document = nullptr;
    QLabel *readLabel = nullptr;
};

#endif
