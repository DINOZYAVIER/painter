#include "custompainter.h"

CustomPainter::CustomPainter( QObject *parent, QPixmap* pixmap ) :
    QObject( parent )
  , m_pixmap( pixmap )
{

}

