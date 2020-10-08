#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>

namespace Ui {
class CustomLabel;
}

class CustomLabel : public QWidget
{
    Q_OBJECT

public:
    explicit CustomLabel( QWidget *parent = nullptr );
    ~CustomLabel();
    void mouseMoveEvent( QMouseEvent *event );
    void mouseReleaseEvent( QMouseEvent *event );
Q_SIGNALS:
    void positionChanged( QPoint last, QPoint current );
private:
    Ui::CustomLabel*    m_ui;
    QPoint              m_lastPoint;
    QPoint              m_currentPoint;
};

#endif // CUSTOMLABEL_H
