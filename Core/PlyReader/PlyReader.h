// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PLYREADER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PLYREADER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef PLYREADER_EXPORTS
#define PLYREADER_API __declspec(dllexport)
#else
#define PLYREADER_API __declspec(dllimport)
#endif

// This class is exported from the PlyReader.dll
class PLYREADER_API CPlyReader {
public:
	CPlyReader(void);
	// TODO: add your methods here.
};

extern PLYREADER_API int nPlyReader;

PLYREADER_API int fnPlyReader(void);
