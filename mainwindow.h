#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QImage>

class QTabWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onActionNewTriggered();
    void onActionOpenTriggered();
    void onActionSaveTriggered();
    void onActionSaveAsTriggered();
    void onActionCloseProjectTriggered();
    void onActionAbout_VectorialDrawTriggered();

private:
    bool saveToFile(const QString &fileName);
    bool exportImage(const QString &fileName);
    bool maybeSave();
    void closeCurrentDocument();
    QString forceExtension(const QString &fileName, const QString &ext);
    void updateActions();
    void closeEvent(QCloseEvent *e) override;

private:
    Ui::MainWindow *ui;

    QImage  m_image;
    QString m_currentFilePath;
    bool    m_isModified = false;
    bool    m_hasDocument = false;

    QTabWidget *m_tabWidget = nullptr;
    int m_untitledCount = 1;
};

#endif // MAINWINDOW_H
