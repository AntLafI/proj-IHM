#include "mainwindow.h"

#include <QPushButton>
#include <QPixmap>

#include <QScrollArea>

#include <QWidget>
#include <QVBoxLayout>
#include <QMainWindow>

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QFileInfo>

#include "scrollbar.h"
#include "renderarea.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QHBoxLayout *mainLayout = new QHBoxLayout(ui->centralwidget);
    QHBoxLayout *mainLayout = ui->horizontalLayout_3 ;

    ScrollBar *myScrollBar = new ScrollBar(this);
    RenderArea *myRenderArea = new RenderArea(this);

    mainLayout->addWidget(myScrollBar); // Index 0
    mainLayout->addWidget(myRenderArea);  // Index 1

    mainLayout->setStretch(0, 3);
    mainLayout->setStretch(1, 7);


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


}

MainWindow::~MainWindow(){ ;
    delete ui ;
}


// ======================= OPEN =======================

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

    if (info.suffix() == "vdraw") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, tr("Erreur"),
                                 tr("Impossible d'ouvrir le fichier."));
            return;
        }
        file.close();
        m_image = QImage(800, 600, QImage::Format_ARGB32_Premultiplied);
        m_image.fill(Qt::white);
    } else {
        if (!m_image.load(fileName)) {
            QMessageBox::warning(this, tr("Erreur"),
                                 tr("Format non supporté."));
            return;
        }
    }

    QLabel *label = new QLabel;
    label->setPixmap(QPixmap::fromImage(m_image));
    label->setAlignment(Qt::AlignCenter);
    ui->horizontalLayout_3->addWidget(label);

    m_currentFilePath = fileName;
    m_isModified = false;
    m_hasDocument = true;

    statusBar()->showMessage(tr("Document ouvert"), 2000);
}

// ======================= SAVE =======================

void MainWindow::onActionSaveTriggered()
{
    if (!m_hasDocument)
        return;

    if (m_currentFilePath.isEmpty()) {
        onActionSaveAsTriggered();
        return;
    }

    if (!saveToFile(m_currentFilePath)) {
        QMessageBox::warning(this, tr("Erreur"),
                             tr("Impossible d'enregistrer."));
    }
}

void MainWindow::onActionSaveAsTriggered()
{
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
    else
        ok = exportImage(fileName);

    if (!ok) {
        QMessageBox::warning(this, tr("Erreur"),
                             tr("Impossible d'enregistrer."));
        return;
    }

    m_currentFilePath = fileName;
    m_isModified = false;
}

// ======================= CLOSE PROJECT =======================

void MainWindow::onActionCloseProjectTriggered()
{
    if (!maybeSave())
        return;

    closeCurrentDocument();
}

bool MainWindow::maybeSave()
{
    if (!m_hasDocument || !m_isModified)
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
    QLayoutItem *item = ui->horizontalLayout_3->takeAt(0);

    if (item != nullptr) {
        if (item->widget()) {
            item->widget()->hide(); // On le cache
            // ou
            delete item->widget();  // On le supprime si on n'en a plus besoin
        }
        delete item; // Il faut toujours supprimer l'item du layout lui-même
    }

    m_image = QImage();
    m_currentFilePath.clear();
    m_isModified = false;
    m_hasDocument = false;

    statusBar()->showMessage(tr("Document fermé"), 2000);
}

// ======================= SAVE HELPERS =======================

bool MainWindow::saveToFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QJsonObject root;
    root["type"] = "VectorialDraw";
    root["width"] = m_image.width();
    root["height"] = m_image.height();

    file.write(QJsonDocument(root).toJson());
    file.close();

    return true;
}

bool MainWindow::exportImage(const QString &fileName)
{
    return m_image.save(fileName);
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
        "Application de dessin vectoriel développée avec Qt.<br><br>"
        "<b>Fonctionnalités actuelles :</b><br>"
        "- Ouverture et sauvegarde de fichiers<br>"
        "- Format propriétaire (.vdraw)<br>"
        "- Import / export d’images standards<br><br>"
        "<b>Formats supportés :</b><br>"
        "- VectorialDraw (*.vdraw)<br>"
        "- PNG (*.png)<br>"
        "- JPEG (*.jpg)<br>"
        "- BMP (*.bmp)<br>"
        "- SVG (*.svg)<br><br>"
        "Projet IHM"
        );

    QMessageBox::about(this, tr("About VectorialDraw"), text);
}
