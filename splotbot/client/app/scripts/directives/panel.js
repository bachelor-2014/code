'use strict';

// Directive definition for the 'Camera' type GUI control
angular.module('clientApp')
  .directive( "panel", function() {
    return {
      restrict: 'E',
      transclude: true,
      replace:true,
      templateUrl: '/views/directives/panel.html',
      link: function (scope, element, attrs) {
        scope.heading = attrs.heading;
        scope.show = false;

        scope.toggle = function(){
          if(scope.show)
            scope.show = false;
          else
            scope.show = true;
          scope.clicked = function(){
            console.log("FDSFSDF");
          }
        }
      }
    }

  })
