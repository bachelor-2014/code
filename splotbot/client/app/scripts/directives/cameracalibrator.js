'use strict';

// Directive definition for the 'CameraCalibrator' type GUI control
angular.module('clientApp')
  .directive( "cameracalibrator", function() {
    return {
      restrict: 'E',

      scope: {
        elementInfo: '=info'
      },
      templateUrl: '/views/directives/cameracalibrator.html'
    }
  })
