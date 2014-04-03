'use strict';

// Directive definition for the 'XYAxes' type GUI control
angular.module('clientApp')
  .directive( "xyaxes", function() {
    return {
      restrict: 'E',

      scope: {
        elementInfo: '=info'
      },
      templateUrl: '/views/directives/xyaxes.html'
    }
  })
