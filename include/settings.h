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
#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    QString title;
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = nullptr, bool controlsEnabled = true);
    ~Settings();

    void saveSettings();

    QByteArray loadStyleSheet(QString & filename);
signals:
    void themeChanged(QByteArray);
    void devModeChanged(bool);

private slots:
    void end();
    void loadTheme();

    void loadDefaultTheme();

    void on_saveTheme_clicked();

    void on_developmentCheck_stateChanged(int arg1);

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
