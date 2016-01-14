/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: zrking
 *
 * Created on 2015年11月20日, 下午2:31
 */

#include <cstdlib>
#include <iostream>
#include <pthread.h>


#include "MessageTest.h"

using namespace std;

bool g_bIm = true;

MessageTest t01;
MessageTest t02;


void* conn(void* arg)
{
    t01.connect("wandoera","wandoerA");
    
    //t02.connect("wandoerb","wandoerB");
    
    
    sleep(5);
    
    while(g_bIm)
    {
	 t01.recive(1000);
	 t02.recive(1000);
    }

}

int main(int argc, char** argv) {
    
    pthread_t th;
    int n = pthread_create(&th,NULL,conn,NULL);
    //MessageTest t1;
    //t1.connect("test1","test1");
    
    while(true)
    {	
	string strMsg;
	cout<<"test001 Send Msg To test002: ";
	cin>>strMsg;
	t01.sendMsg("wandoerb",strMsg);
    }
    
    return 0;
}

