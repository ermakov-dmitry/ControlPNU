#include "reader.h"

using namespace std;

Reader::Reader(char* data) : reply_(data) {}

Position Reader::UnpackReply() const {
    uint16_t code = *(uint16_t*)reply_;
    Position ret;
    ret.azimuth = -1;
    ret.elevator = -1;
    switch (code) {
        case 0x8100:
            ret = ReadState();
            break;
        case 0x8101:
            ret = GoToPoint();
            break;

        case 0x8140:
            MaxAccAndSpeed();
            break;

        case 0x81F0:
            Reset();
            break;

        case 0x8F00:
            ChangeIP();
            break;

        default:
            throw std::invalid_argument("Unknown code\n");
    }
#ifdef LOCAL_MACHINE
    std::cout << print_message_ << '\n';
#endif
    return ret;
}

Position Reader::ReadState() const {
    using namespace std;
    uint16_t code = *(uint16_t*)reply_;
    uint16_t n_packet = *(uint16_t*)(reply_ + 2);
    uint16_t error_code = *(uint16_t*)(reply_ + 4);
    ParseError(error_code);
    uint16_t count_point_in_buffer = *(uint16_t*)(reply_ + 6);
    uint16_t move_unit_state = *(uint16_t*)(reply_ + 8);
    uint16_t stat_error_a = *(uint16_t*)(reply_ + 10);
    double coordinate_a = Transform::MkradToDeg(*(uint16_t*)(reply_ + 12));
    double speed_a = Transform::MkradToDeg(*(uint16_t*)(reply_ + 14));
    uint16_t stat_error_e = *(uint16_t*)(reply_ + 16);
    double coordinate_e = Transform::MkradToDeg(*(uint16_t*)(reply_ + 18));
    double speed_e = Transform::MkradToDeg(*(uint16_t*)(reply_ + 20));
    uint16_t vcc_pwr_ae = *(uint16_t*)(reply_ + 22);
    Position ret;
    ret.azimuth = coordinate_a;
    ret.elevator = coordinate_e;
    print_message_ = "код ответа:                   " + to_string(code) + '\n' +
                     "номер пакета:                 " + to_string(n_packet) + '\n' +
                     "код ошибки:                   " + to_string(error_code) + '\n' +
                     "количество точек в буфере:    " + to_string(count_point_in_buffer) + '\n' +
                     "состояние узла поворота:      " + to_string(move_unit_state) + '\n' +
                     "копия состояния оси азимута:  " + to_string(stat_error_a) + '\n' +
                     "координата оси поворота:      " + to_string(coordinate_a) + '\n' +
                     "скорость оси поворота:        " + to_string(speed_a) + '\n' +
                     "состояния оси наклона:        " + to_string(stat_error_e) + '\n' +
                     "координата оси наклона:       " + to_string(coordinate_e) + '\n' +
                     "скорость оси наклона:         " + to_string(speed_e) + '\n' +
                     "напряжение питания сервок-в:  " + to_string(vcc_pwr_ae) + '\n';

    return ret;
}

Position Reader::GoToPoint() const {
    uint16_t code = *(uint16_t*)reply_;
    uint16_t n_packet = *(uint16_t*)(reply_ + 2);
    double coordinate_a = Transform::MkradToDeg(*(uint16_t*)(reply_ + 4));
    double coordinate_e = Transform::MkradToDeg(*(uint16_t*)(reply_ + 6));
    Position ret;
    ret.azimuth = coordinate_a;
    ret.elevator = coordinate_e;
  print_message_ = "код ответа:                   " + to_string(code) + '\n' +
                   "номер пакета:                 " + to_string(n_packet) + '\n' +
                   "координата оси поворота:      " + to_string(coordinate_a) + '\n' +
                   "координата оси наклона:       " + to_string(coordinate_e) + '\n';
    return ret;

}

void Reader::MaxAccAndSpeed() const {
    uint16_t code = *(uint16_t*)reply_;
    uint16_t n_packet = *(uint16_t*)(reply_ + 2);
    double max_acc_a = Transform::MkradToDeg(*(uint16_t*)(reply_ + 4));
    double max_acc_e = Transform::MkradToDeg(*(uint16_t*)(reply_ + 6));
    double max_vel_a = Transform::MkradToDeg(*(uint16_t*)(reply_ + 8));
    double max_vel_e = Transform::MkradToDeg(*(uint16_t*)(reply_ + 10));
    print_message_ = "код ответа:                   " + to_string(code) + '\n' +
                     "номер пакета:                 " + to_string(n_packet) + '\n' +
                     "макс ускорение оси поворота:  " + to_string(max_acc_a) + '\n' +
                     "макс ускорение оси наклона:   " + to_string(max_acc_e) + '\n' +
                     "макс скорость оси поворота:   " + to_string(max_vel_a) + '\n' +
                     "макс скорость оси наклона:    " + to_string(max_vel_e) + '\n';
}

void Reader::Reset() const {
    uint16_t code = *(uint16_t*)reply_;
    uint16_t n_packet = *(uint16_t*)(reply_ + 2);
    print_message_ = "код ответа:                   " + to_string(code) + '\n' +
                   "номер пакета:                 " + to_string(n_packet) + '\n';
}

void Reader::ChangeIP() const {
    uint16_t code = *(uint16_t*)reply_;
    uint16_t n_packet = *(uint16_t*)(reply_ + 2);
    print_message_ = "код ответа:                   " + to_string(code) + '\n' +
                   "номер пакета:                 " + to_string(n_packet) + '\n';
}

void Reader::ParseError(uint16_t code) const {
    if (!code) {
        return;
    }
    string errors;
    if (code & (1 << 0)) {
        errors += "Ошибка формата или неизвестная команда\n";
    }
    if (code & (1 << 1)) {
        errors += "Была зафиксирована  потеря пакета, сбрасывается командой «Прочитать состояние»\n";
        // throw domain_error("");
    }
    if (code & (1 << 2)) {
        errors += "Ошибка в команде «Загрузить точку»  (во всех режимах)\n";
    }
    if (code & (1 << 3)) {
        errors += "Нарушена последовательность точек в команде «Загрузить точку, режим «Слежение»»\n";
    }
    if (code & (1 << 4)) {
        errors += "Ошибка в команде «Загрузить параметры узла управления поворотами, наклонами»\n";
    }
    if (code & (1 << 5)) {
        errors += "Ошибка в команде «Сменить IP адрес или № UDP порта»\n";
    }
    if (code & (1 << 6)) {
        errors += "Буфер точек перемещения пуст (была попытка чтения из пустого буфера)\n";
    }
    if (code & (1 << 7)) {
        errors += "Буфер точек перемещения полон (была попытка записи в полный буфер)\n";
    }
    string critical_errors;
    if (code & (1 << 8)) {
        critical_errors += "Ошибка внутренней шины CAN\n";
    }
    if (code & (1 << 9)) {
        critical_errors += "Сервоконтролер оси поворота не работает\n";
    }
    if (code & (1 << 10)) {
        critical_errors += "Сервоконтролер оси наклона не работает\n";
    }
#ifdef LOCAL_MACHINE
    if (!errors.empty()) {
        std::cout << errors << '\n';
    }
    if (!critical_errors.empty()) {
        std::cout << critical_errors << '\n';
        throw runtime_error(critical_errors);  // this is gabella
    }
#endif
}
