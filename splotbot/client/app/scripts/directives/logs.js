'use strict';

// Directive definition for the 'Camera' type GUI control
angular.module('clientApp')
  .directive( "logs", function() {
    return {
      restrict: 'E',
      templateUrl: '/views/directives/logs.html',
      controller: function($scope,splotService,$interval){

        $scope.getLogs = function(){
          splotService.getLogs().then(function(data){
            $scope.logs = data.data;
          });
        }

        $scope.getLogLink = function(logname){
          var url = splotService.URL + 'logs/' + logname;
          return url;
        };

        $scope.deleteLog = function(logname){
          splotService.deleteLog(logname).then(function(data){
            $scope.getLogs();
          });
        };

        $scope.clearAll = function(){
          for(var l in $scope.logs){
            $scope.deleteLog($scope.logs[l]);
          }
        }

        $interval(function(){
          console.log("Getting logs");
          $scope.getLogs();
        },15000);
        $scope.getLogs();
      }
    }
 })
