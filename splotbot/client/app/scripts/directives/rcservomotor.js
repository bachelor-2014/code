'use strict';

// Directive definition for the 'RCServoMotor' type GUI control
angular.module('clientApp')
  .directive( "rcservomotor", function() {
    return {
      restrict: 'E',

      scope: {
        elementInfo: '=info'
      },
      templateUrl: '/views/directives/rcservomotor.html'
    }
  })
