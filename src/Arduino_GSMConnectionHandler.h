/*
   This file is part of ArduinoIoTCloud.

   Copyright 2019 ARDUINO SA (http://www.arduino.cc/)

   This software is released under the GNU General Public License version 3,
   which covers the main part of arduino-cli.
   The terms of this license can be found at:
   https://www.gnu.org/licenses/gpl-3.0.en.html

   You can be released from the requirements of the above licenses by purchasing
   a commercial license. Buying such a license is mandatory if you want to modify or
   otherwise use the software for commercial activities involving the Arduino
   software without disclosing the source code of your own applications. To purchase
   a commercial license, send an email to license@arduino.cc.
*/

#ifndef GSM_CONNECTION_MANAGER_H_
#define GSM_CONNECTION_MANAGER_H_

/******************************************************************************
   INCLUDE
 ******************************************************************************/

#include "TCPIP_ConnectionHandler.h"

#ifdef BOARD_HAS_GSM /* Only compile if this is a board with GSM */

/******************************************************************************
   CLASS DECLARATION
 ******************************************************************************/

class GSMConnectionHandler : public TCPIPConnectionHandler {
  public:
    GSMConnectionHandler(const char *pin, const char *apn, const char *login, const char *pass, const bool keepAlive = true);

    virtual void init();
    virtual unsigned long getTime();
    virtual void check() {
      update();
    }
    virtual void update();
    virtual Client &getClient() {
      return networkClient;
    };
    virtual UDP &getUDP() {
      return udp;
    };

    GSMClient networkClient;
    GSM gsmAccess;
    GPRS gprs;
    GSMUDP udp;

    virtual void disconnect();
    virtual void connect();

    virtual void addCallback(NetworkConnectionEvent const event, OnNetworkEventCallback callback);
    virtual void addConnectCallback(OnNetworkEventCallback callback);
    virtual void addDisconnectCallback(OnNetworkEventCallback callback);
    virtual void addErrorCallback(OnNetworkEventCallback callback);

  private:

    void changeConnectionState(NetworkConnectionState _newState);

    const int CHECK_INTERVAL_IDLE = 100;
    const int CHECK_INTERVAL_INIT = 100;
    const int CHECK_INTERVAL_CONNECTING = 500;
    const int CHECK_INTERVAL_CONNECTED = 10000;
    const int CHECK_INTERVAL_RETRYING = 5000;
    const int CHECK_INTERVAL_DISCONNECTED = 1000;
    const int CHECK_INTERVAL_ERROR = 500;

    const char *pin, *apn, *login, *pass;
    unsigned long lastConnectionTickTime;
    int connectionTickTimeInterval;


    bool keepAlive;

    OnNetworkEventCallback  _on_connect_event_callback,
                            _on_disconnect_event_callback,
                            _on_error_event_callback;

    static void execNetworkEventCallback(OnNetworkEventCallback & callback, void * callback_arg);
};

#endif /* #ifdef BOARD_HAS_GSM  */

#endif /* #ifndef GSM_CONNECTION_MANAGER_H_ */
