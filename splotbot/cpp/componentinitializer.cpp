#include <iostream>
#include <fstream>
#include "componentinitializer.h"
#include "singlesteppermotor.h"
#include "xyaxes.h"
#include "rcservomotor.h"
#include "camera.h"
#include "scanner.h"
#include "cameracalibrator.h"
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
 * createRCServoMotor creates a RC servo motor from JSON
 */
Component* createRCServoMotor(cJSON * document) {
    //Get the name
    string name(cJSON_GetObjectItem(document, "name")->valuestring);

    //Get the parameters
    cJSON *parameters = cJSON_GetObjectItem(document, "parameters");
    string device(cJSON_GetObjectItem(parameters, "device")->valuestring);
    int channel(cJSON_GetObjectItem(parameters, "channel")->valueint);

    //Create the RC servo motor 
    return new RCServoMotor(name, device, (unsigned char) channel);
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
 * createXYAxis creates a XYAxis from JSON
 */
Component* createXYAxes(cJSON * document,string mendelSocket) {
    //Get the name
    string name(cJSON_GetObjectItem(document, "name")->valuestring);

    //Get the parameters
    cJSON *parameters = cJSON_GetObjectItem(document, "parameters");
    string xPort(cJSON_GetObjectItem(parameters, "x_port")->valuestring);
    string yPort(cJSON_GetObjectItem(parameters, "y_port")->valuestring);
    string xLimitSwitchPort(cJSON_GetObjectItem(parameters, "x_limit_switch_port")->valuestring);
    string yLimitSwitchPort(cJSON_GetObjectItem(parameters, "y_limit_switch_port")->valuestring);

    int xStepLimit = cJSON_GetObjectItem(parameters, "x_step_limit")->valueint;
    int yStepLimit = cJSON_GetObjectItem(parameters, "y_step_limit")->valueint;

    //Create the xyaxis
    return new XYAxes(name,xPort,yPort, xLimitSwitchPort, yLimitSwitchPort, xStepLimit,yStepLimit, mendelSocket);
}

/**
 * creatScanner creates a Scanner from JSON
 */
Component* createScanner(cJSON * document, vector<Component *> components) {
    //Get the name
    string name(cJSON_GetObjectItem(document, "name")->valuestring);

    //Get the parameters
    cJSON *parameters = cJSON_GetObjectItem(document, "parameters");
    string cameraName(cJSON_GetObjectItem(parameters, "camera_name")->valuestring);
    string xyaxesName(cJSON_GetObjectItem(parameters, "xyaxes_name")->valuestring);

    //Get the referenced components by their name
    Camera *camera;
    XYAxes *xyaxes;

    for (auto it = components.begin(); it != components.end(); ++it) {
        if (cameraName.compare((*it)->name) == 0) {
            camera = (Camera *) (*it);
        }
        if (xyaxesName.compare((*it)->name) == 0) {
            xyaxes = (XYAxes *) (*it);
        }
    }

    //Create the scanner 
    return new Scanner(name, camera, xyaxes);
}

/**
 * createCameraCalibrator creates a CameraCalibrator from JSON
 */
Component* createCameraCalibrator(cJSON * document, vector<Component *> components) {
    //Get the name
    string name(cJSON_GetObjectItem(document, "name")->valuestring);

    //Get the parameters
    cJSON *parameters = cJSON_GetObjectItem(document, "parameters");
    string xyaxesName = getStringParam(parameters, "xyaxes_name");
    string cameraName = getStringParam(parameters, "camera_name");
    string configFile = getStringParam(parameters, "config_file");

    //Get the referenced components based on their name
    Camera *camera;
    XYAxes *xyaxes;

    for (auto it = components.begin(); it != components.end(); ++it) {
        if (cameraName.compare((*it)->name) == 0) {
            camera = (Camera *) (*it);
        }
        if (xyaxesName.compare((*it)->name) == 0) {
            xyaxes = (XYAxes *) (*it);
        }
    }

    if(camera == NULL){
        cerr << "Camera component not found for calibrator" << endl;
        exit(1);
    }

    if(xyaxes == NULL){
        cerr << "XYAxes component not found for calibrator" << endl;
        exit(1);
    }

    return new CameraCalibrator(name,camera,xyaxes);
}

/**
 * getConfigDocument gets the JSON config document
 */
cJSON* getConfigDocument(string configFilename) {
    //Load config file
    ifstream in(configFilename);
    string contents(
            (istreambuf_iterator<char>(in)), 
            istreambuf_iterator<char>()
    );

    //Parse the JSON
    return cJSON_Parse(contents.c_str());
}

/**
 * Extract a string value corresponding to key in 
 * the parameters in the config
 */
string getStringParam(cJSON *parameters,string key){
    return cJSON_GetObjectItem(parameters, key.c_str())->valuestring;
}


/**
 * initilizeComponents initilizes the components from the config file
 */
vector<Component *> initializeComponents(function<void(string,string)> *callback, string configFilename, string mendelSocket) {
    //Load components
    vector<Component *> components;

    cJSON *document = getConfigDocument(configFilename);

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
        } else if (type.compare("RCServoMotor") == 0) {
            Component *c = createRCServoMotor(componentDocument);
            (*c).registerCallback(callback);
            components.push_back(c);
        } else if (type.compare("Camera") == 0) {
            Component *c = createCamera(componentDocument);
            (*c).registerCallback(callback);
            components.push_back(c);
        } else if (type.compare("XYAxes") == 0) {
            Component *c = createXYAxes(componentDocument,mendelSocket);
            (*c).registerCallback(callback);
            components.push_back(c);
        } else if (type.compare("Scanner") == 0) {
            Component *c = createScanner(componentDocument, components);
            (*c).registerCallback(callback);
            components.push_back(c);
        } else {
            cout << "Unknown component " << type << "found" << endl;
        }
    } 

    return components;
}
