'use strict';

// Controller for the 'Integercoder' type GUI control
angular.module('clientApp')
  .controller( "RucolaCoderCtrl", function($scope,$rootScope,$compile,socket,splotService) {
    $scope.output = "";

    $scope.sendRucolaCode = function(){
      var code = $scope.rucolacode;
      splotService.postRucola(code);
    };

    $scope.clearOutput = function() {
      $scope.output = "";
    };

    // The event of an incoming print statement
    socket.on("Rucola_print", function(data){
      $scope.output = data.data + "\n" + $scope.output;
    });
  })
