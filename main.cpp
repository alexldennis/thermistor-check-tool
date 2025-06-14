#include <iostream>
#include "ntc.h"
#include <limits>
#include <chrono>
#include <thread>
#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <unistd.h>
#endif

void sleep500ms()
{	
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void clearScreen()
{
	#ifdef _WIN32
	system("CLS");

	#elif __APPLE__
	system("CLEAR");
	#endif
}

double getTemp()
{
	clearScreen();
	double temperature;
	while (true)
	{	
		ntc::printHeader();
		std::cout << "Enter temperature in fahrenheit: " << std::endl;
		std::cout << "\n";
		std::cin >> temperature;
		if (std::cin.fail())
		{
			clearScreen();	
			std::cout << "INVALID INPUT" << std::endl;
			sleep500ms();
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			clearScreen();

		}
		else
		{
			clearScreen();
			break;
		}
	}
	return temperature;
}

double getRes()
{
	clearScreen();	
	double resistance;
	while (true)
	{
		ntc::printHeader();
		std::cout << "Enter resistance in ohms: " << std::endl;
		std::cout << "\n";
		std::cin >> resistance;
		if (std::cin.fail())
		{
			clearScreen();	
			std::cout << "INVALID INPUT" << std::endl;
			sleep500ms();
			std::cin.clear();\
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			clearScreen();	
		}
		else 
		{
			clearScreen();
			break;
		}
	}
	return resistance;
}

int startLoop()
{
	clearScreen();	
	int option;
	while (true)
	{
		ntc::printHeader();
		std::cout << "Choose a thermistor profile" << std::endl;
		std::cout << "\n";
		std::cout << "1. Default thermistor specs" << std::endl;
		std::cout << "(t0 = 25C, r0 = 1000Ω, beta = 3892K)\n" << std::endl; 
		std::cout << "2. Custom thermistor specs" << std::endl;
		std::cout << "\n";
		std::cin >> option;
		if (std::cin.fail() || option <1 || option > 2)
		{
			clearScreen();	
			std::cout << "INVALID INPUT" << std::endl;
			sleep500ms();
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			clearScreen();	
		}
		else 
		{
			std::cout << "...Building Sensor..." << std::endl;
			sleep500ms();
			clearScreen();	
			break;
		}
	}
	return option;
}

void operationLoop(ntc::NTC_Thermistor sensor)
{
	clearScreen();
	ntc::NTC_Thermistor *p_sensor = &sensor;
	while (true)
	{
		int option;
		ntc::printHeader();
		std::cout << "Select Operation " << std::endl;
		std::cout << "\n";	
		std::cout << "1. Convert temperature to resistance" << std::endl;
		std::cout << "2. Convert resistance to temperature" << std::endl;
		std::cout << "3. Exit program" << std::endl;
		std::cout << "\n";
		std::cin >> option;
		if (option == 1)
		{
			std::cout << "\n";
			double temp = getTemp();
			int resistance = p_sensor->toResistance(ntc::fahrenheitToCelsius(temp));
			std::cout << temp << "F = " << resistance << " ohms" << std::endl;
			sleep500ms();
		}
		else if (option == 2)
		{
			std::cout << "\n";
			double resistance = getRes();
			double tempC = p_sensor->toTemperature(resistance);
			int tempF = std::round(ntc::celsiusToFahrenheit(tempC));
			std::cout << resistance << " = " << tempF << "F" << std::endl; 
			sleep500ms();
		}
		else if (option == 3)
		{
			clearScreen();	
			break;
		}
		else
		{
			clearScreen();	
			std::cout << "INVALID INPUT" << std::endl;
			sleep500ms();
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			clearScreen();	
		}
	}
}

int main()
{
	operationLoop(ntc::createNewSensor(startLoop()));
	return 0;
}
