'use strict';
angular.module('clientApp')
  .controller( "CanvasCtrl", function($scope,$rootScope,$compile,socket,splotService) {

    var canvas,
        context;

    var img = new Image();

    $scope.init = function(elementInfo){
      $scope.elementInfo = elementInfo;

      //$scope.setupCanvas(elementInfo);
      addCanvas($("#"+elementInfo.name));
    }

    function setupCanvas (){
      var cId = $scope.elementInfo.name+"_canvas";
      canvas = document.getElementById(cId);
      context = canvas.getContext("2d");
      img.onload = function(){
        context.drawImage(this,0,0,canvas.width, canvas.height);
      };

      var canvasPosition = {
          x: canvas.offsetLeft,
          y: canvas.offsetTop
      };

      canvas.addEventListener("click",function(e){
        console.log("Click on canvas",
          $scope.elementInfo.name,
          "on(",e.pageX-canvasPosition.x,",",
          e.pageY-canvasPosition.y,")");

          splotService.postInput({
            type:"click",
            element:$scope.elementInfo.name,
            xCoord: e.pageX-canvasPosition.x,
            yCoord: e.pageY-canvasPosition.y
          });

      });

      addSocket(cId,$scope.elementInfo.parameters.event_name);
    }

    function addCanvas(element){
      console.log($scope.elementInfo);
      element.append($compile(""+
        "<canvas id='"+$scope.elementInfo.name+"_canvas' width='800'"+
        " height='640'></canvas>")($scope))
      setupCanvas();
    }


    function addSocket(canvasId,eventName){
      socket.on(eventName,function(data){
        renderImage(data.image_data,canvas,context,$scope);
      })
    }

    function renderImage(data,canvas,context,$scope){
        var img_data = 'data:image/png;base64,'+data;
        img.src = img_data;
    }
  })
