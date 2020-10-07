#ifndef CUSTOMPAINTER_H
#define CUSTOMPAINTER_H

#include <QObject>

class QPixmap;

class CustomPainter : public QObject
{
    Q_OBJECT
public:
    explicit CustomPainter( QObject *parent = nullptr, QPixmap* pixmap = nullptr );
private:
    QPixmap* m_pixmap;
};

#endif // CUSTOMPAINTER_H
