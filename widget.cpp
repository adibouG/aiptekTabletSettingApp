#include "widget.h"
#include "ui_widget.h"
#include "tabletdriversetting.h"

#include <QFile>
#include <QDir>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , _kernelInfo(new TabletDriverSetting)
{
    ui->setupUi(this);
    ui->deviceSelectorRefresh_button->setEnabled(false);
    connect(ui->deviceSelectorRefresh_button, &QAbstractButton::clicked,
            this, &Widget::refreshSelectedDevice);
    connect(ui->deviceSelector_comboBox, &QComboBox::currentIndexChanged,
            this, &Widget::onSelectedDeviceChanged);
    ui->deviceSelector_comboBox->addItems(_kernelInfo->usbDevicePaths());

    // if (ui->deviceSelector_comboBox->currentIndex() > -1)
    // {
    //     ui->deviceSelectorRefresh_button->setEnabled(true);
    // }
}

Widget::~Widget()
{
    delete _kernelInfo;
    delete ui;
}


void Widget::onSelectedDeviceChanged(int idx)
{
    if (idx > -1 && _kernelInfo->usbDevicePaths().length() > idx)
    {
        ui->deviceSelectorRefresh_button->setEnabled(true);
    }

}

void Widget::refreshSelectedDevice()
{

    if (ui->deviceSelector_comboBox->currentIndex() > -1)
    {
        int idx = ui->deviceSelector_comboBox->currentIndex();
        qDebug() << QString("6000x4500");

        if (_kernelInfo->usbDevicePaths().length() > idx)
        {
            QString selectedDevice = _kernelInfo->usbDevicePaths().at(idx);
            _kernelInfo->setSelectedPathIdx(idx);
            _kernelInfo->driverSettings();

            auto valueMap = _kernelInfo->paramValues();
            for (const auto s : valueMap.keys())
            {
                qDebug() <<valueMap.value(s);
            }
            ui->productValue->setText(valueMap.value(TabletDriverSetting::AttributeType::VendorIDAttribute));
            ui->sizeValue->setText(valueMap.value(TabletDriverSetting::AttributeType::XMaxYMaxCoordinateAttribute));
        }

    }
}
