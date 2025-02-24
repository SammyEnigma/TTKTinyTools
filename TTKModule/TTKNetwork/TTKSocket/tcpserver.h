#ifndef TCPSERVER_H
#define TCPSERVER_H

/***************************************************************************
 * This file is part of the TTK Tiny Tools project
 * Copyright (C) 2015 - 2025 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <QTcpServer>
#include "tcpclient.h"

class TTK_MODULE_EXPORT TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);

    void sendData(int clientID, const QByteArray &data);
    void closeAllClient();

Q_SIGNALS:
    void clientReadData(const ClientData &pair, const QByteArray &data);
    void clientConnect(const ClientData &pair);
    void clientDisConnect(const ClientData &pair);

private Q_SLOTS:
    void clientDisConnectChanged(const ClientData &pair);

private:
#if TTK_QT_VERSION_CHECK(5,0,0)
    virtual void incomingConnection(qintptr handle) override;
#else
    virtual void incomingConnection(int handle) override;
#endif

    QList<TcpClient*> m_clientList;

};

#endif // TCPSERVER_H
