#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CustomLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = nullptr );
    ~MainWindow();

public Q_SLOTS:
    void onOpenImage();
    void onSaveImage();
    void onAboutClicked();
    void onAboutQtClicked();
    void onPositionChanged( QPoint last, QPoint current );
    void onColorChanged();
protected:
    void paintEvent( QPaintEvent* event );

private:
    Ui::MainWindow*     m_ui;
    QPoint              m_lastPoint;
    QPoint              m_currentPoint;
    QString             m_filename;
    QPixmap*            m_pixmap;
    CustomLabel*        m_label;
    QColor              m_color;
};
#endif // MAINWINDOW_H
