'use strict';

// Controller for the 'RCServoMotor' GUI control
angular.module('clientApp')
  .controller( "RCServoMotorCtrl", function($scope,splotService){

    $scope.currentPosition = 0;

    $scope.currentOperation = "";

    // Initialize the element from the configuration
    $scope.init = function(elementInfo){
      $scope.elementInfo = elementInfo;
      console.log($scope.elementInfo.start_action);

      //Reset the position
      splotService.postInput([$scope.elementInfo.start_action,0]);
    };

    // The action of set the position of the hardware motor
    // Send the instruction to the web server
    $scope.setPosition = function(position) {
      $scope.currentPosition = position;
        
      $scope.currentPosition = $scope.currentPosition < 0 ? 0 : $scope.currentPosition;
      $scope.currentPosition = $scope.currentPosition > 90 ? 90 : $scope.currentPosition;

      console.log("Moving to " + $scope.currentPosition);

      splotService.postInput([$scope.elementInfo.start_action, $scope.currentPosition]);
    };

    // Move the motor the specified number of steps
    // Depends on the setPosition function
    $scope.move = function(direction) {
      $scope.setPosition($scope.currentPosition + direction);
    };

    // Input field key press event
    $scope.keyPressEvent = function(event) {
      if(event.keyCode == 13) {
        $scope.setPosition($scope.position);
      }
    };
  });
