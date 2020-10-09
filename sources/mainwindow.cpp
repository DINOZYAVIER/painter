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
    , m_currentPath ( 0 )
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

    connect( m_ui->aUndo, &QAction::triggered, this, &MainWindow::onUndo );
    connect( m_ui->aRedo, &QAction::triggered, this, &MainWindow::onRedo );
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
    qDebug() << "path started" << m_currentPath << m_path.size();
    if( m_currentPath < m_path.size() )
    {
        int var = m_path.size() - m_currentPath;
        while( var-- )
            delete m_path.takeLast();
    }
    m_path.append( new QPainterPath() );
    m_path.last()->moveTo( m_currentPoint );
    ++m_currentPath;
    update();
}

void MainWindow::onUndo()
{
    if( m_path.size() == 0 || m_currentPath == 0 )
        return;
    if( m_currentPath > 0 )
        --m_currentPath;
    else
        m_currentPath = m_path.size() - 2;
    delete m_pixmap;
    m_pixmap = new QPixmap( m_filename );
    qDebug() << "undo" << m_currentPath;
}

void MainWindow::onRedo()
{
    if( m_currentPath == m_path.size() )
        return;
    ++m_currentPath;
    delete m_pixmap;
    m_pixmap = new QPixmap( m_filename );
    qDebug() << "redo" << m_currentPath;
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
    m_showFlag = true;
    QPainter painter( m_pixmap );

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
        for( int i = 0; i < m_currentPath; ++i )
            painter.drawPath( *m_path.at( i ) );
    }
    m_ui->paintLabel->setPixmap( *m_pixmap );

}
