'use strict';

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
