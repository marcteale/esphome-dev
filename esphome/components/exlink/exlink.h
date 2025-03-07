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
  void send_cmd_(uint8_t[4]);
};  // class exlink

#define EXLINK_SIMPLE_ACTION(ACTION_CLASS, ACTION_METHOD) \
  template<typename... Ts> class ACTION_CLASS : public Action<Ts...>, public Parented<exlink> { \
    void play(Ts... x) override { this->parent_->ACTION_METHOD(); } \
  };

EXLINK_SIMPLE_ACTION(VolumeUpAction, volume_up)

}  // namespace exlink
}  // namespace esphome
