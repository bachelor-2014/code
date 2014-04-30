'use strict';

// Controller for the 'Integercoder' type GUI control
angular.module('clientApp')
  .controller( "RucolaCoderCtrl", function($scope,$rootScope,$compile,socket,splotService) {
    $scope.sendRucolaCode = function(){
        var code = $scope.rucolacode;
        splotService.postRucola(code);
    };
  })
