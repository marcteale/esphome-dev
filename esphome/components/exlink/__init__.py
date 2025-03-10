from esphome import automation
import esphome.codegen as cg
from esphome.components import uart
import esphome.config_validation as cv
from esphome.const import CONF_ID

# TODO: Add sensors
# TODO: Validate UART configuration, see uart > __init__.py

DEPENDENCIES = ["uart"]

exlink_ns = cg.esphome_ns.namespace("exlink")
ExlinkComponent = exlink_ns.class_("exlink", cg.Component, uart.UARTDevice)

VolumeUpAction = exlink_ns.class_("VolumeUpAction", automation.Action)

CONF_EXLINK_ID = "exlink_id"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(ExlinkComponent),
    }
)

CONFIG_SCHEMA = cv.All(
    CONFIG_SCHEMA.extend(uart.UART_DEVICE_SCHEMA).extend(cv.COMPONENT_SCHEMA)
)

FINAL_VALIDATE_SCHEMA = uart.final_validate_device_schema(
    "exlink",
    require_rx=True,
    require_tx=True,
    baud_rate=9600,
    parity="NONE",
    stop_bits=1,
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
            cv.GenerateID(): cv.use_id(ExlinkComponent),
        }
    ),
)
async def exlink_volume_up_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var
