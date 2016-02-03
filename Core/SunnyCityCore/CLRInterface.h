#pragma once
#using <mscorlib.dll>

using namespace System;


public ref class OutputParams
{
private:
public:
	OutputParams()
	{

	}

	//---------------------Final OUTPUT VALUES------------------------

	double jd; //Julian Day
	double l; // printf("L:             %.6e degrees\n", spa.l);
	double b; // printf("B:             %.6e degrees\n", spa.b);
	double r; // printf("R:             %.6f AU\n", spa.r);
	double h; // printf("H:             %.6f degrees\n", spa.h);
	double del_psi;// printf("Delta Psi:     %.6e degrees\n", spa.del_psi);
	double del_epsilon; // printf("Delta Epsilon: %.6e degrees\n", spa.del_epsilon);
	double epsilon; // printf("Epsilon:       %.6f degrees\n", spa.epsilon);
	double zenith; // printf("Zenith:        %.6f degrees\n", spa.zenith);
	double azimuth; // printf("Azimuth:       %.6f degrees\n", spa.azimuth);
	double incidence; // printf("Incidence:     %.6f degrees\n", spa.incidence);
	double sunrise;
	double sunset;
	/*
	min = 60.0*(spa.sunrise - (int)(spa.sunrise));
	sec = 60.0*(min - (int)min);
	printf("Sunrise:       %02d:%02d:%02d Local Time\n", (int)(spa.sunrise), (int)min, (int)sec);

	min = 60.0*(spa.sunset - (int)(spa.sunset));
	sec = 60.0*(min - (int)min);
	printf("Sunset:        %02d:%02d:%02d Local Time\n", (int)(spa.sunset), (int)min, (int)sec);*/

};

public ref class InputParams
{
private:
public:
	InputParams()
	{

	}

	int year;            // 4-digit year,      valid range: -2000 to 6000, error code: 1
	int month;           // 2-digit month,         valid range: 1 to  12,  error code: 2
	int day;             // 2-digit day,           valid range: 1 to  31,  error code: 3
	int hour;            // Observer local hour,   valid range: 0 to  24,  error code: 4
	int minute;          // Observer local minute, valid range: 0 to  59,  error code: 5
	double second;       // Observer local second, valid range: 0 to <60,  error code: 6

	double delta_ut1;    // Fractional second difference between UTC and UT which is used
	// to adjust UTC for earth's irregular rotation rate and is derived
	// from observation only and is reported in this bulletin:
	// http://maia.usno.navy.mil/ser7/ser7.dat,
	// where delta_ut1 = DUT1
	// valid range: -1 to 1 second (exclusive), error code 17

	double delta_t;      // Difference between earth rotation time and terrestrial time
	// It is derived from observation only and is reported in this
	// bulletin: http://maia.usno.navy.mil/ser7/ser7.dat,
	// where delta_t = 32.184 + (TAI-UTC) - DUT1
	// valid range: -8000 to 8000 seconds, error code: 7

	double timezone;     // Observer time zone (negative west of Greenwich)
	// valid range: -18   to   18 hours,   error code: 8

	double longitude;    // Observer longitude (negative west of Greenwich)
	// valid range: -180  to  180 degrees, error code: 9

	double latitude;     // Observer latitude (negative south of equator)
	// valid range: -90   to   90 degrees, error code: 10

	double elevation;    // Observer elevation [meters]
	// valid range: -6500000 or higher meters,    error code: 11

	double pressure;     // Annual average local pressure [millibars]
	// valid range:    0 to 5000 millibars,       error code: 12

	double temperature;  // Annual average local temperature [degrees Celsius]
	// valid range: -273 to 6000 degrees Celsius, error code; 13

	double slope;        // Surface slope (measured from the horizontal plane)
	// valid range: -360 to 360 degrees, error code: 14

	double azm_rotation; // Surface azimuth rotation (measured from south to projection of
	//     surface normal on horizontal plane, negative east)
	// valid range: -360 to 360 degrees, error code: 15

	double atmos_refract;// Atmospheric refraction at sunrise and sunset (0.5667 deg is typical)
	// valid range: -5   to   5 degrees, error code: 16

	int function;        // Switch to choose functions for desired output (from enumeration)

	static OutputParams^ spa_calculate(InputParams^ spa);
};
