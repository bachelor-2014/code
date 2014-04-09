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
    };

    // The action of homing
    // Sends the instruction to the web server
    $scope.home = function() {
      splotService.postInput([$scope.elementInfo.start_action]);
        $scope.currentPosition = {
          x: 0,
          y: 0
        }
    }

    // The action of set the position of the hardware motor
    // Send the instruction to the web server
    $scope.moveTo = function(x, y) {
      $scope.currentPosition.x = parseInt($scope.currentPosition.x) + parseInt(x);
      $scope.currentPosition.y = parseInt($scope.currentPosition.y) + parseInt(y);
      console.log("Sending:", $scope.currentPosition);
      splotService.postInput([$scope.elementInfo.start_action + 1, $scope.currentPosition.x, $scope.currentPosition.y]);
    };
  });
