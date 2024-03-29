#ifndef PAPERSIZECOMBO_H
#define PAPERSIZECOMBO_H

#include <QListWidget>
#include <QMap>
#include <QString>
#include <QPageSize>
#include <QList>

class PaperSizeCombo : public QListWidget
{
public:
    explicit PaperSizeCombo(const QPageSize& currentSize);

    QPageSize getSelectedPageSize();

private:
    QMap<QString, QPageSize> *paperSizeOptions;
};

#endif // PAPERSIZECOMBO_H
