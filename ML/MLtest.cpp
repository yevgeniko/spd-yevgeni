#include <Python.h>
#include <cstdlib>  // For std::system


int connect_to_tree(const double& a_saturation, const double& a_temp, const double& a_pulse) {
    // Initialize Python
    Py_Initialize();

    PyObject* sys_path = PySys_GetObject("path");
    PyObject* path = PyUnicode_DecodeFSDefault(".");
    PyList_Append(sys_path, path);
    Py_DECREF(path);

    // Execute the Python script with arguments
    PyObject* pName = PyUnicode_DecodeFSDefault("tree");
    PyObject* pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    int result = -1; // Default result in case of errors

    if (pModule != NULL) {
        PyObject* pFunc = PyObject_GetAttrString(pModule, "load_classifier_and_predict");

        if (PyCallable_Check(pFunc)) {
            PyObject* pArgs = PyTuple_Pack(3, PyFloat_FromDouble(a_pulse), PyFloat_FromDouble(a_temp), PyFloat_FromDouble(a_saturation));
            PyObject* pValue = PyObject_CallObject(pFunc, pArgs);

            if (pValue != NULL) {
                // Process the result
                result = PyLong_AsLong(pValue);
                Py_DECREF(pValue);
            } else {
                PyErr_Print();
            }
        } else {
            PyErr_Print();
        }
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
    }

    // Finalize Python
    Py_Finalize();

    return result;
}

int main() {
    double saturation = 82.0;
    double temp = 38.1;
    double pulse = 96.0;

    int result = connect_to_tree(saturation, temp, pulse);
    printf("Result from Python: %d\n", result);

    return 0;
}
