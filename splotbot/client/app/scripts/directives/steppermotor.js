'use strict';

// Directive definition for the 'SingleStepperMotor' type GUI control
angular.module('clientApp')
  .directive( "singlesteppermotor", function() {
    return {
      restrict: 'E',

      scope: {
        elementInfo: '=info'
      },
      templateUrl: '/views/directives/steppermotor.html'
    }
  })
