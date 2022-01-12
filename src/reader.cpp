#include "reader.h"

// using data_ptr = std::unique_ptr<const std::vector<std::byte>>;
using namespace std;

Reader::Reader(bool is_print, bool is_log) : print_replies(is_print), log_replies(is_log) {}

void Reader::DefineReply(data_ptr&& reply) const {
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
            throw std::logic_error("Unknown reply");  // TODO may be change
    }
    if (print_replies) {
        cout << print_message_ << '\n';
    }
    if (log_replies) {

    }
}

void Reader::ReadState(data_ptr&& reply) const {

}

void Reader::GoToPoint(data_ptr&& reply) const {

}

void Reader::MaxAccAndSpeed(data_ptr&& reply) const {

}

void Reader::Reset(data_ptr&& reply) const {

}

