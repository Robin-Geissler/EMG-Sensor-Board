# Multichannel EMG
This is a multichannel Eelectro Myogram (EMG) sensor. The project provides hardware and driver software to conclude multichannel EMG measurements.

The system provides measurement functions for up to 16 differential EMG channels. It can be used to measurem 4x4 high density EMG grids, or 16 individual channels. The system can be operated mobile, receiving energy from a LiPo 1P1S battery and publishing the measurement data on an SD card.

Further documentation can be found in the Wiki:

- A description of the system hardware can be found under: [Hardware](./../../wikis/Hardware)
- A description of the system software can be found under: [Software](./../../wikis/Firmware)

Projects related to this:
- An audio jack electrode adapter can be fountd under: [Audio Jack Adapter](./../../../emg-sensor-electrode-adapter)
- A live visualisation software can be fountd under: [Live Visualization](./../../../emg-evaluation-plotting)
- A post measurement visualization software can be found under: [Post Measurement Visualization](./../../../emg-sensor-board-evaluation-plot)

![Multichannel EMG PCB](Figures/PCB.svg "Multichannel EMG PCB")


## Hardware
Anti aliasing first order lowpass filters are implemented for all channels. The measurement system uses two ADS1299 Analog Frontends (AFEs) for signal aquisistion. An STM32WB MCU is used for digital data processing. Data for live data visualization is published permanently over a USB 2.0 interface. Additionally measurement data can be stored on an on board SD card.

![Architecture](Figures/Architecture.svg "Architecture")

The system hardware can be configured over the pin header bridges B 1 to B 8.

## Data Processing
Show your appreciation to those who have contributed to the project. 

## Getting started with basic multichannel measurements
To conclude basic multichannel EMG measurents follow these steps:

1. **Configure the system hardware:** For standard operation place the pin header bridges B1, B2, B3, B7.
2. **Connect electordes to the _ELECTORDES_ connector:** The electrodes connector is a 0.5 mm pitch FPC connector on the left side of the PCB. There, it is possible to connect a 4x4 EMG grid. To conduct measurements on individual electorde pairs you can use an adapter like [this](./../../../emg-sensor-electrode-adapter), to connect audio jack based EMG electordes. Place the electrode pairs on the muscle to be measured.
3. **Connect the RLD Electrode:** Connect the RLD electrode over the _BIAS OUT_ connector in the bottom left. Place the RLD electrode on a bone aria where no muscle interferes with it.
4. **Insert an SD Card into the SD Card slot:** Due to high write speeds industrial SD Cards must be used. Make sure the SD card does not hold a file with the name LOG.csv.
5. **Power the measurement system:** Power the system either over the micro USB connector (_USB_) with 5 V, or the battery connector (_BAT_) with 3.7 V to 4.2 V. Wait for 5 seconds so the system can boot.
6. **Start a measurement:** Press the button to start a measurement. LED L1 will light up if the measurement was started. Measurement data will be conducted on all available channels and saved on the SD card.
7. **Finish a measurement:** Press the button again to finish a measurement. LED L1 will power down. Disconnecto all power supplies (USB and battery).
8. **Extract the measurement data:** Remove the SD card from the SD card slot and read it on a PC. The measurement data is saved in the file LOG.csv.
9. **Visualize the measurement data:** A visualization script like [this](./../../../emg-sensor-board-evaluation-plot) can be used to visualize the measurement data.

## Trouble Shooting



## License
For open source projects, say how it is licensed.

## Project status

