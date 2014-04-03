'use strict';

// Controller for the 'RCServoMotor' GUI control
angular.module('clientApp')
  .controller( "XYAxesCtrl", function($scope,splotService){

    $scope.movementAmount = 10;
    $scope.currentPosition = {
      x: 0,
      y: 0
    }

    // Initialize the element from the configuration
    $scope.init = function(elementInfo){
      $scope.elementInfo = elementInfo;
      console.log($scope.elementInfo.start_action);

      //Reset the position
      splotService.postInput([$scope.elementInfo.start_action,0,0]);
    };

    // The action of set the position of the hardware motor
    // Send the instruction to the web server
    $scope.moveTo = function(x, y) {
      $scope.currentPosition.x += x;
      $scope.currentPosition.y += y;
      splotService.postInput([$scope.elementInfo.start_action, $scope.currentPosition.x, $scope.currentPosition.y]);
    };
  });
