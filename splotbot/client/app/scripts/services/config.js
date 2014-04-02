'use strict';

// App configuration
// Defines the loading of the config file
angular.module('clientApp')
  .service('configService', function($http){
    this.host = "http://130.226.133.54";
    // Load the config file
    this.getConfig = function(path){
        return $http.get(path).then(
          function(result){
            var data = result.data;

            // Fixed number of actions for each component type
            var componentActions = {
              "SingleStepperMotor": 1,
              "RCServoMotor": 1,
              "Camera": 1
            }

            var actions = 0;

            // Iterate through the elements in the config file, storing
            // the integer instructions defining the actions of each component
            for(var e in data){
              var numberOfActions = componentActions[data[e].type]

              data[e]["start_action"] = actions;

              actions += numberOfActions;

            };

            return data;

          });
    }
  });
