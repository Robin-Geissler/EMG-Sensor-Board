# Multichannel EMG
This is a multichannel Eelectro Myogram (EMG) sensor. The project provides hardware and driver software to conclude multichannel EMG measurements.

![Multichannel EMG PCB](Figures/PCB.svg "Multichannel EMG PCB")

The system provides measurement functions for up to 16 differential EMG channels. It can be used to measurem 4x4 high density EMG grids, or 16 individual channels. The system hardware can be configured over pin header bridges.

## Getting started
To conclude basic multichannel EMG measurents follow these steps:

1. **Configure the system hardware:** For standard operation place the pin header bridges B1, B2, B3, B7.
2. **Connect electordes to the _ELECTORDES_ connector:** The electrodes connector is a 0.5mm pitch FPC connector on the left side of the PCB. There, it is possible to connect a 4x4 EMG grid. To conduct measurements on individual electorde pairs you can use an adapter like this, to connect audio based EMG electordes.
3. **Insert an SD Card into the SD Card slot:** Due to high write speeds industrial SD Cards must be used. Make sure the SD card does not hold a file with the name LOG.csv.
4. **Power the measurement system:** Power the system either over the micro USB connector (_USB_) with 5V, or the battery connector (_BAT_) with 3.7V to 4.2V. Wait for 5 seconds so the system can boot.
5. **Start a measurement:** Press the button to start a measurement. LED 1 will light up if the measurement was started. Measurement data will be conducted on all available channels and saved on the SD Card.
6. **Finish a measurement:** Press the button again to finish a measurement. LED 1 will power down. Disconnecto all power supplies (USB and Battery).
7. **Extract the measurement data:** Remove the SD Card from the SD Card slot and read it on a PC. The measurement data is saved in the file LOG.csv.
8. **Visualize the measurement data:** A visualization script like ... can be used to visualize the measurement data.

## General System Description


## Authors and acknowledgment
Show your appreciation to those who have contributed to the project.

## License
For open source projects, say how it is licensed.

## Project status

