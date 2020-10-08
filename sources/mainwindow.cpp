#include "precompiled.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
    , m_ui( new Ui::MainWindow )
    , m_filename( QString() )
{
    m_ui->setupUi( this );
    setMouseTracking( true );

    connect( m_ui->aAbout, &QAction::triggered, this, &MainWindow::onAboutClicked );
    connect( m_ui->aAboutQt, &QAction::triggered, this, &MainWindow::onAboutQtClicked );
    connect( m_ui->aOpen, &QAction::triggered, this, &MainWindow::onOpenImage );
    connect( m_ui->aClose, &QAction::triggered, this, &MainWindow::close );

    m_pixmap = nullptr;
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::onOpenImage()
{
    m_filename = QFileDialog::getOpenFileName( this,
        tr( "Open Image" ), QCoreApplication::applicationDirPath(), tr( "Image Files (*.png *.jpg *.bmp)" ) );
    m_pixmap = new QPixmap( m_filename );
    update();
}

void MainWindow::onAboutClicked()
{
    QMessageBox::about( this, "About the program",
                              "Painter Application \nTest assignment by Arthur Konovalov for NIX Solutions." );
}

void MainWindow::onAboutQtClicked()
{
    QMessageBox::aboutQt( this, "About Qt" );
}

void MainWindow::mouseMoveEvent( QMouseEvent* event)
{
    if( m_lastPoint == QPoint( 0, 0 ) && m_currentPoint == QPoint( 0, 0 ))
        m_lastPoint = m_currentPoint = event->pos();
    else
    {
        m_lastPoint = m_currentPoint;
        m_currentPoint = event->pos();
    }
    update();
}

void MainWindow::mouseReleaseEvent( QMouseEvent *event )
{
    Q_UNUSED( event );
    m_lastPoint = m_currentPoint = QPoint( 0, 0 );
}

void MainWindow::paintEvent( QPaintEvent* event )
{
    Q_UNUSED( event );
    if( m_pixmap != 0 )
    {
        QPainter painter( m_pixmap );
        painter.setPen( QColor( 0, 0, 0, 255 ) );

        painter.drawLine( m_lastPoint, m_currentPoint );

        m_ui->paintLabel->setPixmap( m_pixmap->scaled( m_ui->paintLabel->width(),
                                                      m_ui->paintLabel->height(),
                                                      Qt::KeepAspectRatio ) );
    }
}
