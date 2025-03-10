import esphome.codegen as cg
from esphome.components import button
import esphome.config_validation as cv
from esphome.const import CONF_BUTTON

from .. import CONF_EXLINK_ID, ExlinkComponent, exlink_ns

VolumeUpButton = exlink_ns.class_("VolumeUpButton", button.Button)

CONFIG_SCHEMA = {
    cv.GenerateID(CONF_EXLINK_ID): cv.use_id(ExlinkComponent),
    cv.Optional(CONF_BUTTON): button.button_schema(
        VolumeUpButton,
        icon="mdi:volume-plus",
    ),
}


async def to_code(config):
    exlink_component = await cg.get_variable(config[CONF_EXLINK_ID])
    if volumeup_config := config.get(CONF_BUTTON):
        b = await button.new_button(volumeup_config)
        await cg.register_parented(b, config[CONF_EXLINK_ID])
        cg.add(exlink_component.set_volumeup_button(b))
