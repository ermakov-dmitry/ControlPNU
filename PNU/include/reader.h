#ifndef DIPLOMA_READER_H
#define DIPLOMA_READER_H
#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "commands.h"
#include "transformer.h"

struct Position {
    double azimuth;
    double elevator;
};

class Reader{
public:
    //! Конструктор класса
    explicit Reader(char* data);
    //! Парсинг полученных данных
    Position UnpackReply() const;

private:
    //! Парсинг состояния
    Position ReadState() const;
    //! Парсинг сообщения "двигаться в точку"
    Position GoToPoint() const;
    //! Парсинг сообщения с ограничениями скоростей и ускорений
    void MaxAccAndSpeed() const;
    //! Парсинг сообщения сброса
    void Reset() const;
    //! Парсинг ошибок в чтении состояния
    void ParseError(unsigned short code) const;
    //! Парсинг ответа на команду смены IP адреса
    void ChangeIP() const;
    //! Буфер с данными полученного сообщения
    char* reply_;
    //! Данные для вывода
    mutable std::string print_message_;
};

#endif //DIPLOMA_READER_H
