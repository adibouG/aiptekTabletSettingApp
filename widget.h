#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE



class TabletDriverSetting;
class TabletEventHandler;
class XConfSetting;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    enum class AttributeType {
        KernelType,
        XServerType
    } ;

    enum class SizeUnitType {
        CoordinateTabletSize = 0,
        InchTabletSize = 1,
        MillimeterTabletSize = 2
    } ;

    struct TabletSize {
        AttributeType   _type;
        SizeUnitType    _units;
        QPair<int, int> _size;
    } ;

    void setKernelSizeUnitTypes (const SizeUnitType &t) { _kernelSizeUnitsType = t; }
    const SizeUnitType& kernelSizeUnitType() const { return _kernelSizeUnitsType; }

    void setXServerSizeUnitsType(const SizeUnitType &t) { _xserverSizeUnitsType = t; }
    const SizeUnitType& xserverSizeUnitsType() const { return _xserverSizeUnitsType; }

public slots:
    //TODO: add UI tab for XConf change
    //TODO: in-app logs and debug
    //TODO: refresh button
    //TODO: Add Tablet Active area definitions
    //TODO: Add Stylus pressure settings
      // + TOTRY:  tweaks using tilts and movements values for a reallistic stroke pressure effect
    //TODO: Add Xconf file update ?

    virtual void onRelativeCoordModeRadioButton_toggled(bool);
    virtual void onAbsoluteModeRadioButton_toggled(bool);

    virtual void onAbsoluteCoordinatesRadioButton_toggled(bool);
    virtual void onRelativeCoordinatesRadioButton_toggled(bool);

    virtual void onMouseOnlyRadioButton_toggled(bool);
    virtual void onStylusOnlyRadioButton_toggled(bool);
    virtual void onEitherPointerRadioButton_toggled(bool);

    virtual void onjitterLineEdit_lostFocus();
    virtual void onYAxisSlider_sliderMoved(int);
    virtual void onXAxisSlider_sliderMoved(int);

    virtual void delaySetting(const QString&);
    virtual void programTablet();
    virtual void openTablet();
    virtual void refreshTablet();


protected:
    void refreshXServerInfo();
    void refreshKernelInfo();
    void dispatchKernelDisplayFieldCallbacks();
    void dispatchKernelDisplayField(const AttributeType&);

    void programDisplayFieldCallbacks();
    void programComboVectors();
    void dispatchAllDisplayFieldCallbacks();
    void dispatchSharedDisplayFieldCallbacks();
    void dispatchXServerDisplayFieldCallbacks();
    void dispatchSharedDisplayField(const AttributeType&);
   // void dispatchXServerDisplayField(const XServerInfo::Attribute&);

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

    TabletDriverSetting*  _kernelInfo;
    TabletEventHandler*   _eventPump;
    XConfSetting*         _xserverInfo;

    SizeUnitType _kernelSizeUnitsType;
    SizeUnitType _xserverSizeUnitsType;


};
#endif // WIDGET_H
