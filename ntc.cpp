#include "ntc.h"
#include <cmath>
#include <iostream>

namespace ntc {

	void printHeader()
	{
		std::cout << "\n";
		std::cout << "                    NTC Check Program                   " << std::endl;
		std::cout << "========================================================\n" << std::endl;
	}

    double fahrenheitToCelsius(double temperature_fahrenheit)
    {
        return (temperature_fahrenheit -32) * 5/9;
    }

    double celsiusToFahrenheit(double temperature_celsius)
    {
        return (temperature_celsius * 1.8) + 32;
    }

    double kelvinToCelsius(double temperature_kelvin)
    {
        return temperature_kelvin - 273.15;
    }

    double celsiusToKelvin(double temperature_celsius)
    {
        return temperature_celsius + 273.15;
    }

    int calculateBeta(double r1, double r2, double t1, double t2)
    {
        return round(log((r1/r2))/(1/celsiusToKelvin(t1)-1/celsiusToKelvin(t2)));
    }

    void printThermistorSpecs(ntc::NTC_Thermistor *sensor)
    {
        std::cout << "Temp_value: " << sensor->getTempValue() << std::endl;
        std::cout << "Resistance_value: " << sensor->getResValue() << std::endl;
        std::cout << "Beta_value: " << sensor->getBetaValue() << std::endl;
    }

	ntc::NTC_Thermistor createNewSensor(int selection)
	{
		if (selection == 1)
		{
			ntc::NTC_Thermistor newSensor;
			return newSensor;
		}
		else
		{
			int temp;
			int res;
			int beta;
			ntc::printHeader();
			std::cout << "Enter temp value in celsius:" << std::endl;
			std::cin >> temp;
			std::cout << "\n";
			std::cout << "Enter resistance value at temp value in ohms:" << std::endl;
			std::cin >> res;
			std::cout << "\n";
			std::cout << "Enter beta value in kelvin:" << std::endl;
			std::cin >> beta;
			std::cout << "\n";
			ntc::NTC_Thermistor newSensor(temp, res, beta);
			return newSensor;
		}
	}
}
