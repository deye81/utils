// Include Python API
#include <Python.h>
// Include utils implementation
#include "Utils.h"
using namespace deye81::utils;
// Exception
#include <exception>
using namespace std;

//
// Utils error object
//
static PyObject* UtilsError;

//
// deye81::utils::numDigits() 
//
static PyObject*
utils_numDigits(PyObject* self, PyObject* args)
{
    PyObject* res = NULL;

    try {

        const char* numStr;
        
        if(PyArg_ParseTuple(args, "s", &numStr)) {

            if(numStr[0] == '-') {
                // Use the largest signed integral type allowed by
                // C++
                res = Py_BuildValue("L", numDigits<long long>(asNumber<long long>(numStr)));
            } else {
                // Use the largest unsigned integral type allowed by
                // C++
                res = Py_BuildValue("K", numDigits<unsigned long long>(asNumber<unsigned long long>(numStr)));
            }
        }
    } catch (std::exception& ex) {
        PyErr_SetString(UtilsError, ex.what()); 
        res = NULL;
    }

    return res;

}

//
// Utils method table 
// These are the methods of the Utils module that are 
// callable from python
//
static PyMethodDef UtilsMethods[] = {

    {"numDigits",  utils_numDigits, METH_VARARGS, 
     "Get Number of Digits in a Number"},

    {NULL, NULL, 0, NULL}        // Sentinel 
};

//
// Utils Module initialization function 
// Called when utils is imported by python
//
PyMODINIT_FUNC
initutils(void)
{
    PyObject *m;
    m = Py_InitModule("utils", UtilsMethods);
    if (m == NULL)
        return;

    // Create a new exception class named utils.error
    // that derives from 
    UtilsError = PyErr_NewException("utils.error", NULL, NULL);
    Py_INCREF(UtilsError);
    PyModule_AddObject(m, "error", UtilsError);
}
