#include "precompiled.h"
#include "mainwindow.h"
#include "customlabel.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
    , m_ui( new Ui::MainWindow )
    , m_filename( QString() )
    , m_pixmap( nullptr )
    , m_color( QColor() )
    , m_showFlag( true )
{
    m_ui->setupUi( this );
    setMouseTracking( true );

    connect( m_ui->aAbout, &QAction::triggered, this, &MainWindow::onAboutClicked );
    connect( m_ui->aAboutQt, &QAction::triggered, this, &MainWindow::onAboutQtClicked );
    connect( m_ui->aOpen, &QAction::triggered, this, &MainWindow::onOpenImage );
    connect( m_ui->aSave, &QAction::triggered, this, &MainWindow::onSaveImage );
    connect( m_ui->aClose, &QAction::triggered, this, &MainWindow::close );
    connect( m_ui->paintLabel, &CustomLabel::positionChanged, this, &MainWindow::onPositionChanged );
    connect( m_ui->paintLabel, &CustomLabel::mousePressed, this, &MainWindow::onPathStarted );
    connect( m_ui->aClearAll, &QAction::triggered, this, &MainWindow::onClearAll );
    connect( m_ui->aShowAll, &QAction::triggered, this, &MainWindow::onShowAll );

    connect( m_ui->aBlack, &QAction::triggered, this, &MainWindow::onColorChanged );
    connect( m_ui->aWhite, &QAction::triggered, this, &MainWindow::onColorChanged );
    connect( m_ui->aRed, &QAction::triggered, this, &MainWindow::onColorChanged );
    connect( m_ui->aGreen, &QAction::triggered, this, &MainWindow::onColorChanged );
    connect( m_ui->aBlue, &QAction::triggered, this, &MainWindow::onColorChanged );
}

MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_pixmap;
    delete m_label;
    while( !m_path.isEmpty() )
    {
        delete m_path.takeLast();
    }
}

void MainWindow::onOpenImage()
{
    m_filename = QFileDialog::getOpenFileName( this,
        tr( "Open Image" ), QCoreApplication::applicationDirPath(), tr( "Image Files (*.png *.jpg *.bmp)" ) );
    m_pixmap = new QPixmap( m_filename );
    m_ui->paintLabel->setPixmap( *m_pixmap );
    update();
}

void MainWindow::onSaveImage()
{
    m_pixmap->save( m_filename );
    delete m_pixmap;
    m_pixmap = nullptr;
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

void MainWindow::onColorChanged()
{
    QObject* colorAddress = sender();
    if( colorAddress == m_ui->aBlack )
    {
        qDebug() << "Changed current color to black";
        m_color = QColor ( 0, 0, 0, 255 );
        return;
    }
    if( colorAddress == m_ui->aWhite )
    {
        qDebug() << "Changed current color to white";
        m_color = QColor ( 255, 255, 255, 255 );
        return;
    }
    if( colorAddress == m_ui->aRed )
    {
        qDebug() << "Changed current color to red";
        m_color = QColor ( 255, 0, 0, 255 );
        return;
    }
    if( colorAddress == m_ui->aGreen )
    {
        qDebug() << "Changed current color to green";
        m_color = QColor ( 0, 255, 0, 255 );
        return;
    }
    if( colorAddress == m_ui->aBlue )
    {
        qDebug() << "Changed current color to blue";
        m_color = QColor ( 0, 0, 255, 255 );
        return;
    }
}

void MainWindow::onPositionChanged( QPoint last, QPoint current )
{
    m_lastPoint = last;
    m_currentPoint = current;
}

void MainWindow::onPathStarted()
{
    m_path.append( new QPainterPath() );
    m_path.last()->moveTo( m_currentPoint );
    update();
}

void MainWindow::onClearAll()
{
    delete m_pixmap;
    m_pixmap = new QPixmap( m_filename );
    m_showFlag = false;
    update();
}

void MainWindow::onShowAll()
{
    QPainter painter( m_pixmap );
    m_showFlag = true;

    painter.setPen( m_color );

    foreach( auto item, m_path )
        painter.drawPath( *item );

    m_ui->paintLabel->setPixmap( *m_pixmap );
    update();
}

void MainWindow::paintEvent( QPaintEvent* event )
{
    Q_UNUSED( event );
    if( m_pixmap == 0 || m_path.isEmpty() )
        return;

    if( m_showFlag )
    {
        QPainter painter( m_pixmap );

        painter.setPen( m_color );

        m_path.last()->lineTo( m_currentPoint );
        painter.drawPath( *m_path.last() );
    }
    m_ui->paintLabel->setPixmap( *m_pixmap );

}
