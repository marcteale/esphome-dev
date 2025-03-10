#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/button/button.h"
#include "esphome/components/exlink/exlink.h"

// TODO: Figure out how to add sensors.

namespace esphome {
namespace exlink {

class exlink : public button::Button, public uart::UARTDevice, public Component {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  void volume_up();
  void send_cmd_(uint8_t[4]);
};  // class exlink

}  // namespace exlink
}  // namespace esphome
