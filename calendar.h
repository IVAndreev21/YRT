#ifndef CALENDAR_H
#define CALENDAR_H

#include <QWidget>

namespace Ui {
class calendar;
}

class calendar : public QWidget
{
    Q_OBJECT

public:
    explicit calendar(QWidget *parent = nullptr);
    ~calendar();

private:
    Ui::calendar *ui;
};

#endif // CALENDAR_H
