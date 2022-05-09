#ifndef DIPLOMA_CONNECTION_H
#define DIPLOMA_CONNECTION_H
#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include <memory>
#ifdef LOCAL_MACHINE
#include <cstdint>
#ifdef __linux__  // TODO test for Linux
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#elif __MINGW32__
#include<cstdio>
#include<winsock2.h>
#define MSG_DONTWAIT 0
#endif
#else
#include "sockLib.h"
#include "inetLib.h"
#endif
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

//! Класс для сетевого обмена по UDP протоколу между ПНУ и внешним устройством
class UDPConnecter {
public:
    //! Констуктор класса UDP соединения
    explicit UDPConnecter(const std::string& ip_address, int port, char* data);
    //! Отправка данных на устройство
    void SendData(char*, size_t);
    //! Получение данных от устройсва
    void ReadData() const;
    //! Чтение номера пакета
    unsigned short GetPacketNumber() const;
    //! Сброс номера пакета
    void ResetPackageNumber();
    //! Деструктор класса
    ~UDPConnecter();
    //! Метод смены IP адреса
    void ChangeIP(const std::string& ip_address);

private:
    //! Номер порта
    int port_;
    //! IP адрес устройства
    std::string ip_address_;
    //! Номер пакета
    unsigned short packet_number_;
    struct Socket {
        int sockfd;
        struct sockaddr_in servaddr;
    };
    //! Буфер с данными полученного сообщения
    char* reply_;
    Socket socket_;
};
#endif //DIPLOMA_CONNECTION_H
