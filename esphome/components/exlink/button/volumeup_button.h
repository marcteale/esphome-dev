#pragma once

#include "esphome/components/button/button.h"
#include "../exlink.h"

namespace esphome {
namespace exlink {

class VolumeUpButton : public button::Button, public Parented<exlink> {
 public:
  VolumeUpButton() = default;

 protected:
  void press_action() override;
};

}  // namespace exlink
}  // namespace esphome
