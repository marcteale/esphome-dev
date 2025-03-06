#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/exlink/exlink.h"

// TODO: Figure out how to add sensors.

namespace esphome {
namespace exlink {
class exlink : public uart::UARTDevice, public Component {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  void volume_up();

 protected:
  void send_cmd_(uint8_t cmd, uint16_t argument = 0);
  void send_cmd_(uint8_t cmd, uint16_t high, uint16_t low) {
    this->send_cmd_(cmd, ((high & 0xFF) << 8) | (low & 0xFF));
  }
  uint8_t sent_cmd_{0};
};

}  // namespace exlink
}  // namespace esphome
