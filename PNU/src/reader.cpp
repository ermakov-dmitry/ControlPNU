#include "reader.h"

// using data_ptr = std::unique_ptr<const std::vector<char>>;
using namespace std;

Reader::Reader(bool is_print, char* data) : print_replies(is_print), reply_(data) {}

void Reader::UnpackReply() {
  uint16_t code = *(uint16_t*)reply_;
  switch (code) {
    case 0x8100:
      ReadState();
      break;
    case 0x8101:
      GoToPoint();
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
  if (print_replies) {
    cout << print_message_ << '\n';
  }
  log_command_.clear();
}

void Reader::ReadState() {
  using namespace std;
  log_command_.reserve(12);

  uint16_t code = *(uint16_t*)reply_;
  //log_command_.push_back(to_string(code));

  uint16_t n_packet = *(uint16_t*)(reply_ + 2);
  //log_command_.push_back(to_string(n_packet));

  uint16_t error_code = *(uint16_t*)(reply_ + 4);
  //log_command_.push_back(to_string(error_code));
  ParseError(error_code);

  uint16_t count_point_in_buffer = *(uint16_t*)(reply_ + 6);
  //log_command_.push_back(to_string(count_point_in_buffer));

  uint16_t move_unit_state = *(uint16_t*)(reply_ + 8);
  //log_command_.push_back(to_string(move_unit_state));
  //ParseUnitState(move_unit_state);

  uint16_t stat_error_a = *(uint16_t*)(reply_ + 10);
  //log_command_.push_back(to_string(stat_error_a));

  long double coordinate_a = Transform::MkradToDeg(*(uint16_t*)(reply_ + 12));
  //log_command_.push_back(to_string(coordinate_a));

  long double speed_a = Transform::MkradToDeg(*(uint16_t*)(reply_ + 14));
  //log_command_.push_back(to_string(speed_a));

  uint16_t stat_error_e = *(uint16_t*)(reply_ + 16);
  //log_command_.push_back(to_string(stat_error_e));

  long double coordinate_e = Transform::MkradToDeg(*(uint16_t*)(reply_ + 18));
  //log_command_.push_back(to_string(coordinate_e));

  long double speed_e = Transform::MkradToDeg(*(uint16_t*)(reply_ + 20));
  //log_command_.push_back(to_string(speed_e));

  uint16_t vcc_pwr_ae = *(uint16_t*)(reply_ + 22);
  //log_command_.push_back(to_string(vcc_pwr_ae));
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

void Reader::GoToPoint() {
  //log_command_.reserve(4);

  uint16_t code = *(uint16_t*)reply_;
  //log_command_.push_back(to_string(code));

  uint16_t n_packet = *(uint16_t*)(reply_ + 2);
  //log_command_.push_back(to_string(n_packet));

  long double coordinate_a = Transform::MkradToDeg(*(uint16_t*)(reply_ + 4));
  //log_command_.push_back(to_string(coordinate_a));

  long double coordinate_e = Transform::MkradToDeg(*(uint16_t*)(reply_ + 6));
  //log_command_.push_back(to_string(coordinate_e));

  print_message_ = "код ответа:                   " + to_string(code) + '\n' +
                   "номер пакета:                 " + to_string(n_packet) + '\n' +
                   "координата оси поворота:      " + to_string(coordinate_a) + '\n' +
                   "координата оси наклона:       " + to_string(coordinate_e) + '\n';
}

void Reader::MaxAccAndSpeed() {
  //log_command_.reserve(6);

  uint16_t code = *(uint16_t*)reply_;
  //log_command_.push_back(to_string(code));

  uint16_t n_packet = *(uint16_t*)(reply_ + 2);
  //log_command_.push_back(to_string(n_packet));

  long double max_acc_a = Transform::MkradToDeg(*(uint16_t*)(reply_ + 4));
  //log_command_.push_back(to_string(max_acc_a));

  long double max_acc_e = Transform::MkradToDeg(*(uint16_t*)(reply_ + 6));
  //log_command_.push_back(to_string(max_acc_e));

  long double max_vel_a = Transform::MkradToDeg(*(uint16_t*)(reply_ + 8));
  //log_command_.push_back(to_string(max_vel_a));

  long double max_vel_e = Transform::MkradToDeg(*(uint16_t*)(reply_ + 10));
  //log_command_.push_back(to_string(max_vel_e));

  print_message_ = "код ответа:                   " + to_string(code) + '\n' +
                   "номер пакета:                 " + to_string(n_packet) + '\n' +
                   "макс ускорение оси поворота:  " + to_string(max_acc_a) + '\n' +
                   "макс ускорение оси наклона:   " + to_string(max_acc_e) + '\n' +
                   "макс скорость оси поворота:   " + to_string(max_vel_a) + '\n' +
                   "макс скорость оси наклона:    " + to_string(max_vel_e) + '\n';
}

void Reader::Reset() {
  log_command_.reserve(2);

  uint16_t code = *(uint16_t*)reply_;
  //log_command_.push_back(to_string(code));

  uint16_t n_packet = *(uint16_t*)(reply_ + 2);
  //log_command_.push_back(to_string(n_packet));

  print_message_ = "код ответа:                   " + to_string(code) + '\n' +
                   "номер пакета:                 " + to_string(n_packet) + '\n';
}

void Reader::ChangeIP() {
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
  //logger_.LogStateErrors(errors);
  if (!critical_errors.empty()) {
    //logger_.LogStateCriticalErrors(critical_errors);
    throw runtime_error(critical_errors);  // this is gabella
  }
}

/*void Reader::ParseUnitState(uint16_t unit_state) const {
    ostringstream state;
    if (unit_state & (1 << 0)) {
        state << "Сервоконтролеры оси поворота и оси наклона к работе готовы" << '\n';
    } else {
        //logger_.LogMoveUnitState(state.str());
        // throw runtime_error("Сервоконтролеры оси поворота и оси наклона к работе не готовы!");
    }
    if (unit_state & (1 << 1)) {
        state << "Сервоконтролеры оси поворота и оси наклона активны" << '\n';
    }
    if (unit_state & (1 << 1)) {
        state << "Сервоконтролеры оси поворота и оси наклона активны" << '\n';
    }
    if (unit_state & (1 << 3)) {
        state << "узел осуществляет перемещение в требуемую точку»,"
                                             " в режиме «Позиция»  или набор скорости, в режиме «Скорость»" << '\n';
    }
    if (unit_state & (1 << 4)) {
        state << "Установлен режим работы «Позиция»" << '\n';}
    if (unit_state & (1 << 5)) {state << "Установлен режим работы «Скорость»" << '\n';
    }
    if (unit_state & (1 << 6)) {
        state << "Установлен режим работы «Слежение»" << '\n';
    }
    //logger_.LogMoveUnitState(state.str());
}*/