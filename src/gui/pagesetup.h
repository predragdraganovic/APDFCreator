#ifndef PAGESETUP_H
#define PAGESETUP_H

#include <QDialog>
#include <QPageSize>
#include <QListWidgetItem>
#include <QGraphicsView>
#include "gui/document.h"
#include <map>
#include <QHBoxLayout>
#include "components/settingsscopecombo.h"
#include "components/papersizecombo.h"
#include "components/pageproperties.h"

namespace Ui {
class pagesetup;
}

class PageSetup : public QDialog
{
    Q_OBJECT

public:
    explicit PageSetup(Document &document, QGraphicsView &view, QWidget *parent = nullptr);
    ~PageSetup();

    const QPageSize &getNewSize() const;
    void setNewSize(const QPageSize &newNewSize);
    int getNewDPI() const;
    void setNewDPI(int newNewDPI);
    void updateView(QGraphicsView &view);

signals:
    void PageSizeChanged();

private slots:
    void on_pushButton_2_clicked();
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_pushButton_clicked();

private:
    Ui::pagesetup *ui;

    PageProperties *pageProperties;

    PaperSizeCombo *paperSize;
    SettingsScopeCombo *comboSettingsScope;
    Document *document;
    QGraphicsView *currentView;

};

#endif // PAGESETUP_H
