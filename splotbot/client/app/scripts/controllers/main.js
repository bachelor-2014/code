'use strict';

// Capitalize first letter in a string
function capitalize(word){
  return word.charAt(0).toUpperCase() + word.slice(1);
}

// Create a JS object from an entry in the configuration file
function extractInfo(config_entry){
  return {
    "html_name": config_entry.name.replace(" ","-").toLowerCase(),
    "js_name": config_entry.name.split(" ").map(capitalize).join(""),
    "type": config_entry.type,
    "name":config_entry.name,
    "parameters":config_entry.parameters,
    "start_action": config_entry.start_action
  }
}

// Add the GUI controls to the user interface based on the loaded elements
function addDirectiveElements(elements,$scope,$compile,$rootScope){

    $rootScope["elements"] = {}

    for (var e in elements){

      var ename = elements[e].type;

      $rootScope["element"+e] = {
        name: elements[e].name,
        type: elements[e].type,
        parameters: elements[e].parameters,
        start_action: elements[e].start_action
      };

      $("#splotcontrols").append($compile("<"+ename+" info=element"+e+" id="+elements[e].js_name+"></"+ename+">")($scope))

    }
}

// Add the main controller to the app and initialize it from the config file
angular.module('clientApp')
  .controller('MainCtrl', function ($scope, $compile, $rootScope,socket, configService) {
    configService.getConfig("basic_config.json").then( function(conf){
      var confElements = conf.map(extractInfo)
      addDirectiveElements(confElements, $scope,$compile,$rootScope);
    })
  })
