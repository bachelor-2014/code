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
      .when('/logs', {
        templateUrl: 'views/logs.html'
      })
      .when('/contact', {
        templateUrl: 'views/contact.html'
      })
      .otherwise({
        redirectTo: '/'
      });
  }).run(function($rootScope,$location){
	$rootScope.location = $location;
	$rootScope.john = "JOHN";
  });
