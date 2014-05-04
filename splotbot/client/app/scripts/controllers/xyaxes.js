'use strict';

// Controller for the 'RCServoMotor' GUI control
angular.module('clientApp')
  .controller( "XYAxesCtrl", function($scope,splotService){

    $scope.movementAmount = 10;
    $scope.currentPosition = {
      x: 0,
      y: 0
    }
    $scope.newPosition = {
      x: 0,
      y: 0
    }

    // Initialize the element from the configuration
    $scope.init = function(elementInfo){
      $scope.elementInfo = elementInfo;
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

    // The action of moving the position of the axes by the given amounts
    // Sends the instruction to the web server
    $scope.moveBy = function(x, y) {
      $scope.currentPosition.x = parseInt($scope.currentPosition.x) + parseInt(x);
      $scope.currentPosition.y = parseInt($scope.currentPosition.y) + parseInt(y);

      splotService.postInput([$scope.elementInfo.start_action + 1, $scope.currentPosition.x, $scope.currentPosition.y]);
    };

    // The action of setting the position of the axes to the given position
    // Sends the instruction to the web server
    $scope.moveTo = function(x, y) {
      $scope.currentPosition.x = parseInt(x);
      $scope.currentPosition.y = parseInt(y);

      splotService.postInput([$scope.elementInfo.start_action + 1, $scope.currentPosition.x, $scope.currentPosition.y]);
    };
  });
