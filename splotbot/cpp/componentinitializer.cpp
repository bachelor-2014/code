#include <iostream>
#include <fstream>
#include "componentinitializer.h"
#include "singlesteppermotor.h"
#include "camera.h"
#include "libraries/cJSON/cJSON.h"

using namespace std;

/**
 * createSingleStepperMotor creates a single stepper motor from JSON
 */
Component* createSingleStepperMotor(cJSON * document) {
    //Get the name
    string name(cJSON_GetObjectItem(document, "name")->valuestring);

    //Get the parameters
    cJSON *parameters = cJSON_GetObjectItem(document, "parameters");
    string gpioMode1(cJSON_GetObjectItem(parameters, "gpio_mode1")->valuestring);
    string gpioMode2(cJSON_GetObjectItem(parameters, "gpio_mode2")->valuestring);
    string gpioStep(cJSON_GetObjectItem(parameters, "gpio_step")->valuestring);
    string gpioSleep(cJSON_GetObjectItem(parameters, "gpio_sleep")->valuestring);

    //Create the SingleStepperMotor
    return new SingleStepperMotor(name, gpioMode1, gpioMode2, gpioStep, gpioSleep);
}

/**
 * createCamera create a camera from JSON
 */
Component* createCamera(cJSON * document) {
    //Get the name
    string name(cJSON_GetObjectItem(document, "name")->valuestring);

    //Get the parameters
    cJSON *parameters = cJSON_GetObjectItem(document, "parameters");
    int videoDevice = cJSON_GetObjectItem(parameters, "video_device")->valueint;
    string eventName(cJSON_GetObjectItem(parameters, "event_name")->valuestring);

    //Create the camera
    return new Camera(name, videoDevice, eventName);
}

/**
 * getConfigDocument gets the JSON config document
 */
cJSON* getConfigDocument() {
    //Load config file
    ifstream in("../basic_config.json");
    string contents(
            (istreambuf_iterator<char>(in)), 
            istreambuf_iterator<char>()
    );

    //Parse the JSON
    return cJSON_Parse(contents.c_str());
}

/**
 * initilizeComponents initilizes the components from the config file
 */
vector<Component *> initializeComponents(function<void(string,string)> *callback) {
    //Load components
    vector<Component *> components;

    cJSON *document = getConfigDocument();

    //Run throught components
    for (int i = 0 ; i < cJSON_GetArraySize(document) ; i++) {
        cJSON *componentDocument = cJSON_GetArrayItem(document, i);
        string type(cJSON_GetObjectItem(componentDocument, "type")->valuestring);
        cout << i << ": " << type << endl;

        //Determine components
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
