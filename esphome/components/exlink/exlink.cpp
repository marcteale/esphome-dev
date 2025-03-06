#include "exlink.h"
#include "esphome/core/log.h"

namespace esphome {
namespace exlink {

static const char *const TAG = "exlink";

void exlink::volume_up() {
  ESP_LOGD(TAG, "Increasing volume");
  this->send_cmd_(0x04);
}

void exlink::send_cmd_(uint8_t cmd, uint16_t argument) {
  uint8_t buffer[10]{0x7e, 0xff, 0x06, cmd, 0x01, (uint8_t) (argument >> 8), (uint8_t) argument, 0x00, 0x00, 0xef};
  uint16_t checksum = 0;
  for (uint8_t i = 1; i < 7; i++)
    checksum += buffer[i];
  checksum = -checksum;
  buffer[7] = checksum >> 8;
  buffer[8] = (uint8_t) checksum;

  this->sent_cmd_ = cmd;

  ESP_LOGV(TAG, "Send Command %#02x arg %#04x", cmd, argument);
  this->write_array(buffer, 10);
}
void exlink::dump_config() {
  ESP_LOGCONFIG(TAG, "exlink:");
  this->check_uart_settings(9600);
}
void exlink::setup() { ESP_LOGD(TAG, "Setup"); }
float exlink::get_setup_priority() const { return setup_priority::DATA; }

}  // namespace exlink
}  // namespace esphome
