#include "precompiled.h"
#include "customlabel.h"

CustomLabel::CustomLabel( QWidget* parent ) :
    QLabel( parent )
{
}

CustomLabel::~CustomLabel()
{
}

void CustomLabel::mouseMoveEvent( QMouseEvent* event )
{
    if( m_lastPoint == QPoint( 0, 0 ) && m_currentPoint == QPoint( 0, 0 ) )
    {
        m_lastPoint = m_currentPoint = event->pos();
    }
    else
    {
        m_lastPoint = m_currentPoint;
        m_currentPoint = event->pos();
    }
    Q_EMIT positionChanged( m_lastPoint, m_currentPoint );
}

void CustomLabel::mousePressEvent( QMouseEvent* event )
{
    m_lastPoint = m_currentPoint = event->pos();
    Q_EMIT positionChanged( m_lastPoint, m_currentPoint );
    Q_EMIT mousePressed();
}

void CustomLabel::mouseReleaseEvent( QMouseEvent* event )
{
    Q_UNUSED( event );
    Q_EMIT positionChanged( m_lastPoint, m_currentPoint );
}


