'use strict';

// Controller for the 'CameraCalibrator' GUI control
angular.module('clientApp')
  .controller( "CameraCalibratorCtrl", function($scope, splotService, socket){

    // Whether or not the camera is calibrated
    $scope.cameraCalibrated = false;

    // The event of the camera being calibrated
    socket.on($scope.elementInfo.name, function(data){
        $scope.cameraCalibrated = true;
    });

    // Initialize the element from the configuration
    $scope.init = function(elementInfo){
      $scope.elementInfo = elementInfo;
    };

    // Get the existing camera calibration, if it exists
    $scope.calibrate = function() {
      splotService.postInput([$scope.elementInfo.start_action]);
    }

    // Perform a new camera calibration
    $scope.recalibrate = function() {
      splotService.postInput([$scope.elementInfo.start_action + 1]);
    }
  });
