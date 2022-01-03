#ifndef SETTINGSSCOPECOMBO_H
#define SETTINGSSCOPECOMBO_H

#include <QComboBox>
#include <QMap>
#include <QString>
#include <QVariant>

class SettingsScopeCombo : public QComboBox
{
public:
    SettingsScopeCombo();

    /** Got it from https://stackoverflow.com/questions/34281682/how-to-convert-enum-to-qstring */
    enum SetupScope {THIS_POINT_FORWARD, THIS_PAGE, WHOLE_DOCUMENT };
    Q_ENUM(SetupScope)

    SetupScope getSelectedScope();

private:
    QMap<QString, SetupScope> *setupScopeOptions;

};

#endif // SETTINGSSCOPECOMBO_H
