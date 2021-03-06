#include "precompiled.h"
#include "mainwindow.h"
#include "customlabel.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
    , m_ui( new Ui::MainWindow )
    , m_filename( QString() )
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

    m_penColorGroup = new QActionGroup( this );
    m_penColorGroup->addAction( m_ui->aBlack );
    m_penColorGroup->addAction( m_ui->aWhite );
    m_penColorGroup->addAction( m_ui->aRed );
    m_penColorGroup->addAction( m_ui->aGreen );
    m_penColorGroup->addAction( m_ui->aBlue );
    m_ui->aBlack->setCheckable( true );
    m_ui->aWhite->setCheckable( true );
    m_ui->aRed->setCheckable( true );
    m_ui->aGreen->setCheckable( true );
    m_ui->aBlue->setCheckable( true );
    m_ui->aBlack->setChecked( true );
    m_penColorGroup->setExclusive( true );
    connect( m_penColorGroup, &QActionGroup::triggered, this, &MainWindow::onColorChanged );

    m_ui->paintLabel->setAlignment( Qt::AlignLeft );
    m_ui->aSave->setEnabled( false );
    m_ui->aUndo->setEnabled( false );
    m_ui->aRedo->setEnabled( false );
    m_ui->aClearAll->setEnabled( false );
    m_ui->aShowAll->setEnabled( false );
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::onOpenImage()
{
    m_filename = QFileDialog::getOpenFileName( this,
        tr( "Open Image" ), QCoreApplication::applicationDirPath(), tr( "Image Files (*.png *.jpg *.bmp)" ) );
    m_pixmap = QPixmap( m_filename );
    m_ui->paintLabel->setPixmap( m_pixmap );
    update();

    m_ui->aSave->setEnabled( true );
    checkActions();
}

void MainWindow::onSaveImage()
{
    m_pixmap.save( m_filename );
    m_ui->aSave->setEnabled( false );
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
    QAction* colorAddress = m_penColorGroup->checkedAction();
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
    qDebug() << "Path started";
    m_showFlag = true;
    if( m_currentPath < m_path.size() )
    {
        int var = m_path.size() - m_currentPath;
        while( var-- )
            m_path.takeLast();
    }
    m_path.append( QPainterPath() );
    m_path.last().moveTo( m_currentPoint );
    ++m_currentPath;
    checkActions();
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
    m_pixmap = QPixmap( m_filename );
    checkActions();
    qDebug() << "Undo, current path:" << m_currentPath;
}

void MainWindow::onRedo()
{
    if( m_currentPath == m_path.size() )
        return;
    ++m_currentPath;
    m_pixmap = QPixmap( m_filename );
    checkActions();
    qDebug() << "Redo, current path:" << m_currentPath;
}

void MainWindow::onClearAll()
{
    m_pixmap = QPixmap( m_filename );
    m_showFlag = false;
    checkActions();
    update();
}

void MainWindow::onShowAll()
{
    checkActions();
    m_showFlag = true;
    QPainter painter( &m_pixmap );

    painter.setPen( m_color );

    foreach( auto item, m_path )
        painter.drawPath( item );

    m_ui->paintLabel->setPixmap( m_pixmap );
    update();
}

void MainWindow::paintEvent( QPaintEvent* event )
{
    Q_UNUSED( event );
    if( m_path.isEmpty() )
        return;

    if( m_showFlag )
    {
        QPainter painter( &m_pixmap );

        painter.setPen( m_color );

        m_path.last().lineTo( m_currentPoint );
        for( int i = 0; i < m_currentPath; ++i )
            painter.drawPath( m_path.at( i ) );
    }
    m_ui->paintLabel->setPixmap( m_pixmap );
}

void MainWindow::checkActions()
{
    if( m_currentPath == 0 )
        m_ui->aUndo->setEnabled( false );
    else
        m_ui->aUndo->setEnabled( true );
    if( m_currentPath == m_path.size() )
        m_ui->aRedo->setEnabled( false );
    else
        m_ui->aRedo->setEnabled( true );
    if( m_showFlag )
    {
        m_ui->aShowAll->setEnabled( false );
        if( !m_path.isEmpty() )
            m_ui->aClearAll->setEnabled( true );
    }
    else
    {
        m_ui->aShowAll->setEnabled( true );
        m_ui->aClearAll->setEnabled( false );
    }
}
