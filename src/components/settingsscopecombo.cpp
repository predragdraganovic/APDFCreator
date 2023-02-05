#include "settingsscopecombo.h"
#include <iostream>

SettingsScopeCombo::SettingsScopeCombo()
{
    setupScopeOptions = new QMap<QString, SetupScope>();

    setupScopeOptions->insert("This point forward", SetupScope::THIS_POINT_FORWARD);
    setupScopeOptions->insert("This page only", SetupScope::THIS_PAGE);
    setupScopeOptions->insert("Whole document", SetupScope::WHOLE_DOCUMENT);

    this->addItems(QStringList(setupScopeOptions->keys()));

    this->setCurrentIndex(2);

    this->setToolTip("Changes will be applied accordingly to whole document, or a part of "
                     "it.");

    // TODO: obrisati ovaj test
    connect(this, &SettingsScopeCombo::currentTextChanged, this, [=](const QString &text) {
        std::cout << this->currentText().toStdString() << std::endl;
        std::cout << QString(QVariant::fromValue(getSelectedScope()).toString()).toStdString() << std::endl;
    });
}

SettingsScopeCombo::SetupScope SettingsScopeCombo::getSelectedScope()
{
    return this->setupScopeOptions->value(this->currentText(), SetupScope::WHOLE_DOCUMENT);
}
