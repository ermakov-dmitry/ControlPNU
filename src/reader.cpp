#include "reader.h"

// using data_ptr = std::unique_ptr<const std::vector<std::byte>>;
using namespace std;

Reader::Reader(bool is_print, bool is_log) : print_replies(is_print), log_replies(is_log) {}

void Reader::UnpackReply(data_ptr&& reply) {
    uint16_t code = *(uint16_t*)reply->data();
    switch (code) {
        case 0x8100:
            ReadState(move(reply));
            break;
        case 0x8101:
            GoToPoint(move(reply));
            break;

        case 0x8140:
            MaxAccAndSpeed(move(reply));
            break;

        case 0x81F0:
            Reset(move(reply));
            break;

        default:
            throw std::invalid_argument("Unknown reply");
    }
    if (print_replies) {
        cout << print_message_ << '\n';
    }
    if (log_replies) {
        // TODO create logic of logger
    }
}

void Reader::ReadState(data_ptr&& reply) {
    uint16_t code = *(uint16_t*)reply->data();
    uint16_t n_packet = *(uint16_t*)(reply->data() + 2);
    uint16_t error_code = *(uint16_t*)(reply->data() + 4);
    // TODO create parse error method
    uint16_t count_point_in_buffer = *(uint16_t*)(reply->data() + 6);
    uint16_t move_unit_state = *(uint16_t*)(reply->data() + 8);
    // TODO move unit state method
    uint16_t stat_error_a = *(uint16_t*)(reply->data() + 10);
    long double coordinate_a = transformer_.MkradToDeg(*(uint16_t*)(reply->data() + 12));
    long double speed_a = transformer_.MkradToDeg(*(uint16_t*)(reply->data() + 14));
    uint16_t stat_error_e = *(uint16_t*)(reply->data() + 16);
    long double coordinate_e = transformer_.MkradToDeg(*(uint16_t*)(reply->data() + 18));
    long double speed_e = transformer_.MkradToDeg(*(uint16_t*)(reply->data() + 20));
    uint16_t vcc_pwr_ae = *(uint16_t*)(reply->data() + 22);
    // TODO create vcc method
    print_message_ = "код ответа:                   " + to_string(code) + '\n' +
                     "номер пакета:                 " + to_string(n_packet) + '\n' +
                     "код ошибки:                   " + to_string(error_code) + '\n' +
                     "кол-во точек в буфере:        " + to_string(count_point_in_buffer) + '\n' +
                     "состояние узла управления:    " + to_string(move_unit_state) + '\n' +
                     "копия состояния оси азимута:  " + to_string(stat_error_a) + '\n' +
                     "координата оси поворота:      " + to_string(coordinate_a) + '\n' +
                     "скорость оси поворота:        " + to_string(speed_a) + '\n' +
                     "копия состояния оси наклона:  " + to_string(stat_error_e) + '\n' +
                     "координата оси наклона:       " + to_string(coordinate_e) + '\n' +
                     "скорость оси наклона:         " + to_string(speed_e) + '\n' +
                     "напряжение сервоконтроллеров: " + to_string(vcc_pwr_ae) + '\n';
}

void Reader::GoToPoint(data_ptr&& reply) {
    uint16_t code = *(uint16_t*)reply->data();
    uint16_t n_packet = *(uint16_t*)(reply->data() + 2);
    long double coordinate_a = transformer_.MkradToDeg(*(uint16_t*)(reply->data() + 4));
    long double coordinate_e = transformer_.MkradToDeg(*(uint16_t*)(reply->data() + 6));
    print_message_ = "код ответа:                   " + to_string(code) + '\n' +
                     "номер пакета:                 " + to_string(n_packet) + '\n' +
                     "координата оси поворота:      " + to_string(coordinate_a) + '\n' +
                     "координата оси наклона:       " + to_string(coordinate_e) + '\n';
}

void Reader::MaxAccAndSpeed(data_ptr&& reply) {
    uint16_t code = *(uint16_t*)reply->data();
    uint16_t n_packet = *(uint16_t*)(reply->data() + 2);
    long double max_acc_a = transformer_.MkradToDeg(*(uint16_t*)(reply->data() + 4));
    long double max_acc_e = transformer_.MkradToDeg(*(uint16_t*)(reply->data() + 6));
    long double max_vel_a = transformer_.MkradToDeg(*(uint16_t*)(reply->data() + 8));
    long double max_vel_e = transformer_.MkradToDeg(*(uint16_t*)(reply->data() + 10));
    print_message_ = "код ответа:                   " + to_string(code) + '\n' +
                     "номер пакета:                 " + to_string(n_packet) + '\n' +
                     "макс ускорение оси поворота:  " + to_string(max_acc_a) + '\n' +
                     "макс ускорение оси наклона:   " + to_string(max_acc_e) + '\n' +
                     "макс скорость оси поворота:   " + to_string(max_vel_a) + '\n' +
                     "макс скорость оси наклона:    " + to_string(max_vel_e) + '\n';
}

void Reader::Reset(data_ptr&& reply) {
    uint16_t code = *(uint16_t*)reply->data();
    uint16_t n_packet = *(uint16_t*)(reply->data() + 2);
    print_message_ = "код ответа:                   " + to_string(code) + '\n' +
                     "номер пакета:                 " + to_string(n_packet) + '\n';
}

