'use strict';

angular.module('clientApp')
  .service('configService', function($http){
    this.getConfig = function(path){
        return $http.get(path).then(
          function(result){
            return result.data;
          });
    }
  });
