#include "tabletdriversetting.h"
#include <QFile>
#include <QDir>
#include <QRegularExpression>

TabletDriverSetting::TabletDriverSetting()
{
    makeAttributeFileList();
    getUsbDevicePaths();
}

// TabletDriverSetting::TabletDriverSetting(const TabletDriverSetting&) {

// }
void TabletDriverSetting::getUsbDevicePaths() {
    QDir dir(DEFAULT_DRIVER_ROOT_PATH);
    auto l = dir.entryList(QDir::Dirs);
    QRegularExpression usbSlot ("[0-9]-[0-9](.[0-9])*:[0-9].[0-9]");

    for (const auto &s : l)
    {
        qDebug() << s;
        auto res = usbSlot.match(s);

        if (res.hasMatch())
        {
            qDebug() << "match "<< s;
            _usbDevicePaths << s; //QString("%1/%2)").arg(DEFAULT_DRIVER_ROOT_PATH).arg(s);

        }
    }
    return ;
}

bool TabletDriverSetting::setDriverSettings() {
    return true;
}

bool TabletDriverSetting::driverSettings() {

    for (const auto &att : readableParams.keys()){
        TabletDriverSetting::AttributeFile a;
        a.first = att;
        a.second = readableParams.value(att);

        auto b = readKernelAttributeFile(a);

        _paramValues.insert(b.first, QString(b.second));

    }

    for (const auto &att : writableParams.keys()){
        TabletDriverSetting::AttributeFile a;
        a.first = att;
        a.second = writableParams.value(att);

        auto b = readKernelAttributeFile(a);

        _paramValues.insert(b.first, QString(b.second));

    }

    for (const auto &att : writableWheelOnlyParams.keys()){
        TabletDriverSetting::AttributeFile a;
        a.first = att;
        a.second = writableWheelOnlyParams.value(att);

        auto b = readKernelAttributeFile(a);

        _paramValues.insert(b.first, QString(b.second));

    }
    return true;

}


void TabletDriverSetting::makeAttributeFileList()
{
    //These are keywords that may be read from the kernel driver's file.

    readableParams.insert(
        AttributeType::XMaxYMaxCoordinateAttribute, std::string("size"));
    readableParams.insert(
        AttributeType::VendorIDAttribute,           std::string("vendor_id"));
    readableParams.insert
        (AttributeType::ProductIDAttribute,          std::string("product_id"));
    readableParams.insert
        (AttributeType::ODMCodeAttribute,            std::string("odm_code"));
    readableParams.insert
        (AttributeType::ModelCodeAttribute,          std::string("model_code"));
    readableParams.insert
        (AttributeType::FirmwareCodeAttribute,       std::string("firmware_code"));
    readableParams.insert
        (AttributeType::InputDevicePathAttribute,    std::string("input_path"));
    readableParams.insert
        (AttributeType::PointerCodeAttribute,        std::string("pointer_mode"));
    readableParams.insert
        (AttributeType::CoordinateCodeAttribute,     std::string("coordinate_mode"));
    readableParams.insert
        (AttributeType::ToolCodeAttribute,           std::string("tool_mode"));
    readableParams.insert
        (AttributeType::XTiltAttribute,              std::string("xtilt"));
    readableParams.insert
        (AttributeType::YTiltAttribute,              std::string("ytilt"));
    readableParams.insert
        (AttributeType::JitterDelayAttribute,        std::string("jitter"));
    readableParams.insert
        (AttributeType::DiagnosticMessageAttribute,  std::string("diagnostic"));
    readableParams.insert
        (AttributeType::EventsReceivedAttribute,     std::string("event_count"));
    readableParams.insert
        (AttributeType::ProductNameAttribute,        std::string("product"));
    readableParams.insert
        (AttributeType::ManufacturerNameAttribute,   std::string("vendor"));
    readableParams.insert
        (AttributeType::ProgrammableDelayAttribute,  std::string("delay"));
    readableParams.insert
        (AttributeType::StylusUpperButtonAttribute,  std::string("stylus_upper"));
    readableParams.insert
        (AttributeType::StylusLowerButtonAttribute,  std::string("stylus_lower"));
    readableParams.insert
        (AttributeType::MouseLeftButtonAttribute,    std::string("mouse_left"));
    readableParams.insert
        (AttributeType::MouseMiddleButtonAttribute,  std::string("mouse_middle"));
    readableParams.insert
        (AttributeType::MouseRightButtonAttribute,   std::string("mouse_right"));

    // These are keywords that may be written to the procfs/sysfs files.
    writableParams.insert
        (AttributeType::PointerCodeAttribute,        std::string("pointer_mode"));
    writableParams.insert
        (AttributeType::CoordinateCodeAttribute,     std::string("coordinate_mode"));
    writableParams.insert
        (AttributeType::ToolCodeAttribute,           std::string("tool_mode"));
    writableParams.insert
        (AttributeType::XTiltAttribute,              std::string("xtilt"));
    writableParams.insert
        (AttributeType::YTiltAttribute,              std::string("ytilt"));
    writableParams.insert
        (AttributeType::JitterDelayAttribute,        std::string("jitter"));
    writableParams.insert
        (AttributeType::ProgrammableDelayAttribute,  std::string("delay"));
    writableParams.insert
        (AttributeType::StylusUpperButtonAttribute,  std::string("stylus_upper"));
    writableParams.insert
        (AttributeType::StylusLowerButtonAttribute,  std::string("stylus_lower"));
    writableParams.insert
        (AttributeType::MouseLeftButtonAttribute,    std::string("mouse_left"));
    writableParams.insert
        (AttributeType::MouseMiddleButtonAttribute,  std::string("mouse_middle"));
    writableParams.insert
        (AttributeType::MouseRightButtonAttribute,   std::string("mouse_right"));
    writableParams.insert
        (AttributeType::ExecuteAttribute,            std::string("execute"));

    writableWheelOnlyParams.insert
        (AttributeType::WheelAttribute,              std::string("wheel"));
    writableWheelOnlyParams.insert
        (AttributeType::ExecuteAttribute,            std::string("execute"));

    }



    TabletDriverSetting::AttributeValue TabletDriverSetting::readKernelAttributeFile(const  TabletDriverSetting::AttributeFile &a)
{


    TabletDriverSetting::AttributeValue v;
    if (selectedPathIdx() > -1 &&  usbDevicePaths().length() > selectedPathIdx())
    {

        QString selectedDevice = usbDevicePaths().at(selectedPathIdx());


        QString selectedDevicePath = QString("%1/%2")
                                     .arg(DEFAULT_DRIVER_ROOT_PATH,
                                          selectedDevice);
        QDir dir(selectedDevicePath);

        qDebug() << selectedDevicePath;

        //readableParams
        for (const auto &e : dir.entryInfoList(QDir::AllDirs| QDir::AllEntries | QDir::NoDotAndDotDot ))
        {
            qDebug() << e.absolutePath(); // .absolutePath();
            if (e.isFile() && e.fileName() == QString::fromStdString(a.second))
            {

                QString filePath = e.absoluteFilePath();
                QFile f (filePath);

                if (f.open(QFileDevice::OpenModeFlag::ReadOnly))
                {
                    qDebug() << "open " << filePath;
                    QTextStream st(&f);
                    QString data = st.readAll();
                    qDebug() << data;
                    v.first = a.first;

                    v.second = QString(data);


                    f.close();
                }

                break;
            }
            else if (e.isDir() && e.absolutePath().endsWith("firmware_node"))
            {
                QDir n(e.absolutePath());
                for (const auto &s : n.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot ))
                {
                    qDebug() << s.absoluteFilePath();
                    if (s.isFile() && s.fileName()== QString::fromStdString(a.second))
                    {

                        QString filePath = s.absoluteFilePath();
                        QFile f (filePath);

                        if (f.open(QFileDevice::OpenModeFlag::ReadOnly))
                        {
                            qDebug() << "open " << filePath;
                            QTextStream st(&f);
                            QString data = st.readAll();
                            qDebug() << data;
                            v.first = a.first;

                            v.second = data;


                            f.close();
                        }

                        break;
                    }

                }
            }
        }
    }
    return v;
}


bool TabletDriverSetting::programKernelAttributeFile(const AttributeFile &a)
{


}
