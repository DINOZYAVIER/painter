#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QActionGroup;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = nullptr );
    ~MainWindow();

    void checkActions();

public Q_SLOTS:
    void onOpenImage();
    void onSaveImage();
    void onAboutClicked();
    void onAboutQtClicked();
    void onPositionChanged( QPoint last, QPoint current );
    void onColorChanged();
    void onPathStarted();
    void onUndo();
    void onRedo();
    void onClearAll();
    void onShowAll();
protected:
    void paintEvent( QPaintEvent* event );

private:
    Ui::MainWindow*        m_ui;
    QPoint                 m_lastPoint;
    QPoint                 m_currentPoint;
    QString                m_filename;
    QPixmap                m_pixmap;
    QColor                 m_color;
    QVector<QPainterPath>  m_path;
    QActionGroup*          m_penColorGroup;
    bool                   m_showFlag;
    int                    m_currentPath;
};
#endif // MAINWINDOW_H
