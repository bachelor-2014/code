'use strict';

angular.module('clientApp')
  .controller('ScannerCtrl', function ($scope,splotService, socket) {
    $scope.scanner = {};
    $scope.scanner.algorithm = 0;

    $scope.init = function(elementInfo){
        $scope.elementInfo = elementInfo;
        
        socket.on($scope.elementInfo.name, function(data){
            $scope.scannedimg = 'data:image/png;base64,'+data.data;
        });
    };


    $scope.scannersubmit = function(){
        console.log($scope.scanner);
        var instr = [
            $scope.elementInfo.start_action,
            $scope.scanner.stepsize,
            $scope.scanner.sleep,
            $scope.scanner.start.x,
            $scope.scanner.start.y,
            $scope.scanner.stop.x,
            $scope.scanner.stop.y,
            $scope.scanner.algorithm
        ];

        console.log(instr);
        splotService.postInput(instr);
    };
  });
