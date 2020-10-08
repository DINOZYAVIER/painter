#include "precompiled.h"
#include "customlabel.h"
#include "ui_customlabel.h"

CustomLabel::CustomLabel( QWidget *parent ) :
    QWidget( parent ),
    m_ui( new Ui::CustomLabel )
{
    m_ui->setupUi( this );
}

CustomLabel::~CustomLabel()
{
    delete m_ui;
}

void CustomLabel::mouseMoveEvent( QMouseEvent *event )
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
    update();
    Q_EMIT positionChanged( m_lastPoint, m_currentPoint );
}

void CustomLabel::mouseReleaseEvent( QMouseEvent *event )
{
    Q_UNUSED( event );
    m_lastPoint = m_currentPoint = QPoint( 0, 0 );
    Q_EMIT positionChanged( m_lastPoint, m_currentPoint );
}
