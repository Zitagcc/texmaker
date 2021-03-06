/***************************************************************************
 *   copyright       : (C) 2006 by Pascal Brachet                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef PLAYERBUTTON_H
#define PLAYERBUTTON_H

#include <QLabel>
#include <QPixmap>

class PlayerButton : public QLabel
{
    Q_OBJECT

public:
PlayerButton( QWidget *parent = 0 );

void setImages( QString name);
void setEnabled( bool enabled );
void enterEvent( QEvent * e );
void leaveEvent( QEvent * e );
void mouseReleaseEvent( QMouseEvent * e );

private:
QPixmap pixEnabled;
QPixmap pixHover;
QPixmap pixDisabled;
bool state;

signals:
void clicked();
};

#endif
