'use strict';
angular.module('clientApp')
  .directive( "camera", function() {
    return {
      restrict: 'E',
      scope: {
        elementInfo: '=info'
      },
      templateUrl: '/views/directives/camera.html'
    }
  })
