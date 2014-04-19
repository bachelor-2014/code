'use strict';

// Directive definition for the 'ErrorDisplay' type GUI control
angular.module('clientApp')
  .directive("errordisplay", function() {
    return {
      restrict: 'E',
      templateUrl: '/views/directives/errordisplay.html'
    }
  });
