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
      $scope.currentOperation = "move_"+direction
      splotService.postInput({type:"move",element:"camera1",direction:direction});
    };

  });
