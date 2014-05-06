'use strict';

// Controller for the 'ErrorDisplay' type GUI control
angular.module('clientApp')
  .controller( "ErrorDisplayCtrl", function($scope,$rootScope,$compile,socket) {

    // The event of an incoming error
    socket.on("error", function(data){
        var element = $('#error-message-container');

        element.append($compile(
            '<div class="alert alert-danger alert-dismissable">' + 
              '<button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>' +
              data.data + 
            '</div>'
            )($scope));
    });
  })
