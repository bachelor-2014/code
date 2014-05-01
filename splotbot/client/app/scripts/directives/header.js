'use strict';

// Directive definition for the 'ErrorDisplay' type GUI control
angular.module('clientApp')
  .directive("header", function() {
    return {
      restrict: 'E',
      templateUrl: '/views/directives/header.html'
    }
  });
