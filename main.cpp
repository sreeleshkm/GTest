//*************************** Socket communication ****************************
// Copyright (c) 2024 Trenser Technology Solutions (P) Ltd.
// All Rights Reserved
//*****************************************************************************
//
// File     : main.cpp
// Summary  : Main file of the server communication
// Note     : Nil
// Author   : Sreelesh KM
// Date     : 01/10/2024
//
//*****************************************************************************

//******************************* Include Files *******************************
#include <iostream>
#include <gtest/gtest.h>
#include "socket_common.h"

#if (SOCKET_COM == SOC_SER)
#include "server.h"
#elif (SOCKET_COM == SOC_CLI)
#include "client.h"
#endif

//******************************* Local Types *********************************
using namespace std;

//***************************** Local Constants *******************************
#define GTEST_ENABLE            1
#define TEST_CREATESOCKET       0
#define TEST_SETOPTION          0
#define TEST_BINDSOC            0
#define TEST_BINDSOCWITHOPT     0
#define TEST_SOCKETLISTEN       0
#define TEST_SOCKETACCEPT       0
#define TEST_SOCKETCONNECT      0
#define TEST_STARTCONECTION     1

#if (GTEST_ENABLE == 1)
#if (TEST_CREATESOCKET == 1) 
TEST(SocCom, createSocket)
{
    SocketCom sock;
    EXPECT_EQ(sock.createSocket(), 1);
}
#endif

#if (TEST_SETOPTION == 1)
#if (SOCKET_COM == SOC_SER)
TEST(SocCom, setOption1)
{
    SocketCom sock;
    ServerCom Ser;
    EXPECT_EQ(Ser.setOption(sock.getSocketDes()), 1);
}

TEST(SocCom, setOption2)
{
    SocketCom sock;
    ServerCom Ser;
    
    bool blStatus = false;
    blStatus = sock.createSocket();
    if (blStatus == true)
    {
        blStatus = Ser.setOption(sock.getSocketDes()); 
        EXPECT_EQ(blStatus, 1);
    }
}
#endif
#endif

#if (TEST_BINDSOC == 1)
TEST(SocCom, bindSocket1)
{
    SocketCom sock;
    EXPECT_EQ(sock.bindSocket(), 1);
}
#endif

#if (SOCKET_COM == SOC_SER)
#if (TEST_BINDSOC == 1)
TEST(SocCom, bindSocket2)
{
    SocketCom sock;
    bool blStatus = false;
    blStatus = sock.createSocket();
    if (blStatus == true)
    {
        blStatus = sock.bindSocket(); 
        ASSERT_EQ(blStatus, 1);
    }
}
#endif

#if (TEST_BINDSOCWITHOPT == 1)
TEST(SocCom, bindSocket3)
{
    SocketCom sock;
    ServerCom Ser;
    
    bool blStatus = false;
    blStatus = sock.createSocket();
    if (blStatus == true)
    {
        blStatus = Ser.setOption(sock.getSocketDes());

        if (blStatus == true)
        {
            blStatus = sock.bindSocket(); 
            EXPECT_EQ(blStatus, 1);
        }
    }
}
#endif
#endif

#if (SOCKET_COM == SOC_SER)
#if (TEST_SOCKETLISTEN == 1)
TEST(SocCom, socketListen1)
{
    ServerCom Ser;
    SocketCom sock;
    bool blStatus = false;

    blStatus = Ser.listenSocket(sock.getSocketDes());
    EXPECT_EQ(blStatus, 1);
}

TEST(SocCom, socketListen2)
{
    SocketCom sock;
    ServerCom Ser;
    
    bool blStatus = false;
    blStatus = sock.createSocket();
    if (blStatus == true)
    {
        blStatus = Ser.setOption(sock.getSocketDes());

        if (blStatus == true)
        {
            blStatus = sock.bindSocket();

            if (blStatus == true)
            {
                blStatus = Ser.listenSocket(sock.getSocketDes());
                EXPECT_EQ(blStatus, 1);
            }
        }
    }
}
#endif

#if (TEST_SOCKETACCEPT == 1)
TEST(SocCom, socketAccept1)
{
    ServerCom Ser;
    SocketCom sock;
    bool blStatus = false;

    blStatus = Ser.acceptConnection(sock.getSocketDes());
    EXPECT_EQ(blStatus, 1);
}

TEST(SocCom, socketAccept2)
{
    SocketCom sock;
    ServerCom Ser;
    bool blStatus = false;

    blStatus = sock.createSocket();
    if (blStatus == true)
    {
        blStatus = Ser.setOption(sock.getSocketDes());

        if (blStatus == true)
        {
            blStatus = sock.bindSocket();

            if (blStatus == true)
            {
                blStatus = Ser.listenSocket(sock.getSocketDes());

                if (blStatus == true)
                {
                    blStatus = Ser.acceptConnection(sock.getSocketDes());
                    cout << "Socket accept : " << blStatus + 48 << endl;
                    EXPECT_EQ(blStatus, 1);
                }
            }
        }
    }
}
#endif
#endif

#if (SOCKET_COM == SOC_CLI)
#if (TEST_SOCKETCONNECT == 1)
TEST(SocCom, socketCliCon1)
{
    ClientCom Cli;
    SocketCom sock;
    bool blStatus = false;

    blStatus = Cli.connectToSocket(sock.getSocketDes());
    EXPECT_EQ(blStatus, 1);
}

TEST(SocCom, socketCliCon2)
{
    bool blConState = false;
    ClientCom Cli;

    blConState = Cli.startConnection();
    EXPECT_EQ(blConState, 1);
}
#endif
#endif

#if (TEST_STARTCONECTION == 1)
TEST(SocCom, startConnection)
{
    bool blStatus = false;
    bool blRcvMsgStatus = false;
    bool blSndMsgStatus = false;

#if (SOCKET_COM == SOC_SER)
    bool blMesState = false;
    uint8 pucMessage[10] = "Recieved!";
    ServerCom Server;
#elif (SOCKET_COM == SOC_CLI)
    uint8 pucMessage[4] = "Hii";
    ClientCom Client;
#endif
#if (SOCKET_COM == SOC_SER)
    blStatus = Server.startConnection();
#elif (SOCKET_COM == SOC_CLI)
    blStatus = Client.startConnection();
#endif
    EXPECT_EQ(blStatus, 1);
}
#endif
#endif

//*********************************** main ************************************
//Purpose : Socket communication
//Inputs  : Nil
//Outputs : Nil
//Return  : Nil
//Notes   : Nil
//*****************************************************************************
int main()
{
    cout << "Program Started\n";

#if (GTEST_ENABLE == 1)
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();

#else
    bool blStatus = false;
    bool blRcvMsgStatus = false;
    bool blSndMsgStatus = false;

#if (SOCKET_COM == SOC_SER)
    bool blMesState = false;
    uint8 pucMessage[10] = "Recieved!";
    ServerCom Server;
#elif (SOCKET_COM == SOC_CLI)
    uint8 pucMessage[4] = "Hii";
    ClientCom Client;
#endif

#if (SOCKET_COM == SOC_SER)
    blStatus = Server.startConnection();
#elif (SOCKET_COM == SOC_CLI)
    blStatus = Client.startConnection();
#endif

    if (blStatus == true)
    {
        while (true)
        {
#if (SOCKET_COM == SOC_SER)
            blRcvMsgStatus = Server.readMessage(Server.getCliSoc());
#elif (SOCKET_COM == SOC_CLI)
            blRcvMsgStatus = Client.readMessage(Client.getSocketDes());
#endif
            if (blRcvMsgStatus == true)
            {
#if (SOCKET_COM == SOC_SER)
                cout << "Message : " << Server.pucRecieveBuffer << endl;
                blMesState = Server.sendMessage(Server.getCliSoc(), pucMessage);
            
                if (blMesState == false)
                {
                    printf("Message not send\n");
                }
#elif (SOCKET_COM == SOC_CLI)
                cout << "Message : " << Client.pucRecieveBuffer << endl;
#endif
            }

#if (SOCKET_COM == SOC_CLI)
            blSndMsgStatus = Client.exceedTime(SEND_MES_TIME_DIF);

            if (blSndMsgStatus == true)
            {
                Client.sendMessage(Client.getSocketDes(), pucMessage);
            }
#endif
        }
    }

    return 0;

#endif
}

// EOF
