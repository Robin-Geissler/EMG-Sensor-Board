# Multichannel EMG
This is a multichannel Eelectro Myogram (EMG) sensor. The project provides hardware and driver software to conclude multichannel EMG measurements.

The system provides measurement functions for up to 16 differential EMG channels. It can be used to measurem 4x4 high density EMG grids, or 16 individual channels. The system can be operated mobile, receiving energy from a LiPo 1P1S battery and publishing the measurement data on an SD card.

A description of the system hardware can be found under: [Hardware](./../../wikis/Hardware)
A description of the system software can be found under: [Software](./../../wikis/Firmware)


![Multichannel EMG PCB](Figures/PCB.svg "Multichannel EMG PCB")


## Hardware
Anti aliasing first order lowpass filters are implemented for all channels. The measurement system uses two ADS1299 Analog Frontends (AFEs) for signal aquisistion. An STM32WB MCU is used for digital data processing. Data for live data visualization is published permanently over a USB 2.0 interface. Additionally measurement data can be stored on an on board SD card.

![Architecture](Figures/Architecture.svg "Architecture")

The system hardware can be configured over the pin header bridges B 1 to B 8.

## Data Processing
Show your appreciation to those who have contributed to the project. 

## Getting started with simple multichannel
To conclude basic multichannel EMG measurents follow these steps:

1. **Configure the system hardware:** For standard operation place the pin header bridges B1, B2, B3, B7.
2. **Connect electordes to the _ELECTORDES_ connector:** The electrodes connector is a 0.5 mm pitch FPC connector on the left side of the PCB. There, it is possible to connect a 4x4 EMG grid. To conduct measurements on individual electorde pairs you can use an adapter like this, to connect audio based EMG electordes. Place the electrode pairs on the muscle to be measured.
3. **Connect the RLD Electrode:** Connect the RLD electrode over the _BIAS OUT_ connector in the bottom left. Place the RLD electrode on a bone aria where no muscle interferes with it.
4. **Insert an SD Card into the SD Card slot:** Due to high write speeds industrial SD Cards must be used. Make sure the SD card does not hold a file with the name LOG.csv.
5. **Power the measurement system:** Power the system either over the micro USB connector (_USB_) with 5 V, or the battery connector (_BAT_) with 3.7 V to 4.2 V. Wait for 5 seconds so the system can boot.
6. **Start a measurement:** Press the button to start a measurement. LED L1 will light up if the measurement was started. Measurement data will be conducted on all available channels and saved on the SD card.
7. **Finish a measurement:** Press the button again to finish a measurement. LED L1 will power down. Disconnecto all power supplies (USB and battery).
8. **Extract the measurement data:** Remove the SD card from the SD card slot and read it on a PC. The measurement data is saved in the file LOG.csv.
9. **Visualize the measurement data:** A visualization script like ... can be used to visualize the measurement data.

## General Hardware Conviguration
It is possible to configure the hardware using pin header bridges. 

- **Current Measurements:** The bridges B 1 and B 2 should always be set in normal operation. They are used to
supply the analog and digital parts of the PCB with power. They offer a possibility to measure the supply current of both parts. 
- **Bias Configuration:** Bridges B3 and B5 can be used to configure the bias outputs of the AFEs as driver signals for the driver electrode for AFE1 and AFE2. Bridges B7 or B8 can then be used to select the driver signal from one of the two AFEs and apply it to the bias drive output. 
- **Bias Test Measurement:** By setting bridges B4 and B6, it is also possible to feed the bias signal outputs of the AFEs back to the AFEs, where they can be measured and valuated via a measurement pin.

## License
For open source projects, say how it is licensed.

## Project status

