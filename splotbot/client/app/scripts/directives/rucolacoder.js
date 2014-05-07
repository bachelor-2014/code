'use strict';

// Directive definition for the 'Integercoder' type GUI control
angular.module('clientApp')
  .directive( "rucolacoder", function() {
    return {
      restrict: 'E',
      templateUrl: '/views/directives/rucolacoder.html'
    }
  });
