'use strict';

// Controller for the 'SingleStepperMotor' GUI control
angular.module('clientApp')
  .controller( "MotorCtrl", function($scope,splotService){

    $scope.currentOperation = "";

    // Initialize the element from the configuration
    $scope.init = function(elementInfo){
      $scope.elementInfo = elementInfo;
      console.log($scope.elementInfo.start_action);
    };

    // The action of moving the corresponding hardware motor
    // Send the instruction to the web server
    $scope.move = function(direction){
      console.log("moving "+direction);
      console.log($scope.elementInfo.start_action);

      splotService.postInput([$scope.elementInfo.start_action,direction]);
    };

  });
