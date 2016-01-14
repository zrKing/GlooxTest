/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MessageTest.h
 * Author: zrking
 *
 * Created on 2015年11月20日, 下午2:38
 */

#ifndef MESSAGETEST_H
#define MESSAGETEST_H

#include <gloox/client.h>
#include <gloox/messagesessionhandler.h>
#include <gloox/messagehandler.h>
#include <gloox/chatstatehandler.h>
#include <gloox/messageeventhandler.h>
#include <gloox/chatstatehandler.h>
#include <gloox/connectionlistener.h>
#include <gloox/presencehandler.h>
#include <gloox/loghandler.h>
#include <gloox/message.h>
#include <gloox/flexoff.h>
#include <gloox/flexoffhandler.h>

#include <string.h>

using namespace std;
using namespace gloox;

class MessageTest : public 
    MessageSessionHandler, ConnectionListener, LogHandler,
    MessageEventHandler, MessageHandler, ChatStateHandler,
    PresenceHandler,FlexibleOfflineHandler {
public:
    MessageTest();
    MessageTest(const MessageTest& orig);
    virtual ~MessageTest();
 
public:
    bool connect(string userName, string pwd);
    void recive(int nStamp);
    void sendMsg(string strToId, string strMsg);
    
public:
    virtual void onConnect();
    virtual void onDisconnect(ConnectionError e);

    virtual bool onTLSConnect(const CertInfo& info);
    virtual void handleLog(LogLevel level, LogArea area, const std::string& message);
    virtual void handleMessageEvent(const JID& from, MessageEventType event);
    virtual void handleMessage(const Message& msg, MessageSession* session );
    virtual void handleMessageSession(MessageSession* session);
    virtual void handleChatState(const JID& from, ChatStateType state);
    virtual void handlePresence(const Presence& presence);
    
    //offline
    virtual void handleFlexibleOfflineSupport( bool support );
    virtual void handleFlexibleOfflineMsgNum( int num );
    virtual void handleFlexibleOfflineMessageHeaders( const Disco::ItemList& headers );
    virtual void handleFlexibleOfflineResult( FlexibleOfflineResult foResult );
    
    
    
private:
    
    FlexibleOffline* m_pFlexOff;
    Client* m_pClient;
    MessageSession* m_pMs;

};

#endif /* MESSAGETEST_H */

