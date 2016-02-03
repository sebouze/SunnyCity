#ifdef SUNNYCITYCORE_EXPORTS
#define SUNNYCITYCORE __declspec(dllexport)
#else
#define SUNNYCITYCORE __declspec(dllimport)
#endif