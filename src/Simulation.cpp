#include "Simulation.h"

Simulation(const string &configFilePath)
    :isRunning(true){

    std::ifstream file(configFilePath); //לפתוח את הקובץ שקיבלנו
    if (!file.is_open()) { //לבדוק שהוא פתיח
        throw std::runtime_error("Unable to open config file: " + configFilePath); //not sure if needed
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line[0]=="#") continue; //כדי להתעלם מהערות שהם הוסיפו

        std::istringstream ss(line); //אובייקט מיוחד שמאפשר לנו לחלץ מילה מילה מהשורה
        std::string type; //נאתחל משתנה שישמש לאחסון המילה שנחלץ בכל פעם מן השורה
        ss >> type; //שומר את המילה המחולצת כל פעם במשתנה TYPE

        if(type == "settlement"){
            std::string name;
            int SettlementType;
            ss >> name >> SettlementType;

        }


    }

