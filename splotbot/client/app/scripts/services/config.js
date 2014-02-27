'use strict';

angular.module('clientApp')
  .service('configService', function($http){
    this.getConfig = function(path){
        return $http.get(path).then(
          function(result){
            var data = result.data;

            var componentActions = {
              "SingleStepperMotor": 1,
              "Camera": 1
            }

            var actions = 0;

            for(var e in data){
              var numberOfActions = componentActions[data[e].type]

              data[e]["start_action"] = actions;

              actions += numberOfActions;

            };

            return data;

          });
    }
  });
