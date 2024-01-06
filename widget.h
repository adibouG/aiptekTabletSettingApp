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



public slots:



protected:


private slots:
    void refreshSelectedDevice();

    void onSelectedDeviceChanged(int idx);

private:
    Ui::Widget *ui;

    TabletDriverSetting*  _kernelInfo;
   // TabletEventHandler*   _eventPump;
    //XConfSetting*         _xserverInfo;

    SizeUnitType _kernelSizeUnitsType;
    SizeUnitType _xserverSizeUnitsType;


};
#endif // WIDGET_H
