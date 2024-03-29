/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "settings.h"
#include "QDebug"
#include "QFile"
#include "QSettings"
#include <QStyleFactory>
#include "ui_settings.h"
#include "filedialogwithhistory.h"
#include "commons.h"
#include "QResource"
#include "QJsonValue"

Settings::Settings(QWidget *parent, bool controlsEnabled) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    title = windowTitle();
    ui->setupUi(this);
    setWindowTitle(qApp->applicationName().append(". Settings"));

    QSettings sets(qApp->organizationName(), qApp->applicationName());
    sets.beginGroup("global");
    sets.beginGroup("view");
    ui->minimizeToTrayCheck->setChecked(sets.value("minimizeToTray", true).toBool());
    ui->rememberLatestCheck->setChecked(sets.value("saveLatestDevice", true).toBool());
    ui->developmentCheck->setChecked(sets.value("devMode", false).toBool());
    if(!controlsEnabled) {
         ui->minimizeToTrayCheck->setVisible(false);
         ui->rememberLatestCheck->setVisible(false);
         ui->developmentCheck->setVisible(false);
    }
    sets.endGroup();
    sets.endGroup();
    this->adjustSize();
    this->setMaximumSize(this->size());
    //    connect(ui->checkBox_minimizeToTray, SIGNAL(stateChanged(int)), parent, SLOT(showHide()));

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(end()));
    connect(ui->loadThemeButton, SIGNAL(clicked()), this, SLOT(loadTheme()));
    connect(ui->defaultThemeButton, SIGNAL(clicked()), this, SLOT(loadDefaultTheme()));
    //connect(ui->developmentCheck, SIGNAL(stateChanged(int)), this, SLOT(devModeChanged()));

    setWindowFlags(WINDOW_FLAGS);

}

Settings::~Settings() {
    setWindowTitle(title);
    delete ui;
}

void Settings::saveSettings() {
    QSettings sets(qApp->organizationName(), qApp->applicationName());
    sets.beginGroup("global");
    sets.beginGroup("view");
    if(ui->minimizeToTrayCheck->isVisible()) {
        sets.setValue("minimizeToTray", QVariant(ui->minimizeToTrayCheck->isChecked()));
    }
    if(ui->rememberLatestCheck->isVisible()) {
        sets.setValue("saveLatestDevice", QVariant(ui->rememberLatestCheck->isChecked()));
    }
    if(ui->developmentCheck->isVisible()) {
        sets.setValue("devMode", QVariant(ui->developmentCheck->isChecked()));
    }
    sets.endGroup();
    sets.endGroup();
}

void Settings::end() {
    saveSettings();
    this->close();
}

QByteArray Settings::loadStyleSheet(QString & filename) {
    QFile file(filename);
    file.open(QFile::ReadOnly);
    QByteArray style = file.readAll();
    emit themeChanged(style);

    QSettings sets(qApp->organizationName(), qApp->applicationName());
    sets.beginGroup("global");
    sets.setValue("theme", style);
    sets.endGroup();
    return style;
}

void Settings::loadTheme() {
    QString xfile = FileDialogWithHistory().
            resolveLoadFileName(this, tr("Load Theme file"),
                                tr(" Files")
                                .append(" (*.qss);;")
                                .append(tr("All files"))
                                .append(" (* *.*)"), "theme");
    if (!xfile.isEmpty()) {
        loadStyleSheet(xfile);
    }
}

void Settings::loadDefaultTheme() {
    QString styleFile = (":/commons/style/black.qss");
    loadStyleSheet(styleFile);
}

void Settings::on_saveTheme_clicked() {

    QString xfile = FileDialogWithHistory().
            resolveSaveFileName(this, tr("Save Theme file"),
                                tr(" Files")
                                .append(" (*.qss);;")
                                .append(tr("All files"))
                                .append(" (* *.*)"), "theme");
    if (!xfile.isEmpty()) {
            QFile file(xfile);
            if (file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
                QSettings sets(qApp->organizationName(), qApp->applicationName());
                sets.beginGroup("global");
                QString settings = sets.value("theme").toString();
                file.write(settings.toUtf8());
                file.close();
                sets.endGroup();
            }
    }

}


void Settings::on_developmentCheck_stateChanged(int) {
    emit devModeChanged(ui->developmentCheck->isChecked());
}

