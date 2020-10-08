#include "precompiled.h"
#include "mainwindow.h"
#include "customlabel.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
    , m_ui( new Ui::MainWindow )
    , m_filename( QString() )
    , m_pixmap( nullptr )
{
    m_ui->setupUi( this );
    setMouseTracking( true );

    connect( m_ui->aAbout, &QAction::triggered, this, &MainWindow::onAboutClicked );
    connect( m_ui->aAboutQt, &QAction::triggered, this, &MainWindow::onAboutQtClicked );
    connect( m_ui->aOpen, &QAction::triggered, this, &MainWindow::onOpenImage );
    connect( m_ui->aClose, &QAction::triggered, this, &MainWindow::close );
    connect( m_ui->paintLabel, &CustomLabel::positionChanged, this, &MainWindow::onPositionChanged );
}

MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_pixmap;
    delete m_label;
}

void MainWindow::onOpenImage()
{
    m_filename = QFileDialog::getOpenFileName( this,
        tr( "Open Image" ), QCoreApplication::applicationDirPath(), tr( "Image Files (*.png *.jpg *.bmp)" ) );
    m_pixmap = new QPixmap( m_filename );
    m_ui->paintLabel->setPixmap( *m_pixmap );
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

void MainWindow::onPositionChanged( QPoint last, QPoint current )
{
    m_lastPoint = last;
    m_currentPoint = current;
    qDebug() << last << current;
}

void MainWindow::paintEvent( QPaintEvent* event )
{
    Q_UNUSED( event );
    if( m_pixmap != 0 )
    {
        QPainter painter( m_pixmap );
        painter.setPen( QColor( 0, 0, 0, 255 ) );

        painter.drawLine( m_lastPoint, m_currentPoint );

        m_ui->paintLabel->setPixmap( *m_pixmap );
    }
}
