#ifndef TABLETDRIVERSETTING_H
#define TABLETDRIVERSETTING_H
#include <QPair>
#include <QList>
#include <QMap>


#include  <stddef.h>
#include  <ostream>
#include  <iostream>

#define DEFAULT_DRIVER_ROOT_PATH "/sys/bus/usb/drivers/aiptek"



class TabletDriverSetting
{
public:
    TabletDriverSetting ();
    //TabletDriverSetting(const TabletDriverSetting&);
    ~TabletDriverSetting(){}

    enum class PointerInputType {
        All=0,
        OnlyStylus=1,
        OnlyMouse=2
    } ;

    enum class CoordinatesType {
        AbsoluteCoordinates=0,
        RelativeCoordinates=1
    } ;

    enum class AttributeType { // All the parameters
        //Read Only parameters
        XMaxYMaxCoordinateAttribute,
        USBDevicePathAttribute,
        InputDevicePathAttribute,
        MappedInputDriverAttribute,   // Mapped is a diag
        XMaxCoordinateAttribute,
        YMaxCoordinateAttribute,
        VendorIDAttribute,
        ProductIDAttribute,
        ODMCodeAttribute,
        ModelCodeAttribute,
        FirmwareCodeAttribute,
        ProductNameAttribute,
        ManufacturerNameAttribute,
        // Read-only diagnostics
        EventsReceivedAttribute,
        DiagnosticMessageAttribute,
        // Read/Writeable parameters
        PointerCodeAttribute,
        CoordinateCodeAttribute,
        ToolCodeAttribute,
        XTiltAttribute,
        YTiltAttribute,
        JitterDelayAttribute,
        ProgrammableDelayAttribute,
        StylusLowerButtonAttribute,
        StylusUpperButtonAttribute,
        MouseLeftButtonAttribute,
        MouseMiddleButtonAttribute,
        MouseRightButtonAttribute,
        // Write-only parameter
        WheelAttribute,
        ExecuteAttribute
    } ;

    // Link Attribute - Access File Descriptor
    typedef QPair<AttributeType,  std::string> AttributeFile;
    typedef QPair<AttributeType, QString> AttributeValue;



    void makeAttributeFileList();

    bool driverSettings(); //read the device kernel values
    bool setDriverSettings(); // set the device  kernel value

    int selectedPathIdx() const { return _selectedPathIdx; }
    void setSelectedPathIdx(const int i) { _selectedPathIdx = i; }

    AttributeValue readKernelAttributeFile(const AttributeFile &a);
    bool programKernelAttributeFile(const AttributeFile &a);

    void toStream(std::ostream&) const;
    void toStream(std::ostream&, const AttributeType&) const;

    void fromStream(std::istream&);
    void fromStream(std::istream&, const AttributeType&);
    void fromString(const std::string&, const AttributeType&);

    const QList<QString> usbDevicePaths() const  { return _usbDevicePaths; }
    void getUsbDevicePaths();

    const QMap<AttributeType, QString> paramValues() { return _paramValues; }

private:

    void toStream(std::ostream&, const QMap<AttributeType, std::string>&) const;
    void fromStream(std::istream&, const QMap<AttributeType, std::string>&);


    struct TiltType
    {
        TiltType() {}
        ~TiltType() {}

        int getAmount() const {return amount_;}
        void setAmount(const int amount) {amount_=amount;}

    private:
        bool    enabled_;
        int     amount_;
    };

    int                _selectedPathIdx = -1;
    QList<QString>   _usbDevicePaths;
    QMap<AttributeType, std::string> readableParams;
    QMap<AttributeType, std::string> writableParams;
    QMap<AttributeType, std::string> writableWheelOnlyParams;
    QMap<AttributeType, QString>   _paramValues;


};

#endif // TABLETDRIVERSETTING_H
