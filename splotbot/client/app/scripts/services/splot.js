'use strict';

// Service defining a method for POSTing instructions to the web server
angular.module('clientApp')
  .service('splotService', function($http){
    // The web server URL
    var url = "http://localhost:8000/";
    //var url = "http://192.168.133.132:8000/";

    // Post the given data (instructions) to the web server
    this.postInput = function(data){
        return $http.post(url+"runcode",data);
    }
  });
