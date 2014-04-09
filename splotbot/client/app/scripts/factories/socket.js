'use strict';

// Factory for the Socket.io connections to the web server
angular.module('clientApp')
  .factory('socket', function($rootScope,configService) {

      // Connect to the web server
      var socket = io.connect(configService.host+":8000");

      return {
        // Allow for registering events on incoming data
        on: function(eventName, callback) {
          socket.on(eventName, function() {
            var args = arguments;
            $rootScope.$apply(function() {
              callback.apply(socket, args);
            });
          });
        },
        // Allow for sending data through the socket
        emit: function(eventName, data, callback) {
          socket.emit(eventName, data, function() {
            var args = arguments;
            $rootScope.$apply(function() {
              if(callback) {
                callback.apply(socket, args);
              }
            });
          });
        }
      };
    })
