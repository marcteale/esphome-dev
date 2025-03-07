# TODO: Audit the necessity of these later.
from esphome import automation
import esphome.codegen as cg
from esphome.components import uart
import esphome.config_validation as cv
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]

exlink_ns = cg.esphome_ns.namespace("exlink")
exlink = exlink_ns.class_("exlink", cg.Component)

VolumeUpAction = exlink_ns.class_("VolumeUpAction", automation.Action)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(exlink),
        }
    ).extend(uart.UART_DEVICE_SCHEMA)
)
FINAL_VALIDATE_SCHEMA = uart.final_validate_device_schema(
    "exlink", baud_rate=9600, require_tx=True
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)


@automation.register_action(
    "exlink.volume_up",
    VolumeUpAction,
    cv.Schema(
        {
            cv.GenerateID(): cv.use_id(exlink),
        }
    ),
)
async def dfplayer_volume_up_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var
