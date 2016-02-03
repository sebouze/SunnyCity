// PlyReader.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "PlyReader.h"
#include <iostream>
#include <fstream>
#include <map>
#include <iosfwd>
#include "rply.h"

// This is an example of an exported variable
PLYREADER_API int nPlyReader=0;

/*
idée pour echantilloner:
on découpe la zone en grille(ex 1m*1m). Pour chaque zone on trouve le Z max.
Ensuite on essaie de constuire le profil
On fait une map <int,int>, float.
int,int c'est la partie entière de x,y. Float c'est le z, on stock le max.
On stock la map dans un csv.
Idem pour deuxième fichier.
On doit pouvoir un extraire un profil
*/

static double last_x = 0.0;
static double last_y = 0.0;
static int count;
static std::map<std::pair<int, int>, double > mapXYZ;

static int getX(p_ply_argument argument) {
	long eol;
	ply_get_argument_user_data(argument, NULL, &eol);
	last_x = ply_get_argument_value(argument);
	return 1;
}

static int getY(p_ply_argument argument) {
	long eol;
	ply_get_argument_user_data(argument, NULL, &eol);
	last_y = ply_get_argument_value(argument);
	return 1;
}

static int getZ(p_ply_argument argument) {
	long eol;
	ply_get_argument_user_data(argument, NULL, &eol);
	double z = ply_get_argument_value(argument);
	int xEchantillone = (int)last_x;
	int yEchantillone = (int)last_y;
	std::pair<int, int> xy(xEchantillone, yEchantillone);
	std::map<std::pair<int, int>, double >::iterator iter = mapXYZ.find(xy);
	if (iter != mapXYZ.end())
	{
		if (iter->second > z)
		{
			iter->second = z;
		}
	}
	else
	{
		mapXYZ[xy] = z;
	}
	printf("%d", count++);
	printf("\n");
	//if (count > 100)
	//	return 0;
	return 1;
}

static int vertex_cb(p_ply_argument argument) {
	/*long eol;
	ply_get_argument_user_data(argument, NULL, &eol);
	printf("%g", ply_get_argument_value(argument));
	if (eol) printf("\n");
	else printf(" ");
	*/return 1;
}
static int face_cb(p_ply_argument argument) {
	long length, value_index;
	ply_get_argument_property(argument, NULL, &length, &value_index);
	switch (value_index) {
	case 0:
	case 1:
		printf("%g ", ply_get_argument_value(argument));
		break;
	case 2:
		printf("%g\n", ply_get_argument_value(argument));
		break;
	default:
		break;
	}
	return 1;
}

static int ProcessOneFile(std::string fileName)
{
	count = 0;
	long nvertices, ntriangles;
	//p_ply ply = ply_open("C:\\DEV\\SunnyCity\\Core\\SunnyCityApplication\\bin\\Debug\\input.ply", NULL, 0, NULL);
	p_ply ply = ply_open(fileName.c_str(), NULL, 0, NULL);

	if (!ply) return 1;
	if (!ply_read_header(ply)) return 1;
	nvertices = ply_set_read_cb(ply, "vertex", "x", getX, NULL, 0);
	ply_set_read_cb(ply, "vertex", "y", getY, NULL, 0);
	ply_set_read_cb(ply, "vertex", "z", getZ, NULL, 0);
	ply_set_read_cb(ply, "vertex", "reflectance", vertex_cb, NULL, 0);
	ply_set_read_cb(ply, "vertex", "class", vertex_cb, NULL, 0);
	ply_set_read_cb(ply, "vertex", "id", vertex_cb, NULL, 1);
	ntriangles = ply_set_read_cb(ply, "face", "vertex_indices", face_cb, NULL, 0);
	printf("%ld\n%ld\n", nvertices, ntriangles);
	if (!ply_read(ply)) return 1;
	ply_close(ply);
	return 0;

}
// This is an example of an exported function.
PLYREADER_API int fnPlyReader(void)
{
	std::string fileName= "C:\\DEV\\SunnyCity\\Data\\GT_Madame1_2.ply";
	ProcessOneFile(fileName);
	fileName = "C:\\DEV\\SunnyCity\\Data\\GT_Madame1_3.ply";
	ProcessOneFile(fileName);

	std::ofstream myfile;
	myfile.open("C:\\DEV\\SunnyCity\\Data\\xyz.csv");
	
	std::map<std::pair<int, int>, double >::iterator iter = mapXYZ.begin();
	while (iter != mapXYZ.end())
	{
		myfile << iter->first.first << ",";
		myfile << iter->first.second << ",";
		myfile << iter->second << ",";
		myfile << "\n";
		iter++;
	}

	myfile.close();

	return 0;

}

// This is the constructor of a class that has been exported.
// see PlyReader.h for the class definition
CPlyReader::CPlyReader()
{
	return;
}
