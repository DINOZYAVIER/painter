#ifndef CUSTOMPAINTER_H
#define CUSTOMPAINTER_H

#include <QObject>

class CustomPainter : public QObject
{
    Q_OBJECT
public:
    explicit CustomPainter( QObject *parent = nullptr );

signals:

};

#endif // CUSTOMPAINTER_H
