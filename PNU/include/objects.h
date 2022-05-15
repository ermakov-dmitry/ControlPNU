#ifndef DIPLOMA_OBJECTS_H
#define DIPLOMA_OBJECTS_H
#pragma once
#include <string>
#include <memory>
#include "connection.h"
#include "transformer.h"
#include "reader.h"
#include "commands.h"
#ifndef LOCAL_MACHINE
#include "globaldefs.h"
#include "ModelEnable.h"
#endif

//! Основной класс с командами управления ПНУ
class PNU {
public:
    //! Вспомогательная структура с полями смещения
    struct Offsets {
        double azimuth;
        double elevator;
    };
    //! Вспомогательная структура с ограничениями по азимуту и углу места
    struct Bounds {
        double min_azimuth;
        double max_azimuth;
        double min_elevator;
        double max_elevator;
    };
    //! Вспомогательная структура с ограничениями скоростных характеристик
    struct MaxSpeedData {
        double azimuth_acceleration;
        double elevator_acceleration;
        double azimuth_velocity;
        double elevator_velocity;
    };
    //! Конструктор класса
    explicit PNU(const std::string& ip_address, int port);  // may be other for new objects
    //! Команда "Прочитать состояние"
    void GetState();
    //! Команда "Двигаться в точку"
    void GoToPoint(double azimuth, double elevator);
    //! Команда "Задать максимальные ускорения и скорости"
    void SetMaxAccelerationAndSpeed(const MaxSpeedData&);
    //! Команда "Сброс"
    void Reset();
    //! Команда "Прочитать состояние"
    void ReadReply();
    //! Команда "Сменить IP Адрес"
    void ChangeIPAddress(const char* ip);
#ifndef LOCAL_MACHINE
    void npsk_ssk(double &x, double &y, double &z);
#endif
    //! Команда "Задать смещения и ограничения углов поворота"
    void SetOffsetsAndBounds(Offsets offsets, const Bounds& bounds);
    //! Команда запроса угловых координат ПНУ TODO
    void GetOutput();
    //! Деструктор класса
    ~PNU();
    //! Структура для управления ПНУ через GUI
    struct Setup {
        int manual_mode;
        int ust;
        int cartesizan_mode;
        double x;
        double y;
        double z;
        double azimuth;
        double elevator;
        double azimuth_offset;
        double elevator_offset;
        double min_elevator;
        double max_elevator;
        double min_azimuth;
        double max_azimuth;
    };
    Setup setup_;
    //! Структура для отображения угловых координат в GUI
    struct Output{
        double azimuth;
        double elevator;
    };
    Output output_;
    //! Флаг для проверки инициализации объекта
    bool is_init_;

private:
    //! Буфер с данными межсетевого обмена
    char* reply_pnu_;
    //! Вспомогательный метод для чтения полученных данных от ПНУ
    void CheckReply();
    //! Поле для сетевого обмена по UDP протоколу
    UDPConnecter connecter_;
    //! Поле для разбора входящих данных
    Reader reader_;
    //! Смещения углов ПНУ
    double azimuth_offset_;
    double elevator_offset_;
    //! Текущие значения углов ПНУ
    double azimuth_;
    double elevator_;
};

#ifndef LOCAL_MACHINE
extern PNU* pPNU;
void CreatePNU();
void InitPNU();
void CalculatePNU();
void StopPNU();
#endif


#endif //DIPLOMA_OBJECTS_H
