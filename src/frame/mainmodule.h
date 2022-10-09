/*
 * Copyright (C) 2021 ~ 2023 Deepin Technology Co., Ltd.
 *
 * Author:     caixiangrong <caixiangrong@uniontech.com>
 *
 * Maintainer: caixiangrong <caixiangrong@uniontech.com>
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
#ifndef MAINMODULE_H
#define MAINMODULE_H
#include "interface/moduleobject.h"

DCC_BEGIN_NAMESPACE
class MainModulePrivate;
class MainModule : public ModuleObject
{
    Q_OBJECT
public:
    explicit MainModule(QObject *parent = nullptr);
    MainModule(const QString &name, const QString &displayName = {}, QObject *parent = nullptr);
    MainModule(const QString &name, const QStringList &contentText, QObject *parent = nullptr);
    MainModule(const QString &name, const QString &displayName, const QStringList &contentText, QObject *parent = nullptr);
    MainModule(const QString &name, const QString &displayName, const QVariant &icon, QObject *parent = nullptr);
    MainModule(const QString &name, const QString &displayName, const QString &description, QObject *parent = nullptr);
    MainModule(const QString &name, const QString &displayName, const QString &description, const QVariant &icon, QObject *parent = nullptr);
    MainModule(const QString &name, const QString &displayName, const QString &description, const QIcon &icon, QObject *parent = nullptr);
    MainModule(const QString &name, const QString &displayName, const QString &description, const QStringList &contentText, const QVariant &icon, QObject *parent = nullptr);
    ~MainModule() override;

    QWidget *page() override;
    ModuleObject *defultModule() override;
    inline DCC_MODULE_TYPE getClassID() const override { return MAINLAYOUT; }

    DCC_DECLARE_PRIVATE(MainModule)
};
DCC_END_NAMESPACE
#endif // MAINMODULE_H