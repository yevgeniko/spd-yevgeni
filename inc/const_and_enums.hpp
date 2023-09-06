#ifndef CONST_AND_ENUMS
#define CONST_AND_ENUMS

#include <cstdlib>
#include <QString>

namespace spd {

const size_t WINDOW_WIDTH = 1100;
const size_t WINDOW_HEIGHT = 700;
const QString WINDOW_TITLE = "S.P.D.";
const QString WIN_BACKGROUND_PATH = "../../assets/ward_blueprint.jpeg";

const size_t NUM_OF_ROOMS = 6;

const int64_t MAX_ABNORMAL_DURATION = 30;

const QString AI_EVENT = "AI_EVENT";

//room layout
const QString PATIENT_STATUS = "Patient Status";
const QString PULSE = "PULSE";
const QString BP = "BP";
const QString SET = "SET";
const QString TEMP = "TEMP";
const QString DETAILS = "Details";

struct EventDetails
{
    size_t m_room_num;
    QString m_data;
    QString m_max;
    QString m_min;
};

} // namespace spd

#endif // CONST_AND_ENUMS