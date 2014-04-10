'use strict';

angular.module('clientApp')
  .controller('ScannerCtrl', function ($scope) {

    $scope.init = function(elementInfo){
        $scope.elementInfo = elementInfo;
    };

  });
