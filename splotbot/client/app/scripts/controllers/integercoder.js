'use strict';

// Controller for the 'Integercoder' type GUI control
angular.module('clientApp')
  .controller( "IntegerCoderCtrl", function($scope,$rootScope,$compile,socket,splotService) {
    $scope.sendIntegerCode = function(){
        var arr = $scope.integercode.split(" ");
        var arri = [];
        for(var i = 0; i<arr.length; i++){
            arri.push(parseInt(arr[i])); 
        }
        console.log(arri);
        splotService.postInput(arri);
    };
  })
