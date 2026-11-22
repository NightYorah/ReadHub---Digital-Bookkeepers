#ifndef STARRATINGWIDGET_H
#define STARRATINGWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QList>

class StarRatingWidget : public QWidget {
public:
    explicit StarRatingWidget(QWidget *parent = nullptr) : QWidget(parent) {
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(3);

        for (int i = 1; i <= 5; ++i) {
            QPushButton *btn = new QPushButton("☆", this);
            btn->setProperty("starIndex", i);
            btn->setCursor(Qt::PointingHandCursor);
            btn->setFixedSize(24, 24);
            btn->setStyleSheet("QPushButton { border: none; background: transparent; font-size: 19px; color: #bdc3c7; }");
            connect(btn, &QPushButton::clicked, this, [this, i]() {
                setRating(i);
            });
            starButtons.append(btn);
            layout->addWidget(btn);
        }
        layout->addStretch();
    }

    int rating() const { return currentRating; }

    void setRating(int rating) {
        currentRating = qBound(0, rating, 5);
        for (int i = 0; i < starButtons.size(); ++i) {
            if (i < currentRating) {
                starButtons[i]->setText("★");
                starButtons[i]->setStyleSheet("QPushButton { border: none; background: transparent; font-size: 19px; color: #f39c12; }");
            } else {
                starButtons[i]->setText("☆");
                starButtons[i]->setStyleSheet("QPushButton { border: none; background: transparent; font-size: 19px; color: #bdc3c7; }");
            }
        }
    }

private:
    int currentRating = 0;
    QList<QPushButton*> starButtons;
};

#endif // STARRATINGWIDGET_H
