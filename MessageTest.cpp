/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MessageTest.cpp
 * Author: zrking
 * 
 * Created on 2015年11月20日, 下午2:38
 */

#include "MessageTest.h"

using namespace std;
#include <iostream>

MessageTest::MessageTest() {

}

MessageTest::MessageTest(const MessageTest& orig) {
}

MessageTest::~MessageTest() {
    if(m_pClient)
        delete m_pClient;
    if(m_pMs)
        delete m_pMs;
}

bool MessageTest::connect(string userName, string pwd)
{
    cout<<"connecting ..."<<endl;
    JID jid;
    jid.setServer("im.koderoot.net");
    jid.setUsername(userName.c_str());

    m_pClient = new Client(jid, pwd.c_str());
    m_pClient->registerPresenceHandler(this);
    m_pClient->registerConnectionListener(this);
    m_pClient->registerMessageHandler(this);
    m_pClient->registerMessageSessionHandler(this);
    
    if(!m_pFlexOff)
	m_pFlexOff = new FlexibleOffline(m_pClient);
    
    bool b = m_pClient->connect(false);
    
    cout<<"  connect "; 
    if(b)
    {
	cout<<"OK"<<endl;
	m_pFlexOff->registerFlexibleOfflineHandler(this);
    }
    else
        cout<<"Error"<<endl;
}

void MessageTest::onConnect()
{
    cout<<"ON CONNECT!!!"<<endl;
    m_pFlexOff->checkSupport();
    //m_pFlexOff->fetchHeaders();
    m_pFlexOff->getMsgCount();
}

void MessageTest::recive(int nStamp)
{
    m_pClient->recv(nStamp);
}

void MessageTest::sendMsg(string strToId, string strMsg)
{
    JID jid;
    jid.setUsername(strToId);
    jid.setServer(m_pClient->server());
    
    MessageSession* pMsgSession = new MessageSession(m_pClient, jid);
    pMsgSession->registerMessageHandler(this);
    pMsgSession->send(strMsg);
    m_pClient->disposeMessageSession(pMsgSession);
}

void MessageTest::onDisconnect(ConnectionError e)
{
    cout<<"ON DISCONNECT : "<<e<<endl;
    if(e == ConnAuthenticationFailed)
    {
        cout<<" -- AuthError:"<<m_pClient->authError()<<endl;; 
    }
}

void MessageTest::handleChatState(const JID& from, ChatStateType state)
{
    cout<<"HANDLE CHAT STAT"<<endl;
}

void MessageTest::handleLog(LogLevel level, LogArea area, const std::string& message)
{
    printf("log: level: %d, area: %d, %s\n", level, area, message.c_str() );
}

void MessageTest::handleMessage(const Message& msg, MessageSession* session = 0)
{
    printf( "type: %d, subject: %s, message: %s, thread id: %s\n", msg.subtype(),
              msg.subject().c_str(), msg.body().c_str(), msg.thread().c_str() );
}

void MessageTest::handleMessageEvent(const JID& from, MessageEventType event)
{
    cout<<"HANDLE MESSAGEEVENT"<<endl;
    cout<<"    -- state:"<<event<<endl;
    cout<<"    -- name:"<<from.username()<<"  "<<from.full()<<endl;
}

void MessageTest::handleMessageSession(MessageSession* session)
{
    cout<<"HANDLE MESSAGE SESSION"<<endl;
    //
    JID id = session->target();
    cout<<id.username()<<endl;
    cout<<id.full()<<endl;
    session->registerMessageHandler(this);
    
}

bool MessageTest::onTLSConnect(const CertInfo& info)
{
    return false;
}

void MessageTest::handlePresence(const Presence& presence)
{}

void MessageTest::handleFlexibleOfflineSupport( bool support )
{
    cout<<"Offline Message "<<(support ? "supported" : "not supported")<<endl;
}

void MessageTest::handleFlexibleOfflineMsgNum( int num )
{
    cout<<"Offline Message num :"<<num<<endl;
}
void MessageTest::handleFlexibleOfflineMessageHeaders( const Disco::ItemList& headers )
{
    Disco::ItemList::const_iterator it = headers.begin();
    while(it != headers.end())
    {
	cout<<"Offline Message header:";
	cout<<(*it)->jid()<<endl;
	++it;
    }
}

void MessageTest::handleFlexibleOfflineResult( FlexibleOfflineResult foResult )
{
    
}




