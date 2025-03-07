#include "exlink.h"
#include "esphome/core/log.h"

namespace esphome {
namespace exlink {

static const char *const TAG = "exlink";

void exlink::volume_up() {
  ESP_LOGD(TAG, "Increasing volume");
  uint8_t cmd[4] = {0x01, 0x00, 0x01, 0x00};
  this->send_cmd_(cmd);
}

void exlink::send_cmd_(uint8_t cmd[4]) {
  /*
  Bytes 1-2 : Header, [0x08, 0x22]
  Bytes 3-6 : Command
  Byte    7 : CRC, Two's complement of the sum of bytes 1-6
  */
  ESP_LOGV(TAG, "Command received: %s", format_hex_pretty(cmd, 4).c_str());
  uint8_t send_data[7] = {0x08, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00};
  for (uint8_t i = 0; i < 4; i++)
    send_data[i + 2] = cmd[i];

  uint8_t checksum = 0x00;
  for (uint8_t i = 1; i < 6; i++)
    checksum += cmd[i];
  ESP_LOGV(TAG, "Byte total: 0x%02x", checksum);
  checksum = ~checksum + 1;
  ESP_LOGV(TAG, "Checksum total: 0x%02x", checksum);

  this->write_array(send_data, 7);
  ESP_LOGV(TAG, "Command sent: %s", format_hex_pretty(send_data, 7).c_str());
}
void exlink::dump_config() {
  ESP_LOGCONFIG(TAG, "exlink:");
  this->check_uart_settings(9600);
}
void exlink::setup() { ESP_LOGD(TAG, "Setup"); }
float exlink::get_setup_priority() const { return setup_priority::DATA; }

}  // namespace exlink
}  // namespace esphome
