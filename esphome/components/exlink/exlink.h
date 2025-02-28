#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/exlink/exlink.h"

namespace esphome {
namespace exlink {
class exlinkComponent : public PollingComponent {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  void update() override;

 protected:
  bool read_data_(uint8_t *data);
  sensor::Sensor *power_sensor_{nullptr};
};
}  // namespace exlink
}  // namespace esphome
