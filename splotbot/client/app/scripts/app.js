'use strict';

// Define the main app module
angular.module('clientApp', [
  'ngResource',
  'ngRoute'
])
  // Configure routing
  .config(function ($routeProvider) {
    $routeProvider
      .when('/', {
        templateUrl: 'views/main.html',
        controller: 'MainCtrl'
      })
      .otherwise({
        redirectTo: '/'
      });
  });
