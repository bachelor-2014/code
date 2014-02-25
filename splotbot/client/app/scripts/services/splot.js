'use strict';

angular.module('clientApp')
  .service('splotService', function($http){
    var url = "http://localhost:8000/";
    this.postInput = function(data){
        return $http.post(url+"input",data);
    }
  });
