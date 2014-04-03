'use strict';

// Directive definition for the 'Integercoder' type GUI control
angular.module('clientApp')
  .directive( "integercoder", function() {
    return {
      restrict: 'E',
      templateUrl: '/views/directives/integercoder.html'
    }
  });
