#include "exlink.h"
#include "esphome/core/log.h"

namespace esphome {
namespace exlink {

static const char *const TAG = "exlink";

void exlinkComponent::update() { ESP_LOGD(TAG, "Update"); }
void exlinkComponent::setup() { ESP_LOGD(TAG, "Setup"); }
void exlinkComponent::dump_config() { ESP_LOGD(TAG, "Dump config"); }
float exlinkComponent::get_setup_priority() const { return setup_priority::DATA; }
bool exlinkComponent::read_data_(uint8_t *data) {
  ESP_LOGD(TAG, "Read data");
  return true;
}

}  // namespace exlink
}  // namespace esphome
