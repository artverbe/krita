/*
 *  Copyright (c) 2016 Boudewijn Rempt <boud@valdyas.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#include "Krita.h"

#include <QPointer>

#include <KoDockRegistry.h>
#include <kactioncollection.h>
#include <KisPart.h>
#include <KisMainWindow.h>
#include <KisDocument.h>
#include <kis_image.h>
#include <kis_action.h>
#include <kis_script_manager.h>
#include <KisViewManager.h>

#include "View.h"
#include "Document.h"
#include "Window.h"
#include "ViewExtension.h"
#include "DockWidgetFactoryBase.h"

#include <QVariantMap>
#include <QVariant>

Krita* Krita::s_instance = 0;

struct Krita::Private {
    Private() {}
    QList<ViewExtension*> viewExtensions;
    bool batchMode {false};
    Notifier *notifier{new Notifier()};
};

Krita::Krita(QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    qRegisterMetaType<Notifier*>();
}

Krita::~Krita()
{
    qDeleteAll(d->viewExtensions);
    delete d->notifier;
    delete d;
}

QVariantMap Krita::actions() const
{
    QVariantMap actionList;
    KisMainWindow *mainWindow = KisPart::instance()->currentMainwindow();
    KActionCollection *actionCollection = mainWindow->actionCollection();
    Q_FOREACH(QAction *action, actionCollection->actions()) {
        actionList.insert(action->objectName(), QVariant::fromValue<QObject*>(new Action(action->objectName(), action)));
    }
    return actionList;
}

Document* Krita::activeDocument() const
{
    return 0;
}

void Krita::setActiveDocument(Document* value)
{
}


bool Krita::batchmode() const
{
    return d->batchMode;
}

void Krita::setBatchmode(bool value)
{
    d->batchMode = value;
}


QVariantList Krita::documents() const
{
    QVariantList ret;
    foreach(QPointer<KisDocument> doc, KisPart::instance()->documents()) {
        ret << QVariant::fromValue<Document*>(new Document(doc));
    }
    return ret;
}

QVariantList Krita::exporters() const
{
    return QVariantList();
}

QVariantList Krita::filters() const
{
    return QVariantList();
}

QVariantList Krita::generators() const
{
    return QVariantList();
}

QVariantList Krita::importers() const
{
    return QVariantList();
}

Notifier* Krita::notifier() const
{
    return d->notifier;
}


InfoObject* Krita::preferences() const
{
    return 0;
}

void Krita::setPreferences(InfoObject* value)
{
}


QString Krita::version() const
{
    return QString();
}

QVariantList Krita::views() const
{
    QVariantList ret;
    foreach(QPointer<KisView> view, KisPart::instance()->views()) {
        ret << QVariant::fromValue<View*>(new View(view));
    }
    return ret;
}

QVariantList Krita::windows() const
{
    QVariantList ret;
    foreach(QPointer<KisMainWindow> mainWin, KisPart::instance()->mainWindows()) {
        ret << QVariant::fromValue<Window*>(new Window(mainWin));
    }
    return ret;

}

QVariantList Krita::resources() const
{
    return QVariantList();
}

void Krita::addDockWidget(DockWidget *dockWidget)
{
}

void Krita::addAction(Action *action)
{
}

bool Krita::closeApplication()
{
    qDebug() << "closeApplication called";
    return false;
}

Document* Krita::createDocument()
{
    return 0;
}

Document* Krita::openDocument()
{
    return 0;
}

Window* Krita::openWindow()
{
    return 0;
}


QAction *Krita::createAction(const QString &text)
{
    KisAction *action = new KisAction(text, this);
    KisPart::instance()->addScriptAction(action);
    return action;
}

void Krita::addViewExtension(ViewExtension* viewExtension)
{
    d->viewExtensions.append(viewExtension);
}

QList< ViewExtension* > Krita::viewExtensions()
{
    return d->viewExtensions;
}

void Krita::addDockWidgetFactory(DockWidgetFactoryBase* factory)
{
    KoDockRegistry::instance()->add(factory);
}

Krita* Krita::instance()
{
    if (!s_instance)
    {
        s_instance = new Krita;
    }
    return s_instance;
}

/**
 * Scripter.fromVariant(variant)
 * variant is a QVariant
 * returns instance of QObject-subclass
 *
 * This is a helper method for PyQt
 * Because PyQt cannot cast a variant to a QObject or QWidget
 * I hope that will change some time.
 */
QObject *Krita::fromVariant(const QVariant& v)
{

    if (v.canConvert< QWidget* >())
    {
        QObject* obj = qvariant_cast< QWidget* >(v);
        return obj;
    }
    else if (v.canConvert< QObject* >())
    {
        QObject* obj = qvariant_cast< QObject* >(v);
        return obj;
    }
    else
        return 0;
}

