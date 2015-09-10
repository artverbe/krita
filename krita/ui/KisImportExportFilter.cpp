/* This file is part of the KDE libraries
   Copyright (C) 2001 Werner Trobin <trobin@kde.org>
                 2002 Werner Trobin <trobin@kde.org>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public License
along with this library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.
*/

#include "KisImportExportFilter.h"

#include <QFile>
#include <QUrl>
#include <kmimetype.h>
#include <QTemporaryFile>
#include <kis_debug.h>
#include <QStack>
#include "KisImportExportManager.h"
#include "KoUpdater.h"

class Q_DECL_HIDDEN KisImportExportFilter::Private
{
public:
    QPointer<KoUpdater> updater;

    Private() :updater(0) {}
};

KisImportExportFilter::KisImportExportFilter(QObject *parent)
    : QObject(parent), m_chain(0), d(new Private)
{
}

KisImportExportFilter::~KisImportExportFilter()
{
    if (d->updater) d->updater->setProgress(100);
    delete d;
}

void KisImportExportFilter::setUpdater(const QPointer<KoUpdater>& updater)
{
    if (d->updater && !updater) {
        disconnect(this, SLOT(slotProgress(int)));
    } else if (!d->updater && updater) {
        connect(this, SIGNAL(sigProgress(int)), SLOT(slotProgress(int)));
    }
    d->updater = updater;
}

void KisImportExportFilter::slotProgress(int value)
{
    if (d->updater) {
        d->updater->setValue(value);
    }
}

#include <KisImportExportFilter.moc>
