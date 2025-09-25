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
#ifndef FILEDIALOGWITHHISTORY_H
#define FILEDIALOGWITHHISTORY_H

#include <QString>
#include <QWidget>
#include <QComboBox>

class FileDialogWithHistory
{
private:
    QString resolveFileName(QWidget *parent, QString header, QString &filters, QString alias,
                                  bool load, QString &label, QComboBox &combo, QString &prefferedName);
public:
    FileDialogWithHistory();
    QString resolveLoadFileName(QWidget *parent, QString header, QString &filters, QString alias);
    QString resolveLoadFileName(QWidget *parent, QString header, QString &filters, QString alias,
                                QString &label, QComboBox &combo);

    QString resolveSaveFileName(QWidget *parent, QString header, QString &filters, QString alias,
                                QString &prefferedName= QString().append(""));
    QString resolveSaveFileName(QWidget *parent, QString header, QString &filters, QString alias,
                                QString &label, QComboBox &combo, QString &prefferedName = QString().append(""));

};
#endif // FILEDIALOGWITHHISTORY_H
