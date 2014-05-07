'use strict';

// Service defining a method for POSTing instructions to the web server
angular.module('clientApp')
  .service('splotService', function($http,configService){
	// The web server URL
	var url = configService.host+":8000/";
	//var url = "http://192.168.133.132:8000/";

	// Post the given data (instructions) to the web server
	this.postInput = function(data){
		return $http.post(url+"runcode",data);
	}

	this.postRucola = function(code){
		var data = {
		    code : code
		}
		return $http.post(url+"rucola",data);
	}

	this.getLogs = function(){
		return $http.get(url+"logs");
	}

	this.deleteLog = function(logname){
		return $http.delete(url+"logs/"+logname);
	}

	this.URL = url;
});
