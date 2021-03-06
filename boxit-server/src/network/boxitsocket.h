/*
 *  BoxIt - Manjaro Linux Repository Management Software
 *  Roland Singer <roland@manjaro.org>
 *
 *  Copyright (C) 2007 Free Software Foundation, Inc.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BOXITSOCKET_H
#define BOXITSOCKET_H

#include <QString>
#include <QSslSocket>
#include <QSslError>
#include <QByteArray>
#include <QDataStream>
#include <QList>
#include <QTimer>
#include <iostream>
#include "const.h"

using namespace std;


class BoxitSocket : public QSslSocket
{
    Q_OBJECT
public:
    explicit BoxitSocket(const int sessionID, QObject *parent = 0);

    void sendData(quint16 msgID);
    void sendData(quint16 msgID, QByteArray data);

signals:
    void readData(quint16 msgID, QByteArray data);

private slots:
    void readyReadData();
    void socketError();
    void sslErrors(const QList<QSslError> &errors);
    void timeOutDestroy();

private:
    quint16 readBlockSize, readMSGID;
    QByteArray data;
    int timeoutCount;
    QTimer timeOutTimer;

protected:
    const int sessionID;

};

#endif // BOXITSOCKET_H
