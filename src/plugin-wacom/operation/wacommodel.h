/*
 * Copyright (C) 2021 ~ 2023 Deepin Technology Co., Ltd.
 *
 * Author:     duanhongyu <duanhongyu@uniontech.com>
 *
 * Maintainer: duanhongyu <duanhongyu@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef WACOMMODEL_H
#define WACOMMODEL_H

#include <QObject>

class WacomModelPrivate;
class WacomModel : public QObject
{
    Q_OBJECT
public:
    explicit WacomModel(QObject *parent = nullptr);
    ~WacomModel();

    Q_PROPERTY(bool Exist READ exist NOTIFY ExistChanged)
    bool exist() const;

    Q_PROPERTY(bool CursorMode READ CursorMode WRITE setCursorMode NOTIFY CursorModeChanged)
    bool CursorMode() const;
    void setCursorMode(bool value);

    Q_PROPERTY(uint EraserPressureSensitive READ eraserPressureSensitive WRITE setEraserPressureSensitive NOTIFY EraserPressureSensitiveChanged)
    uint eraserPressureSensitive();
    void setEraserPressureSensitive(uint value);

Q_SIGNALS:
    void ExistChanged(bool exist);
    void CursorModeChanged(const bool cursorMode);
    void EraserPressureSensitiveChanged(const uint value);

private:
    QScopedPointer<WacomModelPrivate> d_ptr;
    Q_DECLARE_PRIVATE_D(qGetPtrHelper(d_ptr), WacomModel)
};

#endif // WACOMMODEL_H