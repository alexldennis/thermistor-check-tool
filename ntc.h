#ifndef NTC_H
#define NTC_H

#include <cmath>
#include <cstddef>
#include <ios>
#include <math.h>

namespace ntc
{
    class NTC_Thermistor {
    private:
        double temp_value; // temperature value given by manufacturer data sheet
        double res_value; // resistance value of thermistor at temp_value
        double beta_value; // beta value given by manufacturer data sheet
    public:
        NTC_Thermistor()
        {
            temp_value = 25;
            res_value = 1000;
            beta_value = 3892;
        }

        NTC_Thermistor(double temp, double res, double beta)
        {
            this->temp_value = temp;
            this->res_value = res;
            this->beta_value = beta;
        }

        void setTempValue(int temp)
        {
            this->temp_value = temp;
        }

        void setResValue(int res)
        {
            this->res_value = res;
        }

        void setBetaValue(int beta)
        {
            this->beta_value = beta;
        }

        int getTempValue()
        {
            return this->temp_value;
        }

        int getResValue()
        {
            return this->res_value;
        }

        int getBetaValue()
        {
            return this->beta_value;
        }

        double toTemperature(int res)
        {
            return std::round(1/(1/(this->temp_value+273.15)+1/this->beta_value*(log(res/this->res_value)))-273.15);
        }

        double toResistance(double temp)
        {
            return std::round(this->res_value*exp(this->beta_value*((1/(temp+273.15))-(1/(this->temp_value+273.15)))));
        }

    };
	
	void printHeader();
	ntc::NTC_Thermistor createNewSensor(int selection);
	double fahrenheitToCelsius(double temperature_fahrenheit);
	double celsiusToFahrenheit(double temperature_celsius);
	double kelvinToCelsius(double temperature_kelvin);
	double celsiusToKelvin(double temperature_celsius);
	int calculateBeta(double r1, double r2, double t1, double t2);
	void printThermistorSpecs(NTC_Thermistor *sensor);
}

#endif
