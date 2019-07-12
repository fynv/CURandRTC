#include <Python.h>
#include "DVRNG.h"

static PyObject* n_dvrng_create(PyObject* self, PyObject* args)
{
	return PyLong_FromVoidPtr(new DVRNG_Multi);
}

static PyMethodDef s_Methods[] = {
	{ "n_dvrng_create", n_dvrng_create, METH_VARARGS, "" },
	0
};

static struct PyModuleDef cModPyDem = { PyModuleDef_HEAD_INIT, "CURandRTC_module", "", -1, s_Methods };

PyMODINIT_FUNC PyInit_PyCURandRTC(void)
{
	return PyModule_Create(&cModPyDem);
}
