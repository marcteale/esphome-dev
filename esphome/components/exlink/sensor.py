import esphome.codegen as cg  # noqa: I001
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_INPUT,
)

DEPENDENCIES = ["uart"]

exlink_ns = cg.esphome_ns.namespace("exlink")
exlink = exlink_ns.class_("exlink", cg.PollingComponent)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(exlink),
        cv.Optional(CONF_INPUT): sensor.sensor_schema(),
    }
).extend(cv.polling_component_schema("60s"))
