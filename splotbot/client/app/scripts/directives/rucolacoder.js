'use strict';

// Directive definition for the 'Integercoder' type GUI control
angular.module('clientApp')
  .directive( "rucolacoder", function(socket,splotService) {
    return {
      restrict: 'E',
      templateUrl: '/views/directives/rucolacoder.html',
      link: function(scope, element, attributes) {
        scope.output = "";
        scope.rucolacode = "";

        scope.sendRucolaCode = function(){
          var code = scope.rucolacode;
          splotService.postRucola(code);
        };

        scope.sendRucolaClear = function(){
            splotService.postRucola("");
        };

        scope.clearOutput = function() {
          scope.output = "";
        };

        // The event of an incoming print statement
        socket.on("Rucola_print", function(data){
          scope.output = data.data + "\n" + scope.output;
        });
      }
    }
  });
