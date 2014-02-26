#include <iostream>
#include <fstream>
#include "componentinitializer.h"
#include "singlesteppermotor.h"
#include "camera.h"
#include "libraries/cJSON/cJSON.h"

using namespace std;

Component* createSingleStepperMotor(cJSON * document) {
    string name(cJSON_GetObjectItem(document, "name")->valuestring);

    cJSON *parameters = cJSON_GetObjectItem(document, "parameters");
    string gpioMode1(cJSON_GetObjectItem(parameters, "gpio_mode1")->valuestring);
    string gpioMode2(cJSON_GetObjectItem(parameters, "gpio_mode2")->valuestring);
    string gpioStep(cJSON_GetObjectItem(parameters, "gpio_step")->valuestring);
    string gpioSleep(cJSON_GetObjectItem(parameters, "gpio_sleep")->valuestring);

    return new SingleStepperMotor(name, gpioMode1, gpioMode2, gpioStep, gpioSleep);
}

Component* createCamera(cJSON * document) {
    string name(cJSON_GetObjectItem(document, "name")->valuestring);

    cJSON *parameters = cJSON_GetObjectItem(document, "parameters");
    int videoDevice = cJSON_GetObjectItem(parameters, "video_device")->valueint;
    string eventName(cJSON_GetObjectItem(parameters, "event_name")->valuestring);

    return new Camera(name, videoDevice, eventName);
}

cJSON* getConfigDocument() {
    ifstream in("../basic_config.json");
    string contents(
            (istreambuf_iterator<char>(in)), 
            istreambuf_iterator<char>()
    );
    return cJSON_Parse(contents.c_str());
}

vector<Component *> initializeComponents(function<void(string,string)> *callback) {
    vector<Component *> components;

    cJSON *document = getConfigDocument();
    for (int i = 0 ; i < cJSON_GetArraySize(document) ; i++) {
        cJSON *componentDocument = cJSON_GetArrayItem(document, i);
        string type(cJSON_GetObjectItem(componentDocument, "type")->valuestring);
        cout << i << ": " << type << endl;

        if (type.compare("SingleStepperMotor") == 0) {
            Component *c = createSingleStepperMotor(componentDocument);
            (*c).registerCallback(callback);
            components.push_back(c);
        } else if (type.compare("Camera") == 0) {
            Component *c = createCamera(componentDocument);
            (*c).registerCallback(callback);
            components.push_back(c);
        } else {
            cout << "Unknown component found" << endl;
        }
    } 

    return components;
}
