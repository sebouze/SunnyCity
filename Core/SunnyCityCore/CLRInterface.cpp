#include "CLRInterface.h"
#include "MainAlgo.h"

OutputParams^ InputParams::spa_calculate(InputParams^ spa)
{
	spa_data natData;
	natData.year = spa->year;            // 4-digit year,      valid range: -2000 to 6000, error code: 1
	natData.month = spa->month;           // 2-digit month,         valid range: 1 to  12,  error code: 2
	natData.day = spa->day;             // 2-digit day,           valid range: 1 to  31,  error code: 3
	natData.hour = spa->hour;            // Observer local hour,   valid range: 0 to  24,  error code: 4
	natData.minute = spa->minute;          // Observer local minute, valid range: 0 to  59,  error code: 5
	natData.second = spa->second;       // Observer local second, valid range: 0 to <60,  error code: 6

	natData.delta_ut1 = spa->delta_ut1;    // Fractional second difference between UTC and UT which is used
	// to adjust UTC for earth's irregular rotation rate and is derived
	// from observation only and is reported in this bulletin:
	// http://maia.usno.navy.mil/ser7/ser7.dat,
	// where delta_ut1 = DUT1
	// valid range: -1 to 1 second (exclusive), error code 17

	natData.delta_t = spa->delta_t;      // Difference between earth rotation time and terrestrial time
	// It is derived from observation only and is reported in this
	// bulletin: http://maia.usno.navy.mil/ser7/ser7.dat,
	// where delta_t = 32.184 + (TAI-UTC) - DUT1
	// valid range: -8000 to 8000 seconds, error code: 7

	natData.timezone = spa->timezone;     // Observer time zone (negative west of Greenwich)
	// valid range: -18   to   18 hours,   error code: 8

	natData.longitude = spa->longitude;    // Observer longitude (negative west of Greenwich)
	// valid range: -180  to  180 degrees, error code: 9

	natData.latitude = spa->latitude;     // Observer latitude (negative south of equator)
	// valid range: -90   to   90 degrees, error code: 10

	natData.elevation = spa->elevation;    // Observer elevation [meters]
	// valid range: -6500000 or higher meters,    error code: 11

	natData.pressure = spa->pressure;     // Annual average local pressure [millibars]
	// valid range:    0 to 5000 millibars,       error code: 12

	natData.temperature  = spa->temperature;  // Annual average local temperature [degrees Celsius]
	// valid range: -273 to 6000 degrees Celsius, error code; 13

	natData.slope = spa->slope;        // Surface slope (measured from the horizontal plane)
	// valid range: -360 to 360 degrees, error code: 14

	natData.azm_rotation = spa->azm_rotation; // Surface azimuth rotation (measured from south to projection of
	//     surface normal on horizontal plane, negative east)
	// valid range: -360 to 360 degrees, error code: 15

	natData.atmos_refract = spa->atmos_refract;// Atmospheric refraction at sunrise and sunset (0.5667 deg is typical)
	// valid range: -5   to   5 degrees, error code: 16

	natData.function = spa->function;        // Switch to choose functions for desired output (from enumeration)

	//---------------------Final OUTPUT VALUES------------------------

	int res = spa_data::spa_calculate(&natData);

	if (res == 0)
	{
		OutputParams^ output = gcnew OutputParams();
		output->jd = natData.jd; //Julian Day
		output->l = natData.l; // printf("L:             %.6e degrees\n", spa.l);
		output->b = natData.b; // printf("B:             %.6e degrees\n", spa.b);
		output->r = natData.r; // printf("R:             %.6f AU\n", spa.r);
		output->h = natData.h; // printf("H:             %.6f degrees\n", spa.h);
		output->del_psi = natData.del_psi;// printf("Delta Psi:     %.6e degrees\n", spa.del_psi);
		output->del_epsilon = natData.del_epsilon; // printf("Delta Epsilon: %.6e degrees\n", spa.del_epsilon);
		output->epsilon = natData.epsilon; // printf("Epsilon:       %.6f degrees\n", spa.epsilon);
		output->zenith = natData.zenith; // printf("Zenith:        %.6f degrees\n", spa.zenith);
		output->azimuth = natData.azimuth; // printf("Azimuth:       %.6f degrees\n", spa.azimuth);
		output->incidence = natData.incidence; // printf("Incidence:     %.6f degrees\n", spa.incidence);
		output->sunrise = natData.sunrise;
		output->sunset = natData.sunset;
		return output;
	}
	return nullptr;
}