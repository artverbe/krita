/*
 *  Copyright (c) 2002 Patrick Julien <freak@codepimps.org>
 *  Copyright (c) 2004 Boudewijn Rempt <boud@valdyas.org>
 *  Copyright (c) 2004 Clarence Dang <dang@kde.org>
 *  Copyright (c) 2004 Adrian Page <adrian@pagenet.plus.com>
 *  Copyright (c) 2004 Cyrille Berger <cberger@cberger.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef KIS_ERASEOP_H_
#define KIS_ERASEOP_H_

#include "kis_paintop.h"
#include "kis_point.h"
#include "kis_painter.h"
#include "kis_types.h"

class KisEraseOpFactory : public KisPaintOpFactory {

public:
	KisEraseOpFactory() {}
	virtual ~KisEraseOpFactory() {}

	virtual KisPaintOp * createOp(KisPainter * painter);
	virtual QString name() { return QString("eraser"); }
};


class KisEraseOp : public KisPaintOp {

	typedef KisPaintOp super;

public:

	KisEraseOp(KisPainter * painter);
	virtual ~KisEraseOp();

	void paintAt(const KisPoint &pos,
		     const double pressure,
		     const double /*xTilt*/,
		     const double /*yTilt*/);

};

#endif // KIS_ERASEOP_H_
