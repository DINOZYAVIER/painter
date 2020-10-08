#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>

class CustomLabel : public QLabel
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
    QPoint              m_lastPoint;
    QPoint              m_currentPoint;
};

#endif // CUSTOMLABEL_H
