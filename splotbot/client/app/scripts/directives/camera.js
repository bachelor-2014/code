'use strict';

// Directive definition for the 'Camera' type GUI control
angular.module('clientApp')
  .directive( "camera", function($timeout) {
    return {
      restrict: 'E',
      scope: {
        elementInfo: '=info'
      },
      templateUrl: '/views/directives/camera.html',
      link: function(scope,element,attrs){
        $timeout(function(){
          scope.$broadcast("broadcasted",{});
        },500)
      }
    }
  })
