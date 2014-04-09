'use strict';

// Controller for the 'Camera' type GUI control
angular.module('clientApp')
  .controller( "CanvasCtrl", function($scope,$rootScope,$compile,socket,splotService) {

    // The canvas and contexts for drawing the image
    var canvas,
        context;

    // The image to draw
    var img = new Image();

    // Initializer
    // Add the canvas to the GUI control
    $scope.init = function(elementInfo){
      $scope.elementInfo = elementInfo;
      addCanvas($("#"+elementInfo.name));
    }

    //Set the camera mode
    $scope.mode = function(mode){
          splotService.postInput([$scope.elementInfo.start_action,mode]);
    };

    // Initialize the canvas and context, including event listeners
    function setupCanvas (){

      // Initialize the canvas
      var cId = $scope.elementInfo.name+"_canvas";
      canvas = document.getElementById(cId);
      context = canvas.getContext("2d");

      // On load, draw the image on the canvas
      img.onload = function(){
        context.drawImage(this,0,0,canvas.width, canvas.height);
      };

      // Get the position of the canvas
      var canvasPosition = {
          x: canvas.offsetLeft,
          y: canvas.offsetTop
      };

      // Add an on-click event to the canvas, logging the location
      // of the mouse click in the console
      canvas.addEventListener("click",function(e){
        console.log("Click on canvas",
          $scope.elementInfo.name,
          "on(",e.pageX-canvasPosition.x,",",
          e.pageY-canvasPosition.y,")");

          var scale_x = img.width / context.canvas.clientWidth;
          var scale_y = img.height / context.canvas.clientHeight;

          var click_x = e.pageX-canvasPosition.x;
          var click_y = e.pageY-canvasPosition.y;

          var x = Math.floor(click_x * scale_x);
          var y = Math.floor(click_y * scale_y);

          splotService.postInput([$scope.elementInfo.start_action+1,x,y]);


      });

      // Add a socket connection for the camera event
      addSocket(cId,$scope.elementInfo.parameters.event_name);
    }

    // Adds a canvas to the GUI control initialized form the given config element
    function addCanvas(element){

      element.append($compile(""+
        "<canvas id='"+$scope.elementInfo.name+"_canvas' width='320'"+
        " height='240'></canvas>")($scope))

      setupCanvas();
    }

    // Adds an event handler to the socket, rendering the image
    // contained in the event data on the canvas
    function addSocket(canvasId,eventName){
      socket.on(eventName,function(data){
        renderImage(data.data,canvas,context,$scope);
      })
    }

    // Renders the given image data on the canvas
    function renderImage(data,canvas,context,$scope){
        var img_data = 'data:image/png;base64,'+data;
        img.src = img_data;
    }
  })
