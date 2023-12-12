#include "tabletdriversetting.h"

TabletDriverSetting::TabletDriverSetting() {}

TabletDriverSetting::TabletDriverSetting(const TabletDriverSetting&) {

}


QPair<AtributeType, QString> TabletDriverSetting::AtributeKeyToStringKey() These are keywords that may be read from the kernel driver's file.
readableParams.insert(
    AttributeFile(XMaxYMaxCoordinateAttribute, std::string("size")));
readableParams.insert(
    AttributeFile(VendorIDAttribute,           std::string("vendor_id")));
readableParams.insert(
    AttributeFile(ProductIDAttribute,          std::string("product_id")));
readableParams.insert(
    AttributeFile(ODMCodeAttribute,            std::string("odm_code")));
readableParams.insert(
    AttributeFile(ModelCodeAttribute,          std::string("model_code")));
readableParams.insert(
    AttributeFile(FirmwareCodeAttribute,       std::string("firmware_code")));
readableParams.insert(
    AttributeFile(InputDevicePathAttribute,    std::string("input_path")));
readableParams.insert(
    AttributeFile(PointerCodeAttribute,        std::string("pointer_mode")));
readableParams.insert(
    AttributeFile(CoordinateCodeAttribute,     std::string("coordinate_mode")));
readableParams.insert(
    AttributeFile(ToolCodeAttribute,           std::string("tool_mode")));
readableParams.insert(
    AttributeFile(XTiltAttribute,              std::string("xtilt")));
readableParams.insert(
    AttributeFile(YTiltAttribute,              std::string("ytilt")));
readableParams.insert(
    AttributeFile(JitterDelayAttribute,        std::string("jitter")));
readableParams.insert(
    AttributeFile(DiagnosticMessageAttribute,  std::string("diagnostic")));
readableParams.insert(
    AttributeFile(EventsReceivedAttribute,     std::string("event_count")));
readableParams.insert(
    AttributeFile(ProductNameAttribute,        std::string("product")));
readableParams.insert(
    AttributeFile(ManufacturerNameAttribute,   std::string("vendor")));
readableParams.insert(
    AttributeFile(ProgrammableDelayAttribute,  std::string("delay")));
readableParams.insert(
    AttributeFile(StylusUpperButtonAttribute,  std::string("stylus_upper")));
readableParams.insert(
    AttributeFile(StylusLowerButtonAttribute,  std::string("stylus_lower")));
readableParams.insert(
    AttributeFile(MouseLeftButtonAttribute,    std::string("mouse_left")));
readableParams.insert(
    AttributeFile(MouseMiddleButtonAttribute,  std::string("mouse_middle")));
readableParams.insert(
    AttributeFile(MouseRightButtonAttribute,   std::string("mouse_right")));

// These are keywords that may be written to the procfs/sysfs files.
writableParams.insert(
    AttributeFile(PointerCodeAttribute,        std::string("pointer_mode")));
writableParams.insert(
    AttributeFile(CoordinateCodeAttribute,     std::string("coordinate_mode")));
writableParams.insert(
    AttributeFile(ToolCodeAttribute,           std::string("tool_mode")));
writableParams.insert(
    AttributeFile(XTiltAttribute,              std::string("xtilt")));
writableParams.insert(
    AttributeFile(YTiltAttribute,              std::string("ytilt")));
writableParams.insert(
    AttributeFile(JitterDelayAttribute,        std::string("jitter")));
writableParams.insert(
    AttributeFile(ProgrammableDelayAttribute,  std::string("delay")));
writableParams.insert(
    AttributeFile(StylusUpperButtonAttribute,  std::string("stylus_upper")));
writableParams.insert(
    AttributeFile(StylusLowerButtonAttribute,  std::string("stylus_lower")));
writableParams.insert(
    AttributeFile(MouseLeftButtonAttribute,    std::string("mouse_left")));
writableParams.insert(
    AttributeFile(MouseMiddleButtonAttribute,  std::string("mouse_middle")));
writableParams.insert(
    AttributeFile(MouseRightButtonAttribute,   std::string("mouse_right")));
writableParams.insert(
    AttributeFile(ExecuteAttribute,            std::string("execute")));

writableWheelOnlyParams.insert(
    AttributeFile(WheelAttribute,              std::string("wheel")));
writableWheelOnlyParams.insert(
    AttributeFile(ExecuteAttribute,            std::string("execute")));
