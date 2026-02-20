#include "mainwindow.h"

#include <QPushButton>
#include <QPixmap>
#include <QScrollArea>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QFileInfo>
#include <QTabWidget>
#include <QDir>
#include <QBuffer>
#include <QCloseEvent>
#include <QtSvg/QSvgGenerator>

#include "scrollbar.h"
#include "renderarea.h"
#include "imageviewer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QHBoxLayout *mainLayout = ui->horizontalLayout_3;

    ScrollBar *myScrollBar = new ScrollBar(this);
    m_tabWidget = new QTabWidget(this);
    m_tabWidget->setTabsClosable(true);

    connect(m_tabWidget, &QTabWidget::tabCloseRequested, this,
            [this](int idx){
                int prev = m_tabWidget->currentIndex();
                m_tabWidget->setCurrentIndex(idx);
                if (!maybeSave()) {
                    m_tabWidget->setCurrentIndex(prev);
                    return;
                }
                QWidget *w = m_tabWidget->widget(idx);
                m_tabWidget->removeTab(idx);
                delete w;
                m_hasDocument = (m_tabWidget->count() > 0);
                if (!m_hasDocument) {
                    m_currentFilePath.clear();
                    m_isModified = false;
                }
                updateActions();
            });

    connect(m_tabWidget, &QTabWidget::currentChanged, this,
            [this](int){
                auto *area = qobject_cast<RenderArea*>(m_tabWidget->currentWidget());

                ui->actionUndo->disconnect();
                ui->actionRedo->disconnect();

                if (area) {
                    connect(ui->actionUndo, &QAction::triggered, area, &RenderArea::undo);
                    connect(ui->actionRedo, &QAction::triggered, area, &RenderArea::redo);
                    connect(area, &RenderArea::canUndoChanged, ui->actionUndo, &QAction::setEnabled);
                    connect(area, &RenderArea::canRedoChanged, ui->actionRedo, &QAction::setEnabled);
                    connect(area, &RenderArea::modified, this, [this, area]{
                        m_isModified = true;
                        area->setProperty("modified", true);
                    });
                    ui->actionUndo->setEnabled(area->canUndo());
                    ui->actionRedo->setEnabled(area->canRedo());
                } else {
                    ui->actionUndo->setEnabled(false);
                    ui->actionRedo->setEnabled(false);
                }

                updateActions();
            });

    mainLayout->addWidget(myScrollBar);
    mainLayout->addWidget(m_tabWidget);

    mainLayout->setStretch(0, 3);
    mainLayout->setStretch(1, 7);

    connect(ui->actionNew, &QAction::triggered,
            this, &MainWindow::onActionNewTriggered);
    connect(ui->actionOpen, &QAction::triggered,
            this, &MainWindow::onActionOpenTriggered);
    connect(ui->actionSave, &QAction::triggered,
            this, &MainWindow::onActionSaveTriggered);
    connect(ui->actionSave_As, &QAction::triggered,
            this, &MainWindow::onActionSaveAsTriggered);
    connect(ui->actionClose_Project, &QAction::triggered,
            this, &MainWindow::onActionCloseProjectTriggered);
    connect(ui->actionabout_VectorialDraw, &QAction::triggered,
            this, &MainWindow::onActionAbout_VectorialDrawTriggered);

    updateActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int prev = m_tabWidget->currentIndex();
    for (int i = 0; i < m_tabWidget->count(); ++i) {
        m_tabWidget->setCurrentIndex(i);
        if (!maybeSave()) {
            m_tabWidget->setCurrentIndex(prev);
            event->ignore();
            return;
        }
    }
    m_tabWidget->setCurrentIndex(prev);
    event->accept();
}

void MainWindow::updateActions()
{
    const bool hasDoc = (m_tabWidget && m_tabWidget->count() > 0);
    ui->actionSave->setEnabled(hasDoc);
    ui->actionSave_As->setEnabled(hasDoc);
    ui->actionClose_Project->setEnabled(hasDoc);

    auto *area = qobject_cast<RenderArea*>(m_tabWidget ? m_tabWidget->currentWidget() : nullptr);
    ui->actionUndo->setEnabled(area && area->canUndo());
    ui->actionRedo->setEnabled(area && area->canRedo());
}

void MainWindow::onActionNewTriggered()
{
    RenderArea *area = new RenderArea(this);
    const QString title = QString("Untitled %1").arg(m_untitledCount++);
    m_tabWidget->addTab(area, title);
    m_tabWidget->setCurrentWidget(area);
    area->setProperty("modified", false);

    m_image = QImage(800, 600, QImage::Format_ARGB32_Premultiplied);
    m_image.fill(Qt::white);

    m_currentFilePath.clear();
    m_isModified = false;
    m_hasDocument = true;

    updateActions();
    statusBar()->showMessage(tr("Nouveau document"), 2000);
}

void MainWindow::onActionOpenTriggered()
{
    if (!maybeSave())
        return;

    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open"),
        QDir::homePath(),
        tr("Images (*.png *.jpg *.bmp *.svg);;VectorialDraw (*.vdraw)")
        );

    if (fileName.isEmpty())
        return;

    QFileInfo info(fileName);

    if (info.suffix().compare("vdraw", Qt::CaseInsensitive) == 0) {

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, tr("Erreur"),
                                 tr("Impossible d'ouvrir le fichier."));
            return;
        }
        const QByteArray data = file.readAll();
        file.close();

        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(data, &err);

        if (err.error != QJsonParseError::NoError || !doc.isObject()) {
            QMessageBox::warning(this, tr("Erreur"),
                                 tr("Fichier .vdraw invalide."));
            return;
        }

        QJsonObject root = doc.object();
        const QString pngB64 = root.value("image").toString();

        RenderArea *area = new RenderArea(this);

        if (!pngB64.isEmpty()) {
            QByteArray pngBytes = QByteArray::fromBase64(pngB64.toUtf8());
            QImage img;
            if (img.loadFromData(pngBytes, "PNG")) {
                area->setBackgroundImage(img);
            } else {
                QMessageBox::warning(this, tr("Erreur"),
                                     tr("Image embarquée invalide."));
                delete area;
                return;
            }
        }

        int idx = m_tabWidget->addTab(area, info.completeBaseName());
        m_tabWidget->setCurrentIndex(idx);

        m_image = QImage(800, 600, QImage::Format_ARGB32_Premultiplied);
        m_image.fill(Qt::white);

        area->setProperty("modified", false);

    } else {

        QImage img;
        if (!img.load(fileName)) {
            QMessageBox::warning(this, tr("Erreur"),
                                 tr("Format non supporté."));
            return;
        }

        RenderArea *area = new RenderArea(this);
        area->setBackgroundImage(img);
        int idx = m_tabWidget->addTab(area, info.fileName());
        m_tabWidget->setCurrentIndex(idx);
        area->setProperty("modified", false);
    }

    m_currentFilePath = fileName;
    m_isModified = false;
    m_hasDocument = true;

    updateActions();
    statusBar()->showMessage(tr("Document ouvert"), 2000);
}

void MainWindow::onActionSaveTriggered()
{
    if (m_tabWidget->count() == 0)
        return;

    if (m_currentFilePath.isEmpty()) {
        onActionSaveAsTriggered();
        return;
    }

    const QString ext = QFileInfo(m_currentFilePath).suffix().toLower();
    bool ok = false;

    if (ext == "vdraw") {
        ok = saveToFile(m_currentFilePath);
    } else if (ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "bmp") {
        ok = exportImage(m_currentFilePath);
    } else if (ext == "svg") {
        ok = exportSvg(m_currentFilePath);
    } else {
        QMessageBox::warning(this, tr("Erreur"),
                             tr("Extension non supportée pour 'Save'. Utilisez 'Save As'."));
        return;
    }

    if (!ok) {
        QMessageBox::warning(this, tr("Erreur"),
                             tr("Impossible d'enregistrer."));
        return;
    }

    QWidget *w = m_tabWidget->currentWidget();
    if (w) w->setProperty("modified", false);
    m_isModified = false;

    int idx = m_tabWidget->currentIndex();
    if (idx >= 0)
        m_tabWidget->setTabText(idx, QFileInfo(m_currentFilePath).fileName());

    statusBar()->showMessage(tr("Document enregistré"), 2000);
}

void MainWindow::onActionSaveAsTriggered()
{
    if (m_tabWidget->count() == 0)
        return;

    QString selectedFilter;

    QString fileName = QFileDialog::getSaveFileName(
        this,
        tr("Save As"),
        QDir::homePath(),
        tr("VectorialDraw (*.vdraw);;"
           "PNG (*.png);;"
           "JPEG (*.jpg);;"
           "Bitmap (*.bmp);;"
           "SVG (*.svg)"),
        &selectedFilter
        );

    if (fileName.isEmpty())
        return;

    QString ext;
    if (selectedFilter.contains("*.vdraw")) ext = "vdraw";
    else if (selectedFilter.contains("*.png")) ext = "png";
    else if (selectedFilter.contains("*.jpg")) ext = "jpg";
    else if (selectedFilter.contains("*.bmp")) ext = "bmp";
    else if (selectedFilter.contains("*.svg")) ext = "svg";

    fileName = forceExtension(fileName, ext);

    bool ok = false;
    if (ext == "vdraw")
        ok = saveToFile(fileName);
    else if (ext == "svg")
        ok = exportSvg(fileName);
    else
        ok = exportImage(fileName);

    if (!ok) {
        QMessageBox::warning(this, tr("Erreur"),
                             tr("Impossible d'enregistrer."));
        return;
    }

    m_currentFilePath = fileName;

    QWidget *w = m_tabWidget->currentWidget();
    if (w) w->setProperty("modified", false);
    m_isModified = false;

    int idx = m_tabWidget->currentIndex();
    if (idx >= 0)
        m_tabWidget->setTabText(idx, QFileInfo(fileName).fileName());

    statusBar()->showMessage(tr("Document enregistré"), 2000);
}

void MainWindow::onActionCloseProjectTriggered()
{
    if (!maybeSave())
        return;

    closeCurrentDocument();
}

bool MainWindow::maybeSave()
{
    if (m_tabWidget->count() == 0)
        return true;

    QWidget *w = m_tabWidget->currentWidget();
    if (!w) return true;

    const bool modified = w->property("modified").toBool();
    if (!modified)
        return true;

    auto reply = QMessageBox::question(
        this,
        tr("Document modifié"),
        tr("Le document a été modifié.\nVoulez-vous enregistrer ?"),
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
        QMessageBox::Save
        );

    if (reply == QMessageBox::Cancel)
        return false;

    if (reply == QMessageBox::Save)
        onActionSaveTriggered();

    return true;
}

void MainWindow::closeCurrentDocument()
{
    QWidget *w = m_tabWidget->currentWidget();
    if (w) {
        int idx = m_tabWidget->currentIndex();
        m_tabWidget->removeTab(idx);
        delete w;
    }

    if (m_tabWidget->count() == 0) {
        m_image = QImage();
        m_currentFilePath.clear();
        m_isModified = false;
        m_hasDocument = false;
    } else {
        m_hasDocument = true;
    }

    updateActions();
    statusBar()->showMessage(tr("Document fermé"), 2000);
}

bool MainWindow::saveToFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QWidget *w = m_tabWidget->currentWidget();
    if (!w) {
        file.close();
        return false;
    }

    int width = 0, height = 0;
    QJsonObject root;
    root["type"] = "VectorialDraw";

    QByteArray pngBytes;

    QImage img = w->grab().toImage();
    if (!img.isNull()) {
        width  = img.width();
        height = img.height();
        QBuffer buf(&pngBytes);
        buf.open(QIODevice::WriteOnly);
        img.save(&buf, "PNG");
        root["contentType"] = "render";
    }

    root["width"]  = width;
    root["height"] = height;

    if (!pngBytes.isEmpty()) {
        root["image"] = QString::fromUtf8(pngBytes.toBase64());
    }

    file.write(QJsonDocument(root).toJson());
    file.close();

    return true;
}

bool MainWindow::exportImage(const QString &fileName)
{
    QWidget *w = m_tabWidget->currentWidget();
    if (!w) return false;

    QImage img = w->grab().toImage();
    if (img.isNull()) return false;
    return img.save(fileName);
}

bool MainWindow::exportSvg(const QString &fileName)
{
    QWidget *w = m_tabWidget->currentWidget();
    auto *area = qobject_cast<RenderArea*>(w);
    if (!area) return false;

    QSvgGenerator gen;
    gen.setFileName(fileName);
    gen.setSize(area->size());
    gen.setViewBox(QRect(QPoint(0,0), area->size()));
    gen.setTitle("VectorialDraw");
    gen.setDescription("Export SVG");

    QPainter p;
    if (!p.begin(&gen)) return false;
    area->renderToPainter(&p, area->size());
    p.end();
    return true;
}

QString MainWindow::forceExtension(const QString &fileName, const QString &ext)
{
    QFileInfo info(fileName);
    return info.path() + "/" + info.completeBaseName() + "." + ext;
}

void MainWindow::onActionAbout_VectorialDrawTriggered()
{
    QString text = tr(
        "<b>VectorialDraw</b><br><br>"
        "Application de dessin développée avec Qt.<br><br>"

        "<b>Fonctionnalités actuelles :</b><br>"
        "- Multi-documents avec onglets<br>"
        "- Création de nouveaux projets<br>"
        "- Ouverture de projets existants<br>"
        "- Zone de dessin interactive (pinceau)<br>"
        "- Annulation et rétablissement (Undo / Redo)<br>"
        "- Import d'images comme fond de dessin<br>"
        "- Barre d'outils verticale (outils graphiques)<br>"
        "- Sauvegarde au format propriétaire (.vdraw) avec image embarquée<br>"
        "- Export aux formats PNG, JPG, BMP, SVG<br><br>"

                       "<b>Formats supportés :</b><br>"
                       "- VectorialDraw (*.vdraw)<br>"
                       "- PNG (*.png)<br>"
                       "- JPEG (*.jpg)<br>"
                       "- BMP (*.bmp)<br>"
                       "- SVG (*.svg)<br><br>"

                       "Projet IHM – 2025/2026"
        );

    QMessageBox::about(this, tr("About VectorialDraw"), text);
}
