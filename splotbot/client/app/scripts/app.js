'use strict';

// Define the main app module
angular.module('clientApp', [
  'ngResource',
  'ngRoute',
  'ui.ace'
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
