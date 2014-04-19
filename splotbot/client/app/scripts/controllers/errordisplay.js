'use strict';

// Controller for the 'ErrorDisplay' type GUI control
angular.module('clientApp')
  .controller( "ErrorDisplayCtrl", function($scope,$rootScope,$compile,socket) {

    $scope.errorMessage = "";

    // The event of an incoming error
    socket.on("error", function(data){
        $scope.errorMessage = data.data;
    });
  })
