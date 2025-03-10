#include "volumeup_button.h"

namespace esphome {
namespace exlink {

void VolumeUpButton::press_action() { this->parent_->volume_up(); }

}  // namespace exlink
}  // namespace esphome
