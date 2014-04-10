'use strict';

// Stepsize, x_start, y_start x_end, y_end
angular.module('clientApp')
  .directive('scanner', function () {
    return {
      restrict: 'E',
      scope: {
        elementInfo: '=info'
      },
      templateUrl: '/views/directives/scanner.html'
    };
  });
