#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

#define DEFAULT_DRIVER_ROOT_PATH "/sys/bus/usb/drivers/aiptek"

class KernelInfo {
public:
    typedef enum {
        All=0,
        OnlyStylus=1,
        OnlyMouse=2
    } PointerInputType;

    typedef enum {
        AbsoluteCoordinates=0,
        RelativeCoordinates=1
    } CoordinatesType;

    typedef enum { // All the parameters
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
    } AttributeType;

    // Link Attribute - Access File Descriptor
    typedef std::pair<AttributeType, std::string> AttributeFile;

    KernelInfo();
    KernelInfo(const KernelInfo&);
    virtual ~KernelInfo();


    bool readKernel();
    bool programKernel();


    bool readKernelAttributeFile(const AttributeFile &a);
    bool programKernelAttributeFile(const AttributeFile &a);


    void toStream(std::ostream&) const;
    void toStream(std::ostream&, const AttributeType&) const;

    void fromStream(std::istream&);
    void fromStream(std::istream&, const AttributeType&);
    void fromString(const std::string&, const AttributeType&);

    const std::vector<std::string>& getUSBDevicePaths() const
    {return usbDevicePaths;}

private:

    void toStream(std::ostream&, const std::map<AttributeType, std::string>&) const;
    void fromStream(std::istream&, const std::map<AttributeType, std::string>&);


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
};

//class KernelInfo;
class EventPump;
class XServerInfo;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    typedef enum {
        KernelType,
        XServerType
    } AttributeType;

    typedef enum {
        CoordinateTabletSize = 0,
        InchTabletSize = 1,
        MillimeterTabletSize = 2
    } SizeUnitType;

    typedef struct {
        AttributeType   _type;
        SizeUnitType    _units;
        QPair<int, int> _size;
    } TabletSize;

    void setKernelSizeUnitTypes (const SizeUnitType &t) { _kernelSizeUnitsType = t; }
    const SizeUnitType& kernelSizeUnitType() const { return _kernelSizeUnitsType; }

    void setXServerSizeUnitsType(const SizeUnitType &t) { _xserverSizeUnitsType = t; }
    const SizeUnitType& xserverSizeUnitsType() const { return _xserverSizeUnitsType; }

public slots:
    // TODO :
//    virtual void diagnosticsButton_toggled(); //For debug
//    virtual void diagnosticsStartButton_clicked();
//    virtual void diagnosticsStopPushButton_clicked();

    virtual void pressureTable_valueChanged(int,int);
    virtual void relativeCoordModeRadioButton_toggled(bool);
    virtual void absoluteModeRadioButton_toggled(bool);

    virtual void absoluteCoordinatesRadioButton_toggled(bool);
    virtual void relativeCoordinatesRadioButton_toggled(bool);


    virtual void mouseOnlyRadioButton_toggled(bool);
    virtual void stylusOnlyRadioButton_toggled(bool);
    virtual void eitherPointerRadioButton_toggled(bool);

    virtual void xServerOffAlwaysCoreRadioButton_toggled(bool);
    virtual void xServerOnAlwaysCoreRadioButton_toggled(bool);

    virtual void xServerOnInvXRadioButton_toggled(bool);
    virtual void xServerOffInvXRadioButton_toggled(bool);

    virtual void xServerOffInvYRadioButton_toggled(bool);
    virtual void xServerOnInvYRadioButton_toggled(bool);

    virtual void xServerOffKeepShapeRadioButton_toggled(bool);
    virtual void xServerOnKeepShapeRadioButton_toggled(bool);

    virtual void xServerPuckCursorRadioButton_toggled(bool);
    virtual void xServerStylusCursorRadioButton_toggled(bool);

    virtual void xOffsetRadioButton_toggled(bool);
    virtual void xTopRadioButton_toggled(bool);
    virtual void xMaxRadioButton_toggled(bool);

    virtual void refreshPushButton1_clicked();
    virtual void refreshPushButton2_clicked();

    virtual void executePushButton1_clicked();
    virtual void executePushButton2_clicked();

    virtual void yAxisSlider_sliderMoved(int);
    virtual void xAxisSlider_sliderMoved(int);

    virtual void applyWheelPushButton_clicked();

    virtual void yAxisEnabledCheckBox_toggled(bool);
    virtual void xAxisEnabledCheckBox_toggled(bool);

    virtual void wheelSlider_sliderMoved(int);

//    virtual void lensPushButton_clicked();
//    virtual void mousePushButton_clicked();
//    virtual void eraserPushButton_clicked();
//    virtual void airbrushPushButton_clicked();
//    virtual void brushPushButton_clicked();
//    virtual void pencilPushButton_clicked();
//    virtual void penPushButton_clicked();

    virtual void zMaxLineEdit_lostFocus();
    virtual void zMinLineEdit_lostFocus();

    virtual void zThresholdLineEdit_lostFocus();
    virtual void yThresholdLineEdit_lostFocus();
    virtual void xThresholdLineEdit_lostFocus();
DEFAULT_26x_DRIVER_ROOT_PATH(   "/sys/bus/usb/drivers/aiptek")
    virtual void ySizeLineEdit_lostFocus();
    virtual void yOffsetLineEdit_lostFocus();
    virtual void xSizeLineEdit_lostFocus();
    virtual void xOffsetLineEdit_lostFocus();
    virtual void yBottomLineEdit_lostFocus();
    virtual void yTopLineEdit_lostFocus();
//    virtual void xBottomLineEdit_lostFocus();
//    virtual void xTopLineEdit_lostFocus();
//    virtual void xserverScreenNoLineEdit_lostFocus();
    virtual void xserverHistorySizeLineEdit_lostFocus();
    virtual void xserverDebugLevelLineEdit_lostFocus();
    virtual void yMaxLineEdit_lostFocus();
    virtual void xMaxLineEdit_lostFocus();
    virtual void jitterLineEdit_lostFocus();

    // virtual void curveTypeComboBox_activated(const QString&);
    // virtual void xserverMeasurementsComboBox1_activated(const QString&);
    // virtual void xServerDriverComboBox1_activated(const QString&);
    // virtual void xserverMeasurementsComboBox2_activated(const QString&);
    // virtual void xServerDriverComboBox2_activated(const QString&);
    // virtual void rightButtonComboBox_activated(const QString&);
    // virtual void middleButtonComboBox_activated(const QString&);
    // virtual void leftButtonComboBox_activated(const QString&);
    // virtual void lowerButtonComboBox_activated(const QString&);
    // virtual void upperButtonComboBox_activated(const QString&);

    virtual void delaySetting(const QString&);
    virtual void programTablet();
    virtual void refreshTablet();
    virtual void invokeTools();
    virtual void openTablet();

protected:
    void refreshXServerInfo();
    void refreshKernelInfo();
    void dispatchKernelDisplayFieldCallbacks();
    void dispatchKernelDisplayField(const KernelInfo::Attribute&);

    void programDisplayFieldCallbacks();
    void programComboVectors();
    void dispatchAllDisplayFieldCallbacks();
    void dispatchSharedDisplayFieldCallbacks();
    void dispatchXServerDisplayFieldCallbacks();
    void dispatchSharedDisplayField(const AttributeType&);
    void dispatchXServerDisplayField(const XServerInfo::Attribute&);

    void dispatchXServerActiveAreaDisplayFields();
    void dispatchXServerSetXTopXBottomFieldsActive(bool);
    void dispatchXServerSetXOffsetXSizeFieldsActive(bool);
    void dispatchXServerSetXMaxYMaxFieldsActive(bool);

    virtual void absoluteCoordinatesRadioButton_toggled(bool);
    virtual void relativeCoordinatesRadioButton_toggled(bool);

    void   setManufacturerNameLabel(const std::string&);
    void   setProductNameLabel(const std::string&);
    void   setInputPathLabel(const std::string&);
    void   setVendorIDLabel(const std::string&);
    void   setProductIDLabel(const std::string&);
    void   setModelCodeLabel(const std::string&);

    void   setKernelSizeLabel(const std::string&);
    std::string getKernelSizeLabel();

private:
    Ui::Widget *ui;

    KernelInfo*  _kernelInfo;
    EventPump*   _eventPump;
    XServerInfo* _xserverInfo;

    SizeUnitType _kernelSizeUnitsType;
    SizeUnitType _xserverSizeUnitsType;


};
#endif // WIDGET_H
