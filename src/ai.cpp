#include <Python.h>
#include "ai.hpp"
#include <QDebug>
#include <unistd.h>



AI::AI() {
    // Initialize Python
    Py_Initialize();
    
    PyObject* sys_path = PySys_GetObject("path");
    PyObject* path = PyUnicode_FromString("/home/linuxos/spd-yevgeni/AI");
    PyList_Append(sys_path, path);
    Py_DECREF(path);
}

AI::~AI() {
    // Finalize Python
    Py_Finalize();
}

int AI::connect_to_tree(const double& a_saturation, const double& a_temp, const double& a_pulse)
{
    qDebug() << "####### IN CONNECT TO TREE ##########";
    chdir("/home/linuxos/spd-yevgeni/AI");

    PyObject* pName = PyUnicode_FromString("tree");
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
            Py_DECREF(pFunc);
        } else {
            PyErr_Print();
        }
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
    }

    return result;
}

void AI::buffer_event(const Event& event)
{
    qDebug() << "####### IN BUFFER_EVENT ##########";
    
    // Print out the received event details
    qDebug() << "Event Type:" << event.getEventType();
    qDebug() << "Event Data:" << event.getEventData();
    qDebug() << "Event Location (Room):" << event.getEventLocation();

    int room = event.getEventLocation().toInt();
    m_package[room][event.getEventType()] = event.getEventData();

    qDebug() << "Buffered events for room" << room << ":" << m_package[room];

    // Check if the package is complete
    if (m_package[room].contains("PULSE") &&
        m_package[room].contains("TEMP") &&
        m_package[room].contains("SAT")) {

        qDebug() << "All required event types are present for room:" << room;

        // Fetch the data
        double pulse = m_package[room]["PULSE"].toDouble();
        double temp = m_package[room]["TEMP"].toDouble();
        QString satString = m_package[room]["SAT"];
        double sat = satString.split(' ').last().toDouble();

        qDebug() << "PULSE Value:" << pulse;
        qDebug() << "TEMP Value:" << temp;
        qDebug() << "SAT Value:" << sat;

        // Clear the buffered events for the room
        m_package.remove(room);

        // Get the prediction
        int prediction = connect_to_tree(sat, temp, pulse);
        qDebug() << "AI Prediction:" << prediction;

        // Generate the AI_EVENT (assuming you have a suitable method for this)
        emit predictionReady(prediction, room);
    } else {
        qDebug() << "Not all event types are present for room:" << room;
    }
}
