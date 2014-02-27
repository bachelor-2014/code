'use strict';

angular.module('clientApp')
  .controller( "MotorCtrl", function($scope,splotService){

    $scope.currentOperation = "";

    $scope.init = function(elementInfo){
      $scope.elementInfo = elementInfo;
      console.log($scope.elementInfo.start_action);
    };

    $scope.move = function(direction){
      console.log("moving "+direction);
      console.log($scope.elementInfo.start_action);

      splotService.postInput([$scope.elementInfo.start_action,direction]);
    };

  });
