'use strict';

// Controller for the 'Camera' type GUI control
angular.module('clientApp')
  .controller( "CanvasCtrl", function($scope,$rootScope,$compile,socket,splotService) {


    // The image to draw
    $scope.img = new Image();

    // Initializer
    // Add the canvas to the GUI control
    $scope.init = function(elementInfo){
      $scope.elementInfo = elementInfo;

      $scope.$on("broadcasted", function(event,element) {
        //addCanvas($("#"+$scope.elementInfo.name));
        $scope.$apply(function(){
          setupCanvas()
        })
      });


      socket.on($scope.elementInfo.name + "_dropletspeed", function(data){
        $scope.dropletspeed = data.data;
      });
    }

    //Set the camera mode
    $scope.mode = function(mode){
          splotService.postInput([$scope.elementInfo.start_action,mode]);
    };

    // Initialize the canvas and context, including event listeners
    function setupCanvas (){

      // Initialize the canvas
      var cId = $scope.elementInfo.name+"_canvas";
      $scope.canvas = document.getElementById(cId);
      $scope.context = $scope.canvas.getContext("2d");

      // On load, draw the image on the canvas
      $scope.img.onload = function(){
        $scope.context.drawImage(this,0,0,canvas.width, canvas.height);
      };

      // Get the position of the canvas
      $scope.canvasPosition = {
          x: $scope.context.canvas.offsetLeft,
          y: $scope.context.canvas.offsetTop
        };

      // Add an on-click event to the canvas, logging the location
      // of the mouse click in the console
      $scope.canvas.addEventListener("click",function(e){
        var canvas = $scope.context.canvas
        var rect = canvas.getBoundingClientRect();
        var x = e.clientX - rect.left;
        var y = e.clientY - rect.top;

          //var scale_x = $scope.img.width / $scope.context.canvas.clientWidth;
          //var scale_y = $scope.img.height / $scope.context.canvas.clientHeight;

          //var click_x = e.pageX-$scope.canvasPosition.x;
          //var click_y = e.pageY-$scope.canvasPosition.y;
          //var click = getCursorPosition(e,$scope.context.canvas);

          //var x = Math.floor(click.x * scale_x);
          //var y = Math.floor(click.y * scale_y);

        console.log("x,y",x,y)
        splotService.postInput([$scope.elementInfo.start_action+1,x,y]);

      });

      // Add a socket connection for the camera event
      addSocket(cId,$scope.elementInfo.parameters.event_name);
    }

    // Adds an event handler to the socket, rendering the image
    // contained in the event data on the canvas
    function addSocket(canvasId,eventName){
      socket.on(eventName,function(data){
        renderImage(data.data,$scope.canvas,$scope.context,$scope);
      });

    }

    // Renders the given image data on the canvas
    function renderImage(data,canvas,context,$scope){
        var img_data = 'data:image/png;base64,'+data;
        $scope.img.src = img_data;
    }
  });

function getCursorPosition(e,canvas) {
    var x,y;

    if (e.pageX != undefined && e.pageY != undefined) {
      x = e.pageX;
      y = e.pageY;
    }
    else {
    x = e.clientX + document.body.scrollLeft +
            document.documentElement.scrollLeft;
    y = e.clientY + document.body.scrollTop +
            document.documentElement.scrollTop;
    }

    x -= canvas.offsetLeft;
    y -= canvas.offsetTop;

    return { x:x, y:y };
}
